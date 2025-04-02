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

#ifndef OHOS_FORM_FWK_FORM_MGR_SERVICE_QUEUE_H
#define OHOS_FORM_FWK_FORM_MGR_SERVICE_QUEUE_H

#include <singleton.h>
#include "form_serial_queue.h"

namespace OHOS {
namespace AppExecFwk {
class FormMgrServiceQueue final : public DelayedRefSingleton<FormMgrServiceQueue> {
    DECLARE_DELAYED_REF_SINGLETON(FormMgrServiceQueue)

public:
    DISALLOW_COPY_AND_MOVE(FormMgrServiceQueue);

    bool ScheduleTask(uint64_t ms, std::function<void()> func);
    void ScheduleDelayTask(const std::pair<int64_t, int64_t> &eventMsg, uint32_t ms, std::function<void()> func);
    void CancelDelayTask(const std::pair<int64_t, int64_t> &eventMsg);

private:
    std::shared_ptr<FormSerialQueue> serialQueue_ = nullptr;
};
}  // namespace AppExecFwk
}  // namespace OHOS
#endif // OHOS_FORM_FWK_FORM_MGR_SERVICE_QUEUE_H