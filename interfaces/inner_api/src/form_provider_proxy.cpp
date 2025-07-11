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
#include "form_provider_proxy.h"
#include "appexecfwk_errors.h"
#include "string_ex.h"

namespace OHOS {
namespace AppExecFwk {
namespace {
    static constexpr int32_t MAX_ALLOW_SIZE = 8 * 1024;
}
int FormProviderProxy::AcquireProviderFormInfo(
    const FormJsInfo &formJsInfo,
    const Want &want,
    const sptr<IRemoteObject> &callerToken)
{
    int error;
    MessageParcel data;
    MessageParcel reply;
    MessageOption option(MessageOption::TF_ASYNC);

    if (!WriteInterfaceToken(data)) {
        HILOG_ERROR("write interface token failed");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }
    if (!data.WriteParcelable(&formJsInfo)) {
        HILOG_ERROR("write formJsInfo error");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }
    if (!data.WriteParcelable(&want)) {
        HILOG_ERROR("write want fail");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }

    if (!data.WriteRemoteObject(callerToken)) {
        HILOG_ERROR("write callerToken fail");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }

    error = SendTransactCmd(
        IFormProvider::Message::FORM_ACQUIRE_PROVIDER_FORM_INFO,
        data,
        reply,
        option);
    if (error != ERR_OK) {
        HILOG_ERROR("SendRequest:%{public}d failed", error);
        return error;
    }
    return ERR_OK;
}

/**
 * @brief Notify provider when the form was deleted.
 * @param formIds The id list of forms.
 * @param want Indicates the structure containing form info.
 * @param callerToken Caller ability token.
 * @return Returns ERR_OK on success, others on failure.
 */
int FormProviderProxy::NotifyFormDelete(const int64_t formId, const Want &want, const sptr<IRemoteObject> &callerToken)
{
    int error;
    MessageParcel data;
    MessageParcel reply;
    MessageOption option(MessageOption::TF_ASYNC);

    if (!WriteInterfaceToken(data)) {
        HILOG_ERROR("error to write interface token");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }
    if (!data.WriteInt64(formId)) {
        HILOG_ERROR("error to write formId");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }
    if (!data.WriteParcelable(&want)) {
        HILOG_ERROR("error to write want");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }
    if (!data.WriteRemoteObject(callerToken)) {
        HILOG_ERROR("error to write callerToken");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }

    error = SendTransactCmd(
        IFormProvider::Message::FORM_PROVIDER_NOTIFY_FORM_DELETE,
        data,
        reply,
        option);
    if (error != ERR_OK) {
        HILOG_ERROR("SendRequest:%{public}d failed", error);
        return error;
    }
    return ERR_OK;
}
/**
 * @brief Notify provider when the forms was deleted.
 * @param formIds The id list of forms.
 * @param want Indicates the structure containing form info.
 * @param callerToken Caller ability token.
 * @return Returns ERR_OK on success, others on failure.
 */
int FormProviderProxy::NotifyFormsDelete(
    const std::vector<int64_t> &formIds,
    const Want &want,
    const sptr<IRemoteObject> &callerToken)
{
    int error;
    MessageParcel data;
    MessageParcel reply;
    MessageOption option(MessageOption::TF_ASYNC);

    if (!WriteInterfaceToken(data)) {
        HILOG_ERROR("write interface token failed");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }
    if (!data.WriteInt64Vector(formIds)) {
        HILOG_ERROR("write formIds failed");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }
    if (!data.WriteParcelable(&want)) {
        HILOG_ERROR("write to want error");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }
    if (!data.WriteRemoteObject(callerToken)) {
        HILOG_ERROR("write to callerToken error");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }

    error = SendTransactCmd(
        IFormProvider::Message::FORM_PROVIDER_NOTIFY_FORMS_DELETE,
        data,
        reply,
        option);
    if (error != ERR_OK) {
        HILOG_ERROR("SendRequest:%{public}d failed", error);
        return error;
    }
    return ERR_OK;
}

/**
 * @brief Notify provider when the form need update.
 * @param formId The Id of the form.
 * @param want Indicates the structure containing form info.
 * @param callerToken Caller ability token.
 * @return Returns ERR_OK on success, others on failure.
 */
int FormProviderProxy::NotifyFormUpdate(const int64_t formId, const Want &want, const sptr<IRemoteObject> &callerToken)
{
    int error;
    MessageParcel data;
    MessageParcel reply;
    MessageOption option(MessageOption::TF_ASYNC);

    if (!WriteInterfaceToken(data)) {
        HILOG_ERROR("write interface token failed");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }
    if (!data.WriteInt64(formId)) {
        HILOG_ERROR("write formId failed");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }

    if (!data.WriteParcelable(&want)) {
        HILOG_ERROR("write want failed");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }

    if (!data.WriteRemoteObject(callerToken)) {
        HILOG_ERROR("write callerToken failed");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }

    error = SendTransactCmd(
        IFormProvider::Message::FORM_PROVIDER_NOTIFY_FORM_UPDATE,
        data,
        reply,
        option);
    if (error != ERR_OK) {
        HILOG_ERROR("SendRequest:%{public}d failed", error);
        return error;
    }
    return ERR_OK;
}

/**
 * @brief Event notify when change the form visible.
 *
 * @param formIds The vector of form ids.
 * @param formVisibleType The form visible type, including FORM_VISIBLE and FORM_INVISIBLE.
 * @param want Indicates the structure containing form info.
 * @param callerToken Caller ability token.
 * @return Returns ERR_OK on success, others on failure.
 */
int FormProviderProxy::EventNotify(const std::vector<int64_t> &formIds, const int32_t formVisibleType,
    const Want &want, const sptr<IRemoteObject> &callerToken)
{
    int error;
    MessageParcel data;
    MessageParcel reply;
    MessageOption option(MessageOption::TF_ASYNC);

    if (!WriteInterfaceToken(data)) {
        HILOG_ERROR("write interface token failed");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }

    if (!data.WriteInt64Vector(formIds)) {
        HILOG_ERROR("fail write formIds");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }

    if (!data.WriteInt32(formVisibleType)) {
        HILOG_ERROR("fail write formVisibleType");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }

    if (!data.WriteParcelable(&want)) {
        HILOG_ERROR("errpr to write want");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }

    if (!data.WriteRemoteObject(callerToken)) {
        HILOG_ERROR("error to write callerToken");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }

    error = SendTransactCmd(
        IFormProvider::Message::FORM_PROVIDER_EVENT_NOTIFY,
        data,
        reply,
        option);
    if (error != ERR_OK) {
        HILOG_ERROR("SendRequest:%{public}d failed", error);
        return error;
    }
    return ERR_OK;
}

/**
 * @brief Notify provider when the temp form was cast to normal form.
 * @param formId The Id of the form to update.
 * @param want Indicates the structure containing form info.
 * @param callerToken Caller ability token.
 * @return Returns ERR_OK on success, others on failure.
 */
int FormProviderProxy::NotifyFormCastTempForm(
    const int64_t formId,
    const Want &want,
    const sptr<IRemoteObject> &callerToken)
{
    int error;
    MessageParcel data;
    MessageParcel reply;
    MessageOption option(MessageOption::TF_ASYNC);

    if (!WriteInterfaceToken(data)) {
        HILOG_ERROR("write interface token failed");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }

    if (!data.WriteInt64(formId)) {
        HILOG_ERROR("write formId failed");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }
    if (!data.WriteParcelable(&want)) {
        HILOG_ERROR("write want failed");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }
    if (!data.WriteRemoteObject(callerToken)) {
        HILOG_ERROR("write callerToken failed");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }

    error = SendTransactCmd(
        IFormProvider::Message::FORM_PROVIDER_NOTIFY_TEMP_FORM_CAST,
        data,
        reply,
        option);
    if (error != ERR_OK) {
        HILOG_ERROR("SendRequest:%{public}d failed", error);
        return error;
    }
    return ERR_OK;
}

/**
 * @brief Notify provider when system configuration changed.
 * @param configuration system configuration.
 * @param want Indicates the structure containing form info.
 * @param callerToken Caller ability token.
 * @return Returns ERR_OK on success, others on failure.
 */
int FormProviderProxy::NotifyConfigurationUpdate(
    const AppExecFwk::Configuration& configuration,
    const Want &want,
    const sptr<IRemoteObject> &callerToken)
{
    int error;
    MessageParcel data;
    MessageParcel reply;
    MessageOption option(MessageOption::TF_ASYNC);

    if (!WriteInterfaceToken(data)) {
        HILOG_ERROR("write interface token failed");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }

    if (!data.WriteParcelable(&configuration)) {
        HILOG_ERROR("write configuration failed");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }
    if (!data.WriteParcelable(&want)) {
        HILOG_ERROR("write want failed");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }
    if (!data.WriteRemoteObject(callerToken)) {
        HILOG_ERROR("write callerToken failed");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }

    error = SendTransactCmd(
        IFormProvider::Message::FORM_PROVIDER_NOTIFY_CONFIGURATION_UPDATE,
        data,
        reply,
        option);
    if (error != ERR_OK) {
        HILOG_ERROR("SendRequest:%{public}d failed", error);
        return error;
    }
    return ERR_OK;
}

/**
 * @brief Fire message event to form provider.
 * @param formId The Id of the from.
 * @param message Event message.
 * @param want The want of the request.
 * @param callerToken Form provider proxy object.
 * @return Returns ERR_OK on success, others on failure.
 */
int FormProviderProxy::FireFormEvent(
    const int64_t formId,
    const std::string &message,
    const Want &want,
    const sptr<IRemoteObject> &callerToken)
{
    MessageParcel data;
    if (!WriteInterfaceToken(data)) {
        HILOG_ERROR("write interface token failed");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }
    if (!data.WriteInt64(formId)) {
        HILOG_ERROR("write formId failed");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }
    if (!data.WriteString(message)) {
        HILOG_ERROR("fail write message");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }
    if (!data.WriteParcelable(&want)) {
        HILOG_ERROR("write to want failed");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }
    if (!data.WriteRemoteObject(callerToken)) {
        HILOG_ERROR("write to callerToken failed");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }
    MessageParcel reply;
    MessageOption option(MessageOption::TF_ASYNC);
    int error = SendTransactCmd(
        IFormProvider::Message::FORM_PROVIDER_EVENT_MESSAGE,
        data,
        reply,
        option);
    if (error != ERR_OK) {
        HILOG_ERROR("SendRequest:%{public}d failed", error);
        return error;
    }
    return ERR_OK;
}

/**
 * @brief Acquire form state to form provider.
 * @param wantArg The want of onAcquireFormState.
 * @param provider The provider info.
 * @param want The want of the request.
 * @param callerToken Form provider proxy object.
 * @return Returns ERR_OK on success, others on failure.
 */
int FormProviderProxy::AcquireState(const Want &wantArg, const std::string &provider, const Want &want,
                                    const sptr<IRemoteObject> &callerToken)
{
    int error;
    MessageParcel data;
    MessageParcel reply;
    MessageOption option(MessageOption::TF_ASYNC);

    if (!WriteInterfaceToken(data)) {
        HILOG_ERROR("write interface token failed");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }

    if (!data.WriteParcelable(&wantArg)) {
        HILOG_ERROR("write wantArg failed");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }
    if (!data.WriteString(provider)) {
        HILOG_ERROR("write string failed");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }
    if (!data.WriteParcelable(&want)) {
        HILOG_ERROR("write want failed");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }
    if (!data.WriteRemoteObject(callerToken)) {
        HILOG_ERROR("write callerToken failed");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }

    error = SendTransactCmd(
        IFormProvider::Message::FORM_PROVIDER_NOTIFY_STATE_ACQUIRE,
        data,
        reply,
        option);
    if (error != ERR_OK) {
        HILOG_ERROR("SendRequest:%{public}d failed", error);
        return error;
    }
    return ERR_OK;
}

int32_t FormProviderProxy::AcquireFormData(int64_t formId, const sptr<IRemoteObject> &formSupplyCallback,
                                           int64_t requestCode)
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option(MessageOption::TF_ASYNC);

