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

#include "mock_form_data_mgr.h"
#include <gtest/gtest.h>

#include "fms_log_wrapper.h"
#include "data_center/form_data_mgr.h"

namespace OHOS {
namespace AppExecFwk {
std::shared_ptr<MockFormDataMgr> MockFormDataMgr::obj = nullptr;

bool FormDataMgr::GetFormRecord(const int64_t formId, FormRecord &formRecord) const
{
    GTEST_LOG_(INFO) << "GetFormRecord called";
    if (AppExecFwk::MockFormDataMgr::obj) {
        return AppExecFwk::MockFormDataMgr::obj->GetFormRecord(formId, formRecord);
    }
    formRecord = FormRecord();
    return false;
}

void FormDataMgr::CheckForms(const std::vector<int64_t> &formIds)
{
    GTEST_LOG_(INFO) << "CheckForms called";
    if (AppExecFwk::MockFormDataMgr::obj) {
        AppExecFwk::MockFormDataMgr::obj->CheckForms(formIds);
    }
}

bool FormDataMgr::GetUpdatedForm(const FormRecord &record, const std::vector<FormInfo> &targetForms,
    FormInfo &updatedForm)
{
    GTEST_LOG_(INFO) << "GetUpdatedForm called";
    if (AppExecFwk::MockFormDataMgr::obj) {
        return AppExecFwk::MockFormDataMgr::obj->GetUpdatedForm(record, targetForms, updatedForm);
    }
    updatedForm = FormInfo();
    return false;
}

void FormDataMgr::SetNeedRefresh(const int64_t formId, const bool needRefresh)
{
    GTEST_LOG_(INFO) << "SetNeedRefresh called";
    if (AppExecFwk::MockFormDataMgr::obj) {
        AppExecFwk::MockFormDataMgr::obj->SetNeedRefresh(formId, needRefresh);
    }
}

bool FormDataMgr::SetRecordNeedFreeInstall(int64_t formId, bool isNeedFreeInstall)
{
    GTEST_LOG_(INFO) << "SetRecordNeedFreeInstall called";
    if (AppExecFwk::MockFormDataMgr::obj) {
        return AppExecFwk::MockFormDataMgr::obj->SetRecordNeedFreeInstall(formId, isNeedFreeInstall);
    }
    return false;
}
}  // namespace AppExecFwk
}  // namespace OHOS