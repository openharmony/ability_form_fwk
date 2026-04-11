/*
 * Copyright (c) 2021-2026 Huawei Device Co., Ltd.
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
#include <fcntl.h>
#include <fstream>
#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <sys/mman.h>
#include <thread>
#include <unistd.h>

#include "buffer_handle_parcel.h"
#include "ipc_file_descriptor.h"
#include "nlohmann/json.hpp"
#include "string_ex.h"

#include "fms_log_wrapper.h"
#define private public
#include "form_provider_data.h"
#undef private

using namespace testing::ext;

namespace OHOS::AppExecFwk {
const std::string FORM_DB_DATA_BASE_FILE_DIR = "/data/formmgr";
const int32_t TEN = 10;
const int32_t ELEVEN = 11;
const int32_t DEFAULT_VALUE = 0;  // Used to adapt functional code.

class FmsFormProviderDataTest : public testing::Test {
public:
    void SetUp();
    void Test();
    bool InitJsonData();
    bool InitJsonData2();

    nlohmann::json jsonData_;
};
void FmsFormProviderDataTest::SetUp()
{
    jsonData_.clear();
    DIR *dirptr = opendir(FORM_DB_DATA_BASE_FILE_DIR.c_str());
    if (dirptr == nullptr) {
        HILOG_WARN("%{public}s, opendir is fail", __func__);
        if (mkdir(FORM_DB_DATA_BASE_FILE_DIR.c_str(), S_IRWXU) == -1) {
            HILOG_ERROR("%{public}s, dir create fail", __func__);
            return;
        }
    } else {
        closedir(dirptr);
    }
}

bool FmsFormProviderDataTest::InitJsonData()
{
    jsonData_.clear();
    nlohmann::json tmpJson;
    tmpJson["name"] = "li";
    tmpJson["age"] = TEN;
    jsonData_["0"] = tmpJson;
    return true;
}

bool FmsFormProviderDataTest::InitJsonData2()
{
    jsonData_.clear();
    nlohmann::json tmpJson;
    tmpJson["name"] = "wang";
    tmpJson["age"] = ELEVEN;
    jsonData_["1"] = tmpJson;
    return true;
}

/**
 * @tc.name: GetDataString_Normal_001
 * @tc.type: FUNC
 * @tc.desc: Verify the GetDataString function.
 */
HWTEST_F(FmsFormProviderDataTest, GetDataString_Normal_001, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "GetDataString_Normal_001 start";
    InitJsonData();
    FormProviderData formProviderData(jsonData_);
    auto result = formProviderData.GetDataString();
    EXPECT_FALSE(result.empty());
    GTEST_LOG_(INFO) << "GetDataString_Normal_001 end";
}

/**
 * @tc.name: MergeData_Normal_001
 * @tc.type: FUNC
 * @tc.desc: Verify the MergeData function merges additional json data correctly.
 */
HWTEST_F(FmsFormProviderDataTest, MergeData_Normal_001, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "MergeData_Normal_001 start";
    InitJsonData();
    FormProviderData formProviderData(jsonData_);
    
    EXPECT_EQ(formProviderData.jsonFormProviderData_.size(), 1);
    EXPECT_TRUE(formProviderData.jsonFormProviderData_.contains("0"));
    
    InitJsonData2();
    formProviderData.MergeData(jsonData_);
    
    EXPECT_EQ(formProviderData.jsonFormProviderData_.size(), 2);
    EXPECT_TRUE(formProviderData.jsonFormProviderData_.contains("0"));
    EXPECT_TRUE(formProviderData.jsonFormProviderData_.contains("1"));
    
    EXPECT_EQ(formProviderData.jsonFormProviderData_["0"]["name"], "li");
    EXPECT_EQ(formProviderData.jsonFormProviderData_["0"]["age"], TEN);
    EXPECT_EQ(formProviderData.jsonFormProviderData_["1"]["name"], "wang");
    EXPECT_EQ(formProviderData.jsonFormProviderData_["1"]["age"], ELEVEN);
    
    GTEST_LOG_(INFO) << "MergeData_Normal_001 end";
}

/**
 * @tc.name: EnableDbCache_IsDbCacheEnabled_001
 * @tc.type: FUNC
 * @tc.desc: Verify the EnableDbCache and IsDbCacheEnabled interface calls normally
 */
HWTEST_F(FmsFormProviderDataTest, EnableDbCache_IsDbCacheEnabled_001, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "EnableDbCache_IsDbCacheEnabled_001 start";
    InitJsonData();
    FormProviderData formProviderData(jsonData_);

    formProviderData.EnableDbCache(true);
    EXPECT_TRUE(formProviderData.IsDbCacheEnabled());
    EXPECT_TRUE(formProviderData.enableDbCache_);

    formProviderData.EnableDbCache(false);
    EXPECT_FALSE(formProviderData.IsDbCacheEnabled());
    EXPECT_FALSE(formProviderData.enableDbCache_);

    GTEST_LOG_(INFO) << "EnableDbCache_IsDbCacheEnabled_001 end";
}

/**
 * @tc.name: Constructor_NonObjectJson_003
 * @tc.type: FUNC
 * @tc.desc: When jsonData is not an object, constructor should return early
 */
HWTEST_F(FmsFormProviderDataTest, Constructor_NonObjectJson_003, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Constructor_NonObjectJson_003 start";
    nlohmann::json jsonArray = nlohmann::json::array();
    jsonArray.push_back("test");
    FormProviderData formProviderData(jsonArray);
    EXPECT_TRUE(formProviderData.jsonFormProviderData_.empty());
    GTEST_LOG_(INFO) << "Constructor_NonObjectJson_003 end";
}

/**
 * @tc.name: Constructor_WithIsUsedInFRS_001
 * @tc.type: FUNC
 * @tc.desc: When isUsedInFRS is true, ParseImagesData should not be called
 */
HWTEST_F(FmsFormProviderDataTest, Constructor_WithIsUsedInFRS_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Constructor_WithIsUsedInFRS_001 start";
    std::string jsonStr = R"({"formImages": {"image1": 1}})";
    FormProviderData formProviderData(jsonStr, true);
    EXPECT_FALSE(formProviderData.jsonFormProviderData_.empty());
    GTEST_LOG_(INFO) << "Constructor_WithIsUsedInFRS_001 end";
}

/**
 * @tc.name: SetDataString_InvalidJson_001
 * @tc.type: FUNC
 * @tc.desc: When jsonDataString is invalid json, SetDataString should return early
 */
HWTEST_F(FmsFormProviderDataTest, SetDataString_InvalidJson_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "SetDataString_InvalidJson_001 start";
    FormProviderData formProviderData(jsonData_);
    std::string invalidJson = "{invalid json}";
    formProviderData.SetDataString(invalidJson);
    EXPECT_TRUE(formProviderData.jsonFormProviderData_.empty());
    GTEST_LOG_(INFO) << "SetDataString_InvalidJson_001 end";
}

/**
 * @tc.name: SetDataString_ValidJsonNotObject_001
 * @tc.type: FUNC
 * @tc.desc: When jsonDataString is valid json but not object, SetDataString should return early
 */
HWTEST_F(FmsFormProviderDataTest, SetDataString_ValidJsonNotObject_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "SetDataString_ValidJsonNotObject_001 start";
    FormProviderData formProviderData(jsonData_);
    std::string jsonArray = "[1, 2, 3]";
    formProviderData.SetDataString(jsonArray);
    EXPECT_TRUE(formProviderData.jsonFormProviderData_.empty());
    GTEST_LOG_(INFO) << "SetDataString_ValidJsonNotObject_001 end";
}

/**
 * @tc.name: SetDataString_ValidJsonObject_001
 * @tc.type: FUNC
 * @tc.desc: When jsonDataString is valid json object, SetDataString should succeed
 */
HWTEST_F(FmsFormProviderDataTest, SetDataString_ValidJsonObject_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "SetDataString_ValidJsonObject_001 start";
    FormProviderData formProviderData(jsonData_);
    std::string validJson = R"({"key": "value"})";
    formProviderData.SetDataString(validJson);
    EXPECT_FALSE(formProviderData.jsonFormProviderData_.empty());
    GTEST_LOG_(INFO) << "SetDataString_ValidJsonObject_001 end";
}

/**
 * @tc.name: MergeData_EmptyCurrent_001
 * @tc.type: FUNC
 * @tc.desc: When current jsonFormProviderData_ is empty, MergeData should set it directly
 */
HWTEST_F(FmsFormProviderDataTest, MergeData_EmptyCurrent_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "MergeData_EmptyCurrent_001 start";
    FormProviderData formProviderData("");
    formProviderData.jsonFormProviderData_.clear();
    nlohmann::json addJson;
    addJson["newKey"] = "newValue";
    formProviderData.MergeData(addJson);
    EXPECT_FALSE(formProviderData.jsonFormProviderData_.empty());
    EXPECT_EQ(formProviderData.jsonFormProviderData_["newKey"], "newValue");
    GTEST_LOG_(INFO) << "MergeData_EmptyCurrent_001 end";
}

/**
 * @tc.name: MergeData_EmptyAddData_001
 * @tc.type: FUNC
 * @tc.desc: When addJsonData is empty, MergeData should return early
 */
HWTEST_F(FmsFormProviderDataTest, MergeData_EmptyAddData_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "MergeData_EmptyAddData_001 start";
    InitJsonData();
    FormProviderData formProviderData(jsonData_);
    nlohmann::json emptyJson;
    formProviderData.MergeData(emptyJson);
    EXPECT_FALSE(formProviderData.jsonFormProviderData_.empty());
    GTEST_LOG_(INFO) << "MergeData_EmptyAddData_001 end";
}

/**
 * @tc.name: ReadFromParcel_InvalidJson_001
 * @tc.type: FUNC
 * @tc.desc: When parcel contains invalid json, ReadFromParcel should return false
 */
HWTEST_F(FmsFormProviderDataTest, ReadFromParcel_InvalidJson_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "ReadFromParcel_InvalidJson_001 start";
    FormProviderData formProviderData(jsonData_);
    Parcel parcel;
    parcel.WriteInt32(DEFAULT_VALUE);
    parcel.WriteString16(Str8ToStr16("{invalid json}"));
    auto result = formProviderData.ReadFromParcel(parcel);
    EXPECT_FALSE(result);
    GTEST_LOG_(INFO) << "ReadFromParcel_InvalidJson_001 end";
}

/**
 * @tc.name: SetImageDataMap_EmptyMap_001
 * @tc.type: FUNC
 * @tc.desc: When imageDataMap is empty, imageDataState should be set to NO_OPERATION
 */
HWTEST_F(FmsFormProviderDataTest, SetImageDataMap_EmptyMap_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "SetImageDataMap_EmptyMap_001 start";
    FormProviderData formProviderData(jsonData_);
    std::map<std::string, std::pair<sptr<FormAshmem>, int32_t>> emptyMap;
    formProviderData.SetImageDataMap(emptyMap);
    EXPECT_EQ(formProviderData.imageDataState_, FormProviderData::IMAGE_DATA_STATE_NO_OPERATION);
    EXPECT_TRUE(formProviderData.imageDataMap_.empty());
    GTEST_LOG_(INFO) << "SetImageDataMap_EmptyMap_001 end";
}