    if (!WriteInterfaceToken(data)) {
        HILOG_ERROR("write interface token failed");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }

    if (!data.WriteInt64(formId)) {
        HILOG_ERROR("write formId failed");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }

    if (!data.WriteRemoteObject(formSupplyCallback)) {
        HILOG_ERROR("fail write formSupplyCallback");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }

    if (!data.WriteInt64(requestCode)) {
        HILOG_ERROR("write requestCode failed");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }
    int32_t result = SendTransactCmd(
        IFormProvider::Message::FORM_ACQUIRE_PROVIDER_FOMR_DATA,
        data,
        reply,
        option);
    if (result != ERR_OK) {
        HILOG_ERROR("error to SendRequest:%{public}d", result);
        return result;
    }

    auto retval = reply.ReadInt32();
    if (retval != ERR_OK) {
        HILOG_ERROR("error to replyData:%{public}d", retval);
    }

    return retval;
}

template<typename T>
int  FormProviderProxy::GetParcelableInfos(MessageParcel &reply, std::vector<T> &parcelableInfos)
{
    int32_t infoSize = reply.ReadInt32();
    if (infoSize < 0 || infoSize > MAX_ALLOW_SIZE) {
        HILOG_ERROR("invalid size:%{public}d", infoSize);
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }
    for (int32_t i = 0; i < infoSize; i++) {
        std::unique_ptr<T> info(reply.ReadParcelable<T>());
        if (!info) {
            HILOG_ERROR("read Parcelable infos failed");
            return ERR_NULL_OBJECT;
        }
        parcelableInfos.emplace_back(*info);
    }
    HILOG_INFO("get success");
    return ERR_OK;
}

bool  FormProviderProxy::WriteInterfaceToken(MessageParcel &data)
{
    if (!data.WriteInterfaceToken(FormProviderProxy::GetDescriptor())) {
        HILOG_ERROR("write interface token failed");
        return false;
    }
    return true;
}

int32_t FormProviderProxy::AcquireShareFormData(int64_t formId, const std::string &remoteDeviceId,
    const sptr<IRemoteObject> &formSupplyCallback, int64_t requestCode)
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option(MessageOption::TF_ASYNC);

