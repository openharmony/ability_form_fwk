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

#ifndef OHOS_FORM_FWK_FORM_REFRESH_INTERFACE_H
#define OHOS_FORM_FWK_FORM_REFRESH_INTERFACE_H

#include "data_center/form_record/form_record.h"
#include "common/timer_mgr/form_timer.h"
#include "fms_log_wrapper.h"

namespace OHOS {
namespace AppExecFwk {
using Want = OHOS::AAFwk::Want;

struct RefreshData {
    int64_t formId;
    int64_t nextTime;
    int32_t callingUid;
    FormRecord record;
    FormTimer formTimer;
    sptr<IRemoteObject> callerToken;
    Want want;
    FormProviderData providerData;
};

/**
* @class IFormRefresh
* IFormRefresh interface is used to refresh form.
*/
class IFormRefresh {
public:
    virtual int RefreshFormRequest(RefreshData &data) = 0;
};
} // namespace AppExecFwk
} // namespace OHOS

#endif // OHOS_FORM_FWK_FORM_REFRESH_INTERFACE_H