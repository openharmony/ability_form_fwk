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

#include <gtest/gtest.h>

#include "form_mgr_adapter.h"
#include "form_mgr_errors.h"
#include "fms_log_wrapper.h"

namespace {
    int g_enableUpdateForm = OHOS::ERR_OK;
    int g_disableUpdateForm = OHOS::ERR_OK;
    int g_addForm = OHOS::ERR_OK;
    int g_deleteForm = OHOS::ERR_OK;
    int g_releaseForm = OHOS::ERR_OK;
    int g_requestForm = OHOS::ERR_OK;
    int g_notifyWhetherVisibleForms = OHOS::ERR_OK;
    int g_castTempForm = OHOS::ERR_OK;
    int g_messageEvent = OHOS::ERR_OK;
    int g_routerEvent = OHOS::ERR_OK;
    int g_deleteInvalidForms = OHOS::ERR_OK;
    int g_acquireFormState = OHOS::ERR_OK;
    int g_notifyFormsVisible = OHOS::ERR_OK;
    int g_notifyFormsEnableUpdate = OHOS::ERR_OK;
    int g_getFormsInfoByApp = OHOS::ERR_OK;
    int g_getFormsInfoByModule = OHOS::ERR_OK;
    int g_updateForm = OHOS::ERR_OK;
    int g_updateFormLocation = OHOS::ERR_OK;
    bool g_isRequestPublishFormSupported = true;
}

void MockEnableUpdateForm(int mockRet)
{
    g_enableUpdateForm = mockRet;
}

void MockDisableUpdateForm(int mockRet)
{
    g_disableUpdateForm = mockRet;
}

void MockAddForm(int mockRet)
{
    g_addForm = mockRet;
}

void MockDeleteForm(int mockRet)
{
    g_deleteForm = mockRet;
}

void MockReleaseForm(int mockRet)
{
    g_releaseForm = mockRet;
}

void MockRequestForm(int mockRet)
{
    g_requestForm = mockRet;
}

void MockNotifyWhetherVisibleForms(int mockRet)
{
    g_notifyWhetherVisibleForms = mockRet;
}

void MockCastTempForm(int mockRet)
{
    g_castTempForm = mockRet;
}

void MockMessageEvent(int mockRet)
{
    g_messageEvent = mockRet;
}

void MockRouterEvent(int mockRet)
{
    g_routerEvent = mockRet;
}

void MockAcquireFormState(int mockRet)
{
    g_acquireFormState = mockRet;
}

void MockNotifyFormsVisible(int mockRet)
{
    g_notifyFormsVisible = mockRet;
}

void MockNotifyFormsEnableUpdate(int mockRet)
{
    g_notifyFormsEnableUpdate = mockRet;
}

void MockGetFormsInfoByApp(int mockRet)
{
    g_getFormsInfoByApp = mockRet;
}

void MockGetFormsInfoByModule(int mockRet)
{
    g_getFormsInfoByModule = mockRet;
}

void MockIsRequestPublishFormSupported(bool mockRet)
{
    g_isRequestPublishFormSupported = mockRet;
}

