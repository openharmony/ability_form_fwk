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

#include "form_stop_rendering_connection.h"

#include <cinttypes>

#include "form_bms_helper.h"
#include "form_constants.h"
#include "form_supply_callback.h"
#include "form_render_mgr.h"
#include "form_task_mgr.h"
#include "hilog_wrapper.h"
#include "ipc_skeleton.h"
#include "want.h"

namespace OHOS {
namespace AppExecFwk {
namespace {
    constexpr int32_t CALLING_UID_TRANSFORM_DIVISOR = 200000;
}
FormStopRenderingConnection::FormStopRenderingConnection(const FormRecord &formRecord, const std::string &bundleName,
    const std::string &abilityName) : formRecord_(formRecord)
{
    SetFormId(formRecord.formId);
    SetProviderKey(bundleName, abilityName);
}
/**
 * @brief OnAbilityConnectDone, AbilityMs notify caller ability the result of connect.
 * @param element service ability's ElementName.
 * @param remoteObject the session proxy of service ability.
 * @param resultCode ERR_OK on success, others on failure.
 */
void FormStopRenderingConnection::OnAbilityConnectDone(
    const AppExecFwk::ElementName &element, const sptr<IRemoteObject> &remoteObject, int resultCode)
{
    HILOG_INFO("%{public}s called.", __func__);
    if (resultCode != ERR_OK) {
        HILOG_ERROR("%{public}s, abilityName:%{public}s, formId:%{public}" PRId64 ", resultCode:%{public}d",
           __func__, element.GetAbilityName().c_str(), GetFormId(), resultCode);
        return;
    }
    FormRenderMgr::GetInstance().AddConnection(GetFormId(), this, false);
    int32_t callingUid = IPCSkeleton::GetCallingUid();
    int32_t userId = callingUid / CALLING_UID_TRANSFORM_DIVISOR;
    int32_t bundleUid = FormBmsHelper::GetInstance().GetUidByBundleName(formRecord_.bundleName, userId);
    Want want;
    want.SetParam(Constants::FORM_SUPPLY_UID, bundleUid);
    want.SetParam(Constants::FORM_CONNECT_ID, this->GetConnectId());
    HILOG_DEBUG("%{public}s, connectId:%{public}d", __func__, this->GetConnectId());
    FormTaskMgr::GetInstance().PostStopRenderingForm(formRecord_, want, remoteObject);
}
}  // namespace AppExecFwk
}  // namespace OHOS