    if (!WriteInterfaceToken(data)) {
        HILOG_ERROR("write interface token failed");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }

    if (!data.WriteInt64(formId)) {
        HILOG_ERROR("write formId failed");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }

    if (!data.WriteString(remoteDeviceId)) {
        HILOG_ERROR("fail write remoteDeviceId");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }

    if (!data.WriteRemoteObject(formSupplyCallback)) {
        HILOG_ERROR("fail write formSupplyCallback");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }

    if (!data.WriteInt64(requestCode)) {
        HILOG_ERROR("write requestCode failed");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }
    int32_t result = SendTransactCmd(
        IFormProvider::Message::FORM_ACQUIRE_PROVIDER_SHARE_FOMR_INFO,
        data,
        reply,
        option);
    if (result != ERR_OK) {
        HILOG_ERROR("fail SendRequest:%{public}d", result);
        return result;
    }

    auto retval = reply.ReadInt32();
    if (retval != ERR_OK) {
        HILOG_ERROR("fail replyData:%{public}d", retval);
    }

    return retval;
}

int FormProviderProxy::SendTransactCmd(IFormProvider::Message code, MessageParcel &data,
    MessageParcel &reply, MessageOption &option)
{
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        HILOG_ERROR("null remote");
        return ERR_NULL_OBJECT;
    }

    int ret = remote->SendRequest(static_cast<uint32_t>(code), data, reply, option);
    if (ret != ERR_OK) {
        HILOG_ERROR("SendRequest fail.code= %{public}d,ret= %{public}d", code, ret);
        return ret;
    }
    return ERR_OK;
}