namespace OHOS {
namespace AppExecFwk {
int FormMgrAdapter::EnableUpdateForm(const std::vector<int64_t> formIDs, const sptr<IRemoteObject> &callerToken)
{
    GTEST_LOG_(INFO) << "EnableUpdateForm called " << g_enableUpdateForm;
    return g_enableUpdateForm;
}

int FormMgrAdapter::DisableUpdateForm(const std::vector<int64_t> formIDs, const sptr<IRemoteObject> &callerToken)
{
    GTEST_LOG_(INFO) << "DisableUpdateForm called " << g_disableUpdateForm;
    return g_disableUpdateForm;
}

int FormMgrAdapter::AddForm(
    const int64_t formId, const Want &want, const sptr<IRemoteObject> &callerToken, FormJsInfo &formInfo)
{
    GTEST_LOG_(INFO) << "AddForm called " << g_addForm;
    return g_addForm;
}

int FormMgrAdapter::DeleteForm(const int64_t formId, const sptr<IRemoteObject> &callerToken)
{
    GTEST_LOG_(INFO) << "DeleteForm called " << g_deleteForm;
    return g_deleteForm;
}

int FormMgrAdapter::ReleaseForm(const int64_t formId, const sptr<IRemoteObject> &callerToken, const bool delCache)
{
    GTEST_LOG_(INFO) << "ReleaseForm called " << g_releaseForm;
    return g_releaseForm;
}

int FormMgrAdapter::RequestForm(const int64_t formId, const sptr<IRemoteObject> &callerToken, const Want &want)
{
    GTEST_LOG_(INFO) << "RequestForm called " << g_requestForm;
    return g_requestForm;
}

ErrCode FormMgrAdapter::NotifyWhetherVisibleForms(
    const std::vector<int64_t> &formIds, const sptr<IRemoteObject> &callerToken, const int32_t formVisibleType)
{
    GTEST_LOG_(INFO) << "NotifyWhetherVisibleForms called " << g_notifyWhetherVisibleForms;
    return g_notifyWhetherVisibleForms;
}

int FormMgrAdapter::CastTempForm(const int64_t formId, const sptr<IRemoteObject> &callerToken)
{
    GTEST_LOG_(INFO) << "CastTempForm called " << g_castTempForm;
    return g_castTempForm;
}

int FormMgrAdapter::MessageEvent(const int64_t formId, const Want &want, const sptr<IRemoteObject> &callerToken)
{
    GTEST_LOG_(INFO) << "MessageEvent called " << g_messageEvent;
    return g_messageEvent;
}

int FormMgrAdapter::RouterEvent(const int64_t formId, Want &want, const sptr<IRemoteObject> &callerToken)
{
    GTEST_LOG_(INFO) << "RouterEvent called " << g_routerEvent;
    return g_routerEvent;
}

int FormMgrAdapter::DeleteInvalidForms(
    const std::vector<int64_t> &formIds, const sptr<IRemoteObject> &callerToken, int32_t &numFormsDeleted)
{
    GTEST_LOG_(INFO) << "DeleteInvalidForms called " << g_deleteInvalidForms;
    return g_deleteInvalidForms;
}

int FormMgrAdapter::AcquireFormState(
    const Want &want, const sptr<IRemoteObject> &callerToken, FormStateInfo &stateInfo)
{
    GTEST_LOG_(INFO) << "AcquireFormState called " << g_acquireFormState;
    return g_acquireFormState;
}

int FormMgrAdapter::NotifyFormsVisible(
    const std::vector<int64_t> &formIds, bool isVisible, const sptr<IRemoteObject> &callerToken)
{
    GTEST_LOG_(INFO) << "NotifyFormsVisible called " << g_notifyFormsVisible;
    return g_notifyFormsVisible;
}

int FormMgrAdapter::NotifyFormsEnableUpdate(
    const std::vector<int64_t> &formIds, bool isEnableUpdate, const sptr<IRemoteObject> &callerToken)
{
    GTEST_LOG_(INFO) << "NotifyFormsEnableUpdate called " << g_notifyFormsEnableUpdate;
    return g_notifyFormsEnableUpdate;
}

int FormMgrAdapter::GetFormsInfoByApp(const std::string &bundleName, std::vector<FormInfo> &formInfos)
{
    GTEST_LOG_(INFO) << "GetFormsInfoByApp called " << g_getFormsInfoByApp;
    return g_getFormsInfoByApp;
}

int FormMgrAdapter::GetFormsInfoByModule(
    const std::string &bundleName, const std::string &moduleName, std::vector<FormInfo> &formInfos)
{
    GTEST_LOG_(INFO) << "GetFormsInfoByModule called " << g_getFormsInfoByModule;
    return g_getFormsInfoByModule;
}

bool FormMgrAdapter::IsRequestPublishFormSupported()
{
    return g_isRequestPublishFormSupported;
}

int FormMgrAdapter::UpdateForm(const int64_t formId, const int32_t uid,
    const FormProviderData &formProviderData, const std::vector<FormDataProxy> &formDataProxies)
{
    return g_updateForm;
}

int FormMgrAdapter::UpdateFormLocation(const int64_t &formId, const int32_t &formLocation)
{
    return g_updateFormLocation;
}
} // namespace AppExecFwk
} // namespace OHOS