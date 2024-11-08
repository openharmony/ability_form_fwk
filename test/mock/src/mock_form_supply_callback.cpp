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

#include "fms_log_wrapper.h"
#include "mock_form_supply_callback.h"

namespace OHOS {
namespace AppExecFwk {
sptr<MockFormSupplyCallback> MockFormSupplyCallback::instance = nullptr;
std::mutex MockFormSupplyCallback::mutex;

sptr<MockFormSupplyCallback> MockFormSupplyCallback::GetInstance()
{
    if (instance == nullptr) {
        std::lock_guard<std::mutex> lockl(mutex);
        if (instance == nullptr) {
            instance = new MockFormSupplyCallback();
        }
    }
    return instance;
}

int MockFormSupplyCallback::OnAcquire(const FormProviderInfo& formProviderInfo, const Want& want)
{
    HILOG_INFO("OnAcquire called.");
    return 1;
}

int MockFormSupplyCallback::OnEventHandle(const Want& want)
{
    HILOG_INFO("OnEventHandle called.");
    return 1;
}

int MockFormSupplyCallback::OnAcquireStateResult(FormState state, const std::string& provider, const Want& wantArg,
    const Want& want)
{
    HILOG_INFO("OnAcquireStateResult called.");
    return 1;
}

int MockFormSupplyCallback::OnAcquireDataResult(const AAFwk::WantParams &wantParams, int64_t requestCode)
{
    HILOG_INFO("OnAcquireDataResult called.");
    return 1;
}

void MockFormSupplyCallback::OnShareAcquire(int64_t formId, const std::string& remoteDeviceId,
    const AAFwk::WantParams& wantParams, int64_t requestCode, const bool& result)
{
    HILOG_INFO("OnShareAcquire called.");
}

int32_t MockFormSupplyCallback::OnRenderTaskDone(int64_t formId, const Want &want)
{
    HILOG_INFO("OnRenderTaskDone called.");
    return ERR_OK;
}

int32_t MockFormSupplyCallback::OnStopRenderingTaskDone(int64_t formId, const Want &want)
{
    HILOG_INFO("OnStopRenderingTaskDone called.");
    return ERR_OK;
}
} // namespace AppExecFwk
} // namespace OHOS
