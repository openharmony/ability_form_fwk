/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "formabilityconnection_fuzzer.h"

#include <cstddef>
#include <cstdint>

#define private public
#define protected public
#include "common/connection/form_ability_connection.h"
#include "ams_mgr/form_ams_helper.h"
#include "form_provider/connection/form_batch_delete_connection.h"
#include "form_provider/connection/form_cast_temp_connection.h"
#undef private
#undef protected
#include "securec.h"

using namespace OHOS::AppExecFwk;

namespace OHOS {
constexpr size_t U32_AT_SIZE = 4;
constexpr uint8_t ENABLE = 2;
uint32_t GetU32Data(const char* ptr)
{
    // convert fuzz input data to an integer
    return (ptr[0] << 24) | (ptr[1] << 16) | (ptr[2] << 8) | ptr[3];
}

void DoSomethingInterestingPart2(const char* data, size_t size)
{
    FormAmsHelper formAmsHelper;
    std::string bundleName(data, size);
    std::string abilityName(data, size);
    AppExecFwk::ElementName element;
    sptr<IRemoteObject> providerToken = nullptr;
    sptr<IRemoteObject> remoteObjects = nullptr;
    int resultCode = static_cast<int>(GetU32Data(data));
    Want want;
    sptr<AAFwk::IAbilityConnection> connect = nullptr;
    formAmsHelper.GetAbilityManager();
    formAmsHelper.ConnectServiceAbility(want, connect);
    formAmsHelper.DisconnectServiceAbility(connect);
    formAmsHelper.DisconnectServiceAbilityDelay(connect);
    formAmsHelper.StopExtensionAbility(want);
    formAmsHelper.RegisterConfigurationObserver();
    formAmsHelper.UnRegisterConfigurationObserver();
    sptr<AAFwk::IAbilityManager> abilityManager = nullptr;
    formAmsHelper.SetAbilityManager(abilityManager);
    formAmsHelper.DisconnectAbilityTask(connect);
    int32_t userId = static_cast<int32_t>(GetU32Data(data));
    formAmsHelper.StartAbility(want, userId);
    std::set<int64_t> formIds;
    sptr<IAbilityConnection> batchDeleteConnection = new FormBatchDeleteConnection(formIds, bundleName, abilityName);
    batchDeleteConnection->OnAbilityConnectDone(element, providerToken, userId);
    int64_t formId = static_cast<int64_t>(GetU32Data(data));
    sptr<IAbilityConnection> castTempConnection = new FormCastTempConnection(formId, bundleName, abilityName);
    castTempConnection->OnAbilityConnectDone(element, remoteObjects, resultCode);
}

void DoSomethingInterestingPart3(const char* data, size_t size)
{
    FormAmsHelper formAmsHelper;
    std::string bundleName(data, size);
    std::string abilityName(data, size);
    AppExecFwk::ElementName element;
    sptr<IRemoteObject> providerToken = nullptr;
    sptr<IRemoteObject> remoteObjects = nullptr;
    int resultCode = static_cast<int>(GetU32Data(data));
    Want want;
    sptr<AAFwk::IAbilityConnection> connect = nullptr;
    formAmsHelper.GetAbilityManager();
    formAmsHelper.ConnectServiceAbility(want, connect);
    formAmsHelper.DisconnectServiceAbility(connect);
    formAmsHelper.DisconnectServiceAbilityDelay(connect);
    formAmsHelper.StopExtensionAbility(want);
    formAmsHelper.RegisterConfigurationObserver();
    formAmsHelper.UnRegisterConfigurationObserver();
    sptr<AAFwk::IAbilityManager> abilityManager = nullptr;
    formAmsHelper.SetAbilityManager(abilityManager);
    formAmsHelper.DisconnectAbilityTask(connect);
    int32_t userId = static_cast<int32_t>(GetU32Data(data));
    formAmsHelper.StartAbility(want, userId);
    std::set<int64_t> formIds;
    sptr<IAbilityConnection> batchDeleteConnection = new FormBatchDeleteConnection(formIds, bundleName, abilityName);
    batchDeleteConnection->OnAbilityConnectDone(element, providerToken, userId);
    int64_t formId = static_cast<int64_t>(GetU32Data(data));
    sptr<IAbilityConnection> castTempConnection = new FormCastTempConnection(formId, bundleName, abilityName);
    castTempConnection->OnAbilityConnectDone(element, remoteObjects, resultCode);
}

void DoSomethingInterestingPart4(const char* data, size_t size)
{
    FormAmsHelper formAmsHelper;
    std::string bundleName(data, size);
    std::string abilityName(data, size);
    AppExecFwk::ElementName element;
    sptr<IRemoteObject> providerToken = nullptr;
    sptr<IRemoteObject> remoteObjects = nullptr;
    int resultCode = static_cast<int>(GetU32Data(data));
    Want want;
    sptr<AAFwk::IAbilityConnection> connect = nullptr;
    formAmsHelper.GetAbilityManager();
    formAmsHelper.ConnectServiceAbility(want, connect);
    formAmsHelper.DisconnectServiceAbility(connect);
    formAmsHelper.DisconnectServiceAbilityDelay(connect);
    formAmsHelper.StopExtensionAbility(want);
    formAmsHelper.RegisterConfigurationObserver();
    formAmsHelper.UnRegisterConfigurationObserver();
    sptr<AAFwk::IAbilityManager> abilityManager = nullptr;
    formAmsHelper.SetAbilityManager(abilityManager);
    formAmsHelper.DisconnectAbilityTask(connect);
    int32_t userId = static_cast<int32_t>(GetU32Data(data));
    formAmsHelper.StartAbility(want, userId);
    std::set<int64_t> formIds;
    sptr<IAbilityConnection> batchDeleteConnection = new FormBatchDeleteConnection(formIds, bundleName, abilityName);
    batchDeleteConnection->OnAbilityConnectDone(element, providerToken, userId);
    int64_t formId = static_cast<int64_t>(GetU32Data(data));
    sptr<IAbilityConnection> castTempConnection = new FormCastTempConnection(formId, bundleName, abilityName);
    castTempConnection->OnAbilityConnectDone(element, remoteObjects, resultCode);
}

void DoSomethingInterestingPart5(const char* data, size_t size)
{
    FormAmsHelper formAmsHelper;
    std::string bundleName(data, size);
    std::string abilityName(data, size);
    AppExecFwk::ElementName element;
    sptr<IRemoteObject> providerToken = nullptr;
    sptr<IRemoteObject> remoteObjects = nullptr;
    int resultCode = static_cast<int>(GetU32Data(data));
    Want want;
    sptr<AAFwk::IAbilityConnection> connect = nullptr;
    formAmsHelper.GetAbilityManager();
    formAmsHelper.ConnectServiceAbility(want, connect);
    formAmsHelper.DisconnectServiceAbility(connect);
    formAmsHelper.DisconnectServiceAbilityDelay(connect);
    formAmsHelper.StopExtensionAbility(want);
    formAmsHelper.RegisterConfigurationObserver();
    formAmsHelper.UnRegisterConfigurationObserver();
    sptr<AAFwk::IAbilityManager> abilityManager = nullptr;
    formAmsHelper.SetAbilityManager(abilityManager);
    formAmsHelper.DisconnectAbilityTask(connect);
    int32_t userId = static_cast<int32_t>(GetU32Data(data));
    formAmsHelper.StartAbility(want, userId);
    std::set<int64_t> formIds;
    sptr<IAbilityConnection> batchDeleteConnection = new FormBatchDeleteConnection(formIds, bundleName, abilityName);
    batchDeleteConnection->OnAbilityConnectDone(element, providerToken, userId);
    int64_t formId = static_cast<int64_t>(GetU32Data(data));
    sptr<IAbilityConnection> castTempConnection = new FormCastTempConnection(formId, bundleName, abilityName);
    castTempConnection->OnAbilityConnectDone(element, remoteObjects, resultCode);
}

void DoSomethingInterestingPart6(const char* data, size_t size)
{
    FormAmsHelper formAmsHelper;
    std::string bundleName(data, size);
    std::string abilityName(data, size);
    AppExecFwk::ElementName element;
    sptr<IRemoteObject> providerToken = nullptr;
    sptr<IRemoteObject> remoteObjects = nullptr;
    int resultCode = static_cast<int>(GetU32Data(data));
    Want want;
    sptr<AAFwk::IAbilityConnection> connect = nullptr;
    formAmsHelper.GetAbilityManager();
    formAmsHelper.ConnectServiceAbility(want, connect);
    formAmsHelper.DisconnectServiceAbility(connect);
    formAmsHelper.DisconnectServiceAbilityDelay(connect);
    formAmsHelper.StopExtensionAbility(want);
    formAmsHelper.RegisterConfigurationObserver();
    formAmsHelper.UnRegisterConfigurationObserver();
    sptr<AAFwk::IAbilityManager> abilityManager = nullptr;
    formAmsHelper.SetAbilityManager(abilityManager);
    formAmsHelper.DisconnectAbilityTask(connect);
    int32_t userId = static_cast<int32_t>(GetU32Data(data));
    formAmsHelper.StartAbility(want, userId);
    std::set<int64_t> formIds;
    sptr<IAbilityConnection> batchDeleteConnection = new FormBatchDeleteConnection(formIds, bundleName, abilityName);
    batchDeleteConnection->OnAbilityConnectDone(element, providerToken, userId);
    int64_t formId = static_cast<int64_t>(GetU32Data(data));
    sptr<IAbilityConnection> castTempConnection = new FormCastTempConnection(formId, bundleName, abilityName);
    castTempConnection->OnAbilityConnectDone(element, remoteObjects, resultCode);
}

void DoSomethingInterestingPart7(const char* data, size_t size)
{
    FormAmsHelper formAmsHelper;
    std::string bundleName(data, size);
    std::string abilityName(data, size);
    AppExecFwk::ElementName element;
    sptr<IRemoteObject> providerToken = nullptr;
    sptr<IRemoteObject> remoteObjects = nullptr;
    int resultCode = static_cast<int>(GetU32Data(data));
    Want want;
    sptr<AAFwk::IAbilityConnection> connect = nullptr;
    formAmsHelper.GetAbilityManager();
    formAmsHelper.ConnectServiceAbility(want, connect);
    formAmsHelper.DisconnectServiceAbility(connect);
    formAmsHelper.DisconnectServiceAbilityDelay(connect);
    formAmsHelper.StopExtensionAbility(want);
    formAmsHelper.RegisterConfigurationObserver();
    formAmsHelper.UnRegisterConfigurationObserver();
    sptr<AAFwk::IAbilityManager> abilityManager = nullptr;
    formAmsHelper.SetAbilityManager(abilityManager);
    formAmsHelper.DisconnectAbilityTask(connect);
    int32_t userId = static_cast<int32_t>(GetU32Data(data));
    formAmsHelper.StartAbility(want, userId);
    std::set<int64_t> formIds;
    sptr<IAbilityConnection> batchDeleteConnection = new FormBatchDeleteConnection(formIds, bundleName, abilityName);
    batchDeleteConnection->OnAbilityConnectDone(element, providerToken, userId);
    int64_t formId = static_cast<int64_t>(GetU32Data(data));
    sptr<IAbilityConnection> castTempConnection = new FormCastTempConnection(formId, bundleName, abilityName);
    castTempConnection->OnAbilityConnectDone(element, remoteObjects, resultCode);
}

bool DoSomethingInterestingWithMyAPI(const char* data, size_t size)
{
    FormAbilityConnection formAbilityConnection;
    AppExecFwk::ElementName element;
    sptr<IRemoteObject> remoteObjects = nullptr;
    int resultCode = static_cast<int>(GetU32Data(data));
    bool isFreeInstall = *data % ENABLE;
    formAbilityConnection.SetFreeInstall(isFreeInstall);
    int32_t connectId = static_cast<int32_t>(GetU32Data(data));
    formAbilityConnection.SetConnectId(connectId);
    formAbilityConnection.OnAbilityConnectDone(element, remoteObjects, resultCode);
    formAbilityConnection.GetProviderKey();
    std::string bundleName(data, size);
    std::string abilityName(data, size);
    formAbilityConnection.SetProviderKey(bundleName, abilityName);
    int64_t formId = static_cast<int64_t>(GetU32Data(data));
    formAbilityConnection.SetFormId(formId);
    formAbilityConnection.GetFormId();
    sptr<IRemoteObject> hostToken = nullptr;
    formAbilityConnection.SetHostToken(hostToken);
    formAbilityConnection.GetHostToken();
    sptr<IRemoteObject> providerToken = nullptr;
    formAbilityConnection.SetProviderToken(providerToken);
    formAbilityConnection.GetProviderToken();
    formAbilityConnection.GetAppMgr();
    formAbilityConnection.onFormAppConnect();
    formAbilityConnection.ReportFormAppUnbindEvent();
    formAbilityConnection.GetBundleName();
    formAbilityConnection.GetAppFormPid();
    formAbilityConnection.OnAbilityDisconnectDone(element, resultCode);
    wptr<IRemoteObject> remoteObject1;
    formAbilityConnection.OnConnectDied(remoteObject1);
    DoSomethingInterestingPart2(data, size);
    return formAbilityConnection.GetConnectId();
}

bool DoSomethingInterestingWithMyAPI1(const char* data, size_t size)
{
    FormAbilityConnection formAbilityConnection;
    AppExecFwk::ElementName element;
    sptr<IRemoteObject> remoteObjects = nullptr;
    int resultCode = static_cast<int>(GetU32Data(data));
    bool isFreeInstall = *data % ENABLE;
    formAbilityConnection.SetFreeInstall(isFreeInstall);
    int32_t connectId = static_cast<int32_t>(GetU32Data(data));
    formAbilityConnection.SetConnectId(connectId);
    formAbilityConnection.OnAbilityConnectDone(element, remoteObjects, resultCode);
    formAbilityConnection.GetProviderKey();
    std::string bundleName(data, size);
    std::string abilityName(data, size);
    formAbilityConnection.SetProviderKey(bundleName, abilityName);
    int64_t formId = static_cast<int64_t>(GetU32Data(data));
    formAbilityConnection.SetFormId(formId);
    formAbilityConnection.GetFormId();
    sptr<IRemoteObject> hostToken = nullptr;
    formAbilityConnection.SetHostToken(hostToken);
    formAbilityConnection.GetHostToken();
    sptr<IRemoteObject> providerToken = nullptr;
    formAbilityConnection.SetProviderToken(providerToken);
    formAbilityConnection.GetProviderToken();
    formAbilityConnection.GetAppMgr();
    formAbilityConnection.onFormAppConnect();
    formAbilityConnection.ReportFormAppUnbindEvent();
    formAbilityConnection.GetBundleName();
    formAbilityConnection.GetAppFormPid();
    formAbilityConnection.OnAbilityDisconnectDone(element, resultCode);
    wptr<IRemoteObject> remoteObject1;
    formAbilityConnection.OnConnectDied(remoteObject1);
    DoSomethingInterestingPart2(data, size);
    return formAbilityConnection.GetConnectId();
}

bool DoSomethingInterestingWithMyAPI2(const char* data, size_t size)
{
    FormAbilityConnection formAbilityConnection;
    AppExecFwk::ElementName element;
    sptr<IRemoteObject> remoteObjects = nullptr;
    int resultCode = static_cast<int>(GetU32Data(data));
    bool isFreeInstall = *data % ENABLE;
    formAbilityConnection.SetFreeInstall(isFreeInstall);
    int32_t connectId = static_cast<int32_t>(GetU32Data(data));
    formAbilityConnection.SetConnectId(connectId);
    formAbilityConnection.OnAbilityConnectDone(element, remoteObjects, resultCode);
    formAbilityConnection.GetProviderKey();
    std::string bundleName(data, size);
    std::string abilityName(data, size);
    formAbilityConnection.SetProviderKey(bundleName, abilityName);
    int64_t formId = static_cast<int64_t>(GetU32Data(data));
    formAbilityConnection.SetFormId(formId);
    formAbilityConnection.GetFormId();
    sptr<IRemoteObject> hostToken = nullptr;
    formAbilityConnection.SetHostToken(hostToken);
    formAbilityConnection.GetHostToken();
    sptr<IRemoteObject> providerToken = nullptr;
    formAbilityConnection.SetProviderToken(providerToken);
    formAbilityConnection.GetProviderToken();
    formAbilityConnection.GetAppMgr();
    formAbilityConnection.onFormAppConnect();
    formAbilityConnection.ReportFormAppUnbindEvent();
    formAbilityConnection.GetBundleName();
    formAbilityConnection.GetAppFormPid();
    formAbilityConnection.OnAbilityDisconnectDone(element, resultCode);
    wptr<IRemoteObject> remoteObject1;
    formAbilityConnection.OnConnectDied(remoteObject1);
    DoSomethingInterestingPart2(data, size);
    return formAbilityConnection.GetConnectId();
}

bool DoSomethingInterestingWithMyAPI3(const char* data, size_t size)
{
    FormAbilityConnection formAbilityConnection;
    AppExecFwk::ElementName element;
    sptr<IRemoteObject> remoteObjects = nullptr;
    int resultCode = static_cast<int>(GetU32Data(data));
    bool isFreeInstall = *data % ENABLE;
    formAbilityConnection.SetFreeInstall(isFreeInstall);
    int32_t connectId = static_cast<int32_t>(GetU32Data(data));
    formAbilityConnection.SetConnectId(connectId);
    formAbilityConnection.OnAbilityConnectDone(element, remoteObjects, resultCode);
    formAbilityConnection.GetProviderKey();
    std::string bundleName(data, size);
    std::string abilityName(data, size);
    formAbilityConnection.SetProviderKey(bundleName, abilityName);
    int64_t formId = static_cast<int64_t>(GetU32Data(data));
    formAbilityConnection.SetFormId(formId);
    formAbilityConnection.GetFormId();
    sptr<IRemoteObject> hostToken = nullptr;
    formAbilityConnection.SetHostToken(hostToken);
    formAbilityConnection.GetHostToken();
    sptr<IRemoteObject> providerToken = nullptr;
    formAbilityConnection.SetProviderToken(providerToken);
    formAbilityConnection.GetProviderToken();
    formAbilityConnection.GetAppMgr();
    formAbilityConnection.onFormAppConnect();
    formAbilityConnection.ReportFormAppUnbindEvent();
    formAbilityConnection.GetBundleName();
    formAbilityConnection.GetAppFormPid();
    formAbilityConnection.OnAbilityDisconnectDone(element, resultCode);
    wptr<IRemoteObject> remoteObject1;
    formAbilityConnection.OnConnectDied(remoteObject1);
    DoSomethingInterestingPart2(data, size);
    return formAbilityConnection.GetConnectId();
}

bool DoSomethingInterestingWithMyAPI4(const char* data, size_t size)
{
    FormAbilityConnection formAbilityConnection;
    AppExecFwk::ElementName element;
    sptr<IRemoteObject> remoteObjects = nullptr;
    int resultCode = static_cast<int>(GetU32Data(data));
    bool isFreeInstall = *data % ENABLE;
    formAbilityConnection.SetFreeInstall(isFreeInstall);
    int32_t connectId = static_cast<int32_t>(GetU32Data(data));
    formAbilityConnection.SetConnectId(connectId);
    formAbilityConnection.OnAbilityConnectDone(element, remoteObjects, resultCode);
    formAbilityConnection.GetProviderKey();
    std::string bundleName(data, size);
    std::string abilityName(data, size);
    formAbilityConnection.SetProviderKey(bundleName, abilityName);
    int64_t formId = static_cast<int64_t>(GetU32Data(data));
    formAbilityConnection.SetFormId(formId);
    formAbilityConnection.GetFormId();
    sptr<IRemoteObject> hostToken = nullptr;
    formAbilityConnection.SetHostToken(hostToken);
    formAbilityConnection.GetHostToken();
    sptr<IRemoteObject> providerToken = nullptr;
    formAbilityConnection.SetProviderToken(providerToken);
    formAbilityConnection.GetProviderToken();
    formAbilityConnection.GetAppMgr();
    formAbilityConnection.onFormAppConnect();
    formAbilityConnection.ReportFormAppUnbindEvent();
    formAbilityConnection.GetBundleName();
    formAbilityConnection.GetAppFormPid();
    formAbilityConnection.OnAbilityDisconnectDone(element, resultCode);
    wptr<IRemoteObject> remoteObject1;
    formAbilityConnection.OnConnectDied(remoteObject1);
    DoSomethingInterestingPart2(data, size);
    return formAbilityConnection.GetConnectId();
}

bool DoSomethingInterestingWithMyAPI5(const char* data, size_t size)
{
    FormAbilityConnection formAbilityConnection;
    AppExecFwk::ElementName element;
    sptr<IRemoteObject> remoteObjects = nullptr;
    int resultCode = static_cast<int>(GetU32Data(data));
    bool isFreeInstall = *data % ENABLE;
    formAbilityConnection.SetFreeInstall(isFreeInstall);
    int32_t connectId = static_cast<int32_t>(GetU32Data(data));
    formAbilityConnection.SetConnectId(connectId);
    formAbilityConnection.OnAbilityConnectDone(element, remoteObjects, resultCode);
    formAbilityConnection.GetProviderKey();
    std::string bundleName(data, size);
    std::string abilityName(data, size);
    formAbilityConnection.SetProviderKey(bundleName, abilityName);
    int64_t formId = static_cast<int64_t>(GetU32Data(data));
    formAbilityConnection.SetFormId(formId);
    formAbilityConnection.GetFormId();
    sptr<IRemoteObject> hostToken = nullptr;
    formAbilityConnection.SetHostToken(hostToken);
    formAbilityConnection.GetHostToken();
    sptr<IRemoteObject> providerToken = nullptr;
    formAbilityConnection.SetProviderToken(providerToken);
    formAbilityConnection.GetProviderToken();
    formAbilityConnection.GetAppMgr();
    formAbilityConnection.onFormAppConnect();
    formAbilityConnection.ReportFormAppUnbindEvent();
    formAbilityConnection.GetBundleName();
    formAbilityConnection.GetAppFormPid();
    formAbilityConnection.OnAbilityDisconnectDone(element, resultCode);
    wptr<IRemoteObject> remoteObject1;
    formAbilityConnection.OnConnectDied(remoteObject1);
    DoSomethingInterestingPart2(data, size);
    return formAbilityConnection.GetConnectId();
}

bool DoSomethingInterestingWithMyAPI6(const char* data, size_t size)
{
    FormAbilityConnection formAbilityConnection;
    AppExecFwk::ElementName element;
    sptr<IRemoteObject> remoteObjects = nullptr;
    int resultCode = static_cast<int>(GetU32Data(data));
    bool isFreeInstall = *data % ENABLE;
    formAbilityConnection.SetFreeInstall(isFreeInstall);
    int32_t connectId = static_cast<int32_t>(GetU32Data(data));
    formAbilityConnection.SetConnectId(connectId);
    formAbilityConnection.OnAbilityConnectDone(element, remoteObjects, resultCode);
    formAbilityConnection.GetProviderKey();
    std::string bundleName(data, size);
    std::string abilityName(data, size);
    formAbilityConnection.SetProviderKey(bundleName, abilityName);
    int64_t formId = static_cast<int64_t>(GetU32Data(data));
    formAbilityConnection.SetFormId(formId);
    formAbilityConnection.GetFormId();
    sptr<IRemoteObject> hostToken = nullptr;
    formAbilityConnection.SetHostToken(hostToken);
    formAbilityConnection.GetHostToken();
    sptr<IRemoteObject> providerToken = nullptr;
    formAbilityConnection.SetProviderToken(providerToken);
    formAbilityConnection.GetProviderToken();
    formAbilityConnection.GetAppMgr();
    formAbilityConnection.onFormAppConnect();
    formAbilityConnection.ReportFormAppUnbindEvent();
    formAbilityConnection.GetBundleName();
    formAbilityConnection.GetAppFormPid();
    formAbilityConnection.OnAbilityDisconnectDone(element, resultCode);
    wptr<IRemoteObject> remoteObject1;
    formAbilityConnection.OnConnectDied(remoteObject1);
    DoSomethingInterestingPart2(data, size);
    return formAbilityConnection.GetConnectId();
}

bool DoSomethingInterestingWithMyAPI7(const char* data, size_t size)
{
    FormAbilityConnection formAbilityConnection;
    AppExecFwk::ElementName element;
    sptr<IRemoteObject> remoteObjects = nullptr;
    int resultCode = static_cast<int>(GetU32Data(data));
    bool isFreeInstall = *data % ENABLE;
    formAbilityConnection.SetFreeInstall(isFreeInstall);
    int32_t connectId = static_cast<int32_t>(GetU32Data(data));
    formAbilityConnection.SetConnectId(connectId);
    formAbilityConnection.OnAbilityConnectDone(element, remoteObjects, resultCode);
    formAbilityConnection.GetProviderKey();
    std::string bundleName(data, size);
    std::string abilityName(data, size);
    formAbilityConnection.SetProviderKey(bundleName, abilityName);
    int64_t formId = static_cast<int64_t>(GetU32Data(data));
    formAbilityConnection.SetFormId(formId);
    formAbilityConnection.GetFormId();
    sptr<IRemoteObject> hostToken = nullptr;
    formAbilityConnection.SetHostToken(hostToken);
    formAbilityConnection.GetHostToken();
    sptr<IRemoteObject> providerToken = nullptr;
    formAbilityConnection.SetProviderToken(providerToken);
    formAbilityConnection.GetProviderToken();
    formAbilityConnection.GetAppMgr();
    formAbilityConnection.onFormAppConnect();
    formAbilityConnection.ReportFormAppUnbindEvent();
    formAbilityConnection.GetBundleName();
    formAbilityConnection.GetAppFormPid();
    formAbilityConnection.OnAbilityDisconnectDone(element, resultCode);
    wptr<IRemoteObject> remoteObject1;
    formAbilityConnection.OnConnectDied(remoteObject1);
    DoSomethingInterestingPart2(data, size);
    return formAbilityConnection.GetConnectId();
}
}

/* Fuzzer entry point */
extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
    /* Run your code on data */
    if (data == nullptr) {
        return 0;
    }

    if (size < OHOS::U32_AT_SIZE) {
        return 0;
    }

    char* ch = static_cast<char*>(malloc(size + 1));
    if (ch == nullptr) {
        return 0;
    }

    (void)memset_s(ch, size + 1, 0x00, size + 1);
    if (memcpy_s(ch, size + 1, data, size) != EOK) {
        free(ch);
        ch = nullptr;
        return 0;
    }

    OHOS::DoSomethingInterestingWithMyAPI(ch, size);
    free(ch);
    ch = nullptr;
    return 0;
}

