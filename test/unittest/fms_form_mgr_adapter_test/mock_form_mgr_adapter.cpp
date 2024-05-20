/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "form_mgr_errors.h"
#include "form_mgr_adapter.h"

namespace {
    bool g_mockRequestPublishFormToHost = true;
}

void MockRequestPublishFormToHost(bool mockRet)
{
    g_mockRequestPublishFormToHost = mockRet;
}

namespace OHOS {
namespace AppExecFwk {

ErrCode CheckPublishForm(Want &want, bool needCheckFormPermission = true)
{
    if (g_mockRequestPublishFormToHost) {
        return ERR_OK;
    }
    return ERR_APPEXECFWK_FORM_COMMON_CODE;
}

ErrCode FormMgrAdapter::RequestPublishFormToHost(Want &want)
{
    if (g_mockRequestPublishFormToHost) {
        return ERR_APPEXECFWK_FORM_COMMON_CODE;
    }
    return ERR_OK;
}
}
}