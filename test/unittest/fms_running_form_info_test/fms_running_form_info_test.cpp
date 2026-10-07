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

#define private public
#define protected public
#include "running_form_info.h"
#include "fms_log_wrapper.h"
#include "nlohmann/json.hpp"
#undef private
#undef protected

using namespace testing::ext;

namespace OHOS {
namespace AppExecFwk {

class FmsRunningFormInfoTest : public testing::Test {
public:
    static void SetUpTestCase();

    static void TearDownTestCase();

    void SetUp();

    void TearDown();
};
void FmsRunningFormInfoTest::SetUpTestCase() {}

void FmsRunningFormInfoTest::TearDownTestCase() {}

void FmsRunningFormInfoTest::SetUp() {}

void FmsRunningFormInfoTest::TearDown() {}

/**
 * @tc.name: FmsRunningFormInfoTest_002
 * @tc.desc: text the RunningFormInfo::Marshalling
 * @tc.type: FUNC
 * @tc.require: #I5SNG1
 */
HWTEST_F(FmsRunningFormInfoTest, FmsRunningFormInfoTest_002, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FmsRunningFormInfoTest_002 start";
    RunningFormInfo runningFormInfo;
    Parcel parcel;
    auto result = runningFormInfo.Marshalling(parcel);

    EXPECT_TRUE(result);
    GTEST_LOG_(INFO) << "FmsRunningFormInfoTest_002 end";
}
} // namespace AppExecFwk
} // namespace OHOS
