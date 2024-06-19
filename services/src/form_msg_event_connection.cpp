
/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "form_msg_event_connection.h"

#include <cinttypes>

#include "fms_log_wrapper.h"
#include "form_constants.h"
#include "form_supply_callback.h"
#include "form_task_mgr.h"
#include "want.h"

namespace OHOS {
namespace AppExecFwk {
FormMsgEventConnection::FormMsgEventConnection(const int64_t formId, const Want& want,
    const std::string &bundleName, const std::string &abilityName)
    : want_(want)
{
    SetFormId(formId);
    SetProviderKey(bundleName, abilityName);
}
/**
 * @brief OnAbilityConnectDone, AbilityMs notify caller ability the result of connect.
 *
 * @param element Service ability's ElementName.
 * @param remoteObject The session proxy of service ability.
 * @param resultCode ERR_OK on success, others on failure.
 */
void FormMsgEventConnection::OnAbilityConnectDone(
    const AppExecFwk::ElementName &element, const sptr<IRemoteObject> &remoteObject, int resultCode)
{
    HILOG_INFO("call");
    if (resultCode != ERR_OK) {
        HILOG_ERROR("%{public}s, abilityName:%{public}s, formId:%{public}" PRId64 ", resultCode:%{public}d",
            __func__, element.GetAbilityName().c_str(), GetFormId(), resultCode);
        return;
    }
    onFormAppConnect();
    sptr<FormMsgEventConnection> connection(this);
    FormSupplyCallback::GetInstance()->AddConnection(connection);
    if (!want_.HasParameter(Constants::PARAM_MESSAGE_KEY)) {
        HILOG_ERROR("%{public}s error, message info is not exist", __func__);
        return;
    }
    std::string message = want_.GetStringParam(Constants::PARAM_MESSAGE_KEY);
    Want eventWant = Want(want_);
    eventWant.SetParam(Constants::FORM_CONNECT_ID, this->GetConnectId());
    FormTaskMgr::GetInstance().PostFormEventTask(GetFormId(), message, eventWant, remoteObject);
}
}  // namespace AppExecFwk
}  // namespace OHOS