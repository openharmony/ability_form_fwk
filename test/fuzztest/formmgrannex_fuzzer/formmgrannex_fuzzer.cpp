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

#include "formmgrannex_fuzzer.h"

#include <cstddef>
#include <cstdint>

#define private public
#define protected public
#include "form_mgr.h"
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
bool DoSomethingInterestingWithMyAPI(const char* data, size_t size)
{
    FormMgr formMgr;
    formMgr.Connect();
    wptr<IRemoteObject> remote = nullptr;
    formMgr.ResetProxy(remote);
    sptr<IFormMgr> formMgrService = nullptr;
    formMgr.SetFormMgrService(formMgrService);
    int64_t formId = static_cast<int64_t>(GetU32Data(data));
    std::vector<int64_t> formIds;
    formIds.emplace_back(formId);
    sptr<IRemoteObject> callerToken = nullptr;
    int32_t numFormsDeleted = static_cast<int32_t>(GetU32Data(data));
    formMgr.DeleteInvalidForms(formIds, callerToken, numFormsDeleted);
    Want want;
    FormStateInfo stateInfo;
    formMgr.AcquireFormState(want, callerToken, stateInfo);
    bool isVisible = *data % ENABLE;
    formMgr.NotifyFormsVisible(formIds, isVisible, callerToken);
    FormInfo formInfo;
    std::vector<FormInfo> formInfos;
    formInfos.emplace_back(formInfo);
    formMgr.GetAllFormsInfo(formInfos);
    std::string bundleName(data);
    formMgr.GetFormsInfoByApp(bundleName, formInfos);
    std::string moduleName(data);
    formMgr.GetFormsInfoByModule(bundleName, moduleName, formInfos);
    FormInfoFilter filter;
    formMgr.GetFormsInfo(filter, formInfos);
    return formMgr.IsRequestPublishFormSupported();
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