/**
 * @tc.name: SetImageDataMap_NonEmptyMap_001
 * @tc.type: FUNC
 * @tc.desc: When imageDataMap is not empty, imageDataState should be set to ADDED
 */
HWTEST_F(FmsFormProviderDataTest, SetImageDataMap_NonEmptyMap_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "SetImageDataMap_NonEmptyMap_001 start";
    FormProviderData formProviderData(jsonData_);
    std::map<std::string, std::pair<sptr<FormAshmem>, int32_t>> nonEmptyMap;
    sptr<FormAshmem> formAshmem(new (std::nothrow) FormAshmem());
    nonEmptyMap["test"] = std::make_pair(formAshmem, 10);
    formProviderData.SetImageDataMap(nonEmptyMap);
    EXPECT_EQ(formProviderData.imageDataState_, FormProviderData::IMAGE_DATA_STATE_ADDED);
    EXPECT_FALSE(formProviderData.imageDataMap_.empty());
    EXPECT_EQ(formProviderData.imageDataMap_.size(), 1);
    GTEST_LOG_(INFO) << "SetImageDataMap_NonEmptyMap_001 end";
}

/**
 * @tc.name: Marshalling_BigData_001
 * @tc.type: FUNC
 * @tc.desc: When json data is larger than BIG_DATA, test marshalling
 */
HWTEST_F(FmsFormProviderDataTest, Marshalling_BigData_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Marshalling_BigData_001 start";
    std::string bigJsonStr = R"({"data": ")" + std::string(35000, 'a') + R"("})";
    FormProviderData formProviderData(bigJsonStr);
    Parcel parcel;
    auto result = formProviderData.Marshalling(parcel);
    EXPECT_TRUE(result);
    
    std::unique_ptr<FormProviderData> readProviderData(FormProviderData::Unmarshalling(parcel));
    ASSERT_NE(readProviderData, nullptr);
    EXPECT_FALSE(readProviderData->jsonFormProviderData_.empty());
    
    GTEST_LOG_(INFO) << "Marshalling_BigData_001 end";
}

/**
 * @tc.name: GetDataString_EmptyJson_001
 * @tc.type: FUNC
 * @tc.desc: When jsonFormProviderData_ is empty, GetDataString should return empty string
 */
HWTEST_F(FmsFormProviderDataTest, GetDataString_EmptyJson_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "GetDataString_EmptyJson_001 start";
    FormProviderData formProviderData("");
    formProviderData.jsonFormProviderData_.clear();
    auto result = formProviderData.GetDataString();
    EXPECT_TRUE(result.empty());
    GTEST_LOG_(INFO) << "GetDataString_EmptyJson_001 end";
}

/**
 * @tc.name: ConvertRawImageData_Normal_001
 * @tc.type: FUNC
 * @tc.desc: Verify that ConvertRawImageData function.
 */
HWTEST_F(FmsFormProviderDataTest, ConvertRawImageData_Normal_001, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "ConvertRawImageData_Normal_001 start";
    InitJsonData();
    FormProviderData formProviderData(jsonData_);
    std::string picName = "image";
    std::shared_ptr<char> data = std::make_shared<char>('a');
    formProviderData.AddImageData(picName, data, 1);
    EXPECT_EQ(1, formProviderData.rawImageBytesMap_.size());
    EXPECT_TRUE(formProviderData.ConvertRawImageData());
    EXPECT_EQ(1, formProviderData.GetImageDataMap().size());
    EXPECT_TRUE(formProviderData.rawImageBytesMap_.empty());
    GTEST_LOG_(INFO) << "ConvertRawImageData_Normal_001 end";
}

/**
 * @tc.name: HasData_EmptyData_001
 * @tc.type: FUNC
 * @tc.desc: When both jsonFormProviderData_ and imageDataMap_ are empty, HasData should return false
 */
HWTEST_F(FmsFormProviderDataTest, HasData_EmptyData_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "HasData_EmptyData_001 start";
    FormProviderData formProviderData("");
    formProviderData.jsonFormProviderData_.clear();
    EXPECT_FALSE(formProviderData.HasData());
    GTEST_LOG_(INFO) << "HasData_EmptyData_001 end";
}

/**
 * @tc.name: AddImageData_WriteImageDataToParcel_001
 * @tc.type: FUNC
 * @tc.desc: Verify the AddImageData and WriteImageDataToParcel function.
 */
HWTEST_F(FmsFormProviderDataTest, AddImageData_WriteImageDataToParcel_001, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "AddImageData_WriteImageDataToParcel_001 start";
    FormProviderData formProviderData(jsonData_);
    std::string picName = "image";
    std::shared_ptr<char> data = std::make_shared<char>('a');
    formProviderData.AddImageData(picName, data, 1);
    EXPECT_EQ(1, formProviderData.rawImageBytesMap_.size());
    Parcel parcel;
    EXPECT_TRUE(formProviderData.WriteImageDataToParcel(parcel, picName, data, 1));
    GTEST_LOG_(INFO) << "AddImageData_WriteImageDataToParcel_001 end";
}
/**
 * @tc.name: UpdateData_GetData_001
 * @tc.type: FUNC
 * @tc.desc: Verify the UpdateData and GetData function.
 */
HWTEST_F(FmsFormProviderDataTest, UpdateData_GetData_001, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "UpdateData_GetData_001 start";
    InitJsonData();
    FormProviderData formProviderData(jsonData_);
    formProviderData.UpdateData(jsonData_);
    auto result = formProviderData.GetData();

    EXPECT_EQ(jsonData_, result);
    GTEST_LOG_(INFO) << "UpdateData_GetData_001 end";
}

/**
 * @tc.name: RemoveImageData_AddImageData_001
 * @tc.type: FUNC
 * @tc.desc: Verify the RemoveImageData and AddImageData function.
 */
HWTEST_F(FmsFormProviderDataTest, RemoveImageData_AddImageData_001, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "RemoveImageData_AddImageData_001 start";
    InitJsonData();
    FormProviderData formProviderData(jsonData_);
    std::string picName = "abc";
    int32_t size = 1;
    std::shared_ptr<char> data;
    formProviderData.AddImageData(picName, data, size);
    formProviderData.RemoveImageData(picName);

    EXPECT_TRUE(formProviderData.rawImageBytesMap_.empty());
    GTEST_LOG_(INFO) << "RemoveImageData_AddImageData_001 end";
}

/**
 * @tc.name: SetDataString_GetDataString_002
 * @tc.type: FUNC
 * @tc.desc: Verify SetDataString and GetDataString with valid JSON data.
 */
HWTEST_F(FmsFormProviderDataTest, SetDataString_GetDataString_002, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "SetDataString_GetDataString_002 start";
    FormProviderData formProviderData("");
    std::string jsonDataString = R"({"name": "test", "age": 20})";
    formProviderData.SetDataString(jsonDataString);
    
    auto result = formProviderData.GetDataString();
    EXPECT_FALSE(result.empty());
    
    nlohmann::json resultJson = nlohmann::json::parse(result, nullptr, false);
    EXPECT_FALSE(resultJson.is_discarded());
    EXPECT_EQ(resultJson["name"], "test");
    EXPECT_EQ(resultJson["age"], 20);
    
    GTEST_LOG_(INFO) << "SetDataString_GetDataString_002 end";
}

/**
 * @tc.name: ReadFromParcel_Normal_001
 * @tc.type: FUNC
 * @tc.desc: Verify the ReadFromParcel function.
 */
HWTEST_F(FmsFormProviderDataTest, ReadFromParcel_Normal_001, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "ReadFromParcel_Normal_001 start";
    InitJsonData();
    FormProviderData formProviderData(jsonData_);
    
    Parcel parcel;
    parcel.WriteInt32(DEFAULT_VALUE);
    parcel.WriteString16(Str8ToStr16(jsonData_.dump()));
    parcel.WriteInt32(FormProviderData::IMAGE_DATA_STATE_NO_OPERATION);
    
    auto result = formProviderData.ReadFromParcel(parcel);
    EXPECT_TRUE(result);
    EXPECT_FALSE(formProviderData.jsonFormProviderData_.empty());
    EXPECT_EQ(formProviderData.imageDataState_, FormProviderData::IMAGE_DATA_STATE_NO_OPERATION);
    EXPECT_TRUE(formProviderData.GetImageDataMap().empty());
    EXPECT_FALSE(formProviderData.GetDataString().empty());
    
    GTEST_LOG_(INFO) << "ReadFromParcel_Normal_001 end";
}

/**
 * @tc.name: Marshalling_Normal_001
 * @tc.type: FUNC
 * @tc.desc: Verify the Marshalling function.
 */
HWTEST_F(FmsFormProviderDataTest, Marshalling_Normal_001, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "Marshalling_Normal_001 start";
    InitJsonData();
    FormProviderData formProviderData(jsonData_);
    Parcel parcel;
    
    auto result = formProviderData.Marshalling(parcel);
    EXPECT_TRUE(result);
    EXPECT_FALSE(formProviderData.jsonFormProviderData_.empty());
    EXPECT_EQ(formProviderData.imageDataState_, FormProviderData::IMAGE_DATA_STATE_NO_OPERATION);
    
    GTEST_LOG_(INFO) << "Marshalling_Normal_001 end";
}

/**
 * @tc.name: Unmarshalling_Normal_001
 * @tc.type: FUNC
 * @tc.desc: Verify the Unmarshalling function.
 */
HWTEST_F(FmsFormProviderDataTest, Unmarshalling_Normal_001, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "Unmarshalling_Normal_001 start";
    InitJsonData();
    FormProviderData writeProviderData(jsonData_);
    Parcel parcel;
    EXPECT_TRUE(writeProviderData.Marshalling(parcel));
    
    std::unique_ptr<FormProviderData> readProviderData(FormProviderData::Unmarshalling(parcel));
    ASSERT_NE(readProviderData, nullptr);
    EXPECT_FALSE(readProviderData->jsonFormProviderData_.empty());
    EXPECT_EQ(readProviderData->imageDataState_, FormProviderData::IMAGE_DATA_STATE_NO_OPERATION);
    EXPECT_FALSE(readProviderData->GetDataString().empty());
    
    GTEST_LOG_(INFO) << "Unmarshalling_Normal_001 end";
}

/**
 * @tc.name: ClearData_Normal_001
 * @tc.type: FUNC
 * @tc.desc: Verify the ClearData function.
 */
HWTEST_F(FmsFormProviderDataTest, ClearData_Normal_001, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "ClearData_Normal_001 start";
    InitJsonData();
    FormProviderData formProviderData(jsonData_);
    formProviderData.UpdateData(jsonData_);
    EXPECT_FALSE(formProviderData.jsonFormProviderData_.empty());
    
    formProviderData.ClearData();
    EXPECT_TRUE(formProviderData.jsonFormProviderData_.empty());
    EXPECT_TRUE(formProviderData.imageDataMap_.empty());
    EXPECT_TRUE(formProviderData.rawImageBytesMap_.empty());
    EXPECT_EQ(formProviderData.imageDataState_, FormProviderData::IMAGE_DATA_STATE_NO_OPERATION);
    
    GTEST_LOG_(INFO) << "ClearData_Normal_001 end";
}

/**
 * @tc.name: MergeData_NotNull_002
 * @tc.type: FUNC
 * @tc.desc: Verify MergeData correctly handles repeated merge operations.
 */
