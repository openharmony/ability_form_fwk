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

#ifdef MEM_MGR_ENABLE
#include "common/util/mem_status_listener.h"
#include "fms_log_wrapper.h"
#include "data_center/form_data_mgr.h"

namespace OHOS {
namespace AppExecFwk {
void MemStatusListener::OnConnected()
{
    HILOG_DEBUG("call");
}

void MemStatusListener::OnRemoteDied(const wptr<IRemoteObject> &object)
{
    HILOG_DEBUG("call");
}

void MemStatusListener::OnTrim(Memory::SystemMemoryLevel level)
{
    HILOG_DEBUG("memory level is %{public}d", level);
    FormDataMgr::GetInstance().RecycleAllRecyclableForms();
}

void MemStatusListener::ForceReclaim(int32_t pid, int32_t uid)
{
    HILOG_DEBUG("pid is %{public}d, uid is %{public}d", pid, uid);
    FormDataMgr::GetInstance().RecycleAllRecyclableForms();
}
} // namespace AppExecFwk
} // namespace OHOS
#endif //MEM_MGR_ENABLE
