/*
 * Copyright (c) 2022-2026 Huawei Device Co., Ltd.
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

#include <gtest/gtest.h>
#include <memory>
#include "gmock/gmock.h"
#include "form_mgr_errors.h"
#include "fms_log_wrapper.h"
#include "mock_form_provider_client.h"
#include "mock_form_host_task_mgr.h"
#define private public
#include "bms_mgr/form_bms_helper.h"
#include "form_host/form_host_callback.h"
#undef private

using namespace testing;
using namespace testing::ext;
using namespace OHOS;
using namespace OHOS::AppExecFwk;

namespace {
class FormHostCallbackTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp();
    void TearDown();
};


void FormHostCallbackTest::SetUpTestCase()
{}

void FormHostCallbackTest::TearDownTestCase()
{}

void FormHostCallbackTest::SetUp()
{}

void FormHostCallbackTest::TearDown()
{}
}