HWTEST_F(FmsFormProviderDataTest, MergeData_NotNull_002, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "MergeData_NotNull_002 start";
    InitJsonData();
    FormProviderData formProviderData(jsonData_);
    
    EXPECT_EQ(formProviderData.jsonFormProviderData_.size(), 1);
    
    InitJsonData2();
    formProviderData.MergeData(jsonData_);
    
    EXPECT_EQ(formProviderData.jsonFormProviderData_.size(), 2);
    
    formProviderData.MergeData(jsonData_);
    
    EXPECT_EQ(formProviderData.jsonFormProviderData_.size(), 2);
    EXPECT_TRUE(formProviderData.jsonFormProviderData_.contains("0"));
    EXPECT_TRUE(formProviderData.jsonFormProviderData_.contains("1"));
    
    GTEST_LOG_(INFO) << "MergeData_NotNull_002 end";
}

/**
 * @tc.name: AddImageData_NullSharedPtr_001
 * @tc.type: FUNC
 * @tc.desc: When data is nullptr, the interface calls normally.
 */
HWTEST_F(FmsFormProviderDataTest, AddImageData_NullSharedPtr_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "AddImageData_NullSharedPtr_001 start";
    InitJsonData();
    FormProviderData formProviderData(jsonData_);
    std::string picName = "imageTest";
    std::shared_ptr<char> data = nullptr;
    formProviderData.AddImageData(picName, data, 1);
    EXPECT_TRUE(formProviderData.rawImageBytesMap_.find(picName) == formProviderData.rawImageBytesMap_.end());
    GTEST_LOG_(INFO) << "AddImageData_NullSharedPtr_001 end";
}

/**
 * @tc.name: AddImageData_EmptyPicName_NullSharedPtr_001
 * @tc.type: FUNC
 * @tc.desc: When picName is "", the interface calls normally.
 */
HWTEST_F(FmsFormProviderDataTest, AddImageData_EmptyPicName_NullSharedPtr_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "AddImageData_EmptyPicName_NullSharedPtr_001 start";
    InitJsonData();
    FormProviderData formProviderData(jsonData_);
    std::string picName = "";
    std::shared_ptr<char> data = nullptr;
    formProviderData.AddImageData(picName, data, 1);
    EXPECT_TRUE(formProviderData.rawImageBytesMap_.find(picName) == formProviderData.rawImageBytesMap_.end());
    GTEST_LOG_(INFO) << "AddImageData_EmptyPicName_NullSharedPtr_001 end";
}

/**
 * @tc.name: AddImageData_NegativeFd_001
 * @tc.type: FUNC
 * @tc.desc: When fd is -1, the interface calls normally.
 */
HWTEST_F(FmsFormProviderDataTest, AddImageData_NegativeFd_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "AddImageData_NegativeFd_001 start";
    InitJsonData();
    FormProviderData formProviderData(jsonData_);
    std::string picName = "imageTest";
    int fd = -1;
    formProviderData.AddImageData(picName, fd);
    EXPECT_TRUE(formProviderData.rawImageBytesMap_.find(picName) == formProviderData.rawImageBytesMap_.end());
    GTEST_LOG_(INFO) << "AddImageData_NegativeFd_001 end";
}

/**
 * @tc.name: ReadFromParcel_NoOperationState_001
 * @tc.type: FUNC
 * @tc.desc: When the parameter parcel is IMAGE_DATA_STATE_NO_OPERATION, the interface return value is true.
 */
HWTEST_F(FmsFormProviderDataTest, ReadFromParcel_NoOperationState_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "ReadFromParcel_NoOperationState_001 start";
    InitJsonData();
    FormProviderData formProviderData(jsonData_);
    Parcel parcel;
    parcel.WriteInt32(DEFAULT_VALUE);
    parcel.WriteString16(Str8ToStr16(jsonData_.dump()));
    parcel.WriteInt32(FormProviderData::IMAGE_DATA_STATE_NO_OPERATION);
    auto result = formProviderData.ReadFromParcel(parcel);
    EXPECT_TRUE(result);
    GTEST_LOG_(INFO) << "ReadFromParcel_NoOperationState_001 end";
}

/**
 * @tc.name: ReadFromParcel_RemovedState_001
 * @tc.type: FUNC
 * @tc.desc: When the parameter parcel is IMAGE_DATA_STATE_REMOVED, the interface return value is true.
 */
HWTEST_F(FmsFormProviderDataTest, ReadFromParcel_RemovedState_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "ReadFromParcel_RemovedState_001 start";
    InitJsonData();
    FormProviderData formProviderData(jsonData_);
    Parcel parcel;
    parcel.WriteInt32(DEFAULT_VALUE);
    parcel.WriteString16(Str8ToStr16(jsonData_.dump()));
    parcel.WriteInt32(FormProviderData::IMAGE_DATA_STATE_REMOVED);
    auto result = formProviderData.ReadFromParcel(parcel);
    EXPECT_TRUE(result);
    GTEST_LOG_(INFO) << "ReadFromParcel_RemovedState_001 end";
}

/**
 * @tc.name: ReadFromParcel_CustomState_001
 * @tc.type: FUNC
 * @tc.desc: When the parameter parcel is 100, the interface return value is true.
 */
HWTEST_F(FmsFormProviderDataTest, ReadFromParcel_CustomState_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "ReadFromParcel_CustomState_001 start";
    InitJsonData();
    constexpr int32_t defaultValue = 100;
    FormProviderData formProviderData(jsonData_);
    Parcel parcel;
    parcel.WriteInt32(DEFAULT_VALUE);
    parcel.WriteString16(Str8ToStr16(jsonData_.dump()));
    parcel.WriteInt32(defaultValue);
    auto result = formProviderData.ReadFromParcel(parcel);
    EXPECT_TRUE(result);
    GTEST_LOG_(INFO) << "ReadFromParcel_CustomState_001 end";
}

/**
 * @tc.name: ReadFromParcel_AddedState_001
 * @tc.type: FUNC
 * @tc.desc: When the parameter parcel is IMAGE_DATA_STATE_ADDED, the interface return value is true.
 */
HWTEST_F(FmsFormProviderDataTest, ReadFromParcel_AddedState_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "ReadFromParcel_AddedState_001 start";
    InitJsonData();
    FormProviderData formProviderData(jsonData_);
    Parcel parcel;
    parcel.WriteInt32(DEFAULT_VALUE);
    parcel.WriteString16(Str8ToStr16(jsonData_.dump()));
    parcel.WriteInt32(FormProviderData::IMAGE_DATA_STATE_ADDED);
    auto result = formProviderData.ReadFromParcel(parcel);
    EXPECT_TRUE(result);
    GTEST_LOG_(INFO) << "ReadFromParcel_AddedState_001 end";
}

/**
 * @tc.name: ReadFromParcel_ImageDataNumExceed_001
 * @tc.type: FUNC
 * @tc.desc: When the parameter parcel is IMAGE_DATA_STATE_ADDED and imageDataNum is exception value, the
 *           interface return value is false.
 */
HWTEST_F(FmsFormProviderDataTest, ReadFromParcel_ImageDataNumExceed_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "ReadFromParcel_ImageDataNumExceed_001 start";
    InitJsonData();
    constexpr int32_t imageDataNum = 1001;  // 1001: Eead parcel max image data num size.
    FormProviderData formProviderData(jsonData_);
    Parcel parcel;
    parcel.WriteString16(Str8ToStr16(jsonData_.dump()));
    parcel.WriteInt32(FormProviderData::IMAGE_DATA_STATE_ADDED);
    parcel.WriteInt32(imageDataNum);
    auto result = formProviderData.ReadFromParcel(parcel);
    EXPECT_FALSE(result);
    GTEST_LOG_(INFO) << "ReadFromParcel_ImageDataNumExceed_001 end";
}

/**
 * @tc.name: ReadFromParcel_NormalImageDataNum_001
 * @tc.type: FUNC
 * @tc.desc: When the parameter parcel is IMAGE_DATA_STATE_ADDED and imageDataNum is normal value, the
 *           interface return value is false.
 */
HWTEST_F(FmsFormProviderDataTest, ReadFromParcel_NormalImageDataNum_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "ReadFromParcel_NormalImageDataNum_001 start";
    InitJsonData();
    constexpr int32_t imageDataNum = 1;
    constexpr int32_t len = 0;
    FormAshmem formAshmem;
    char data = 'A';
    constexpr int32_t size = 1;
    FormProviderData formProviderData(jsonData_);
    Parcel parcel;
    parcel.WriteInt32(DEFAULT_VALUE);
    parcel.WriteString16(Str8ToStr16(jsonData_.dump()));
    parcel.WriteInt32(FormProviderData::IMAGE_DATA_STATE_ADDED);
    parcel.WriteInt32(imageDataNum);
    formAshmem.WriteToAshmem("ReadFromParcelTest", &data, size);
    parcel.WriteInt32(len);
    parcel.WriteString16(Str8ToStr16("test"));
    auto result = formProviderData.ReadFromParcel(parcel);
    EXPECT_FALSE(result);
    GTEST_LOG_(INFO) << "ReadFromParcel_NormalImageDataNum_001 end";
}

/**
 * @tc.name: ReadFromParcel_NullAshmem_001
 * @tc.type: FUNC
 * @tc.desc: When the parameter parcel is IMAGE_DATA_STATE_ADDED and imageDataNum is normal value, the
 *           interface return value is false.
 */
HWTEST_F(FmsFormProviderDataTest, ReadFromParcel_NullAshmem_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "ReadFromParcel_NullAshmem_001 start";
    InitJsonData();
    constexpr int32_t imageDataNum = 1;
    FormProviderData formProviderData(jsonData_);
    Parcel parcel;
    parcel.WriteInt32(DEFAULT_VALUE);
    parcel.WriteString16(Str8ToStr16(jsonData_.dump()));
    parcel.WriteInt32(FormProviderData::IMAGE_DATA_STATE_ADDED);
    parcel.WriteInt32(imageDataNum);
    parcel.WriteParcelable(nullptr);
    auto result = formProviderData.ReadFromParcel(parcel);
    EXPECT_FALSE(result);
    GTEST_LOG_(INFO) << "ReadFromParcel_NullAshmem_001 end";
}

/**
 * @tc.name: Marshalling_NoOperationState_001
 * @tc.type: FUNC
 * @tc.desc: When the parameter imageDataState_ is IMAGE_DATA_STATE_NO_OPERATION, the interface return value is true.
 */
HWTEST_F(FmsFormProviderDataTest, Marshalling_NoOperationState_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Marshalling_NoOperationState_001 start";
    InitJsonData();
    FormProviderData formProviderData(jsonData_);
    formProviderData.imageDataState_ = FormProviderData::IMAGE_DATA_STATE_NO_OPERATION;
    Parcel parcel;
    auto result = formProviderData.Marshalling(parcel);
    EXPECT_TRUE(result);
    GTEST_LOG_(INFO) << "Marshalling_NoOperationState_001 end";
}

/**
 * @tc.name: Marshalling_RemovedState_001
 * @tc.type: FUNC
 * @tc.desc: When the parameter imageDataState_ is IMAGE_DATA_STATE_REMOVED, the interface return value is true.
 */
