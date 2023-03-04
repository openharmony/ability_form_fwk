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

#include <gtest/gtest.h>

#include "form_constants.h"
#include "form_js_info.h"
#include "form_mgr_errors.h"
#define private public
#include "form_render_impl.h"
#undef private
#include "gmock/gmock.h"
#include "hilog_wrapper.h"
#include "mock_form_provider_client.h"
#include "want.h"

using namespace testing::ext;
using namespace OHOS;
using namespace OHOS::AppExecFwk;
using namespace OHOS::AppExecFwk::FormRender;

namespace {
    constexpr int32_t RENDER_FORM_FAILED = -1;
    constexpr int32_t RELOAD_FORM_FAILED = -1;
}

class FormRenderImplTest : public testing::Test {
public:
    static void SetUpTestCase();

    static void TearDownTestCase();

    void SetUp();

    void TearDown();
};
void FormRenderImplTest::SetUpTestCase()
{}

void FormRenderImplTest::TearDownTestCase()
{}

void FormRenderImplTest::SetUp()
{}

void FormRenderImplTest::TearDown()
{}

/**
 * @tc.name: FormRenderImplTest_001
 * @tc.desc: 1.Verify RenderForm interface executes as expected.
 *           2.callerToken is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderImplTest, FormRenderImplTest_001, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FormRenderImplTest_001 start";
    FormRenderImpl formRenderImpl;
    FormJsInfo formJsInfo;
    Want want;
    sptr<IRemoteObject> callerToken = nullptr;
    auto ret = formRenderImpl.RenderForm(formJsInfo, want, callerToken);
    EXPECT_EQ(ret, ERR_APPEXECFWK_FORM_BIND_PROVIDER_FAILED);
    GTEST_LOG_(INFO) << "FormRenderImplTest_001 end";
}

/**
 * @tc.name: FormRenderImplTest_002
 * @tc.desc: 1.Verify RenderForm interface executes as expected.
 *           2.callerToken is not nullptr.
 *           3.uid is empty.
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderImplTest, FormRenderImplTest_002, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FormRenderImplTest_002 start";
    FormRenderImpl formRenderImpl;
    FormJsInfo formJsInfo;
    Want want;
    sptr<IRemoteObject> callerToken = new (std::nothrow) MockFormProviderClient();
    auto ret = formRenderImpl.RenderForm(formJsInfo, want, callerToken);
    EXPECT_EQ(ret, ERR_APPEXECFWK_FORM_BIND_PROVIDER_FAILED);
    GTEST_LOG_(INFO) << "FormRenderImplTest_002 end";
}

/**
 * @tc.name: FormRenderImplTest_003
 * @tc.desc: 1.Verify RenderForm interface executes as expected.
 *           2.callerToken is not nullptr.
 *           3.uid is not empty and hostToken is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderImplTest, FormRenderImplTest_003, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FormRenderImplTest_003 start";
    FormRenderImpl formRenderImpl;
    FormJsInfo formJsInfo;
    Want want;
    std::string value = "UID";
    want.SetParam(Constants::FORM_SUPPLY_UID, value);
    sptr<IRemoteObject> callerToken = new (std::nothrow) MockFormProviderClient();
    auto ret = formRenderImpl.RenderForm(formJsInfo, want, callerToken);
    EXPECT_EQ(ret, RENDER_FORM_FAILED);
    GTEST_LOG_(INFO) << "FormRenderImplTest_003 end";
}

/**
 * @tc.name: FormRenderImplTest_004
 * @tc.desc: 1.Verify StopRenderingForm interface executes as expected.
 *           2.callerToken is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderImplTest, FormRenderImplTest_004, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FormRenderImplTest_004 start";
    FormRenderImpl formRenderImpl;
    FormJsInfo formJsInfo;
    Want want;
    sptr<IRemoteObject> callerToken = nullptr;
    auto ret = formRenderImpl.StopRenderingForm(formJsInfo, want, callerToken);
    EXPECT_EQ(ret, ERR_APPEXECFWK_FORM_BIND_PROVIDER_FAILED);
    GTEST_LOG_(INFO) << "FormRenderImplTest_004 end";
}

/**
 * @tc.name: FormRenderImplTest_005
 * @tc.desc: 1.Verify StopRenderingForm interface executes as expected.
 *           2.want is empty
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderImplTest, FormRenderImplTest_005, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FormRenderImplTest_005 start";
    FormRenderImpl formRenderImpl;
    FormJsInfo formJsInfo;
    Want want;
    sptr<IRemoteObject> callerToken = new (std::nothrow) MockFormProviderClient();
    auto ret = formRenderImpl.StopRenderingForm(formJsInfo, want, callerToken);
    EXPECT_EQ(ret, ERR_APPEXECFWK_FORM_BIND_PROVIDER_FAILED);
    GTEST_LOG_(INFO) << "FormRenderImplTest_005 end";
}

/**
 * @tc.name: FormRenderImplTest_006
 * @tc.desc: 1.Verify CleanFormHost interface executes as expected.
 *           2.renderRecord is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderImplTest, FormRenderImplTest_006, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FormRenderImplTest_006 start";
    FormRenderImpl formRenderImpl;
    sptr<IRemoteObject> hostToken = nullptr;
    std::string supplyUid = "UID";
    formRenderImpl.renderRecordMap_.emplace(supplyUid, nullptr);
    EXPECT_EQ(ERR_OK, formRenderImpl.CleanFormHost(hostToken));
    GTEST_LOG_(INFO) << "FormRenderImplTest_006 end";
}

/**
 * @tc.name: FormRenderImplTest_007
 * @tc.desc: 1.Verify CleanFormHost interface executes as expected.
 *           2.renderRecord is not nullptr
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderImplTest, FormRenderImplTest_007, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FormRenderImplTest_007 start";
    FormRenderImpl formRenderImpl;
    sptr<IRemoteObject> hostToken = nullptr;
    std::string supplyUid = "UID";
    auto formRenderRecord = FormRenderRecord::Create("bundleName", "uid");
    formRenderImpl.renderRecordMap_.emplace(supplyUid, formRenderRecord);
    EXPECT_EQ(ERR_OK, formRenderImpl.CleanFormHost(hostToken));
    GTEST_LOG_(INFO) << "FormRenderImplTest_007 end";
}

/**
 * @tc.name: FormRenderImplTest_008
 * @tc.desc: 1.Verify ReloadForm interface executes as expected.
 *           2.uid is empty
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderImplTest, FormRenderImplTest_008, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FormRenderImplTest_008 start";
    FormRenderImpl formRenderImpl;
    std::vector<int64_t> formIds;
    Want want;
    EXPECT_EQ(ERR_APPEXECFWK_FORM_BIND_PROVIDER_FAILED, formRenderImpl.ReloadForm(std::move(formIds), want));
    GTEST_LOG_(INFO) << "FormRenderImplTest_008 end";
}

/**
 * @tc.name: FormRenderImplTest_009
 * @tc.desc: 1.Verify ReloadForm interface executes as expected.
 *           2.uid is not empty.
 *           3.search == renderRecordMap_.end().
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderImplTest, FormRenderImplTest_009, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FormRenderImplTest_009 start";
    FormRenderImpl formRenderImpl;
    std::vector<int64_t> formIds;
    Want want;
    std::string value = "UID";
    want.SetParam(Constants::FORM_SUPPLY_UID, value);
    EXPECT_EQ(RELOAD_FORM_FAILED, formRenderImpl.ReloadForm(std::move(formIds), want));
    GTEST_LOG_(INFO) << "FormRenderImplTest_009 end";
}

/**
 * @tc.name: FormRenderImplTest_010
 * @tc.desc: 1.Verify ReloadForm interface executes as expected.
 *           2.uid is not empty.
 *           3.search->second is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderImplTest, FormRenderImplTest_010, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FormRenderImplTest_010 start";
    FormRenderImpl formRenderImpl;
    std::vector<int64_t> formIds;
    Want want;
    std::string value = "UID";
    want.SetParam(Constants::FORM_SUPPLY_UID, value);
    formRenderImpl.renderRecordMap_.emplace(value, nullptr);
    EXPECT_EQ(ERR_OK, formRenderImpl.ReloadForm(std::move(formIds), want));
    GTEST_LOG_(INFO) << "FormRenderImplTest_010 end";
}

/**
 * @tc.name: FormRenderImplTest_011
 * @tc.desc: 1.Verify ReloadForm interface executes as expected.
 *           2.uid is not empty.
 *           3.search->second is not nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderImplTest, FormRenderImplTest_011, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FormRenderImplTest_011 start";
    FormRenderImpl formRenderImpl;
    std::vector<int64_t> formIds;
    Want want;
    std::string value = "UID";
    want.SetParam(Constants::FORM_SUPPLY_UID, value);
    auto formRenderRecord = FormRenderRecord::Create("bundleName", "uid");
    formRenderImpl.renderRecordMap_.emplace(value, formRenderRecord);
    EXPECT_EQ(ERR_OK, formRenderImpl.ReloadForm(std::move(formIds), want));
    GTEST_LOG_(INFO) << "FormRenderImplTest_011 end";
}

/**
 * @tc.name: FormRenderImplTest_012
 * @tc.desc: 1.Verify StopRenderingForm interface executes as expected.
 *           2.search != renderRecordMap_.end()
 *           3.search->second is not nullptr
 * @tc.type: FUNC
 */
HWTEST_F(FormRenderImplTest, FormRenderImplTest_012, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FormRenderImplTest_012 start";
    FormRenderImpl formRenderImpl;
    FormJsInfo formJsInfo;
    Want want;
    std::string value = "UID";
    want.SetParam(Constants::FORM_SUPPLY_UID, value);
    auto formRenderRecord = FormRenderRecord::Create("bundleName", "uid");
    formRenderImpl.renderRecordMap_.emplace(value, formRenderRecord);
    sptr<IRemoteObject> callerToken = new (std::nothrow) MockFormProviderClient();
    auto ret = formRenderImpl.StopRenderingForm(formJsInfo, want, callerToken);
    EXPECT_EQ(ret, ERR_OK);
    GTEST_LOG_(INFO) << "FormRenderImplTest_012 end";
}