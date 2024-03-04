/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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
#include "js_form_info.h"

#include "fms_log_wrapper.h"
#include "form_constants.h"
#include "form_info.h"
#include "form_info_base.h"
#include "form_instance.h"
#include "form_state_info.h"
#include "js_runtime_utils.h"
namespace OHOS {
namespace AbilityRuntime {
napi_value CreateJsFormType(napi_env engine)
{
    napi_value objValue = nullptr;
    napi_create_object(engine, &objValue);
    napi_set_named_property(engine, objValue, "JS", CreateJsValue(engine, AppExecFwk::FormType::JS));
    napi_set_named_property(engine, objValue, "eTS", CreateJsValue(engine, AppExecFwk::FormType::ETS));
    napi_set_named_property(engine, objValue, "arkTS", CreateJsValue(engine, AppExecFwk::FormType::ETS));
    return objValue;
}

napi_value CreateJsColorMode(napi_env engine)
{
    napi_value objValue = nullptr;
    napi_create_object(engine, &objValue);
    napi_set_named_property(
        engine, objValue, "MODE_AUTO", CreateJsValue(engine, AppExecFwk::FormsColorMode::AUTO_MODE));
    napi_set_named_property(
        engine, objValue, "MODE_DARK", CreateJsValue(engine, AppExecFwk::FormsColorMode::DARK_MODE));
    napi_set_named_property(
        engine, objValue, "MODE_LIGHT", CreateJsValue(engine, AppExecFwk::FormsColorMode::LIGHT_MODE));
    return objValue;
}

napi_value CreateJsFormState(napi_env engine)
{
    napi_value objValue = nullptr;
    napi_create_object(engine, &objValue);
    napi_set_named_property(engine, objValue, "UNKNOWN", CreateJsValue(engine, AppExecFwk::FormState::UNKNOWN));
    napi_set_named_property(engine, objValue, "DEFAULT", CreateJsValue(engine, AppExecFwk::FormState::DEFAULT));
    napi_set_named_property(engine, objValue, "READY", CreateJsValue(engine, AppExecFwk::FormState::READY));
    return objValue;
}

napi_value CreateJsFormParam(napi_env engine)
{
    napi_value objValue = nullptr;
    napi_create_object(engine, &objValue);
    napi_set_named_property(
        engine, objValue, "IDENTITY_KEY", CreateJsValue(engine, AppExecFwk::Constants::PARAM_FORM_IDENTITY_KEY));
    napi_set_named_property(
        engine, objValue, "DIMENSION_KEY", CreateJsValue(engine, AppExecFwk::Constants::PARAM_FORM_DIMENSION_KEY));
    napi_set_named_property(engine, objValue, "RENDERINGMODE_KEY", CreateJsValue(
        engine, AppExecFwk::Constants::PARAM_FORM_RENDERINGMODE_KEY));
    napi_set_named_property(
        engine, objValue, "NAME_KEY", CreateJsValue(engine, AppExecFwk::Constants::PARAM_FORM_NAME_KEY));
    napi_set_named_property(
        engine, objValue, "MODULE_NAME_KEY", CreateJsValue(engine, AppExecFwk::Constants::PARAM_MODULE_NAME_KEY));
    napi_set_named_property(
        engine, objValue, "WIDTH_KEY", CreateJsValue(engine, AppExecFwk::Constants::PARAM_FORM_WIDTH_KEY));
    napi_set_named_property(
        engine, objValue, "HEIGHT_KEY", CreateJsValue(engine, AppExecFwk::Constants::PARAM_FORM_HEIGHT_KEY));
    napi_set_named_property(
        engine, objValue, "TEMPORARY_KEY", CreateJsValue(engine, AppExecFwk::Constants::PARAM_FORM_TEMPORARY_KEY));
    napi_set_named_property(
        engine, objValue, "BUNDLE_NAME_KEY", CreateJsValue(engine, AppExecFwk::Constants::PARAM_BUNDLE_NAME_KEY));
    napi_set_named_property(
        engine, objValue, "ABILITY_NAME_KEY", CreateJsValue(engine, AppExecFwk::Constants::PARAM_ABILITY_NAME_KEY));
    napi_set_named_property(
        engine, objValue, "DEVICE_ID_KEY", CreateJsValue(engine, AppExecFwk::Constants::PARAM_DEVICE_ID_KEY));
    napi_set_named_property(
        engine, objValue, "LAUNCH_REASON_KEY", CreateJsValue(engine, AppExecFwk::Constants::LAUNCH_REASON_KEY));
    napi_set_named_property(engine, objValue,
        "PARAM_FORM_CUSTOMIZE_KEY", CreateJsValue(engine, AppExecFwk::Constants::PARAM_FORM_CUSTOMIZE_KEY));
    napi_set_named_property(engine, objValue,
        "FORM_RENDERING_MODE_KEY", CreateJsValue(engine, AppExecFwk::Constants::PARAM_FORM_RENDERINGMODE_KEY));
    napi_set_named_property(engine, objValue,
        "HOST_BG_INVERSE_COLOR_KEY", CreateJsValue(engine, AppExecFwk::Constants::PARAM_HOST_BG_INVERSE_COLOR_KEY));
    return objValue;
}

napi_value CreateJsFormDimension(napi_env engine)
{
    napi_value objValue = nullptr;
    napi_create_object(engine, &objValue);
    napi_set_named_property(
        engine, objValue, "Dimension_1_2", CreateJsValue(engine, AppExecFwk::Constants::Dimension::DIMENSION_1_2));
    napi_set_named_property(
        engine, objValue, "Dimension_2_2", CreateJsValue(engine, AppExecFwk::Constants::Dimension::DIMENSION_2_2));
    napi_set_named_property(
        engine, objValue, "Dimension_2_4", CreateJsValue(engine, AppExecFwk::Constants::Dimension::DIMENSION_2_4));
    napi_set_named_property(
        engine, objValue, "Dimension_4_4", CreateJsValue(engine, AppExecFwk::Constants::Dimension::DIMENSION_4_4));
    napi_set_named_property(
        engine, objValue, "Dimension_2_1", CreateJsValue(engine, AppExecFwk::Constants::Dimension::DIMENSION_2_1));
    napi_set_named_property(
        engine, objValue, "DIMENSION_1_1", CreateJsValue(engine, AppExecFwk::Constants::Dimension::DIMENSION_1_1));
    return objValue;
}

napi_value CreateJsFormVisibilityType(napi_env engine)
{
    napi_value objValue = nullptr;
    napi_create_object(engine, &objValue);
    napi_set_named_property(engine, objValue, "UNKNOWN", CreateJsValue(engine, AppExecFwk::Constants::UNKNOWN));
    napi_set_named_property(
        engine, objValue, "FORM_VISIBLE", CreateJsValue(engine, AppExecFwk::Constants::FORM_VISIBLE));
    napi_set_named_property(
        engine, objValue, "FORM_INVISIBLE", CreateJsValue(engine, AppExecFwk::Constants::FORM_INVISIBLE));
    return objValue;
}

napi_value CreateJsFormLaunchReason(napi_env engine)
{
    napi_value objValue = nullptr;
    napi_create_object(engine, &objValue);
    napi_set_named_property(
        engine, objValue, "FORM_DEFAULT", CreateJsValue(engine, AppExecFwk::Constants::FORM_DEFAULT));
    napi_set_named_property(engine, objValue, "FORM_SHARE", CreateJsValue(engine, AppExecFwk::Constants::FORM_SHARE));
    return objValue;
}

napi_value CreateJsFormUsageState(napi_env engine)
{
    napi_value objValue = nullptr;
    napi_create_object(engine, &objValue);
    napi_set_named_property(engine, objValue, "USED", CreateJsValue(engine, AppExecFwk::FormUsageState::USED));
    napi_set_named_property(engine, objValue, "UNUSED", CreateJsValue(engine, AppExecFwk::FormUsageState::UNUSED));
    return objValue;
}

napi_value FormInfoInit(napi_env engine, napi_value exportObj)
{
    HILOG_INFO("%{public}s called.", __func__);

    napi_set_named_property(engine, exportObj, "FormType", CreateJsFormType(engine));
    napi_set_named_property(engine, exportObj, "ColorMode", CreateJsColorMode(engine));
    napi_set_named_property(engine, exportObj, "FormState", CreateJsFormState(engine));
    napi_set_named_property(engine, exportObj, "FormParam", CreateJsFormParam(engine));
    napi_set_named_property(engine, exportObj, "FormDimension", CreateJsFormDimension(engine));
    napi_set_named_property(engine, exportObj, "VisibilityType", CreateJsFormVisibilityType(engine));
    napi_set_named_property(engine, exportObj, "LaunchReason", CreateJsFormLaunchReason(engine));
    napi_set_named_property(engine, exportObj, "FormUsageState", CreateJsFormUsageState(engine));
    HILOG_INFO("%{public}s called end.", __func__);
    return exportObj;
}
}  // namespace AbilityRuntime
}  // namespace OHOS