HWTEST_F(FmsFormProviderDataTest, Marshalling_RemovedState_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Marshalling_RemovedState_001 start";
    InitJsonData();
    FormProviderData formProviderData(jsonData_);
    formProviderData.imageDataState_ = FormProviderData::IMAGE_DATA_STATE_REMOVED;
    Parcel parcel;
    auto result = formProviderData.Marshalling(parcel);
    EXPECT_TRUE(result);
    GTEST_LOG_(INFO) << "Marshalling_RemovedState_001 end";
}

/**
 * @tc.name: Marshalling_AddedState_002
 * @tc.type: FUNC
 * @tc.desc: When the parameter imageDataState_ is IMAGE_DATA_STATE_ADDED, the interface return value is true.
 */
HWTEST_F(FmsFormProviderDataTest, Marshalling_AddedState_002, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Marshalling_AddedState_002 start";
    InitJsonData();
    FormProviderData formProviderData(jsonData_);
    std::shared_ptr<char> data = std::make_shared<char>('a');
    formProviderData.AddImageData("test", data, 1);
    formProviderData.imageDataState_ = FormProviderData::IMAGE_DATA_STATE_ADDED;
    Parcel parcel;
    auto result = formProviderData.Marshalling(parcel);
    EXPECT_TRUE(result);
    GTEST_LOG_(INFO) << "Marshalling_AddedState_002 end";
}

/**
 * @tc.name: Marshalling_CustomState_002
 * @tc.type: FUNC
 * @tc.desc: When the parameter imageDataState_ is 100, the interface return value is true.
 */
HWTEST_F(FmsFormProviderDataTest, Marshalling_CustomState_002, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Marshalling_CustomState_002 start";
    InitJsonData();
    constexpr int32_t defaultValue = 100;
    FormProviderData formProviderData(jsonData_);
    formProviderData.imageDataState_ = defaultValue;
    Parcel parcel;
    auto result = formProviderData.Marshalling(parcel);
    EXPECT_TRUE(result);
    GTEST_LOG_(INFO) << "Marshalling_CustomState_002 end";
}

/**
 * @tc.name: Marshalling_NullData_003
 * @tc.type: FUNC
 * @tc.desc: When the parameter imageDataState_ is null, the interface return value is true.
 */
HWTEST_F(FmsFormProviderDataTest, Marshalling_NullData_003, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Marshalling_NullData_003 start";
    InitJsonData();
    FormProviderData formProviderData("");
    formProviderData.jsonFormProviderData_.clear();
    Parcel parcel;
    auto result = formProviderData.Marshalling(parcel);
    EXPECT_TRUE(result);
    GTEST_LOG_(INFO) << "Marshalling_NullData_003 end";
}

/**
 * @tc.name: ParseImagesData_Normal_001
 * @tc.type: FUNC
 * @tc.desc: Verify whether the ParseImagesData interface calls normally.
 */
HWTEST_F(FmsFormProviderDataTest, ParseImagesData_Normal_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "ParseImagesData_Normal_001 start";
    InitJsonData();
    FormProviderData formProviderData(jsonData_);
    formProviderData.ParseImagesData();
    EXPECT_TRUE(formProviderData.jsonFormProviderData_ != nullptr);
    GTEST_LOG_(INFO) << "ParseImagesData_Normal_001 end";
}

/**
 * @tc.name: ParseImagesData_NullJson_001
 * @tc.type: FUNC
 * @tc.desc: When the jsonFormProviderData_ is nullptr, the ParseImagesData interface calls normally.
 */
HWTEST_F(FmsFormProviderDataTest, ParseImagesData_NullJson_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "ParseImagesData_NullJson_001 start";
    FormProviderData formProviderData("");
    formProviderData.jsonFormProviderData_ = nullptr;
    formProviderData.ParseImagesData();
    EXPECT_TRUE(formProviderData.jsonFormProviderData_ == nullptr);
    GTEST_LOG_(INFO) << "ParseImagesData_NullJson_001 end";
}

/**
 * @tc.name: NeedCache_NullJson_002
 * @tc.type: FUNC
 * @tc.desc: When the jsonFormProviderData_ is nullptr, the NeedCache interface calls normally.
 */
HWTEST_F(FmsFormProviderDataTest, NeedCache_NullJson_002, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "NeedCache_NullJson_002 start";
    FormProviderData formProviderData("{'a':'1','b':'2'}");
    formProviderData.jsonFormProviderData_.clear();
    EXPECT_FALSE(formProviderData.NeedCache());
    GTEST_LOG_(INFO) << "NeedCache_NullJson_002 end";
}

/**
 * @tc.name: SetImageDataState_GetImageDataState_001
 * @tc.type: FUNC
 * @tc.desc: Verify whether the NeedCache interface calls normally.
 */
HWTEST_F(FmsFormProviderDataTest, SetImageDataState_GetImageDataState_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "SetImageDataState_GetImageDataState_001 start";
    FormProviderData formProviderData("");
    constexpr int32_t imageStage = 1000;
    EXPECT_NE(imageStage, formProviderData.imageDataState_);
    formProviderData.SetImageDataState(imageStage);
    EXPECT_EQ(imageStage, formProviderData.imageDataState_);
    GTEST_LOG_(INFO) << "SetImageDataState_GetImageDataState_001 end";
}

/**
 * @tc.name: GetImageDataState_Normal_002
 * @tc.type: FUNC
 * @tc.desc: Verify whether the GetImageDataState interface calls normally.
 */
HWTEST_F(FmsFormProviderDataTest, GetImageDataState_Normal_002, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "GetImageDataState_Normal_002 start";
    FormProviderData formProviderData("");
    formProviderData.jsonFormProviderData_.clear();
    EXPECT_EQ(formProviderData.imageDataState_, formProviderData.GetImageDataState());
    GTEST_LOG_(INFO) << "GetImageDataState_Normal_002 end";
}

/**
 * @tc.name: ReadAshmemDataFromParcel_Invalid_001
 * @tc.type: FUNC
 * @tc.desc: Verify whether the ReadAshmemDataFromParcel interface calls normally.
 */
HWTEST_F(FmsFormProviderDataTest, ReadAshmemDataFromParcel_Invalid_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "ReadAshmemDataFromParcel_Invalid_001 start";
    Parcel parcel;
    size_t bufferSize = 0;
    FormProviderData formProviderData("");
    formProviderData.jsonFormProviderData_.clear();
    auto result = formProviderData.ReadAshmemDataFromParcel(parcel, bufferSize);
    EXPECT_EQ(result, nullptr);
    GTEST_LOG_(INFO) << "ReadAshmemDataFromParcel_Invalid_001 end";
}

/**
 * @tc.name: WriteFileDescriptor_InvalidFd_001
 * @tc.type: FUNC
 * @tc.desc: Verify whether the WriteFileDescriptor interface calls normally.
 */
HWTEST_F(FmsFormProviderDataTest, WriteFileDescriptor_InvalidFd_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "WriteFileDescriptor_InvalidFd_001 start";
    Parcel parcel;
    int fd = -1;
    FormProviderData formProviderData("");
    formProviderData.jsonFormProviderData_.clear();
    auto result = formProviderData.WriteFileDescriptor(parcel, fd);
    EXPECT_EQ(result, false);
    GTEST_LOG_(INFO) << "WriteFileDescriptor_InvalidFd_001 end";
}

/**
 * @tc.name: ReadFileDescriptor_ReleaseMemory_001
 * @tc.type: FUNC
 * @tc.desc: Verify whether ReadFileDescriptor and ReleaseMemory interface calls normally.
 */
HWTEST_F(FmsFormProviderDataTest, ReadFileDescriptor_ReleaseMemory_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "ReadFileDescriptor_ReleaseMemory_001 start";
    Parcel parcel;
    FormProviderData formProviderData;
    formProviderData.ReleaseMemory(2, nullptr, nullptr, 0);
    auto result = formProviderData.ReadFileDescriptor(parcel);
    EXPECT_EQ(result, -1);
    GTEST_LOG_(INFO) << "ReadFileDescriptor_ReleaseMemory_001 end";
}

/**
 * @tc.name: AddImageData_FD_EmptyFile_001
 * @tc.type: FUNC
 * @tc.desc: Verify AddImageData with fd, when file size is zero.
 */
