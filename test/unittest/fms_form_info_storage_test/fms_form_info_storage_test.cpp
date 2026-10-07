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

#include <gtest/gtest.h>
#define private public
#define protected public
#include "form_info.h"
#include "data_center/form_info/form_info_storage.h"
#include "form_mgr_errors.h"
#include "nlohmann/json.hpp"
#undef public
#undef protected

using namespace testing::ext;
using namespace OHOS;
using namespace OHOS::AppExecFwk;

namespace OHOS {
namespace AppExecFwk {
class FmsFormInfoStorageTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp();
    void TearDown();
    std::shared_ptr<AAFwk::FormInfoStorage> formInfoStorage_;
};

void FmsFormInfoStorageTest::SetUpTestCase()
{}

void FmsFormInfoStorageTest::TearDownTestCase()
{}

void FmsFormInfoStorageTest::SetUp()
{
    formInfoStorage_ = std::make_shared<AAFwk::FormInfoStorage>();
}

void FmsFormInfoStorageTest::TearDown()
{
    formInfoStorage_ = nullptr;
}

/*
* @tc.name: FmsFormInfoStorageTest_015
* @tc.desc: Test function FormInfoStorage is called
* @tc.type: FUNC
*/
HWTEST_F(FmsFormInfoStorageTest, FmsFormInfoStorageTest_015, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "FmsFormInfoStorageTest_015 start";
    int32_t userId = 1;
    AppExecFwk::FormInfo formInfo = {};
    std::vector<AppExecFwk::FormInfo> formInfos;
    formInfos.emplace_back(formInfo);
    EXPECT_FALSE(formInfos.empty());
    AAFwk::FormInfoStorage formInfoStorage(userId, formInfos);
    GTEST_LOG_(INFO) << "FmsFormInfoStorageTest_015 end";
}

/*
* @tc.name: FmsFormInfoStorageTest_016
* @tc.desc: Test function GetAllFormsInfo is called
* @tc.type: FUNC
*/
HWTEST_F(FmsFormInfoStorageTest, FmsFormInfoStorageTest_016, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "FmsFormInfoStorageTest_016 start";
    int32_t userId = -1;
    std::vector<AppExecFwk::FormInfo> formInfos;
    formInfoStorage_->FormInfoStorage::GetAllFormsInfo(userId, formInfos);
    GTEST_LOG_(INFO) << "FmsFormInfoStorageTest_016 end";
}

/*
* @tc.name: FmsFormInfoStorageTest_017
* @tc.desc: Test function GetAllFormsInfo is called
* @tc.type: FUNC
*/
HWTEST_F(FmsFormInfoStorageTest, FmsFormInfoStorageTest_017, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "FmsFormInfoStorageTest_017 start";
    int32_t userId = 1;
    std::vector<AppExecFwk::FormInfo> formInfos;
    formInfoStorage_->FormInfoStorage::GetAllFormsInfo(userId, formInfos);
    GTEST_LOG_(INFO) << "FmsFormInfoStorageTest_017 end";
}

/*
* @tc.name: FmsFormInfoStorageTest_018
* @tc.desc: Test function GetAllFormsInfo is called
* @tc.type: FUNC
*/
HWTEST_F(FmsFormInfoStorageTest, FmsFormInfoStorageTest_018, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "FmsFormInfoStorageTest_018 start";
    int32_t userId = 1;
    AppExecFwk::FormInfo formInfo1 = {};
    AppExecFwk::FormInfo formInfo2 = {};
    std::vector<AppExecFwk::FormInfo> formInfos;
    formInfoStorage_->userId = 0;
    formInfoStorage_->formInfos.emplace_back(formInfo1);
    formInfoStorage_->formInfos.emplace_back(formInfo2);
    formInfoStorage_->FormInfoStorage::GetAllFormsInfo(userId, formInfos);
    GTEST_LOG_(INFO) << "FmsFormInfoStorageTest_018 end";
}

/*
* @tc.name: FmsFormInfoStorageTest_019
* @tc.desc: Test function GetFormsInfoByModule is called
* @tc.type: FUNC
*/
HWTEST_F(FmsFormInfoStorageTest, FmsFormInfoStorageTest_019, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "FmsFormInfoStorageTest_019 start";
    int32_t userId = 1;
    std::string moduleName = "entry";
    std::vector<AppExecFwk::FormInfo> formInfos;
    formInfoStorage_->FormInfoStorage::GetFormsInfoByModule(userId, moduleName, formInfos);
    GTEST_LOG_(INFO) << "FmsFormInfoStorageTest_019 end";
}

/*
* @tc.name: FmsFormInfoStorageTest_020
* @tc.desc: Test function GetFormsInfoByModule is called
* @tc.type: FUNC
*/
HWTEST_F(FmsFormInfoStorageTest, FmsFormInfoStorageTest_020, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "FmsFormInfoStorageTest_020 start";
    int32_t userId = -1;
    std::string moduleName = "entry";
    std::vector<AppExecFwk::FormInfo> formInfos;
    formInfoStorage_->FormInfoStorage::GetFormsInfoByModule(userId, moduleName, formInfos);
    GTEST_LOG_(INFO) << "FmsFormInfoStorageTest_020 end";
}

/*
* @tc.name: FmsFormInfoStorageTest_021
* @tc.desc: Test function GetFormsInfoByModule is called
* @tc.type: FUNC
*/
HWTEST_F(FmsFormInfoStorageTest, FmsFormInfoStorageTest_021, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "FmsFormInfoStorageTest_021 start";
    int32_t userId = 1;
    std::string moduleName = "entry";
    AppExecFwk::FormInfo formInfo1 = {};
    AppExecFwk::FormInfo formInfo2 = {};
    formInfo1.moduleName = "entry";
    std::vector<AppExecFwk::FormInfo> formInfos;
    formInfoStorage_->userId = 0;
    formInfoStorage_->formInfos.emplace_back(formInfo1);
    formInfoStorage_->formInfos.emplace_back(formInfo2);
    formInfoStorage_->FormInfoStorage::GetFormsInfoByModule(userId, moduleName, formInfos);
    GTEST_LOG_(INFO) << "FmsFormInfoStorageTest_021 end";
}

/*
* @tc.name: FmsFormInfoStorageTest_022
* @tc.desc: Test function to_json and from_json are called
* @tc.type: FUNC
*/
HWTEST_F(FmsFormInfoStorageTest, FmsFormInfoStorageTest_022, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "FmsFormInfoStorageTest_022 start";
    nlohmann::json jsonObject;
    AAFwk::FormInfoStorage formInfoStorage;
    AppExecFwk::FormInfo formInfo = {};
    std::vector<AppExecFwk::FormInfo> formInfos;
    formInfos.emplace_back(formInfo);
    EXPECT_FALSE(formInfos.empty());
    to_json(jsonObject, formInfoStorage);
    from_json(jsonObject, formInfoStorage);
    GTEST_LOG_(INFO) << "FmsFormInfoStorageTest_022 end";
}

/*
* @tc.name: FmsFormInfoStorageTest_023
* @tc.desc: Test function IsEquipmentLevelFiltered
* @tc.type: FUNC
*/
HWTEST_F(FmsFormInfoStorageTest, FmsFormInfoStorageTest_023, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "FmsFormInfoStorageTest_023 start";
    AppExecFwk::FormInfo formInfo;
    EXPECT_FALSE(formInfoStorage_->FormInfoStorage::IsEquipmentLevelFiltered(formInfo));
    GTEST_LOG_(INFO) << "FmsFormInfoStorageTest_023 end";
}

/*
* @tc.name: FmsFormInfoStorageTest_024
* @tc.desc: Test function IsEquipmentLevelFiltered
* @tc.type: FUNC
*/
HWTEST_F(FmsFormInfoStorageTest, FmsFormInfoStorageTest_024, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "FmsFormInfoStorageTest_024 start";
    AppExecFwk::FormInfo formInfo;
    formInfo.supportDeviceTypes = {"123", "456"};
    formInfo.supportDevicePerformanceClasses = {1, 2};
    EXPECT_TRUE(formInfoStorage_->FormInfoStorage::IsEquipmentLevelFiltered(formInfo));
    GTEST_LOG_(INFO) << "FmsFormInfoStorageTest_024 end";
}
}  // namespace AppExecFwk
}  // namespace OHOS