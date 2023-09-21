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

#include "js_form_provider.h"

#include <cinttypes>
#include <vector>

#include "fms_log_wrapper.h"
#include "form_mgr_errors.h"
#include "form_mgr.h"
#include "js_form_info_util.h"
#include "js_runtime_utils.h"
#include "ipc_skeleton.h"
#include "napi_common_util.h"
#include "napi_common_want.h"
#include "napi_form_util.h"
#include "napi/native_api.h"
#include "napi/native_node_api.h"
#include "runtime.h"
#include "tokenid_kit.h"

namespace OHOS {
namespace AbilityRuntime {
using namespace OHOS;
using namespace OHOS::AAFwk;
using namespace OHOS::AppExecFwk;
namespace {
constexpr size_t ARGS_SIZE_ZERO = 0;
constexpr size_t ARGS_SIZE_ONE = 1;
constexpr size_t ARGS_SIZE_TWO = 2;
constexpr size_t ARGS_SIZE_THREE = 3;

bool ConvertFormInfoFilterThrow(napi_env env, napi_value jsValue, AppExecFwk::FormInfoFilter &formInfoFilter)
{
    napi_valuetype jsValueType = napi_undefined;
    napi_typeof(env, jsValue, &jsValueType);
    if (jsValueType != napi_object) {
        HILOG_ERROR("%{public}s, an object is expected, but an argument of different type is passed in.", __func__);
        NapiFormUtil::ThrowParamTypeError(env, "filter", "formInfo.FormInfoFilter");
        return false;
    }

    napi_value nativeDataValue = nullptr;
    napi_status ret = napi_get_named_property(env, jsValue, "moduleName", &nativeDataValue);
    napi_valuetype nativeDataValueType = napi_undefined;
    napi_typeof(env, nativeDataValue, &nativeDataValueType);
    if (nativeDataValue == nullptr || ret != napi_ok || (nativeDataValueType != napi_undefined &&
        !ConvertFromJsValue(env, nativeDataValue, formInfoFilter.moduleName))) {
        HILOG_ERROR("%{public}s called, convert nativeDataValue failed.", __func__);
        NapiFormUtil::ThrowParamError(env, "Failed to convert FormInfoFilter.");
        return false;
    }

    HILOG_INFO("%{public}s called, module name is %{public}s.", __func__, formInfoFilter.moduleName.c_str());

    return true;
}
}

static std::string GetStringByProp(napi_env env, napi_value value, const std::string &prop)
{
    HILOG_DEBUG("GetStringByProp start");
    std::string result;
    bool propExist = false;
    napi_value propValue = nullptr;
    napi_valuetype valueType = napi_undefined;
    napi_has_named_property(env, value, prop.c_str(), &propExist);
    if (!propExist) {
        HILOG_ERROR("%{public}s, prop[%{public}s] absent.", __func__, prop.c_str());
        return result;
    }
    napi_get_named_property(env, value, prop.c_str(), &propValue);
    if (propValue == nullptr) {
        HILOG_ERROR("%{public}s, prop[%{public}s] get error.", __func__, prop.c_str());
        return result;
    }
    napi_typeof(env, propValue, &valueType);
    if (valueType != napi_string) {
        HILOG_ERROR("%{public}s, prop[%{public}s] is not string.", __func__, prop.c_str());
        return result;
    }
    size_t size = 0;
    if (napi_get_value_string_utf8(env, propValue, nullptr, 0, &size) != napi_ok) {
        HILOG_ERROR("%{public}s, prop[%{public}s] get size error.", __func__, prop.c_str());
        return result;
    }
    result.reserve(size + 1);
    result.resize(size);
    if (napi_get_value_string_utf8(env, propValue, result.data(), (size + 1), &size) != napi_ok) {
        HILOG_ERROR("%{public}s, prop[%{public}s] get value error.", __func__, prop.c_str());
        return "";
    }
    return result;
}

void JsFormProvider::Finalizer(napi_env env, void *data, void *hint)
{
    HILOG_INFO("JsFormProvider::Finalizer is called");
    std::unique_ptr<JsFormProvider>(static_cast<JsFormProvider *>(data));
}

napi_value JsFormProvider::GetFormsInfo(napi_env env, napi_callback_info info)
{
    GET_CB_INFO_AND_CALL(env, info, JsFormProvider, OnGetFormsInfo);
}

napi_value JsFormProvider::OnGetFormsInfo(napi_env env, size_t argc, napi_value* argv)
{
    HILOG_DEBUG("%{public}s is called", __FUNCTION__);

    size_t convertArgc = 0;
    bool isPromise = false;
    FormInfoFilter formInfoFilter;
    // GetformsInfo()
    if (argc == ARGS_SIZE_ZERO) {
        isPromise = true;
    }
    if (argc == ARGS_SIZE_ONE) {
        napi_valuetype argvZeroType = napi_undefined;
        napi_typeof(env, argv[0], &argvZeroType);
        if (argvZeroType != napi_undefined) {
            // GetformsInfo(*)
            if (argvZeroType == napi_function) {
                // GetformsInfo(callback)
                isPromise = false;
            } else {
                // GetformsInfo(*);GetformsInfo(fliter)
                if (ConvertFormInfoFilterThrow(env, argv[0], formInfoFilter)) {
                    convertArgc++;
                    isPromise = true;
                } else {
                    // no default value
                    return CreateJsUndefined(env);
                }
            }
        } else {
            isPromise = true;
        }
    }

    if (argc >= ARGS_SIZE_TWO) {
        napi_valuetype argvType = napi_undefined;
        napi_typeof(env, argv[0], &argvType);
        if (argvType != napi_undefined) {
            if (argvType == napi_function) {
                // GetformsInfo(callback, *)
                isPromise = false;
            } else {
                // GetformsInfo(fliter, *) || GetformsInfo(fliter, callback)
                if (ConvertFormInfoFilterThrow(env, argv[0], formInfoFilter)) {
                    convertArgc++;
                    // GetformsInfo(fliter, callback)
                    napi_valuetype typeTwo = napi_undefined;
                    napi_typeof(env, argv[1], &typeTwo);
                    isPromise = typeTwo != napi_function;
                } else {
                    HILOG_ERROR("convert form info filter failed.");
                    return CreateJsUndefined(env);
                }
            }
        } else {
            isPromise = true;
        }
    }

    NapiAsyncTask::CompleteCallback complete =
        [formInfoFilter](napi_env env, NapiAsyncTask &task, int32_t status) {
            std::vector<FormInfo> formInfos;
            auto ret = FormMgr::GetInstance().GetFormsInfo(formInfoFilter, formInfos);
            if (ret != ERR_OK) {
                task.Reject(env, NapiFormUtil::CreateErrorByInternalErrorCode(env, ret));
                return;
            }
            task.ResolveWithNoError(env, CreateJsFormInfoArray(env, formInfos));
        };

    napi_value lastParam = isPromise ? nullptr : argv[convertArgc];
    napi_value result = nullptr;
    NapiAsyncTask::ScheduleWithDefaultQos("JsFormProvider::OnGetFormsInfo",
        env, CreateAsyncTaskWithLastParam(env, lastParam, nullptr, std::move(complete), &result));
    return result;
}

napi_value JsFormProvider::SetFormNextRefreshTime(napi_env env, napi_callback_info info)
{
    GET_CB_INFO_AND_CALL(env, info, JsFormProvider, OnSetFormNextRefreshTime);
}

napi_value JsFormProvider::OnSetFormNextRefreshTime(napi_env env, size_t argc, napi_value* argv)
{
    HILOG_DEBUG("%{public}s is called", __FUNCTION__);
    if (argc < ARGS_SIZE_TWO || argc > ARGS_SIZE_THREE) {
        HILOG_ERROR("wrong number of arguments.");
        NapiFormUtil::ThrowParamNumError(env, std::to_string(argc), "2 or 3");
        return CreateJsUndefined(env);
    }
    napi_valuetype paramZeroType = napi_undefined;
    napi_typeof(env, argv[PARAM0], &paramZeroType);
    if (paramZeroType != napi_string) {
        NapiFormUtil::ThrowParamTypeError(env, "formId", "string");
        return CreateJsUndefined(env);
    }
    int64_t formId = 0;
    std::string strFormId;
    bool confirm = ConvertFromJsValue(env, argv[PARAM0], strFormId);
    if (!confirm) {
        HILOG_ERROR("ConvertFromJsValue failed.");
        NapiFormUtil::ThrowParamTypeError(env, "formId", "string");
        return CreateJsUndefined(env);
    }
    if (!ConvertStringToInt64(strFormId, formId)) {
        HILOG_ERROR("convert form string failed.");
        NapiFormUtil::ThrowParamError(env, "Failed to convert formId.");
        return CreateJsUndefined(env);
    }
    napi_valuetype paramOneType = napi_undefined;
    napi_typeof(env, argv[PARAM1], &paramOneType);
    if (paramOneType != napi_number) {
        NapiFormUtil::ThrowParamTypeError(env, "minute", "number");
        return CreateJsUndefined(env);
    }
    int32_t time;
    bool res = ConvertFromJsValue(env, argv[PARAM1], time);
    if (!res) {
        NapiFormUtil::ThrowParamTypeError(env, "minute", "number");
        return CreateJsUndefined(env);
    }
    NapiAsyncTask::CompleteCallback complete = [formId, time](napi_env env, NapiAsyncTask &task, int32_t status) {
        int32_t ret = FormMgr::GetInstance().SetNextRefreshTime(formId, time);
        if (ret != ERR_OK) {
            task.Reject(env, NapiFormUtil::CreateErrorByInternalErrorCode(env, ret));
            return;
        }
        task.ResolveWithNoError(env, CreateJsUndefined(env));
    };
    napi_value lastParam = (argc == ARGS_SIZE_THREE) ? argv[PARAM2] : nullptr;
    napi_value result = nullptr;
    NapiAsyncTask::ScheduleWithDefaultQos("JsFormProvider::OnSetFormNextRefreshTime",
        env, CreateAsyncTaskWithLastParam(env, lastParam, nullptr, std::move(complete), &result));
    return result;
}

napi_value JsFormProvider::UpdateForm(napi_env env, napi_callback_info info)
{
    GET_CB_INFO_AND_CALL(env, info, JsFormProvider, OnUpdateForm);
}

napi_value JsFormProvider::OnUpdateForm(napi_env env, size_t argc, napi_value* argv)
{
    HILOG_DEBUG("%{public}s is called", __FUNCTION__);
    if (argc < ARGS_SIZE_TWO || argc > ARGS_SIZE_THREE) {
        HILOG_ERROR("wrong number of arguments.");
        NapiFormUtil::ThrowParamNumError(env, std::to_string(argc), "2 or 3");
        return CreateJsUndefined(env);
    }
    napi_valuetype paramZeroType = napi_undefined;
    napi_typeof(env, argv[PARAM0], &paramZeroType);
    if (paramZeroType != napi_string) {
        HILOG_ERROR("formId is not napi_string.");
        NapiFormUtil::ThrowParamTypeError(env, "formId", "string");
        return CreateJsUndefined(env);
    }
    int64_t formId = 0;
    std::string strFormId;
    bool confirm = ConvertFromJsValue(env, argv[PARAM0], strFormId);
    if (!confirm) {
        HILOG_ERROR("ConvertFromJsValue failed.");
        NapiFormUtil::ThrowParamTypeError(env, "formId", "string");
        return CreateJsUndefined(env);
    }
    if (!ConvertStringToInt64(strFormId, formId)) {
        HILOG_ERROR("convert form string failed.");
        NapiFormUtil::ThrowParamError(env, "Failed to convert formId.");
        return CreateJsUndefined(env);
    }
    napi_valuetype paramOneType = napi_undefined;
    napi_typeof(env, argv[PARAM1], &paramOneType);
    if (paramOneType != napi_object) {
        HILOG_ERROR("formBindingData is not napi_object.");
        NapiFormUtil::ThrowParamTypeError(env, "formBindingData", "formBindingData.FormBindingData");
        return CreateJsUndefined(env);
    }
    auto formProviderData = std::make_shared<OHOS::AppExecFwk::FormProviderData>();
    std::string formDataStr = GetStringByProp(env, argv[PARAM1], "data");
    formProviderData->SetDataString(formDataStr);
    formProviderData->ParseImagesData();

    std::vector<AppExecFwk::FormDataProxy> formDataProxies;
    napi_value nativeProxies = nullptr;
    napi_get_named_property(env, argv[PARAM1], "proxies", &nativeProxies);
    if (nativeProxies != nullptr) {
        ConvertFromDataProxies(env, nativeProxies, formDataProxies);
    }

    NapiAsyncTask::CompleteCallback complete =
        [formId, data = formProviderData, formDataProxies](napi_env env, NapiAsyncTask &task, int32_t status) {
            int32_t ret = FormMgr::GetInstance().UpdateForm(formId, *data, formDataProxies);
            if (ret != ERR_OK) {
                task.Reject(env, NapiFormUtil::CreateErrorByInternalErrorCode(env, ret));
                return;
            }
            task.ResolveWithNoError(env, CreateJsUndefined(env));
        };
    napi_value lastParam = (argc == ARGS_SIZE_THREE) ? argv[PARAM2] : nullptr;
    napi_value result = nullptr;
    NapiAsyncTask::ScheduleWithDefaultQos("JsFormProvider::OnUpdateForm",
        env, CreateAsyncTaskWithLastParam(env, lastParam, nullptr, std::move(complete), &result));
    return result;
}

napi_value JsFormProvider::IsRequestPublishFormSupported(napi_env env, napi_callback_info info)
{
    GET_CB_INFO_AND_CALL(env, info, JsFormProvider, OnIsRequestPublishFormSupported);
}

napi_value JsFormProvider::OnIsRequestPublishFormSupported(napi_env env, size_t argc, napi_value* argv)
{
    HILOG_DEBUG("%{public}s is called", __FUNCTION__);

    auto selfToken = IPCSkeleton::GetSelfTokenID();
    if (!Security::AccessToken::TokenIdKit::IsSystemAppByFullTokenID(selfToken)) {
        HILOG_ERROR("This application is not system-app, can not use system-api");
        NapiFormUtil::ThrowByExternalErrorCode(env, ERR_FORM_EXTERNAL_NOT_SYSTEM_APP);
        return CreateJsUndefined(env);
    }

    if (argc > ARGS_SIZE_ONE) {
        HILOG_ERROR("wrong number of arguments.");
        NapiFormUtil::ThrowParamNumError(env, std::to_string(argc), "0 or 1");
        return CreateJsUndefined(env);
    }

    NapiAsyncTask::CompleteCallback complete = [](napi_env env, NapiAsyncTask &task, int32_t status) {
        bool value = FormMgr::GetInstance().IsRequestPublishFormSupported();
        napi_value jsValue = nullptr;
        napi_get_boolean(env, value, &jsValue);
        task.ResolveWithNoError(env, jsValue);
    };
    napi_value lastParam = (argc == ARGS_SIZE_ONE) ? argv[PARAM0] : nullptr;
    napi_value result = nullptr;
    NapiAsyncTask::ScheduleWithDefaultQos("JsFormProvider::OnIsRequestPublishFormSupported",
        env, CreateAsyncTaskWithLastParam(env, lastParam, nullptr, std::move(complete), &result));
    return result;
}

napi_value JsFormProvider::RequestPublishForm(napi_env env, napi_callback_info info)
{
    GET_CB_INFO_AND_CALL(env, info, JsFormProvider, OnRequestPublishForm);
}

napi_value JsFormProvider::OnRequestPublishForm(napi_env env, size_t argc, napi_value* argv)
{
    HILOG_DEBUG("%{public}s is called", __FUNCTION__);
    if (argc < ARGS_SIZE_ONE || argc > ARGS_SIZE_THREE) {
        HILOG_ERROR("wrong number of arguments.");
        NapiFormUtil::ThrowParamNumError(env, std::to_string(argc), "1, 2 or 3");
        return CreateJsUndefined(env);
    }

    auto asyncCallbackInfo = std::make_shared<RequestPublishFormCallbackInfo>();
    decltype(argc) convertArgc = 0;
    napi_valuetype paramZeroType = napi_undefined;
    napi_typeof(env, argv[PARAM0], &paramZeroType);
    if (paramZeroType != napi_object) {
        HILOG_ERROR("formId is not napi_object.");
        NapiFormUtil::ThrowParamTypeError(env, "want", "Want");
        return CreateJsUndefined(env);
    }
    if (!AppExecFwk::UnwrapWant(env, argv[PARAM0], asyncCallbackInfo->want)) {
        HILOG_ERROR("Failed to convert want.");
        NapiFormUtil::ThrowParamError(env, "Failed to convert want.");
        return CreateJsUndefined(env);
    }
    convertArgc++;

    if (argc > ARGS_SIZE_ONE) {
        asyncCallbackInfo->withFormBindingData = true;
        napi_valuetype paramOneType = napi_undefined;
        napi_typeof(env, argv[PARAM1], &paramOneType);
        if (paramOneType != napi_object) {
            HILOG_ERROR("formBindingData is not napi_object.");
            NapiFormUtil::ThrowParamTypeError(env, "formBindingData", "formBindingData.FormBindingData");
            return CreateJsUndefined(env);
        }
        auto formProviderData = std::make_unique<FormProviderData>();
        std::string formDataStr = GetStringByProp(env, argv[PARAM1], "data");
        formProviderData->SetDataString(formDataStr);
        formProviderData->ParseImagesData();
        asyncCallbackInfo->formProviderData = std::move(formProviderData);

        napi_value nativeProxies = nullptr;
        napi_get_named_property(env, argv[PARAM1], "proxies", &nativeProxies);
        if (nativeProxies != nullptr) {
            ConvertFromDataProxies(env, nativeProxies, asyncCallbackInfo->formDataProxies);
        }
        convertArgc++;
    }

    NapiAsyncTask::CompleteCallback complete = [asyncCallbackInfo](napi_env env, NapiAsyncTask &task, int32_t status) {
        int64_t formId = 0;
        ErrCode ret = FormMgr::GetInstance().RequestPublishForm(asyncCallbackInfo->want,
            asyncCallbackInfo->withFormBindingData, asyncCallbackInfo->formProviderData, formId,
            asyncCallbackInfo->formDataProxies);
        if (ret != ERR_OK) {
            task.Reject(env, NapiFormUtil::CreateErrorByInternalErrorCode(env, ret));
            return;
        }
        std::string formIdStr = std::to_string(formId);
        napi_value result = nullptr;
        napi_create_string_utf8(env, formIdStr.c_str(), formIdStr.size(), &result);
        task.ResolveWithNoError(env, result);
    };
    napi_value lastParam = (argc <= convertArgc) ? nullptr : argv[convertArgc];
    napi_value result = nullptr;
    NapiAsyncTask::ScheduleWithDefaultQos("JsFormProvider::OnRequestPublishForm",
        env, CreateAsyncTaskWithLastParam(env, lastParam, nullptr, std::move(complete), &result));
    return result;
}

bool JsFormProvider::ConvertFromDataProxies(napi_env env, napi_value value,
    std::vector<AppExecFwk::FormDataProxy> &formDataProxies)
{
    bool result = false;
    napi_is_array(env, value, &result);
    if (value == nullptr || !result) {
        HILOG_ERROR("%{public}s, jsValue is null not array", __func__);
        return false;
    }

    uint32_t length = 0;
    napi_get_array_length(env, value, &length);
    for (uint32_t i = 0; i < length; i++) {
        AppExecFwk::FormDataProxy formDataProxy("", "");
        napi_value element = nullptr;
        napi_get_element(env, value, i, &element);
        if (!ConvertFormDataProxy(env, element, formDataProxy)) {
            HILOG_ERROR("GetElement from array [%{public}u] error", i);
            continue;
        }
        formDataProxies.push_back(formDataProxy);
    }
    return true;
}

bool JsFormProvider::ConvertFormDataProxy(napi_env env, napi_value value,
    AppExecFwk::FormDataProxy &formDataProxy)
{
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, value, &valueType);
    if (value == nullptr || valueType != napi_object) {
        HILOG_ERROR("%{public}s, jsValue is null not object", __func__);
        return false;
    }

    napi_value key = nullptr;
    napi_get_named_property(env, value, "key", &key);
    if (!ConvertFromJsValue(env, key, formDataProxy.key)) {
        HILOG_ERROR("Parse key error");
        return false;
    }

    napi_value subscribeId = nullptr;
    napi_get_named_property(env, value, "subscriberId", &subscribeId);
    if (subscribeId != nullptr && !ConvertFromJsValue(env, subscribeId, formDataProxy.subscribeId)) {
        HILOG_WARN("Parse subscribeId failed, use empty as default value.");
        formDataProxy.subscribeId = "";
    }
    HILOG_INFO("key is %{public}s, subscribeId is %{public}s", formDataProxy.key.c_str(),
        formDataProxy.subscribeId.c_str());
    return true;
}
}  // namespace AbilityRuntime
}  // namespace OHOS
