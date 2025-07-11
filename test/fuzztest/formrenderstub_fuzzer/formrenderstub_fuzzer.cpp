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

#include "formrenderstub_fuzzer.h"

#include <cstddef>
#include <cstdint>

#define private public
#define protected public
#include "form_render_stub.h"
#undef private
#undef protected
#include "message_parcel.h"
#include "securec.h"

using namespace OHOS::AppExecFwk;

namespace OHOS {
constexpr size_t U32_AT_SIZE = 4;
const std::u16string FORMMGR_INTERFACE_TOKEN = u"ohos.appexecfwk.FormRender";

class FormRenderStubFuzzTest : public FormRenderStub {
public:
    FormRenderStubFuzzTest() = default;
    virtual ~FormRenderStubFuzzTest() = default;
    int32_t RenderForm(const FormJsInfo &formJsInfo, const Want &want,
        sptr<IRemoteObject> callerToken) override
    {
        return 0;
    }

    int32_t StopRenderingForm(
        const FormJsInfo &formJsInfo, const Want &want, const sptr<IRemoteObject> &callerToken) override
    {
        return 0;
    }

    int32_t CleanFormHost(const sptr<IRemoteObject> &hostToken) override
    {
        return 0;
    }

    int32_t ReloadForm(const std::vector<FormJsInfo> &&formJsInfos, const Want &want) override
    {
        return 0;
    }

protected:
    int32_t CheckPermission() override
    {
        return ERR_OK;
    }
};

uint32_t GetU32Data(const char* ptr)
{
    if (ptr == nullptr) {
        return 0;
    }
    // 将第0个数字左移24位，将第1个数字左移16位，将第2个数字左移8位，第3个数字不左移
    return (ptr[0] << 24) | (ptr[1] << 16) | (ptr[2] << 8) | (ptr[3]);
}

bool DoSomethingInterestingWithMyAPI(const char* data, size_t size)
{
    uint32_t code = GetU32Data(data);
    MessageParcel datas;
    datas.WriteInterfaceToken(FORMMGR_INTERFACE_TOKEN);
    datas.WriteBuffer(data, size);
    datas.RewindRead(0);
    MessageParcel reply;
    MessageOption option;
    std::shared_ptr<FormRenderStub> formRenderStub = std::make_shared<FormRenderStubFuzzTest>();
    formRenderStub->OnRemoteRequest(code, datas, reply, option);
    formRenderStub->HandleRenderForm(datas, reply);
    formRenderStub->HandleCleanFormHost(datas, reply);
    formRenderStub->HandleReloadForm(datas, reply);
    formRenderStub->HandleStopRenderingForm(datas, reply);
    formRenderStub->HandleOnUnlock(datas, reply);
    formRenderStub->HandleSetVisibleChange(datas, reply);
    formRenderStub->HandleRecoverForm(datas, reply);
    return true;
}
}

/* Fuzzer entry point */
extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
    /* Run your code on data */
    if (data == nullptr) {
        return 0;
    }

    if (size < OHOS::U32_AT_SIZE) {
        return 0;
    }

    char* ch = static_cast<char*>(malloc(size + 1));
    if (ch == nullptr) {
        return 0;
    }

    (void)memset_s(ch, size + 1, 0x00, size + 1);
    if (memcpy_s(ch, size + 1, data, size) != EOK) {
        free(ch);
        ch = nullptr;
        return 0;
    }

    OHOS::DoSomethingInterestingWithMyAPI(ch, size);
    free(ch);
    ch = nullptr;
    return 0;
}

