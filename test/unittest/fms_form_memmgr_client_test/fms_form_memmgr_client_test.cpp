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

#include "gtest/gtest.h"

#include <dlfcn.h>
#include "form_memmgr_client.h"
#include "fms_log_wrapper.h"

using namespace testing::ext;

namespace OHOS {
namespace AppExecFwk {
class FmsFormMemmgrClientTest : public testing::Test {
public:
    static void SetUpTestCase();

    static void TearDownTestCase();

    void SetUp();

    void TearDown();
};

void FmsFormMemmgrClientTest::SetUpTestCase()
{
    GTEST_LOG_(INFO) << "FmsFormMemmgrClientTest SetUpTestCase";
}

void FmsFormMemmgrClientTest::TearDownTestCase()
{
    GTEST_LOG_(INFO) << "FmsFormMemmgrClientTest TearDownTestCase";
}

void FmsFormMemmgrClientTest::SetUp() {}

void FmsFormMemmgrClientTest::TearDown() {}

/*
* @tc.number: FmsFormMemmgrClientTest_001
* @tc.name: SetCritical
* @tc.desc: Verify that the SetCritical interface executes normally and exits without exception.
*/
HWTEST_F(FmsFormMemmgrClientTest, FmsFormMemmgrClientTest_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "FmsFormMemmgrClientTest_001 start";
    FormMemmgrClient::GetInstance().SetCritical(false);
    EXPECT_EQ(false, FormMemmgrClient::GetInstance().IsCritical());
    GTEST_LOG_(INFO) << "FmsFormMemmgrClientTest_001 end";
}

/*
 * @tc.number: FmsFormMemmgrClientTest_002
 * @tc.name: SetCritical
 * @tc.desc: SetCritical
 */
HWTEST_F(FmsFormMemmgrClientTest, FmsFormMemmgrClientTest_002, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "FmsFormMemmgrClientTest_002 start";
    // No permission to set critical, so critical is false
    FormMemmgrClient::GetInstance().SetCritical(true);
    EXPECT_EQ(false, FormMemmgrClient::GetInstance().IsCritical());
    GTEST_LOG_(INFO) << "FmsFormMemmgrClientTest_002 end";
}
}  // namespace AppExecFwk
}  // namespace OHOS