HWTEST_F(FmsFormProviderDataTest, AddImageData_FD_EmptyFile_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "AddImageData_FD_EmptyFile_001 start";
    InitJsonData();
    FormProviderData formProviderData(jsonData_);
    std::string picName = "emptyImage";
    std::string testFile = FORM_DB_DATA_BASE_FILE_DIR + "/test_empty_image.tmp";
    int fd = open(testFile.c_str(), O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    ASSERT_GE(fd, 0);
    formProviderData.AddImageData(picName, fd);
    close(fd);
    unlink(testFile.c_str());
    EXPECT_TRUE(formProviderData.rawImageBytesMap_.find(picName) == formProviderData.rawImageBytesMap_.end());
    GTEST_LOG_(INFO) << "AddImageData_FD_EmptyFile_001 end";
}

/**
 * @tc.name: AddImageData_FD_ValidFile_001
 * @tc.type: FUNC
 * @tc.desc: Verify AddImageData with fd, when file is a valid small image.
 */
HWTEST_F(FmsFormProviderDataTest, AddImageData_FD_ValidFile_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "AddImageData_FD_ValidFile_001 start";
    InitJsonData();
    FormProviderData formProviderData(jsonData_);
    std::string picName = "validImage";
    std::string testData = "test image data content";
    std::string testFile = FORM_DB_DATA_BASE_FILE_DIR + "/test_valid_image.tmp";
    std::ofstream file(testFile);
    file << testData;
    file.close();
    int fd = open(testFile.c_str(), O_RDONLY);
    ASSERT_GE(fd, 0);
    formProviderData.AddImageData(picName, fd);
    close(fd);
    unlink(testFile.c_str());
    EXPECT_TRUE(formProviderData.rawImageBytesMap_.find(picName) != formProviderData.rawImageBytesMap_.end());
    EXPECT_EQ(formProviderData.rawImageBytesMap_[picName].second, static_cast<int32_t>(testData.length()));
    GTEST_LOG_(INFO) << "AddImageData_FD_ValidFile_001 end";
}

/**
 * @tc.name: ReadAshmem_BufferSizeExceed_001
 * @tc.type: FUNC
 * @tc.desc: Verify ReadAshmemDataFromParcel with bufferSize exceeds MAX_BUFFER_SIZE.
 */
HWTEST_F(FmsFormProviderDataTest, ReadAshmem_BufferSizeExceed_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "ReadAshmem_BufferSizeExceed_001 start";
    FormProviderData formProviderData("");
    Parcel parcel;
    constexpr int32_t overSize = 32 * 1024 * 1024 + 1;
    char *result = formProviderData.ReadAshmemDataFromParcel(parcel, overSize);
    EXPECT_EQ(result, nullptr);
    GTEST_LOG_(INFO) << "ReadAshmem_BufferSizeExceed_001 end";
}

/**
 * @tc.name: ReadAshmem_BufferSizeNegative_001
 * @tc.type: FUNC
 * @tc.desc: Verify ReadAshmemDataFromParcel with negative bufferSize.
 */
HWTEST_F(FmsFormProviderDataTest, ReadAshmem_BufferSizeNegative_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "ReadAshmem_BufferSizeNegative_001 start";
    FormProviderData formProviderData("");
    Parcel parcel;
    char *result = formProviderData.ReadAshmemDataFromParcel(parcel, -1);
    EXPECT_EQ(result, nullptr);
    GTEST_LOG_(INFO) << "ReadAshmem_BufferSizeNegative_001 end";
}

/**
 * @tc.name: WriteFd_ValidFd_001
 * @tc.type: FUNC
 * @tc.desc: Verify WriteFileDescriptor with valid fd.
 */
HWTEST_F(FmsFormProviderDataTest, WriteFd_ValidFd_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "WriteFd_ValidFd_001 start";
    FormProviderData formProviderData("");
    Parcel parcel;
    std::string testFile = FORM_DB_DATA_BASE_FILE_DIR + "/test_fd_write.tmp";
    int fd = open(testFile.c_str(), O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    ASSERT_GE(fd, 0);
    bool result = formProviderData.WriteFileDescriptor(parcel, fd);
    close(fd);
    unlink(testFile.c_str());
    EXPECT_TRUE(result);
    GTEST_LOG_(INFO) << "WriteFd_ValidFd_001 end";
}

/**
 * @tc.name: WriteAshmemDataToParcel_ZeroSize_001
 * @tc.type: FUNC
 * @tc.desc: Verify WriteAshmemDataToParcel with zero size data.
 */
HWTEST_F(FmsFormProviderDataTest, WriteAshmemDataToParcel_ZeroSize_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "WriteAshmemDataToParcel_ZeroSize_001 start";
    FormProviderData formProviderData("");
    Parcel parcel;
    const char *dataPtr = "test";
    bool result = formProviderData.WriteAshmemDataToParcel(parcel, 0, dataPtr);
    EXPECT_FALSE(result);
    GTEST_LOG_(INFO) << "WriteAshmemDataToParcel_ZeroSize_001 end";
}

/**
 * @tc.name: WriteAshmem_LargeData_001
 * @tc.type: FUNC
 * @tc.desc: Verify WriteAshmemDataToParcel with large data.
 */
HWTEST_F(FmsFormProviderDataTest, WriteAshmem_LargeData_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "WriteAshmem_LargeData_001 start";
    FormProviderData formProviderData("");
    Parcel parcel;
    std::string largeData(1024 * 100, 'a');
    size_t size = largeData.length();
    bool result = formProviderData.WriteAshmemDataToParcel(parcel, size, largeData.c_str());
    EXPECT_TRUE(result);
    GTEST_LOG_(INFO) << "WriteAshmem_LargeData_001 end";
}

/**
 * @tc.name: ConvertRawImage_MultiImages_001
 * @tc.type: FUNC
 * @tc.desc: Verify ConvertRawImageData with multiple images.
 */
HWTEST_F(FmsFormProviderDataTest, ConvertRawImage_MultiImages_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "ConvertRawImage_MultiImages_001 start";
    InitJsonData();
    FormProviderData formProviderData(jsonData_);
    std::shared_ptr<char[]> data1 = std::make_shared<char[]>(10);
    std::shared_ptr<char[]> data2 = std::make_shared<char[]>(20);
    formProviderData.AddImageData("image1", data1, 10);
    formProviderData.AddImageData("image2", data2, 20);
    EXPECT_TRUE(formProviderData.ConvertRawImageData());
    EXPECT_EQ(2, static_cast<int>(formProviderData.GetImageDataMap().size()));
    EXPECT_TRUE(formProviderData.rawImageBytesMap_.empty());
    GTEST_LOG_(INFO) << "ConvertRawImage_MultiImages_001 end";
}

/**
 * @tc.name: WriteImageData_EmptyData_001
 * @tc.type: FUNC
 * @tc.desc: Verify WriteImageDataToParcel with empty data.
 */
HWTEST_F(FmsFormProviderDataTest, WriteImageData_EmptyData_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "WriteImageData_EmptyData_001 start";
    InitJsonData();
    FormProviderData formProviderData(jsonData_);
    Parcel parcel;
    std::string picName = "emptyImage";
    std::shared_ptr<char[]> data = std::make_shared<char[]>(1);
    data.get()[0] = '\0';
    bool result = formProviderData.WriteImageDataToParcel(parcel, picName, data, 1);
    EXPECT_TRUE(result);
    GTEST_LOG_(INFO) << "WriteImageData_EmptyData_001 end";
}

/**
 * @tc.name: WriteImageData_ValidData_001
 * @tc.type: FUNC
 * @tc.desc: Verify WriteImageDataToParcel with valid data.
 */
HWTEST_F(FmsFormProviderDataTest, WriteImageData_ValidData_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "WriteImageData_ValidData_001 start";
    InitJsonData();
    FormProviderData formProviderData(jsonData_);
    Parcel parcel;
    std::string picName = "validDataImage";
    std::shared_ptr<char[]> data = std::make_shared<char[]>(100);
    std::fill(data.get(), data.get() + 100, 'A');
    bool result = formProviderData.WriteImageDataToParcel(parcel, picName, data, 100);
    EXPECT_TRUE(result);
    GTEST_LOG_(INFO) << "WriteImageData_ValidData_001 end";
}

/**
 * @tc.name: IsValidSize_ValidSize_001
 * @tc.type: FUNC
 * @tc.desc: Verify isValidSize with valid size.
 */
HWTEST_F(FmsFormProviderDataTest, IsValidSize_ValidSize_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "IsValidSize_ValidSize_001 start";
    FormProviderData formProviderData("");
    EXPECT_TRUE(formProviderData.isValidSize(100));
    EXPECT_TRUE(formProviderData.isValidSize(INT32_MAX));
    GTEST_LOG_(INFO) << "IsValidSize_ValidSize_001 end";
}

/**
 * @tc.name: IsValidSize_NegativeSize_001
 * @tc.type: FUNC
 * @tc.desc: Verify isValidSize with invalid size (zero and negative).
 */
HWTEST_F(FmsFormProviderDataTest, IsValidSize_NegativeSize_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "IsValidSize_NegativeSize_001 start";
    FormProviderData formProviderData("");
    EXPECT_FALSE(formProviderData.isValidSize(0));
    EXPECT_FALSE(formProviderData.isValidSize(-1));
    EXPECT_FALSE(formProviderData.isValidSize(-100));
    GTEST_LOG_(INFO) << "IsValidSize_NegativeSize_001 end";
}

/**
 * @tc.name: IsValidSize_ExceedInt32Max_001
 * @tc.type: FUNC
 * @tc.desc: Verify isValidSize with size exceeds INT32_MAX.
 */
HWTEST_F(FmsFormProviderDataTest, IsValidSize_ExceedInt32Max_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "IsValidSize_ExceedInt32Max_001 start";
    FormProviderData formProviderData("");
    EXPECT_FALSE(formProviderData.isValidSize(static_cast<off_t>(INT32_MAX) + 1));
    EXPECT_FALSE(formProviderData.isValidSize(static_cast<off_t>(INT32_MAX) + 1000));
    GTEST_LOG_(INFO) << "IsValidSize_ExceedInt32Max_001 end";
}

/**
 * @tc.name: HandleImageAdded_ZeroCount_001
 * @tc.type: FUNC
 * @tc.desc: Verify HandleImageDataStateAdded with imageDataNum is zero.
 */
HWTEST_F(FmsFormProviderDataTest, HandleImageAdded_ZeroCount_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "HandleImageAdded_ZeroCount_001 start";
    InitJsonData();
    FormProviderData formProviderData(jsonData_);
    Parcel parcel;
    parcel.WriteInt32(0);
    bool result = formProviderData.HandleImageDataStateAdded(parcel);
    EXPECT_TRUE(result);
    GTEST_LOG_(INFO) << "HandleImageAdded_ZeroCount_001 end";
}

/**
 * @tc.name: MarshallingUnmarshalling_WithImage_001
 * @tc.type: FUNC
 * @tc.desc: Verify Marshalling and Unmarshalling with image data and comprehensive state verification.
 */
HWTEST_F(FmsFormProviderDataTest, MarshallingUnmarshalling_WithImage_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "MarshallingUnmarshalling_WithImage_001 start";
    InitJsonData();
    FormProviderData writeProviderData(jsonData_);
    std::shared_ptr<char[]> data = std::make_shared<char[]>(10);
    std::fill(data.get(), data.get() + 10, 'B');
    writeProviderData.AddImageData("marshTest", data, 10);
    writeProviderData.imageDataState_ = FormProviderData::IMAGE_DATA_STATE_ADDED;
    
    auto writeJsonData = writeProviderData.GetData();
    auto writeImageDataState = writeProviderData.GetImageDataState();
    auto writeRawImageBytesMapSize = writeProviderData.rawImageBytesMap_.size();
    
    Parcel parcel;
    EXPECT_TRUE(writeProviderData.Marshalling(parcel));
    
    std::unique_ptr<FormProviderData> readProviderData(FormProviderData::Unmarshalling(parcel));
    ASSERT_NE(readProviderData, nullptr);
    
    auto readJsonData = readProviderData->GetData();
    EXPECT_EQ(readJsonData.dump(), writeJsonData.dump());
    EXPECT_FALSE(readProviderData->jsonFormProviderData_.empty());
    EXPECT_EQ(readProviderData->GetImageDataState(), writeImageDataState);
    EXPECT_EQ(readProviderData->GetImageDataMap().size(), writeRawImageBytesMapSize);
    EXPECT_TRUE(readProviderData->HasData());
    
    auto readImageDataMap = readProviderData->GetImageDataMap();
    ASSERT_TRUE(readImageDataMap.find("marshTest") != readImageDataMap.end());
    auto formAshmem = readImageDataMap["marshTest"].first;
    ASSERT_NE(formAshmem, nullptr);
    EXPECT_EQ(formAshmem->GetAshmemSize(), 10);
    
    GTEST_LOG_(INFO) << "MarshallingUnmarshalling_WithImage_001 end";
}

/**
 * @tc.name: WriteFormData_EmptyJson_001
 * @tc.type: FUNC
 * @tc.desc: Verify WriteFormData with empty json data.
 */
HWTEST_F(FmsFormProviderDataTest, WriteFormData_EmptyJson_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "WriteFormData_EmptyJson_001 start";
    FormProviderData formProviderData("");
    formProviderData.jsonFormProviderData_.clear();
    Parcel parcel;
    bool result = formProviderData.WriteFormData(parcel);
    EXPECT_TRUE(result);
    GTEST_LOG_(INFO) << "WriteFormData_EmptyJson_001 end";
}

/**
 * @tc.name: WriteFormData_NormalJson_001
 * @tc.type: FUNC
 * @tc.desc: Verify WriteFormData with normal json data.
 */
HWTEST_F(FmsFormProviderDataTest, WriteFormData_NormalJson_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "WriteFormData_NormalJson_001 start";
    InitJsonData();
    FormProviderData formProviderData(jsonData_);
    Parcel parcel;
    bool result = formProviderData.WriteFormData(parcel);
    EXPECT_TRUE(result);
    GTEST_LOG_(INFO) << "WriteFormData_NormalJson_001 end";
}

/**
 * @tc.name: ParseImages_ValidFd_001
 * @tc.type: FUNC
 * @tc.desc: Verify ParseImagesData with valid fd in json.
 */
HWTEST_F(FmsFormProviderDataTest, ParseImages_ValidFd_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "ParseImages_ValidFd_001 start";
    std::string testFile = FORM_DB_DATA_BASE_FILE_DIR + "/test_parse_image.tmp";
    std::ofstream file(testFile);
    file << "test data";
    file.close();
    int fd = open(testFile.c_str(), O_RDONLY);
    ASSERT_GE(fd, 0);
    std::string jsonStr = R"({"formImages": {"parseTest": )" + std::to_string(fd) + R"(}})";
    FormProviderData formProviderData(jsonStr);
    close(fd);
    unlink(testFile.c_str());
    GTEST_LOG_(INFO) << "ParseImages_ValidFd_001 end";
}

/**
 * @tc.name: AddImageData_StateUpdate_001
 * @tc.type: FUNC
 * @tc.desc: Verify AddImageData with shared_ptr and size updates imageDataState.
 */
HWTEST_F(FmsFormProviderDataTest, AddImageData_StateUpdate_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "AddImageData_StateUpdate_001 start";
    InitJsonData();
    FormProviderData formProviderData(jsonData_);
    std::shared_ptr<char[]> data = std::make_shared<char[]>(10);
    formProviderData.AddImageData("stateTest", data, 10);
    EXPECT_EQ(formProviderData.GetImageDataState(), FormProviderData::IMAGE_DATA_STATE_ADDED);
    GTEST_LOG_(INFO) << "AddImageData_StateUpdate_001 end";
}

/**
 * @tc.name: Marshalling_MultiImages_001
 * @tc.type: FUNC
 * @tc.desc: Verify Marshalling with IMAGE_DATA_STATE_ADDED and multiple images.
 */
HWTEST_F(FmsFormProviderDataTest, Marshalling_MultiImages_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Marshalling_MultiImages_001 start";
    InitJsonData();
    FormProviderData formProviderData(jsonData_);
    std::shared_ptr<char[]> data1 = std::make_shared<char[]>(20);
    std::shared_ptr<char[]> data2 = std::make_shared<char[]>(30);
    formProviderData.AddImageData("multi1", data1, 20);
    formProviderData.AddImageData("multi2", data2, 30);
    formProviderData.imageDataState_ = FormProviderData::IMAGE_DATA_STATE_ADDED;
    Parcel parcel;
    bool result = formProviderData.Marshalling(parcel);
    EXPECT_TRUE(result);
    GTEST_LOG_(INFO) << "Marshalling_MultiImages_001 end";
}

/**
 * @tc.name: ReadFromParcel_EmptyJson_001
 * @tc.type: FUNC
 * @tc.desc: Verify ReadFromParcel with empty json string.
 */
HWTEST_F(FmsFormProviderDataTest, ReadFromParcel_EmptyJson_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "ReadFromParcel_EmptyJson_001 start";
    FormProviderData formProviderData("");
    Parcel parcel;
    parcel.WriteInt32(2);
    parcel.WriteString16(Str8ToStr16("{}"));
    parcel.WriteInt32(FormProviderData::IMAGE_DATA_STATE_NO_OPERATION);
    bool result = formProviderData.ReadFromParcel(parcel);
    EXPECT_TRUE(result);
    GTEST_LOG_(INFO) << "ReadFromParcel_EmptyJson_001 end";
}

/**
 * @tc.name: ReadFromParcel_NullJson_001
 * @tc.type: FUNC
 * @tc.desc: Verify ReadFromParcel with invalid json string and verify comprehensive state changes.
 */
HWTEST_F(FmsFormProviderDataTest, ReadFromParcel_NullJson_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "ReadFromParcel_NullJson_001 start";
    FormProviderData formProviderData("");
    auto initialDataString = formProviderData.GetDataString();
    Parcel parcel;
    parcel.WriteInt32(11);
    parcel.WriteString16(Str8ToStr16("{invalid json}"));
    parcel.WriteInt32(FormProviderData::IMAGE_DATA_STATE_NO_OPERATION);
    bool result = formProviderData.ReadFromParcel(parcel);
    EXPECT_FALSE(result);
    EXPECT_TRUE(formProviderData.jsonFormProviderData_.empty());
    EXPECT_EQ(formProviderData.imageDataState_, FormProviderData::IMAGE_DATA_STATE_NO_OPERATION);
    EXPECT_EQ(formProviderData.GetImageDataState(), FormProviderData::IMAGE_DATA_STATE_NO_OPERATION);
    EXPECT_TRUE(formProviderData.GetImageDataMap().empty());
    EXPECT_EQ(formProviderData.GetDataString(), initialDataString);
    EXPECT_FALSE(formProviderData.HasData());
    GTEST_LOG_(INFO) << "ReadFromParcel_NullJson_001 end";
}

/**
 * @tc.name: HasData_OnlyImageMap_001
 * @tc.type: FUNC
 * @tc.desc: Verify HasData with only imageDataMap.
 */
HWTEST_F(FmsFormProviderDataTest, HasData_OnlyImageMap_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "HasData_OnlyImageMap_001 start";
    FormProviderData formProviderData("");
    formProviderData.jsonFormProviderData_.clear();
    std::map<std::string, std::pair<sptr<FormAshmem>, int32_t>> imageDataMap;
    sptr<FormAshmem> formAshmem(new (std::nothrow) FormAshmem());
    imageDataMap["hasDataTest"] = std::make_pair(formAshmem, 10);
    formProviderData.SetImageDataMap(imageDataMap);
    EXPECT_TRUE(formProviderData.HasData());
    GTEST_LOG_(INFO) << "HasData_OnlyImageMap_001 end";
}

/**
 * @tc.name: AddImageData_FileTooLarge_001
 * @tc.type: FUNC
 * @tc.desc: Verify AddImageData when file size exceeds MAX_IMAGE_BYTE_SIZE.
 */
HWTEST_F(FmsFormProviderDataTest, AddImageData_FileTooLarge_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "AddImageData_FileTooLarge_001 start";
    FormProviderData formProviderData("");
    std::string picName = "largeImage";
    std::string testFile = FORM_DB_DATA_BASE_FILE_DIR + "/test_large_image.tmp";
    int fd = open(testFile.c_str(), O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    ASSERT_GE(fd, 0);
    std::string largeData(51 * 1024 * 1024, 'A');
    write(fd, largeData.c_str(), largeData.size());
    close(fd);
    fd = open(testFile.c_str(), O_RDONLY);
    ASSERT_GE(fd, 0);
    formProviderData.AddImageData(picName, fd);
    close(fd);
    unlink(testFile.c_str());
    EXPECT_TRUE(formProviderData.rawImageBytesMap_.find(picName) == formProviderData.rawImageBytesMap_.end());
    GTEST_LOG_(INFO) << "AddImageData_FileTooLarge_001 end";
}

/**
 * @tc.name: ReadAshmemDataFromParcel_InvalidBufferSize_001
 * @tc.type: FUNC
 * @tc.desc: Verify ReadAshmemDataFromParcel with invalid buffer size (zero and negative).
 */
HWTEST_F(FmsFormProviderDataTest, ReadAshmemDataFromParcel_InvalidBufferSize_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "ReadAshmemDataFromParcel_InvalidBufferSize_001 start";
    FormProviderData formProviderData("");
    Parcel parcel;
    char *result1 = formProviderData.ReadAshmemDataFromParcel(parcel, 0);
    EXPECT_EQ(result1, nullptr);
    char *result2 = formProviderData.ReadAshmemDataFromParcel(parcel, -1);
    EXPECT_EQ(result2, nullptr);
    GTEST_LOG_(INFO) << "ReadAshmemDataFromParcel_InvalidBufferSize_001 end";
}

/**
 * @tc.name: WriteFileDescriptor_DupFailed_001
 * @tc.type: FUNC
 * @tc.desc: Verify WriteFileDescriptor when dup fails (invalid fd).
 */
HWTEST_F(FmsFormProviderDataTest, WriteFileDescriptor_DupFailed_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "WriteFileDescriptor_DupFailed_001 start";
    FormProviderData formProviderData("");
    Parcel parcel;
    int invalidFd = -1;
    bool result = formProviderData.WriteFileDescriptor(parcel, invalidFd);
    EXPECT_FALSE(result);
    GTEST_LOG_(INFO) << "WriteFileDescriptor_DupFailed_001 end";
}

/**
 * @tc.name: HandleImageDataStateAdded_NullAshmem_001
 * @tc.type: FUNC
 * @tc.desc: Verify HandleImageDataStateAdded when ReadParcelable returns nullptr.
 */
HWTEST_F(FmsFormProviderDataTest, HandleImageDataStateAdded_NullAshmem_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "HandleImageDataStateAdded_NullAshmem_001 start";
    FormProviderData formProviderData("");
    Parcel parcel;
    parcel.WriteInt32(1);
    parcel.WriteParcelable(nullptr);
    bool result = formProviderData.HandleImageDataStateAdded(parcel);
    EXPECT_FALSE(result);
    GTEST_LOG_(INFO) << "HandleImageDataStateAdded_NullAshmem_001 end";
}

/**
 * @tc.name: ConvertRawImageData_EmptyMap_001
 * @tc.type: FUNC
 * @tc.desc: Verify ConvertRawImageData with empty rawImageBytesMap_.
 */
HWTEST_F(FmsFormProviderDataTest, ConvertRawImageData_EmptyMap_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "ConvertRawImageData_EmptyMap_001 start";
    FormProviderData formProviderData("");
    bool result = formProviderData.ConvertRawImageData();
    EXPECT_TRUE(result);
    EXPECT_TRUE(formProviderData.GetImageDataMap().empty());
    GTEST_LOG_(INFO) << "ConvertRawImageData_EmptyMap_001 end";
}

/**
 * @tc.name: IsValidSize_ZeroSize_001
 * @tc.type: FUNC
 * @tc.desc: Verify isValidSize with zero size.
 */
HWTEST_F(FmsFormProviderDataTest, IsValidSize_ZeroSize_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "IsValidSize_ZeroSize_001 start";
    FormProviderData formProviderData("");
    EXPECT_FALSE(formProviderData.isValidSize(0));
    GTEST_LOG_(INFO) << "IsValidSize_ZeroSize_001 end";
}

/**
 * @tc.name: ParseImagesData_NonIntegerFd_001
 * @tc.type: FUNC
 * @tc.desc: Verify ParseImagesData when fd in json is not integer.
 */
HWTEST_F(FmsFormProviderDataTest, ParseImagesData_NonIntegerFd_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "ParseImagesData_NonIntegerFd_001 start";
    std::string jsonStr = R"({"formImages": {"image1": "not_an_integer"}})";
    FormProviderData formProviderData(jsonStr);
    EXPECT_TRUE(formProviderData.rawImageBytesMap_.empty());
    GTEST_LOG_(INFO) << "ParseImagesData_NonIntegerFd_001 end";
}

/**
 * @tc.name: ReadFromParcel_BigDataNullRawData_001
 * @tc.type: FUNC
 * @tc.desc: Verify ReadFromParcel when ReadAshmemDataFromParcel returns nullptr for big data.
 */
HWTEST_F(FmsFormProviderDataTest, ReadFromParcel_BigDataNullRawData_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "ReadFromParcel_BigDataNullRawData_001 start";
    FormProviderData formProviderData("");
    Parcel parcel;
    parcel.WriteInt32(35000);
    parcel.WriteParcelable(nullptr);
    bool result = formProviderData.ReadFromParcel(parcel);
    EXPECT_FALSE(result);
    GTEST_LOG_(INFO) << "ReadFromParcel_BigDataNullRawData_001 end";
}

/**
 * @tc.name: Marshalling_WriteImageDataFailed_001
 * @tc.type: FUNC
 * @tc.desc: Verify Marshalling with invalid image data state.
 */
HWTEST_F(FmsFormProviderDataTest, Marshalling_WriteImageDataFailed_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Marshalling_WriteImageDataFailed_001 start";
    FormProviderData formProviderData("");
    std::shared_ptr<char> validData = std::make_shared<char>('a');
    formProviderData.AddImageData("test", validData, 1);
    formProviderData.imageDataState_ = FormProviderData::IMAGE_DATA_STATE_NO_OPERATION;
    Parcel parcel;
    bool result = formProviderData.Marshalling(parcel);
    EXPECT_TRUE(result);
    GTEST_LOG_(INFO) << "Marshalling_WriteImageDataFailed_001 end";
}

/**
 * @tc.name: ReadFileDescriptor_NullDescriptor_001
 * @tc.type: FUNC
 * @tc.desc: Verify ReadFileDescriptor when ReadObject returns nullptr.
 */
HWTEST_F(FmsFormProviderDataTest, ReadFileDescriptor_NullDescriptor_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "ReadFileDescriptor_NullDescriptor_001 start";
    FormProviderData formProviderData("");
    Parcel parcel;
    parcel.WriteParcelable(nullptr);
    int fd = formProviderData.ReadFileDescriptor(parcel);
    EXPECT_EQ(fd, -1);
    GTEST_LOG_(INFO) << "ReadFileDescriptor_NullDescriptor_001 end";
}

/**
 * @tc.name: CheckAshmemSize_InvalidFd_001
 * @tc.type: FUNC
 * @tc.desc: Verify CheckAshmemSize with invalid fd.
 */
HWTEST_F(FmsFormProviderDataTest, CheckAshmemSize_InvalidFd_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "CheckAshmemSize_InvalidFd_001 start";
    int fd = -1;
    int32_t bufferSize = 1024;
    bool isAstc = false;
    bool result = FormProviderData::CheckAshmemSize(fd, bufferSize, isAstc);
    EXPECT_FALSE(result);
    GTEST_LOG_(INFO) << "CheckAshmemSize_InvalidFd_001 end";
}

/**
 * @tc.name: WriteAshmemDataToParcel_LargeData_001
 * @tc.type: FUNC
 * @tc.desc: Verify WriteAshmemDataToParcel with large data (100KB).
 */
HWTEST_F(FmsFormProviderDataTest, WriteAshmemDataToParcel_LargeData_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "WriteAshmemDataToParcel_LargeData_001 start";
    FormProviderData formProviderData("");
    Parcel parcel;
    std::string largeData(100 * 1024, 'B');
    size_t size = largeData.length();
    bool result = formProviderData.WriteAshmemDataToParcel(parcel, size, largeData.c_str());
    EXPECT_TRUE(result);
    GTEST_LOG_(INFO) << "WriteAshmemDataToParcel_LargeData_001 end";
}

/**
 * @tc.name: AddImageData_ValidFd_001
 * @tc.type: FUNC
 * @tc.desc: Verify AddImageData with valid file descriptor and small file.
 */
HWTEST_F(FmsFormProviderDataTest, AddImageData_ValidFd_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "AddImageData_ValidFd_001 start";
    FormProviderData formProviderData("");
    std::string picName = "validImage";
    std::string testData = "test image data content";
    std::string testFile = FORM_DB_DATA_BASE_FILE_DIR + "/test_valid_image_001.tmp";
    std::ofstream file(testFile);
    file << testData;
    file.close();
    int fd = open(testFile.c_str(), O_RDONLY);
    ASSERT_GE(fd, 0);
    formProviderData.AddImageData(picName, fd);
    close(fd);
    unlink(testFile.c_str());
    EXPECT_TRUE(formProviderData.rawImageBytesMap_.find(picName) != formProviderData.rawImageBytesMap_.end());
    EXPECT_EQ(formProviderData.rawImageBytesMap_[picName].second, static_cast<int32_t>(testData.length()));
    EXPECT_EQ(formProviderData.imageDataState_, FormProviderData::IMAGE_DATA_STATE_ADDED);
    GTEST_LOG_(INFO) << "AddImageData_ValidFd_001 end";
}

/**
 * @tc.name: ReadFromParcel_InvalidJsonString_001
 * @tc.type: FUNC
 * @tc.desc: Verify ReadFromParcel with invalid json string in parcel.
 */
HWTEST_F(FmsFormProviderDataTest, ReadFromParcel_InvalidJsonString_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "ReadFromParcel_InvalidJsonString_001 start";
    FormProviderData formProviderData("");
    Parcel parcel;
    parcel.WriteInt32(15);
    parcel.WriteString16(Str8ToStr16("{invalid json}"));
    bool result = formProviderData.ReadFromParcel(parcel);
    EXPECT_FALSE(result);
    GTEST_LOG_(INFO) << "ReadFromParcel_InvalidJsonString_001 end";
}

/**
 * @tc.name: ConvertRawImageData_MultiImages_001
 * @tc.type: FUNC
 * @tc.desc: Verify ConvertRawImageData with multiple images in rawImageBytesMap_.
 */
HWTEST_F(FmsFormProviderDataTest, ConvertRawImageData_MultiImages_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "ConvertRawImageData_MultiImages_001 start";
    FormProviderData formProviderData("");
    std::shared_ptr<char[]> data1 = std::make_shared<char[]>(10);
    std::shared_ptr<char[]> data2 = std::make_shared<char[]>(20);
    formProviderData.AddImageData("image1", data1, 10);
    formProviderData.AddImageData("image2", data2, 20);
    EXPECT_EQ(2, static_cast<int>(formProviderData.rawImageBytesMap_.size()));
    bool result = formProviderData.ConvertRawImageData();
    EXPECT_TRUE(result);
    EXPECT_EQ(2, static_cast<int>(formProviderData.GetImageDataMap().size()));
    EXPECT_TRUE(formProviderData.rawImageBytesMap_.empty());
    GTEST_LOG_(INFO) << "ConvertRawImageData_MultiImages_001 end";
}

/**
 * @tc.name: ClearData_WithJsonData_001
 * @tc.type: FUNC
 * @tc.desc: Verify ClearData clears jsonFormProviderData_.
 */
HWTEST_F(FmsFormProviderDataTest, ClearData_WithJsonData_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "ClearData_WithJsonData_001 start";
    FormProviderData formProviderData("{\"key\": \"value\"}");
    EXPECT_FALSE(formProviderData.jsonFormProviderData_.empty());
    formProviderData.ClearData();
    EXPECT_TRUE(formProviderData.jsonFormProviderData_.empty());
    GTEST_LOG_(INFO) << "ClearData_WithJsonData_001 end";
}

/**
 * @tc.name: UpdateData_WithNewJson_001
 * @tc.type: FUNC
 * @tc.desc: Verify UpdateData replaces old json data with new json data.
 */
HWTEST_F(FmsFormProviderDataTest, UpdateData_WithNewJson_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "UpdateData_WithNewJson_001 start";
    nlohmann::json oldJson;
    oldJson["old"] = "value";
    FormProviderData formProviderData(oldJson);
    nlohmann::json newJson;
    newJson["new"] = "data";
    formProviderData.UpdateData(newJson);
    auto data = formProviderData.GetData();
    EXPECT_EQ(data["new"], "data");
    EXPECT_TRUE(data.find("old") == data.end());
    GTEST_LOG_(INFO) << "UpdateData_WithNewJson_001 end";
}

/**
 * @tc.name: RemoveImageData_ExistingImage_001
 * @tc.type: FUNC
 * @tc.desc: Verify RemoveImageData removes existing image from rawImageBytesMap_.
 */
HWTEST_F(FmsFormProviderDataTest, RemoveImageData_ExistingImage_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RemoveImageData_ExistingImage_001 start";
    FormProviderData formProviderData("");
    std::shared_ptr<char> data = std::make_shared<char>('a');
    formProviderData.AddImageData("toRemove", data, 1);
    EXPECT_EQ(1, formProviderData.rawImageBytesMap_.size());
    formProviderData.RemoveImageData("toRemove");
    EXPECT_TRUE(formProviderData.rawImageBytesMap_.empty());
    GTEST_LOG_(INFO) << "RemoveImageData_ExistingImage_001 end";
}

/**
 * @tc.name: WriteImageDataToParcel_ValidData_001
 * @tc.type: FUNC
 * @tc.desc: Verify WriteImageDataToParcel with valid image data.
 */
HWTEST_F(FmsFormProviderDataTest, WriteImageDataToParcel_ValidData_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "WriteImageDataToParcel_ValidData_001 start";
    FormProviderData formProviderData("");
    Parcel parcel;
    std::string picName = "validImage";
    std::shared_ptr<char[]> data = std::make_shared<char[]>(100);
    std::fill(data.get(), data.get() + 100, 'A');
    bool result = formProviderData.WriteImageDataToParcel(parcel, picName, data, 100);
    EXPECT_TRUE(result);
    GTEST_LOG_(INFO) << "WriteImageDataToParcel_ValidData_001 end";
}

/**
 * @tc.name: WriteImageDataToParcel_EmptyData_001
 * @tc.type: FUNC
 * @tc.desc: Verify WriteImageDataToParcel with empty data (size=1).
 */
HWTEST_F(FmsFormProviderDataTest, WriteImageDataToParcel_EmptyData_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "WriteImageDataToParcel_EmptyData_001 start";
    FormProviderData formProviderData("");
    Parcel parcel;
    std::string picName = "emptyImage";
    std::shared_ptr<char[]> data = std::make_shared<char[]>(1);
    data.get()[0] = '\0';
    bool result = formProviderData.WriteImageDataToParcel(parcel, picName, data, 1);
    EXPECT_TRUE(result);
    GTEST_LOG_(INFO) << "WriteImageDataToParcel_EmptyData_001 end";
}

/**
 * @tc.name: ReadFromParcel_ImageDataStateAdded_001
 * @tc.type: FUNC
 * @tc.desc: Verify ReadFromParcel with IMAGE_DATA_STATE_ADDED and zero imageDataNum.
 */
HWTEST_F(FmsFormProviderDataTest, ReadFromParcel_ImageDataStateAdded_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "ReadFromParcel_ImageDataStateAdded_001 start";
    FormProviderData formProviderData("");
    Parcel parcel;
    parcel.WriteInt32(2);
    parcel.WriteString16(Str8ToStr16("{}"));
    parcel.WriteInt32(FormProviderData::IMAGE_DATA_STATE_ADDED);
    parcel.WriteInt32(0);
    bool result = formProviderData.ReadFromParcel(parcel);
    EXPECT_TRUE(result);
    GTEST_LOG_(INFO) << "ReadFromParcel_ImageDataStateAdded_001 end";
}

/**
 * @tc.name: Marshalling_WithDefaultState_001
 * @tc.type: FUNC
 * @tc.desc: Verify Marshalling with default imageDataState_ (NO_OPERATION).
 */
HWTEST_F(FmsFormProviderDataTest, Marshalling_WithDefaultState_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Marshalling_WithDefaultState_001 start";
    FormProviderData formProviderData("{\"key\": \"value\"}");
    formProviderData.imageDataState_ = FormProviderData::IMAGE_DATA_STATE_NO_OPERATION;
    Parcel parcel;
    bool result = formProviderData.Marshalling(parcel);
    EXPECT_TRUE(result);
    GTEST_LOG_(INFO) << "Marshalling_WithDefaultState_001 end";
}

/**
 * @tc.name: Marshalling_WithRemovedState_001
 * @tc.type: FUNC
 * @tc.desc: Verify Marshalling with IMAGE_DATA_STATE_REMOVED.
 */
HWTEST_F(FmsFormProviderDataTest, Marshalling_WithRemovedState_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Marshalling_WithRemovedState_001 start";
    FormProviderData formProviderData("{\"key\": \"value\"}");
    formProviderData.imageDataState_ = FormProviderData::IMAGE_DATA_STATE_REMOVED;
    Parcel parcel;
    bool result = formProviderData.Marshalling(parcel);
    EXPECT_TRUE(result);
    GTEST_LOG_(INFO) << "Marshalling_WithRemovedState_001 end";
}

/**
 * @tc.name: WriteFormData_BigData_001
 * @tc.type: FUNC
 * @tc.desc: Verify WriteFormData with big data (> BIG_DATA) uses ashmem.
 */
HWTEST_F(FmsFormProviderDataTest, WriteFormData_BigData_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "WriteFormData_BigData_001 start";
    std::string bigJsonStr = R"({"data": ")" + std::string(35000, 'C') + R"("})";
    FormProviderData formProviderData(bigJsonStr);
    Parcel parcel;
    bool result = formProviderData.WriteFormData(parcel);
    EXPECT_TRUE(result);
    GTEST_LOG_(INFO) << "WriteFormData_BigData_001 end";
}

/**
 * @tc.name: AddImageData_NullData_001
 * @tc.type: FUNC
 * @tc.desc: Verify AddImageData with null shared_ptr data.
 */
HWTEST_F(FmsFormProviderDataTest, AddImageData_NullData_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "AddImageData_NullData_001 start";
    FormProviderData formProviderData("");
    std::string picName = "nullDataImage";
    std::shared_ptr<char> nullData = nullptr;
    formProviderData.AddImageData(picName, nullData, 10);
    EXPECT_TRUE(formProviderData.rawImageBytesMap_.find(picName) == formProviderData.rawImageBytesMap_.end());
    GTEST_LOG_(INFO) << "AddImageData_NullData_001 end";
}

/**
 * @tc.name: AddImageData_EmptyPicName_001
 * @tc.type: FUNC
 * @tc.desc: Verify AddImageData with empty picName.
 */
HWTEST_F(FmsFormProviderDataTest, AddImageData_EmptyPicName_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "AddImageData_EmptyPicName_001 start";
    FormProviderData formProviderData("");
    std::string emptyPicName = "";
    std::shared_ptr<char> data = std::make_shared<char>('a');
    formProviderData.AddImageData(emptyPicName, data, 1);
    EXPECT_TRUE(formProviderData.rawImageBytesMap_.find(emptyPicName) == formProviderData.rawImageBytesMap_.end());
    GTEST_LOG_(INFO) << "AddImageData_EmptyPicName_001 end";
}

/**
 * @tc.name: ParseImagesData_NoFormImages_001
 * @tc.type: FUNC
 * @tc.desc: Verify ParseImagesData when json does not contain formImages key.
 */
HWTEST_F(FmsFormProviderDataTest, ParseImagesData_NoFormImages_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "ParseImagesData_NoFormImages_001 start";
    std::string jsonStr = R"({"key": "value"})";
    FormProviderData formProviderData(jsonStr);
    formProviderData.ParseImagesData();
    EXPECT_TRUE(formProviderData.rawImageBytesMap_.empty());
    GTEST_LOG_(INFO) << "ParseImagesData_NoFormImages_001 end";
}

/**
 * @tc.name: SetImageDataState_CustomValue_001
 * @tc.type: FUNC
 * @tc.desc: Verify SetImageDataState sets custom value.
 */
HWTEST_F(FmsFormProviderDataTest, SetImageDataState_CustomValue_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "SetImageDataState_CustomValue_001 start";
    FormProviderData formProviderData("");
    constexpr int32_t customValue = 999;
    formProviderData.SetImageDataState(customValue);
    EXPECT_EQ(customValue, formProviderData.GetImageDataState());
    GTEST_LOG_(INFO) << "SetImageDataState_CustomValue_001 end";
}

/**
 * @tc.name: GetImageDataMap_Empty_001
 * @tc.type: FUNC
 * @tc.desc: Verify GetImageDataMap returns empty map when no images.
 */
HWTEST_F(FmsFormProviderDataTest, GetImageDataMap_Empty_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "GetImageDataMap_Empty_001 start";
    FormProviderData formProviderData("");
    auto imageMap = formProviderData.GetImageDataMap();
    EXPECT_TRUE(imageMap.empty());
    GTEST_LOG_(INFO) << "GetImageDataMap_Empty_001 end";
}

/**
 * @tc.name: GetImageDataState_Default_001
 * @tc.type: FUNC
 * @tc.desc: Verify GetImageDataState returns default value (0).
 */
HWTEST_F(FmsFormProviderDataTest, GetImageDataState_Default_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "GetImageDataState_Default_001 start";
    FormProviderData formProviderData("");
    EXPECT_EQ(0, formProviderData.GetImageDataState());
    GTEST_LOG_(INFO) << "GetImageDataState_Default_001 end";
}

/**
 * @tc.name: Unmarshalling_ValidParcel_001
 * @tc.type: FUNC
 * @tc.desc: Verify Unmarshalling creates valid FormProviderData from parcel with consistent data.
 */
HWTEST_F(FmsFormProviderDataTest, Unmarshalling_ValidParcel_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Unmarshalling_ValidParcel_001 start";
    nlohmann::json originalJson;
    originalJson["name"] = "test";
    originalJson["value"] = 123;
    FormProviderData writeProviderData(originalJson);
    writeProviderData.SetImageDataState(1);
    
    Parcel parcel;
    EXPECT_TRUE(writeProviderData.Marshalling(parcel));
    
    std::unique_ptr<FormProviderData> readProviderData(FormProviderData::Unmarshalling(parcel));
    ASSERT_NE(readProviderData, nullptr);
    
    nlohmann::json writeJson = writeProviderData.GetData();
    nlohmann::json readJson = readProviderData->GetData();
    EXPECT_EQ(writeJson.dump(), readJson.dump());
    EXPECT_EQ(readJson["name"], "test");
    EXPECT_EQ(readJson["value"], 123);
    
    EXPECT_EQ(writeProviderData.GetImageDataState(), readProviderData->GetImageDataState());
    EXPECT_FALSE(readProviderData->GetDataString().empty());
    
    GTEST_LOG_(INFO) << "Unmarshalling_ValidParcel_001 end";
}

/**
 * @tc.name: Constructor_NullJson_001
 * @tc.type: FUNC
 * @tc.desc: Verify constructor with nullptr json.
 */
HWTEST_F(FmsFormProviderDataTest, Constructor_NullJson_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Constructor_NullJson_001 start";
    nlohmann::json jsonNull = nullptr;
    FormProviderData formProviderData(jsonNull);
    EXPECT_TRUE(formProviderData.jsonFormProviderData_.empty());
    GTEST_LOG_(INFO) << "Constructor_NullJson_001 end";
}

/**
 * @tc.name: Constructor_StringJson_001
 * @tc.type: FUNC
 * @tc.desc: Verify constructor with string type json.
 */
HWTEST_F(FmsFormProviderDataTest, Constructor_StringJson_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Constructor_StringJson_001 start";
    nlohmann::json jsonString = "test string";
    FormProviderData formProviderData(jsonString);
    EXPECT_TRUE(formProviderData.jsonFormProviderData_.empty());
    GTEST_LOG_(INFO) << "Constructor_StringJson_001 end";
}

/**
 * @tc.name: ReadFromParcel_ImageDataStateRemoved_001
 * @tc.type: FUNC
 * @tc.desc: Verify ReadFromParcel with IMAGE_DATA_STATE_REMOVED.
 */
HWTEST_F(FmsFormProviderDataTest, ReadFromParcel_ImageDataStateRemoved_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "ReadFromParcel_ImageDataStateRemoved_001 start";
    FormProviderData formProviderData("");
    Parcel parcel;
    parcel.WriteInt32(2);
    parcel.WriteString16(Str8ToStr16("{}"));
    parcel.WriteInt32(FormProviderData::IMAGE_DATA_STATE_REMOVED);
    bool result = formProviderData.ReadFromParcel(parcel);
    EXPECT_TRUE(result);
    GTEST_LOG_(INFO) << "ReadFromParcel_ImageDataStateRemoved_001 end";
}

/**
 * @tc.name: ReadFromParcel_UnknownImageDataState_001
 * @tc.type: FUNC
 * @tc.desc: Verify ReadFromParcel with unknown imageDataState value.
 */
HWTEST_F(FmsFormProviderDataTest, ReadFromParcel_UnknownImageDataState_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "ReadFromParcel_UnknownImageDataState_001 start";
    FormProviderData formProviderData("");
    Parcel parcel;
    parcel.WriteInt32(2);
    parcel.WriteString16(Str8ToStr16("{}"));
    parcel.WriteInt32(999);
    bool result = formProviderData.ReadFromParcel(parcel);
    EXPECT_TRUE(result);
    GTEST_LOG_(INFO) << "ReadFromParcel_UnknownImageDataState_001 end";
}

/**
 * @tc.name: Marshalling_UnknownImageDataState_001
 * @tc.type: FUNC
 * @tc.desc: Verify Marshalling with unknown imageDataState value.
 */
HWTEST_F(FmsFormProviderDataTest, Marshalling_UnknownImageDataState_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Marshalling_UnknownImageDataState_001 start";
    FormProviderData formProviderData("{\"key\": \"value\"}");
    formProviderData.imageDataState_ = 999;
    Parcel parcel;
    bool result = formProviderData.Marshalling(parcel);
    EXPECT_TRUE(result);
    GTEST_LOG_(INFO) << "Marshalling_UnknownImageDataState_001 end";
}

/**
 * @tc.name: ReadFromParcel_ImageDataNumExceed_002
 * @tc.type: FUNC
 * @tc.desc: Verify ReadFromParcel when imageDataNum exceeds READ_PARCEL_MAX_IMAGE_DATA_NUM_SIZE.
 */
HWTEST_F(FmsFormProviderDataTest, ReadFromParcel_ImageDataNumExceed_002, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "ReadFromParcel_ImageDataNumExceed_002 start";
    FormProviderData formProviderData("");
    Parcel parcel;
    parcel.WriteInt32(2);
    parcel.WriteString16(Str8ToStr16("{}"));
    parcel.WriteInt32(FormProviderData::IMAGE_DATA_STATE_ADDED);
    parcel.WriteInt32(1001);
    bool result = formProviderData.ReadFromParcel(parcel);
    EXPECT_FALSE(result);
    GTEST_LOG_(INFO) << "ReadFromParcel_ImageDataNumExceed_002 end";
}

}  // namespace OHOS::AppExecFwk