/**
 * @brief Notify provider when the form need update.
 * @param formId The Id of the form.
 * @param want Indicates the structure containing form info.
 * @param callerToken Caller ability token.
 * @return Returns ERR_OK on success, others on failure.
 */
int FormProviderProxy::NotifyFormLocationUpdate(const int64_t formId, const Want &want,
    const sptr<IRemoteObject> &callerToken)
{
    int error;
    MessageParcel data;
    MessageParcel reply;
    MessageOption option(MessageOption::TF_ASYNC);
 
    if (!WriteInterfaceToken(data)) {
        HILOG_ERROR("write interface token failed");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }
    if (!data.WriteInt64(formId)) {
        HILOG_ERROR("write formId failed");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }
 
    if (!data.WriteParcelable(&want)) {
        HILOG_ERROR("write want failed");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }
 
    if (!data.WriteRemoteObject(callerToken)) {
        HILOG_ERROR("write callerToken failed");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }
 
    error = SendTransactCmd(
        IFormProvider::Message::FORM_PROVIDER_NOTIFY_FORM_LOCATION_UPDATE,
        data,
        reply,
        option);
    if (error != ERR_OK) {
        HILOG_ERROR("SendRequest:%{public}d failed", error);
        return error;
    }
    return ERR_OK;
}

/**
 * @brief Notify provider when the form size changed.
 * @param formId The Id of the form to update.
 * @param newDimension The dimension value to be updated.
 * @param newRect The rect value to be updated.
 * @param want Indicates the structure containing form info.
 * @param callerToken Caller ability token.
 * @return Returns ERR_OK on success, others on failure.
 */
int FormProviderProxy::NotifySizeChanged(const int64_t formId, const int32_t newDimension, const Rect &newRect,
    const Want &want, const sptr<IRemoteObject> &callerToken)
{
    int error;
    MessageParcel data;
    MessageParcel reply;
    MessageOption option(MessageOption::TF_ASYNC);
    if (!WriteInterfaceToken(data)) {
        HILOG_ERROR("write interface token failed");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }
    if (!data.WriteInt64(formId)) {
        HILOG_ERROR("write formId failed");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }
    if (!data.WriteInt32(newDimension)) {
        HILOG_ERROR("Write newDimension failed");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }
    if (!data.WriteParcelable(&newRect)) {
        HILOG_ERROR("write newRect failed");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }
    if (!data.WriteParcelable(&want)) {
        HILOG_ERROR("write want failed");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }
    if (!data.WriteRemoteObject(callerToken)) {
        HILOG_ERROR("write callerToken failed");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }
    error = SendTransactCmd(
        IFormProvider::Message::FORM_PROVIDER_NOTIFY_SIZE_CHANGED,
        data,
        reply,
        option);
    if (error != ERR_OK) {
        HILOG_ERROR("SendRequest:%{public}d failed", error);
        return error;
    }
    return ERR_OK;
}
}  // namespace AppExecFwk
}  // namespace OHOS
