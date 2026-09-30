/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FORM_FWK_MOCK_IF_SYSTEM_ABILITY_MANAGER_H
#define FORM_FWK_MOCK_IF_SYSTEM_ABILITY_MANAGER_H

#include <gmock/gmock.h>

#include "iremote_object.h"
#include "refbase.h"

namespace OHOS {
class ISystemAbilityManager : public virtual RefBase {
public:
    ISystemAbilityManager() = default;

    ~ISystemAbilityManager() override = default;

    MOCK_METHOD(sptr<IRemoteObject>, CheckSystemAbility, (int32_t));
};
} // namespace OHOS
#endif // FORM_FWK_MOCK_IF_SYSTEM_ABILITY_MANAGER_H
