/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "form_render_service_mgr.h"

#include <cstddef>
#include <memory>

#include "event_handler.h"
#include "fms_log_wrapper.h"
#include "form_constants.h"
#include "form_render_event_report.h"
#include "form_render_service_extension.h"
#include "js_runtime.h"
#include "service_extension.h"
#include "form_memmgr_client.h"
#ifdef SUPPORT_POWER
#include "power_mgr_client.h"
#endif
#include "status_mgr_center/form_render_status_task_mgr.h"
#include "status_mgr_center/form_render_status_mgr.h"

namespace OHOS {
namespace AppExecFwk {
namespace FormRender {
namespace {
constexpr int32_t RENDER_FORM_FAILED = -1;
constexpr int32_t RELOAD_FORM_FAILED = -1;
constexpr int32_t RECYCLE_FORM_FAILED = -1;
constexpr int32_t SET_VISIBLE_CHANGE_FAILED = -1;
constexpr int32_t FORM_RENDER_TASK_DELAY_TIME = 20;  // ms
constexpr int32_t ENABLE_FORM_FAILED = -1;
constexpr int32_t UPDATE_FORM_SIZE_FAILED = -1;
constexpr int32_t FORM_CLIENT_INVALID = -1;
constexpr int64_t MIN_DURATION_MS = 1500;
constexpr int64_t TASK_ONCONFIGURATIONUPDATED_DELAY_MS = 1000;
const std::string TASK_ONCONFIGURATIONUPDATED = "FormRenderServiceMgr::OnConfigurationUpdated";
const std::string FORM_RENDER_SERIAL_QUEUE = "FormRenderSerialQueue";
}  // namespace
using namespace AbilityRuntime;
using namespace OHOS::AAFwk::GlobalConfigurationKey;

FormRenderServiceMgr::FormRenderServiceMgr()
{
    serialQueue_ = std::make_unique<FormRenderSerialQueue>(FORM_RENDER_SERIAL_QUEUE);
    FormRenderStatusTaskMgr::GetInstance().SetSerialQueue(serialQueue_);
}

FormRenderServiceMgr::~FormRenderServiceMgr() = default;

int32_t FormRenderServiceMgr::RenderForm(
    const FormJsInfo &formJsInfo, const Want &want, const sptr<IRemoteObject> &callerToken)
{
    HILOG_INFO("Render form,bundleName=%{public}s,abilityName=%{public}s,formName=%{public}s,"
               "moduleName=%{public}s,jsFormCodePath=%{public}s,formSrc=%{public}s,formId=%{public}" PRId64,
        formJsInfo.bundleName.c_str(),
        formJsInfo.abilityName.c_str(),
        formJsInfo.formName.c_str(),
        formJsInfo.moduleName.c_str(),
        formJsInfo.jsFormCodePath.c_str(),
        formJsInfo.formSrc.c_str(),
        formJsInfo.formId);

    SetCriticalTrueOnFormActivity();
    sptr<IFormSupply> formSupplyClient = iface_cast<IFormSupply>(callerToken);
    if (formSupplyClient == nullptr) {
        HILOG_ERROR("null IFormSupply");
        return ERR_APPEXECFWK_FORM_BIND_PROVIDER_FAILED;
    }
    SetFormSupplyClient(formSupplyClient);
    HILOG_DEBUG("connectId:%{public}d", want.GetIntParam(Constants::FORM_CONNECT_ID, 0L));

    std::string eventId = want.GetStringParam(Constants::FORM_STATUS_EVENT_ID);
    if (eventId.empty()) {
        HILOG_ERROR("GetTid failed");
        return ERR_APPEXECFWK_FORM_BIND_PROVIDER_FAILED;
    }
    HILOG_INFO("eventId:%{public}s", eventId.c_str());
    FormRenderStatusMgr::GetInstance().SetFormEventId(formJsInfo.formId, eventId);

    std::string uid = want.GetStringParam(Constants::FORM_SUPPLY_UID);
    if (uid.empty()) {
        HILOG_ERROR("GetUid failed");
        return ERR_APPEXECFWK_FORM_BIND_PROVIDER_FAILED;
    }
    Want formRenderWant(want);
    const auto result = UpdateRenderRecordByUid(uid, formRenderWant, formJsInfo, formSupplyClient);
    if (result != ERR_OK) {
        HILOG_ERROR("render form failed");
        FormRenderStatusTaskMgr::GetInstance().OnRenderFormDone(
            formJsInfo.formId, FormFsmEvent::RENDER_FORM_FAIL, formSupplyClient);
    }
    formSupplyClient->OnRenderTaskDone(formJsInfo.formId, formRenderWant);
    return result;
}

int32_t FormRenderServiceMgr::StopRenderingForm(
    const FormJsInfo &formJsInfo, const Want &want, const sptr<IRemoteObject> &callerToken)
{
    HILOG_INFO("call, formId:%{public}" PRId64, formJsInfo.formId);
    SetCriticalTrueOnFormActivity();
    sptr<IFormSupply> formSupplyClient = iface_cast<IFormSupply>(callerToken);
    if (formSupplyClient == nullptr) {
        HILOG_ERROR("null IFormSupply");
        return ERR_APPEXECFWK_FORM_BIND_PROVIDER_FAILED;
    }
    std::string uid = want.GetStringParam(Constants::FORM_SUPPLY_UID);
    std::string eventId = want.GetStringParam(Constants::FORM_STATUS_EVENT_ID);
    if (uid.empty() || eventId.empty()) {
        HILOG_ERROR("GetUid or GetEventid failed");
        return ERR_APPEXECFWK_FORM_BIND_PROVIDER_FAILED;
    }
    FormRenderStatusMgr::GetInstance().SetFormEventId(formJsInfo.formId, eventId);

    bool isRenderGroupEmpty = false;
    sptr<IRemoteObject> hostToken = want.GetRemoteObject(Constants::PARAM_FORM_HOST_TOKEN);
    {
        std::shared_ptr<FormRenderRecord> search = nullptr;
        GetRenderRecordById(search, uid);
        if (search == nullptr) {
            HILOG_ERROR("get render record fail");
            return RENDER_FORM_FAILED;
        }

        std::string compId = want.GetStringParam(Constants::FORM_RENDER_COMP_ID);
        search->DeleteRenderRecord(formJsInfo.formId, compId, hostToken, isRenderGroupEmpty);
        const auto result = DeleteRenderRecordByUid(uid, search);
        if (result != ERR_OK) {
            return result;
        }
    }

    HILOG_INFO("connectId:%{public}d", want.GetIntParam(Constants::FORM_CONNECT_ID, 0L));
    if (isRenderGroupEmpty) {
        formSupplyClient->OnStopRenderingTaskDone(formJsInfo.formId, want);
        FormRenderStatusTaskMgr::GetInstance().OnDeleteFormDone(
            formJsInfo.formId, FormFsmEvent::DELETE_FORM_FINISH, formSupplyClient);
    } else {
        FormRenderStatusTaskMgr::GetInstance().OnDeleteFormDone(
            formJsInfo.formId, FormFsmEvent::DELETE_FORM_DONE, formSupplyClient);
    }

    std::lock_guard<std::mutex> lock(renderRecordMutex_);
    SetCriticalFalseOnAllFormInvisible();

    return ERR_OK;
}

int32_t FormRenderServiceMgr::ReleaseRenderer(
    int64_t formId, const std::string &compId, const std::string &uid, const Want &want)
{
    HILOG_INFO("formId:%{public}" PRId64 ",compId:%{public}s,uid:%{public}s", formId, compId.c_str(), uid.c_str());
    SetCriticalTrueOnFormActivity();
    std::string eventId = want.GetStringParam(Constants::FORM_STATUS_EVENT_ID);
    if (formId <= 0 || compId.empty() || uid.empty() || eventId.empty()) {
        HILOG_ERROR("param invalid");
        return ERR_APPEXECFWK_FORM_BIND_PROVIDER_FAILED;
    }
    FormRenderStatusMgr::GetInstance().SetFormEventId(formId, eventId);

    sptr<IFormSupply> formSupplyClient = GetFormSupplyClient();
    if (formSupplyClient == nullptr) {
        HILOG_ERROR("null formSupplyClient");
        return FORM_CLIENT_INVALID;
    }

    std::lock_guard<std::mutex> lock(renderRecordMutex_);
    bool isRenderGroupEmpty = false;
    auto search = renderRecordMap_.find(uid);
    if (search == renderRecordMap_.end()) {
        HILOG_ERROR("invalid record,formId:%{public}" PRId64, formId);
        return RENDER_FORM_FAILED;
    }

    if (!search->second) {
        HILOG_ERROR("record invalid,formId:%{public}" PRId64, formId);
        return RENDER_FORM_FAILED;
    }

    search->second->ReleaseRenderer(formId, compId, isRenderGroupEmpty);
    HILOG_INFO("end,isRenderGroupEmpty:%{public}d", isRenderGroupEmpty);
    FormRenderStatusTaskMgr::GetInstance().OnRecycleFormDone(formId, FormFsmEvent::RECYCLE_FORM_DONE, formSupplyClient);
    FormRenderStatusTaskMgr::GetInstance().CancelRecycleTimeout(formId);
    if (isRenderGroupEmpty) {
        search->second->Release();
    }

    FormRenderEventReport::StopReleaseTimeoutReportTimer(formId);

    SetCriticalFalseOnAllFormInvisible();

    return ERR_OK;
}

int32_t FormRenderServiceMgr::CleanFormHost(const sptr<IRemoteObject> &hostToken)
{
    HILOG_INFO("Form host is died,clean renderRecord");
    SetCriticalTrueOnFormActivity();
    std::lock_guard<std::mutex> lock(renderRecordMutex_);
    for (auto iter = renderRecordMap_.begin(); iter != renderRecordMap_.end();) {
        auto renderRecord = iter->second;
        if (renderRecord && renderRecord->HandleHostDied(hostToken)) {
            HILOG_DEBUG("empty renderRecord,remove");
            iter = renderRecordMap_.erase(iter);
        } else {
            ++iter;
        }
    }

    SetCriticalFalseOnAllFormInvisible();

    return ERR_OK;
}

int32_t FormRenderServiceMgr::ReloadForm(const std::vector<FormJsInfo> &&formJsInfos, const Want &want)
{
    HILOG_INFO("ReloadForm start");
    SetCriticalTrueOnFormActivity();
    std::string uid = want.GetStringParam(Constants::FORM_SUPPLY_UID);
    if (uid.empty()) {
        HILOG_ERROR("Get uid failed");
        return ERR_APPEXECFWK_FORM_BIND_PROVIDER_FAILED;
    }
    if (!IsRenderRecordExist(uid)) {
        HILOG_ERROR("RenderRecord not find");
        return RELOAD_FORM_FAILED;
    }
    std::shared_ptr<FormRenderRecord> search = nullptr;
    GetRenderRecordById(search, uid);
    if (search != nullptr) {
        search->ReloadFormRecord(std::forward<decltype(formJsInfos)>(formJsInfos), want);
    }
    return ERR_OK;
}

int32_t FormRenderServiceMgr::OnUnlock()
{
    HILOG_INFO("OnUnlock start");
    SetCriticalTrueOnFormActivity();
    std::lock_guard<std::mutex> lock(renderRecordMutex_);
    if (isVerified_) {
        HILOG_WARN("Has been unlocked in render form, maybe miss or delay unlock event");
        return ERR_OK;
    }

    isVerified_ = true;
    for (const auto &iter : renderRecordMap_) {
        if (iter.second) {
            iter.second->OnUnlock();
        }
    }

    SetCriticalFalseOnAllFormInvisible();

    return ERR_OK;
}

int32_t FormRenderServiceMgr::SetVisibleChange(const int64_t formId, bool isVisible, const Want &want)
{
    HILOG_INFO("formId:%{public}" PRId64 " isVisble: %{public}d", formId, isVisible);
    if (formId <= 0) {
        HILOG_ERROR("formId is negative");
        return ERR_APPEXECFWK_FORM_INVALID_FORM_ID;
    }

    std::string uid = want.GetStringParam(Constants::FORM_SUPPLY_UID);
    if (uid.empty()) {
        HILOG_ERROR("empty uid,formId:%{public}" PRId64, formId);
        return ERR_APPEXECFWK_FORM_BIND_PROVIDER_FAILED;
    }
    HILOG_INFO("formId:%{public}" PRId64 ",uid:%{public}s", formId, uid.c_str());

    if (isVisible) {
        SetCriticalTrueOnFormActivity();
    }
    std::lock_guard<std::mutex> lock(renderRecordMutex_);
    if (auto search = renderRecordMap_.find(uid); search != renderRecordMap_.end()) {
        if (search->second == nullptr) {
            HILOG_ERROR("null renderRecord of %{public}" PRId64, formId);
            return SET_VISIBLE_CHANGE_FAILED;
        }
        auto ret = search->second->SetVisibleChange(formId, isVisible);
        if (!isVisible) {
            SetCriticalFalseOnAllFormInvisible();
        }
        if (ret != ERR_OK) {
            HILOG_ERROR("SetVisibleChange %{public}" PRId64 " failed.", formId);
            return ret;
        }
    } else {
        HILOG_ERROR("can't find render record of %{public}" PRId64, formId);
        return SET_VISIBLE_CHANGE_FAILED;
    }
    return ERR_OK;
}

void FormRenderServiceMgr::OnConfigurationUpdated(const std::shared_ptr<OHOS::AppExecFwk::Configuration> &configuration)
{
    HILOG_DEBUG("OnConfigurationUpdated start");
    if (!configuration) {
        HILOG_ERROR("null configuration");
        return;
    }

    SetCriticalTrueOnFormActivity();

    SetConfiguration(configuration);

#ifdef SUPPORT_POWER
    bool screenOnFlag = PowerMgr::PowerMgrClient::GetInstance().IsScreenOn();
    bool collaborationScreenOnFlag = PowerMgr::PowerMgrClient::GetInstance().IsCollaborationScreenOn();
    if (!screenOnFlag && !collaborationScreenOnFlag) {
        HILOG_WARN("screen off");
        hasCachedConfig_ = true;
        return;
    }
#endif

    serialQueue_->CancelDelayTask(TASK_ONCONFIGURATIONUPDATED);
    auto duration = std::chrono::steady_clock::now() - configUpdateTime_;
    if (std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() < MIN_DURATION_MS) {
        HILOG_INFO("OnConfigurationUpdated ignored");
        auto configUpdateFunc = [this]() {
            HILOG_INFO("OnConfigurationUpdated task run");
            this->OnConfigurationUpdatedInner();
        };
        serialQueue_->ScheduleDelayTask(TASK_ONCONFIGURATIONUPDATED,
            TASK_ONCONFIGURATIONUPDATED_DELAY_MS, configUpdateFunc);
        return;
    }
    OnConfigurationUpdatedInner();

    std::lock_guard<std::mutex> lock(renderRecordMutex_);
    SetCriticalFalseOnAllFormInvisible();
}

void FormRenderServiceMgr::OnConfigurationUpdatedInner()
{
    sptr<IFormSupply> formSupplyClient = GetFormSupplyClient();
    if (formSupplyClient == nullptr) {
        HILOG_ERROR("null formSupplyClient");
        return;
    }

    configUpdateTime_ = std::chrono::steady_clock::now();
    size_t allFormCount = 0;
    {
        std::lock_guard<std::mutex> lock(renderRecordMutex_);
        for (auto iter = renderRecordMap_.begin(); iter != renderRecordMap_.end(); ++iter) {
            if (iter->second) {
                iter->second->UpdateConfiguration(configuration_, formSupplyClient);
                allFormCount += iter->second->FormCount();
            }
        }
    }
    HILOG_INFO("OnConfigurationUpdated %{public}zu forms updated.", allFormCount);
    hasCachedConfig_ = false;
    PerformanceEventInfo eventInfo;
    eventInfo.timeStamp = FormRenderEventReport::GetNowMillisecond();
    eventInfo.bundleName = Constants::FRS_BUNDLE_NAME;
    eventInfo.sceneId = Constants::CPU_SCENE_ID_CONFIG_UPDATE;
    FormRenderEventReport::SendPerformanceEvent(SceneType::CPU_SCENE_ENTRY, eventInfo);
}

void FormRenderServiceMgr::SetConfiguration(const std::shared_ptr<OHOS::AppExecFwk::Configuration> &config)
{
    if (config != nullptr && configuration_ != nullptr) {
        const auto checkConfigItem = {
            SYSTEM_COLORMODE, SYSTEM_LANGUAGE, SYSTEM_FONT_SIZE_SCALE, SYSTEM_FONT_WEIGHT_SCALE};
        for (const auto &item : checkConfigItem) {
            std::string newValue = config->GetItem(item);
            std::string oldValue = configuration_->GetItem(item);
            if (newValue.empty() && !oldValue.empty()) {
                config->AddItem(item, oldValue);
            }
        }

        configuration_ = config;
        HILOG_INFO("current configuration_:%{public}s", configuration_->GetName().c_str());
        return;
    }

    configuration_ = config;
}

void FormRenderServiceMgr::RunCachedConfigurationUpdated()
{
    HILOG_INFO("RunCachedConfigUpdated");
    if (hasCachedConfig_) {
        SetCriticalTrueOnFormActivity();
        OnConfigurationUpdatedInner();

        std::lock_guard<std::mutex> lock(renderRecordMutex_);
        SetCriticalFalseOnAllFormInvisible();
    }
}

void FormRenderServiceMgr::FormRenderGCTask(const std::string &uid)
{
    auto mainHandler = std::make_shared<AppExecFwk::EventHandler>(AppExecFwk::EventRunner::GetMainEventRunner());
    if (mainHandler == nullptr) {
        HILOG_ERROR("null mainHandler");
        return;
    }
    auto formRenderGCFunc = [uid]() { FormRenderServiceMgr::GetInstance().FormRenderGC(uid); };
    mainHandler->PostTask(formRenderGCFunc, "FormRenderGC", FORM_RENDER_TASK_DELAY_TIME);
}

void FormRenderServiceMgr::FormRenderGC(const std::string &uid)
{
    HILOG_INFO("form gc, uid is %{public}s", uid.c_str());
    std::lock_guard<std::mutex> lock(renderRecordMutex_);
    if (auto search = renderRecordMap_.find(uid); search != renderRecordMap_.end()) {
        search->second->FormRenderGC();
    }
}

int32_t FormRenderServiceMgr::RecycleForm(const int64_t formId, const Want &want)
{
    if (formId <= 0) {
        HILOG_ERROR("formId is negative");
        return ERR_APPEXECFWK_FORM_INVALID_FORM_ID;
    }
    SetCriticalTrueOnFormActivity();

    std::string uid = want.GetStringParam(Constants::FORM_SUPPLY_UID);
    std::string eventId = want.GetStringParam(Constants::FORM_STATUS_EVENT_ID);
    if (uid.empty() || eventId.empty()) {
        HILOG_ERROR("empty uid or eventId, formId:%{public}" PRId64, formId);
        return ERR_APPEXECFWK_FORM_BIND_PROVIDER_FAILED;
    }
    HILOG_INFO("formId:%{public}" PRId64 ",uid:%{public}s", formId, uid.c_str());
    FormRenderStatusMgr::GetInstance().SetFormEventId(formId, eventId);

    std::string statusData;
    const auto result = RecycleFormByUid(uid, statusData, formId);
    if (result != ERR_OK) {
        HILOG_ERROR("RecycleFormByUid failed");
        return result;
    }

    sptr<IFormSupply> formSupplyClient = GetFormSupplyClient();
    if (formSupplyClient == nullptr) {
        HILOG_ERROR("null formSupplyClient, formId:%{public}" PRId64, formId);
        return RECYCLE_FORM_FAILED;
    }
    FormRenderStatusTaskMgr::GetInstance().OnRecycleForm(
        formId, FormFsmEvent::RECYCLE_DATA_DONE, statusData, want, formSupplyClient);
    FormRenderStatusTaskMgr::GetInstance().ScheduleRecycleTimeout(formId);

    FormRenderEventReport::StartReleaseTimeoutReportTimer(formId, uid);

    std::lock_guard<std::mutex> lock(renderRecordMutex_);
    SetCriticalFalseOnAllFormInvisible();

    return ERR_OK;
}

int32_t FormRenderServiceMgr::RecoverForm(const FormJsInfo &formJsInfo, const Want &want)
{
    auto formId = formJsInfo.formId;
    if (formId <= 0) {
        HILOG_ERROR("formId is negative");
        return ERR_APPEXECFWK_FORM_INVALID_FORM_ID;
    }

    SetCriticalTrueOnFormActivity();

    std::string uid = want.GetStringParam(Constants::FORM_SUPPLY_UID);
    std::string eventId = want.GetStringParam(Constants::FORM_STATUS_EVENT_ID);
    if (uid.empty() || eventId.empty()) {
        HILOG_ERROR("empty uid or eventId, formId:%{public}" PRId64, formId);
        return ERR_APPEXECFWK_FORM_BIND_PROVIDER_FAILED;
    }
    FormRenderStatusMgr::GetInstance().SetFormEventId(formJsInfo.formId, eventId);
    HILOG_INFO("formId:%{public}" PRId64 ", connectId:%{public}d, uid:%{public}s",
        formId,
        want.GetIntParam(Constants::FORM_CONNECT_ID, 0L),
        uid.c_str());

    std::string statusData = want.GetStringParam(Constants::FORM_STATUS_DATA);
    if (statusData.empty()) {
        HILOG_WARN("empty statusData of %{public}s", std::to_string(formId).c_str());
    }
    return RecoverFormByUid(formJsInfo, want, uid, statusData);
}

void FormRenderServiceMgr::ConfirmUnlockState(Want &renderWant)
{
    // Ensure that there are no issues with adding form and unlocking drawing concurrency
    if (isVerified_) {
        renderWant.SetParam(Constants::FORM_RENDER_STATE, true);
    } else if (renderWant.GetBoolParam(Constants::FORM_RENDER_STATE, false)) {
        HILOG_WARN("Maybe unlock event is missed or delayed, all form record begin to render");
        isVerified_ = true;
        for (const auto &iter : renderRecordMap_) {
            if (iter.second) {
                iter.second->OnUnlock();
            }
        }
    } else if (renderWant.GetBoolParam(Constants::FORM_RENDER_WITHOUT_UNLOCK_STATE, false)) {
        HILOG_WARN("The current form allow render without unlocked");
        renderWant.SetParam(Constants::FORM_RENDER_STATE, true);
    }
}

int32_t FormRenderServiceMgr::UpdateFormSize(
    const int64_t formId, float width, float height, float borderWidth, const std::string &uid)
{
    SetCriticalTrueOnFormActivity();

    std::lock_guard<std::mutex> lock(renderRecordMutex_);
    if (auto search = renderRecordMap_.find(uid); search != renderRecordMap_.end()) {
        if (search->second == nullptr) {
            HILOG_ERROR("UpdateFormSize null renderRecord of %{public}" PRId64, formId);
            return UPDATE_FORM_SIZE_FAILED;
        }
        search->second->UpdateFormSizeOfGroups(formId, width, height, borderWidth);
        return ERR_OK;
    }
    HILOG_ERROR("can't find render record of %{public}" PRId64, formId);
    return UPDATE_FORM_SIZE_FAILED;
}

void FormRenderServiceMgr::SetFormSupplyClient(const sptr<IFormSupply> &formSupplyClient)
{
    std::lock_guard<std::mutex> lock(formSupplyMutex_);
    formSupplyClient_ = formSupplyClient;
}

sptr<IFormSupply> FormRenderServiceMgr::GetFormSupplyClient()
{
    std::lock_guard<std::mutex> lock(formSupplyMutex_);
    return formSupplyClient_;
}

bool FormRenderServiceMgr::IsRenderRecordExist(const std::string &uid)
{
    std::lock_guard<std::mutex> lock(renderRecordMutex_);
    auto iterator = renderRecordMap_.find(uid);
    return iterator != renderRecordMap_.end();
}

int32_t FormRenderServiceMgr::UpdateRenderRecordByUid(const std::string &uid, Want &formRenderWant,
    const FormJsInfo &formJsInfo, const sptr<IFormSupply> &formSupplyClient)
{
    if (formSupplyClient == nullptr) {
        HILOG_ERROR("null IFormSupply");
        return ERR_APPEXECFWK_FORM_BIND_PROVIDER_FAILED;
    }
    int32_t result = ERR_OK;
    sptr<IRemoteObject> hostToken = formRenderWant.GetRemoteObject(Constants::PARAM_FORM_HOST_TOKEN);
    std::lock_guard<std::mutex> lock(renderRecordMutex_);
    ConfirmUnlockState(formRenderWant);
    auto search = renderRecordMap_.find(uid);
    if (search != renderRecordMap_.end()) {
        result = search->second->UpdateRenderRecord(formJsInfo, formRenderWant, hostToken);
    } else {
        auto record = FormRenderRecord::Create(formJsInfo.bundleName, uid, formJsInfo.isDynamic, formSupplyClient);
        if (record == nullptr) {
            HILOG_ERROR("null record");
            return RENDER_FORM_FAILED;
        }
        record->SetConfiguration(configuration_);
        result = record->UpdateRenderRecord(formJsInfo, formRenderWant, hostToken);
        if (renderRecordMap_.empty()) {
            FormMemmgrClient::GetInstance().SetCritical(true);
        }
        renderRecordMap_.emplace(uid, record);
        FormRenderGCTask(uid);
    }
    return result;
}

void FormRenderServiceMgr::GetRenderRecordById(std::shared_ptr<FormRenderRecord> &search, const std::string &uid)
{
    std::lock_guard<std::mutex> lock(renderRecordMutex_);
    auto iterator = renderRecordMap_.find(uid);
    if (iterator == renderRecordMap_.end() || !(iterator->second)) {
        HILOG_ERROR("fail");
        return;
    }
    search = iterator->second;
}

int32_t FormRenderServiceMgr::RecoverFormByUid(
    const FormJsInfo &formJsInfo, const Want &want, const std::string &uid, const std::string &statusData)
{
    bool isRecoverFormToHandleClickEvent =
        want.GetBoolParam(Constants::FORM_IS_RECOVER_FORM_TO_HANDLE_CLICK_EVENT, false);
    std::lock_guard<std::mutex> lock(renderRecordMutex_);
    if (auto search = renderRecordMap_.find(uid); search != renderRecordMap_.end()) {
        if (search->second == nullptr) {
            HILOG_ERROR("null renderRecord of %{public}" PRId64, formJsInfo.formId);
            return RECYCLE_FORM_FAILED;
        }
        return search->second->RecoverForm(formJsInfo, statusData, isRecoverFormToHandleClickEvent);
    }
    HILOG_ERROR("can't find render record of %{public}" PRId64, formJsInfo.formId);
    return RENDER_FORM_FAILED;
}

int32_t FormRenderServiceMgr::RecycleFormByUid(const std::string &uid, std::string &statusData, const int64_t formId)
{
    std::lock_guard<std::mutex> lock(renderRecordMutex_);
    auto search = renderRecordMap_.find(uid);
    if (search != renderRecordMap_.end()) {
        if (search->second == nullptr) {
            HILOG_ERROR("null renderRecord of %{public}" PRId64, formId);
            return RECYCLE_FORM_FAILED;
        }
        auto ret = search->second->RecycleForm(formId, statusData);
        if (ret != ERR_OK) {
            HILOG_ERROR("recycleForm failed, %{public}" PRId64, formId);
            return ret;
        }
    } else {
        HILOG_ERROR("can't find render record of %{public}" PRId64, formId);
        return RECYCLE_FORM_FAILED;
    }
    if (statusData.empty()) {
        HILOG_WARN("empty statusData of %{public}" PRId64, formId);
    }
    return ERR_OK;
}

int32_t FormRenderServiceMgr::DeleteRenderRecordByUid(
    const std::string &uid, const std::shared_ptr<FormRenderRecord> &search)
{
    if (!search) {
        HILOG_ERROR("get render record fail");
        return RENDER_FORM_FAILED;
    }
    std::lock_guard<std::mutex> lock(renderRecordMutex_);
    if (search->IsEmpty() && !search->HasRenderFormTask()) {
        auto iterator = renderRecordMap_.find(uid);
        if (iterator == renderRecordMap_.end()) {
            HILOG_ERROR("fail.");
            return RENDER_FORM_FAILED;
        }
        renderRecordMap_.erase(iterator);
        HILOG_INFO("DeleteRenderRecord success,uid:%{public}s", uid.c_str());
    }
    return ERR_OK;
}

/**
 * @note Requires caller to hold FormRenderServiceMgr's renderRecordMutex_
 * The calling context needs to be locked, and locking is not allowed inside the function
 */
void FormRenderServiceMgr::SetCriticalFalseOnAllFormInvisible()
{
    if (!FormMemmgrClient::GetInstance().IsCritical()) {
        return;
    }
    // No need to lock here, the context needs to have a lock renderRecordMutex_
    for (const auto &iter : renderRecordMap_) {
        if (iter.second && !iter.second->IsAllFormsInvisible()) {
            HILOG_INFO("is not AllFormsInvisible, uid: %{public}s", iter.first.c_str());
            return;
        }
    }
    FormMemmgrClient::GetInstance().SetCritical(false);
}

void FormRenderServiceMgr::SetCriticalTrueOnFormActivity()
{
    if (FormMemmgrClient::GetInstance().IsCritical()) {
        return;
    }
    FormMemmgrClient::GetInstance().SetCritical(true);
}

}  // namespace FormRender
}  // namespace AppExecFwk
}  // namespace OHOS
