/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "form_render_mgr.h"

#include <mutex>

#include "fms_log_wrapper.h"
#include "form_ams_helper.h"
#include "form_bms_helper.h"
#include "form_cache_mgr.h"
#include "form_constants.h"
#include "form_data_mgr.h"
#include "form_event_report.h"
#include "form_host_interface.h"
#include "form_mgr_errors.h"
#include "form_sandbox_render_mgr_inner.h"
#include "form_supply_callback.h"
#include "form_task_mgr.h"
#include "form_trust_mgr.h"
#include "form_util.h"
#include "ipc_skeleton.h"
#include "os_account_manager.h"
#include "want.h"

namespace OHOS {
namespace AppExecFwk {
namespace {
    constexpr size_t LAST_CONNECTION = 1;
}
using Want = OHOS::AAFwk::Want;
FormRenderMgr::FormRenderMgr()
{
}
FormRenderMgr::~FormRenderMgr()
{
}

void FormRenderMgr::GetFormRenderState()
{
    // Check whether the account is authenticated.
    bool isVerified = false;
    AccountSA::OsAccountManager::IsOsAccountVerified(FormUtil::GetCurrentAccountId(), isVerified);
    HILOG_INFO("isVerified:%{public}d, isVerified_:%{public}d, screen:%{public}d",
        isVerified, isVerified_, isScreenUnlocked_);

    std::lock_guard<std::mutex> lock(isVerifiedMutex_);
    if (isVerified_ == isVerified) {
        return;
    }

    isVerified_ = isVerified;
    if (!isVerified) {
        return;
    }
    if (!isScreenUnlocked_) {
        PostOnUnlockTask();
    }
    ExecAcquireProviderTask();
}

bool FormRenderMgr::GetIsVerified() const
{
    HILOG_DEBUG("GetIsVerified");
    std::lock_guard<std::mutex> lock(isVerifiedMutex_);
    return isVerified_;
}

ErrCode FormRenderMgr::RenderForm(
    const FormRecord &formRecord, const WantParams &wantParams, const sptr<IRemoteObject> &hostToken)
{
    HILOG_INFO("formId:%{public}" PRId64, formRecord.formId);
    GetFormRenderState();
    HILOG_INFO("the current user authentication status:%{public}d,%{public}d", isVerified_, isScreenUnlocked_);
    if (formRecord.uiSyntax != FormType::ETS) {
        return ERR_OK;
    }
    if (formRecord.formId <= 0) {
        HILOG_ERROR("formId not greater than 0");
        return ERR_APPEXECFWK_FORM_INVALID_PARAM;
    }

    int32_t userId = FormUtil::GetCurrentAccountId();
    Want want;
    want.SetParams(wantParams);
    want.SetParam(Constants::FORM_SUPPLY_UID, std::to_string(userId) + formRecord.bundleName);
    {
        std::lock_guard<std::mutex> lock(isVerifiedMutex_);
        want.SetParam(Constants::FORM_RENDER_STATE, isVerified_ || isScreenUnlocked_);
    }
    if (formRecord.privacyLevel > 0) {
        InitRenderInner(true);
        return sandboxInner_->RenderForm(formRecord, want, hostToken);
    } else {
        InitRenderInner(false);
        return renderInner_->RenderForm(formRecord, want, hostToken);
    }
}

ErrCode FormRenderMgr::UpdateRenderingForm(int64_t formId, const FormProviderData &formProviderData,
    const WantParams &wantParams, bool mergeData)
{
    HILOG_INFO("update formId:%{public}" PRId64 ",%{public}zu", formId, formProviderData.GetDataString().length());

    FormRecord formRecord;
    bool isGetFormRecord = FormDataMgr::GetInstance().GetFormRecord(formId, formRecord);
    if (!isGetFormRecord) {
        HILOG_ERROR("get FormRecord fail, not exist such form, formId:%{public}" PRId64 "", formId);
        return ERR_APPEXECFWK_FORM_NOT_EXIST_ID;
    }
    if (formRecord.privacyLevel > 0) {
        if (sandboxInner_ == nullptr) {
            return ERR_APPEXECFWK_FORM_INVALID_PARAM;
        }
        return sandboxInner_->UpdateRenderingForm(formRecord, formProviderData, wantParams, mergeData);
    } else {
        if (renderInner_ == nullptr) {
            return ERR_APPEXECFWK_FORM_INVALID_PARAM;
        }
        return renderInner_->UpdateRenderingForm(formRecord, formProviderData, wantParams, mergeData);
    }
}

ErrCode FormRenderMgr::ReloadForm(
    const std::vector<FormRecord> &&formRecords, const std::string &bundleName, int32_t userId)
{
    HILOG_DEBUG("call");
    std::vector<FormRecord> sandboxRecords;
    std::vector<FormRecord> normalRecords;
    for (const auto &record : formRecords) {
        if (record.privacyLevel > 0) {
            sandboxRecords.emplace_back(record);
        } else {
            normalRecords.emplace_back(record);
        }
    }
    if (!normalRecords.empty() && renderInner_ != nullptr) {
        renderInner_->ReloadForm(std::move(normalRecords), bundleName, userId);
    }
    if (!sandboxRecords.empty() && sandboxInner_ != nullptr) {
        sandboxInner_->ReloadForm(std::move(sandboxRecords), bundleName, userId);
    }
    return ERR_OK;
}

void FormRenderMgr::PostOnUnlockTask()
{
    if (renderInner_ != nullptr) {
        renderInner_->PostOnUnlockTask();
    }
    if (sandboxInner_ != nullptr) {
        sandboxInner_->PostOnUnlockTask();
    }
}

void FormRenderMgr::AddAcquireProviderFormInfoTask(std::function<void()> task)
{
    HILOG_DEBUG("call");
    std::lock_guard<std::mutex> lock(taskQueueMutex_);
    taskQueue_.push(task);
}

void FormRenderMgr::ExecAcquireProviderTask()
{
    HILOG_INFO("start");
    // start to execute asynchronous tasks in the queue
    std::lock_guard<std::mutex> lock(taskQueueMutex_);
    while (!taskQueue_.empty()) {
        auto task = taskQueue_.front();
        task();
        taskQueue_.pop();
    }
}

void FormRenderMgr::NotifyScreenOn()
{
    if (renderInner_ != nullptr) {
        renderInner_->NotifyScreenOn();
    }
    if (sandboxInner_ != nullptr) {
        sandboxInner_->NotifyScreenOn();
    }
}

void FormRenderMgr::OnScreenUnlock()
{
    HILOG_INFO("call. %{public}d,%{public}d", isVerified_, isScreenUnlocked_);
    if (isScreenUnlocked_) {
        return;
    }
    
    // el2 path maybe not unlocked, should not acquire data
    std::lock_guard<std::mutex> lock(isVerifiedMutex_);
    isScreenUnlocked_ = true;
    if (!isVerified_) {
        PostOnUnlockTask();
    }
}

void FormRenderMgr::OnUnlock()
{
    HILOG_INFO("call. %{public}d,%{public}d", isVerified_, isScreenUnlocked_);
    if (isVerified_) {
        return;
    }
    
    {
        std::lock_guard<std::mutex> lock(isVerifiedMutex_);
        isVerified_ = true;
        if (!isScreenUnlocked_) {
            PostOnUnlockTask();
        }
    }
    ExecAcquireProviderTask();
}

ErrCode FormRenderMgr::StopRenderingForm(
    int64_t formId, const FormRecord &formRecord, const std::string &compId, const sptr<IRemoteObject> &hostToken)
{
    HILOG_DEBUG("call");
    if (formRecord.privacyLevel > 0) {
        if (sandboxInner_ == nullptr) {
            return ERR_APPEXECFWK_FORM_INVALID_PARAM;
        }
        return sandboxInner_->StopRenderingForm(formId, formRecord, compId, hostToken);
    } else {
        if (renderInner_ == nullptr) {
            return ERR_APPEXECFWK_FORM_INVALID_PARAM;
        }
        return renderInner_->StopRenderingForm(formId, formRecord, compId, hostToken);
    }
}

ErrCode FormRenderMgr::RenderFormCallback(int64_t formId, const Want &want)
{
    HILOG_DEBUG("call");
    return ERR_OK;
}

ErrCode FormRenderMgr::StopRenderingFormCallback(int64_t formId, const Want &want)
{
    HILOG_INFO("call");
    if (renderInner_ != nullptr) {
        renderInner_->StopRenderingFormCallback(formId, want);
    }
    if (sandboxInner_ != nullptr) {
        sandboxInner_->StopRenderingFormCallback(formId, want);
    }
    return ERR_OK;
}

ErrCode FormRenderMgr::ReleaseRenderer(int64_t formId, const FormRecord &formRecord, const std::string &compId)
{
    HILOG_DEBUG("call");
    if (formRecord.privacyLevel > 0) {
        if (sandboxInner_ == nullptr) {
            return ERR_APPEXECFWK_FORM_INVALID_PARAM;
        }
        return sandboxInner_->ReleaseRenderer(formId, formRecord, compId);
    } else {
        if (renderInner_ == nullptr) {
            return ERR_APPEXECFWK_FORM_INVALID_PARAM;
        }
        return renderInner_->ReleaseRenderer(formId, formRecord, compId);
    }
}

ErrCode FormRenderMgr::AddConnection(
    int64_t formId, sptr<FormRenderConnection> connection, int32_t privacyLevel)
{
    HILOG_INFO("call");
    if (privacyLevel > 0) {
        if (sandboxInner_ == nullptr) {
            return ERR_APPEXECFWK_FORM_INVALID_PARAM;
        }
        return sandboxInner_->AddConnection(formId, connection);
    } else {
        if (renderInner_ == nullptr) {
            return ERR_APPEXECFWK_FORM_INVALID_PARAM;
        }
        return renderInner_->AddConnection(formId, connection);
    }
}

void FormRenderMgr::RemoveConnection(int64_t formId, int32_t privacyLevel)
{
    HILOG_INFO("Call");
    if (privacyLevel > 0) {
        if (sandboxInner_ == nullptr) {
            return;
        }
        sandboxInner_->RemoveConnection(formId);
    } else {
        if (renderInner_ == nullptr) {
            return;
        }
        renderInner_->RemoveConnection(formId);
    }
}

void FormRenderMgr::CleanFormHost(const sptr<IRemoteObject> &host)
{
    if (renderInner_ != nullptr) {
        renderInner_->CleanFormHost(host);
    }
    if (sandboxInner_ != nullptr) {
        sandboxInner_->CleanFormHost(host);
    }
}

void FormRenderMgr::AddRenderDeathRecipient(const sptr<IRemoteObject> &remoteObject, int32_t privacyLevel)
{
    if (privacyLevel > 0) {
        if (sandboxInner_ == nullptr) {
            return;
        }
        sandboxInner_->AddRenderDeathRecipient(remoteObject);
    } else {
        if (renderInner_ == nullptr) {
            return;
        }
        renderInner_->AddRenderDeathRecipient(remoteObject);
    }
}

void FormRenderMgr::OnRenderingBlock(const std::string &bundleName)
{
    HILOG_INFO("bundleName:%{public}s", bundleName.c_str());
    FormEventInfo eventInfo;
    eventInfo.bundleName = bundleName;
    FormEventReport::SendSecondFormEvent(
        FormEventName::FORM_RENDER_BLOCK, HiSysEventType::FAULT, eventInfo);

    FormTrustMgr::GetInstance().MarkTrustFlag(bundleName, false);

    Want want;
    want.SetElementName(Constants::FRS_BUNDLE_NAME, "ServiceExtension");
    want.AddFlags(Want::FLAG_ABILITY_FORM_ENABLED);
    FormAmsHelper::GetInstance().StopExtensionAbility(want);
}

bool FormRenderMgr::IsNeedRender(int64_t formId)
{
    FormRecord formRecord;
    bool isGetFormRecord = FormDataMgr::GetInstance().GetFormRecord(formId, formRecord);
    if (!isGetFormRecord) {
        HILOG_ERROR("not exist such form, formId:%{public}" PRId64 "", formId);
        return false;
    }
    if (formRecord.uiSyntax != FormType::ETS) {
        HILOG_DEBUG("no need render, formId:%{public}" PRId64 "", formId);
        return false;
    }
    return true;
}

void FormRenderMgr::HandleConnectFailed(int64_t formId, int32_t errorCode) const
{
    HILOG_ERROR("Connect render service failed, formId:%{public}" PRId64 ", errorCode:%{public}d",
        formId, errorCode);
    std::vector<sptr<IRemoteObject>> formHostObjs;
    FormDataMgr::GetInstance().GetFormHostRemoteObj(formId, formHostObjs);
    for (const auto &host : formHostObjs) {
        auto hostClient = iface_cast<IFormHost>(host);
        if (hostClient == nullptr) {
            HILOG_ERROR("null hostClient");
            continue;
        }
        hostClient->OnError(errorCode, "Connect FormRenderService failed");
    }
}

bool FormRenderMgr::IsRerenderForRenderServiceDied(int64_t formId)
{
    int32_t rerenderCount = 0;
    int32_t reSandboxRenderCount = 0;
    if (renderInner_ != nullptr) {
        rerenderCount = renderInner_->GetReRenderCount();
    }
    if (sandboxInner_ != nullptr) {
        reSandboxRenderCount = sandboxInner_->GetReRenderCount();
    }
    bool ret = IsNeedRender(formId) && (rerenderCount > 0 || reSandboxRenderCount > 0);
    HILOG_DEBUG("Is need to rerender:%{public}d", ret);
    return ret;
}

void FormRenderMgr::InitRenderInner(bool isSandbox)
{
    std::lock_guard<std::mutex> lock(renderInnerMutex_);
    if (isSandbox) {
        if (sandboxInner_ == nullptr) {
            sandboxInner_ = std::make_shared<FormSandboxRenderMgrInner>();
        }
    } else {
        if (renderInner_ == nullptr) {
            renderInner_ = std::make_shared<FormRenderMgrInner>();
        }
    }
}

ErrCode FormRenderMgr::RecycleForms(
    const std::vector<int64_t> &formIds, const Want &want, const sptr<IRemoteObject> &remoteObjectOfHost)
{
    if (renderInner_ != nullptr) {
        return renderInner_->RecycleForms(formIds, want, remoteObjectOfHost);
    }
    if (sandboxInner_ != nullptr) {
        return sandboxInner_->RecycleForms(formIds, want, remoteObjectOfHost);
    }
    return ERR_APPEXECFWK_FORM_RENDER_SERVICE_DIED;
}

ErrCode FormRenderMgr::RecoverForms(const std::vector<int64_t> &formIds, const WantParams &wantParams)
{
    if (renderInner_ != nullptr) {
        return renderInner_->RecoverForms(formIds, wantParams);
    }
    if (sandboxInner_ != nullptr) {
        return sandboxInner_->RecoverForms(formIds, wantParams);
    }
    return ERR_APPEXECFWK_FORM_RENDER_SERVICE_DIED;
}
} // namespace AppExecFwk
} // namespace OHOS
