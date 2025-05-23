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

#include "form_edit_extension_module_loader.h"

#include "form_edit_extension.h"
#include "hilog_tag_wrapper.h"

namespace OHOS {
namespace AbilityRuntime {
FormEditExtensionModuleLoader::FormEditExtensionModuleLoader() = default;
FormEditExtensionModuleLoader::~FormEditExtensionModuleLoader() = default;

Extension *FormEditExtensionModuleLoader::Create(const std::unique_ptr<Runtime> &runtime) const
{
    TAG_LOGD(AAFwkTag::FORM_EDIT_EXT, "called");
    return FormEditExtension::Create(runtime);
}

std::map<std::string, std::string> FormEditExtensionModuleLoader::GetParams()
{
    TAG_LOGD(AAFwkTag::FORM_EDIT_EXT, "called");
    std::map<std::string, std::string> params;
    // type means extension type in ExtensionAbilityType of
    // extension_ability_info.h, 27 means formEditExtension.
    params.insert(std::pair<std::string, std::string>("type", "27"));
    params.insert(std::pair<std::string, std::string>("name", "FormEditExtensionAbility"));
    return params;
}

extern "C" __attribute__((visibility("default"))) void *OHOS_EXTENSION_GetExtensionModule()
{
    return &FormEditExtensionModuleLoader::GetInstance();
}
} // namespace AbilityRuntime
} // namespace OHOS