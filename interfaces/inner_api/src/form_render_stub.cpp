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
#include "form_render_stub.h"
#include "appexecfwk_errors.h"
#include "app_scheduler_interface.h"
#include "errors.h"
#include "fms_log_wrapper.h"
#include "form_mgr_errors.h"
#include "ipc_skeleton.h"
#include "ipc_types.h"
#include "iremote_object.h"

namespace OHOS {
namespace AppExecFwk {
namespace {
    constexpr int32_t MAX_ALLOW_SIZE = 8 * 1024;
}

FormRenderStub::FormRenderStub()
{}

FormRenderStub::~FormRenderStub()
{}

int FormRenderStub::OnRemoteRequest(uint32_t code, MessageParcel &data, MessageParcel &reply, MessageOption &option)
{
    HILOG_DEBUG("FormRenderStub::OnReceived,code = %{public}u,flags= %{public}d", code, option.GetFlags());
    std::u16string descriptor = FormRenderStub::GetDescriptor();
    std::u16string remoteDescriptor = data.ReadInterfaceToken();
    if (descriptor != remoteDescriptor) {
        HILOG_ERROR("localDescriptor not equal to remote");
        return ERR_APPEXECFWK_FORM_INVALID_PARAM;
    }

    switch (code) {
        case static_cast<uint32_t>(IFormRender::Message::FORM_RENDER_RENDER_FORM):
            return HandleRenderForm(data, reply);
        case static_cast<uint32_t>(IFormRender::Message::FORM_RENDER_STOP_RENDERING_FORM):
            return HandleStopRenderingForm(data, reply);
        case static_cast<uint32_t>(IFormRender::Message::FORM_RENDER_FORM_HOST_DIED):
            return HandleCleanFormHost(data, reply);
        case static_cast<uint32_t>(IFormRender::Message::FORM_RENDER_RELOAD_FORM):
            return HandleReloadForm(data, reply);
        case static_cast<uint32_t>(IFormRender::Message::FORM_RENDER_RELEASE_RENDERER):
            return HandleReleaseRenderer(data, reply);
        case static_cast<uint32_t>(IFormRender::Message::FORM_RENDER_UNLOCKED):
            return HandleOnUnlock(data, reply);
        case static_cast<uint32_t>(IFormRender::Message::FORM_RECYCLE_FORM):
            return HandleRecycleForm(data, reply);
        case static_cast<uint32_t>(IFormRender::Message::FORM_RECOVER_FORM):
            return HandleRecoverForm(data, reply);
        case static_cast<uint32_t>(IFormRender::Message::FORM_RUN_CACHED_CONFIG):
            RunCachedConfigurationUpdated();
            return ERR_OK;
        case static_cast<uint32_t>(IFormRender::Message::FORM_SET_VISIBLE_CHANGE):
            return HandleSetVisibleChange(data, reply);
        default:
            return IPCObjectStub::OnRemoteRequest(code, data, reply, option);
    }
}

int FormRenderStub::HandleRenderForm(MessageParcel &data, MessageParcel &reply)
{
    std::unique_ptr<FormJsInfo> formJsInfo(data.ReadParcelable<FormJsInfo>());
    if (!formJsInfo) {
        HILOG_ERROR("error to ReadParcelable<formJsInfo>");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }
    std::unique_ptr<Want> want(data.ReadParcelable<Want>());
    if (!want) {
        HILOG_ERROR("error to ReadParcelable<Want>");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }

    sptr<IRemoteObject> client = data.ReadRemoteObject();
    if (client == nullptr) {
        HILOG_ERROR("error to get remote object");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }

    int32_t result = RenderForm(*formJsInfo, *want, client);
    reply.WriteInt32(result);
    return result;
}

int FormRenderStub::HandleStopRenderingForm(MessageParcel &data, MessageParcel &reply)
{
    std::unique_ptr<FormJsInfo> formJsInfo(data.ReadParcelable<FormJsInfo>());
    if (!formJsInfo) {
        HILOG_ERROR("ReadParcelable<formJsInfo> fail");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }
    std::unique_ptr<Want> want(data.ReadParcelable<Want>());
    if (!want) {
        HILOG_ERROR("ReadParcelable<Want> fail");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }

    sptr<IRemoteObject> client = data.ReadRemoteObject();
    if (client == nullptr) {
        HILOG_ERROR("get remote object failed");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }

    int32_t result = StopRenderingForm(*formJsInfo, *want, client);
    reply.WriteInt32(result);
    return result;
}

int FormRenderStub::HandleCleanFormHost(MessageParcel &data, MessageParcel &reply)
{
    sptr<IRemoteObject> hostToken = data.ReadRemoteObject();
    if (hostToken == nullptr) {
        HILOG_ERROR("null hostToken");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }

    int32_t result = CleanFormHost(hostToken);
    reply.WriteInt32(result);
    return result;
}

int32_t FormRenderStub::HandleReleaseRenderer(MessageParcel &data, MessageParcel &reply)
{
    int64_t formId = data.ReadInt64();
    std::string compId = data.ReadString();
    std::string uid = data.ReadString();
    int32_t result = ReleaseRenderer(formId, compId, uid);
    reply.WriteInt32(result);
    return result;
}

int FormRenderStub::HandleReloadForm(MessageParcel &data, MessageParcel &reply)
{
    std::vector<FormJsInfo> formJsInfos;
    int32_t result = GetParcelableInfos(data, formJsInfos);
    if (result != ERR_OK) {
        HILOG_ERROR("fail GetParcelableInfos<FormJsInfo>");
        return result;
    }

    std::unique_ptr<Want> want(data.ReadParcelable<Want>());
    if (!want) {
        HILOG_ERROR("ReadParcelable<Want> failed");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }

    result = ReloadForm(std::move(formJsInfos), *want);
    reply.WriteInt32(result);
    return result;
}

int32_t FormRenderStub::HandleOnUnlock(MessageParcel &data, MessageParcel &reply)
{
    int32_t result = OnUnlock();
    reply.WriteInt32(result);
    return result;
}

int32_t FormRenderStub::HandleSetVisibleChange(MessageParcel &data, MessageParcel &reply)
{
    HILOG_ERROR("begin");
    int64_t formId = data.ReadInt64();
    bool isVisible = data.ReadBool();
    std::unique_ptr<Want> want(data.ReadParcelable<Want>());
    if (!want) {
        HILOG_ERROR("error to ReadParcelable<Want>");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }
    int32_t result = SetVisibleChange(formId, isVisible, *want);
    reply.WriteInt32(result);
    HILOG_ERROR("end");
    return result;
}

template<typename T>
int32_t FormRenderStub::GetParcelableInfos(MessageParcel &reply, std::vector<T> &parcelableInfos)
{
    int32_t infoSize = reply.ReadInt32();
    if (infoSize < 0 || infoSize > MAX_ALLOW_SIZE) {
        HILOG_ERROR("invalid size:%{public}d", infoSize);
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }

    for (int32_t i = 0; i < infoSize; i++) {
        std::unique_ptr<T> info(reply.ReadParcelable<T>());
        if (!info) {
            HILOG_ERROR("Read Parcelable infos error");
            return ERR_APPEXECFWK_PARCEL_ERROR;
        }
        parcelableInfos.emplace_back(*info);
    }
    return ERR_OK;
}

int32_t FormRenderStub::HandleRecycleForm(MessageParcel &data, MessageParcel &reply)
{
    int64_t formId = data.ReadInt64();
    std::unique_ptr<Want> want(data.ReadParcelable<Want>());
    if (!want) {
        HILOG_ERROR("error to ReadParcelable<Want>");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }
    int32_t result = RecycleForm(formId, *want);
    reply.WriteInt32(result);
    return result;
}

int32_t FormRenderStub::HandleRecoverForm(MessageParcel &data, MessageParcel &reply)
{
    std::unique_ptr<FormJsInfo> formJsInfo(data.ReadParcelable<FormJsInfo>());
    if (!formJsInfo) {
        HILOG_ERROR("read FormJsInfo error");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }
    std::unique_ptr<Want> want(data.ReadParcelable<Want>());
    if (!want) {
        HILOG_ERROR("read want error");
        return ERR_APPEXECFWK_PARCEL_ERROR;
    }
    int32_t result = RecoverForm(*formJsInfo, *want);
    reply.WriteInt32(result);
    return result;
}
}  // namespace AppExecFwk
}  // namespace OHOS
