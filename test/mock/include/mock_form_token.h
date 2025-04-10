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

#ifndef OHOS_FORM_FWK_MOCK_FORM_TOKEN_H
#define OHOS_FORM_FWK_MOCK_FORM_TOKEN_H

#include "iremote_broker.h"
#include "iremote_object.h"
#include "iremote_proxy.h"
#include "iremote_stub.h"
#include "nocopyable.h"

namespace OHOS {
namespace AppExecFwk {
class IFormToken : public IRemoteBroker {
public:
    DECLARE_INTERFACE_DESCRIPTOR(u"ohos.appexecfwk.FormToken");
};

class MockFormToken : public IRemoteStub<IFormToken> {
public:
    MockFormToken() = default;
    virtual ~MockFormToken() = default;

    virtual int OnRemoteRequest(uint32_t code, MessageParcel &data, MessageParcel &reply, MessageOption &option)
    {
        return 0;
    }

private:
    DISALLOW_COPY_AND_MOVE(MockFormToken);
};

class FormTokenProxy : public IRemoteProxy<IFormToken> {
public:
    explicit FormTokenProxy(const sptr<IRemoteObject> &impl) : IRemoteProxy<IFormToken>(impl)
    {}

    virtual ~FormTokenProxy() = default;

private:
    DISALLOW_COPY_AND_MOVE(FormTokenProxy);
};

DECLARE_INTERFACE_DESCRIPTOR(u"IFormToken");
}  // namespace AppExecFwk
}  // namespace OHOS
#endif  // OHOS_FORM_FWK_MOCK_FORM_TOKEN_H
