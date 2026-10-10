/*
 * Copyright (c) 2023-2026 Huawei Device Co., Ltd.
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

#include <chrono>
#include <dirent.h>
#include <fstream>
#include <gtest/gtest.h>
#include <string>
#include <thread>

#include "form_constants.h"
#include "form_mgr_errors.h"
#define private public
#include "form_render/form_render_connection.h"
#undef private
#include "ipc_types.h"
#include "fms_log_wrapper.h"

using namespace testing::ext;
using namespace OHOS;
using namespace OHOS::AppExecFwk;

extern void MockGetCompileMode(bool mockRet);

namespace {
class FmsFormRenderConnectionTest : public testing::Test {
public:
    void SetUp();
    void TearDown();
};

void FmsFormRenderConnectionTest::SetUp()
{}

void FmsFormRenderConnectionTest::TearDown()
{}

/**
 * @tc.name: OnAbilityConnectDone_001
 * @tc.desc: Test OnAbilityConnectDone with null remoteObject posts failed task while failedTimes within limit.
 * @tc.type: FUNC
 */
HWTEST_F(FmsFormRenderConnectionTest, OnAbilityConnectDone_001, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "OnAbilityConnectDone_001 start";
    FormRecord formRecord;
    formRecord.formId = 1;
    formRecord.bundleName = "com.test.bundle";
    WantParams wantParams;
    sptr<FormRenderConnection> connection = new FormRenderConnection(formRecord, wantParams);
    ElementName element;
    connection->OnAbilityConnectDone(element, nullptr, ERR_OK);
    EXPECT_EQ(1, connection->failedTimes.load());
    GTEST_LOG_(INFO) << "OnAbilityConnectDone_001 end";
}

/**
 * @tc.name: OnAbilityConnectDone_002
 * @tc.desc: Test OnAbilityConnectDone stops posting failed task once failedTimes exceeds limit.
 * @tc.type: FUNC
 */
HWTEST_F(FmsFormRenderConnectionTest, OnAbilityConnectDone_002, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "OnAbilityConnectDone_002 start";
    FormRecord formRecord;
    formRecord.formId = 1;
    formRecord.bundleName = "com.test.bundle";
    WantParams wantParams;
    sptr<FormRenderConnection> connection = new FormRenderConnection(formRecord, wantParams);
    // MAX_FAILED_TIMES is 5 in form_render_connection.cpp; preset the counter to it.
    connection->failedTimes.store(5);
    ElementName element;
    connection->OnAbilityConnectDone(element, nullptr, ERR_OK);
    EXPECT_EQ(6, connection->failedTimes.load());
    GTEST_LOG_(INFO) << "OnAbilityConnectDone_002 end";
}
}  // namespace
