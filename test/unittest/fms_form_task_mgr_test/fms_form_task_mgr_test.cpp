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

#include <gtest/gtest.h>
#include <memory>
#define private public
#include "form_task_mgr.h"
#undef private
#include "fms_log_wrapper.h"
#include "mock_form_provider_client.h"
#include "gmock/gmock.h"

using namespace testing::ext;
using namespace OHOS;
using namespace OHOS::AppExecFwk;

namespace {
class FormTaskMgrTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp();
    void TearDown();
};


void FormTaskMgrTest::SetUpTestCase()
{}

void FormTaskMgrTest::TearDownTestCase()
{}

void FormTaskMgrTest::SetUp()
{}

void FormTaskMgrTest::TearDown()
{}

/**
 * @tc.name: FormTaskMgr_0001
 * @tc.desc: test PostFrsDiedTaskToHost function
 * @tc.type: FUNC
 */
HWTEST_F(FormTaskMgrTest, FormTaskMgr_0001, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FormTaskMgr_0001 start";
    std::shared_ptr<FormTaskMgr> formTaskMgr = std::make_shared<FormTaskMgr>();
    ASSERT_NE(formTaskMgr, nullptr);
    sptr<IRemoteObject> remoteObject = nullptr;
    formTaskMgr->PostFrsDiedTaskToHost(remoteObject);
    GTEST_LOG_(INFO) << "FormTaskMgr_0001 end";
}

/**
 * @tc.name: FormTaskMgr_0002
 * @tc.desc: test FrsDiedTaskToHost function
 * @tc.type: FUNC
 */
HWTEST_F(FormTaskMgrTest, FormTaskMgr_0002, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FormTaskMgr_0002 start";
    std::shared_ptr<FormTaskMgr> formTaskMgr = std::make_shared<FormTaskMgr>();
    ASSERT_NE(formTaskMgr, nullptr);
    sptr<IRemoteObject> remoteObject = nullptr;
    formTaskMgr->FrsDiedTaskToHost(remoteObject);
    GTEST_LOG_(INFO) << "FormTaskMgr_0002 end";
}

/**
 * @tc.name: FormTaskMgr_0003
 * @tc.desc: test PostAcquireTaskToHost function and eventHandler_ is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(FormTaskMgrTest, FormTaskMgr_0003, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FormTaskMgr_0003 start";
    std::shared_ptr<FormTaskMgr> formTaskMgr = std::make_shared<FormTaskMgr>();
    ASSERT_NE(nullptr, formTaskMgr);
    int64_t formId = 2;
    FormRecord record;
    sptr<IRemoteObject> remoteObject = nullptr;
    formTaskMgr->PostAcquireTaskToHost(formId, record, remoteObject);
    GTEST_LOG_(INFO) << "FormTaskMgr_0003 end";
}

/**
 * @tc.name: FormTaskMgr_0004
 * @tc.desc: test PostUpdateTaskToHost function and eventHandler_ is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(FormTaskMgrTest, FormTaskMgr_0004, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FormTaskMgr_0004 start";
    std::shared_ptr<FormTaskMgr> formTaskMgr = std::make_shared<FormTaskMgr>();
    ASSERT_NE(nullptr, formTaskMgr);
    int64_t formId = 2;
    FormRecord record;
    sptr<IRemoteObject> remoteObject = nullptr;
    formTaskMgr->PostUpdateTaskToHost(formId, record, remoteObject);
    GTEST_LOG_(INFO) << "FormTaskMgr_0004 end";
}

/**
 * @tc.name: FormTaskMgr_0005
 * @tc.desc: test PostUpdateTaskToHost function and eventHandler_ is not nullptr
 * @tc.type: FUNC
 */
HWTEST_F(FormTaskMgrTest, FormTaskMgr_0005, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FormTaskMgr_0005 start";
    std::shared_ptr<FormTaskMgr> formTaskMgr = std::make_shared<FormTaskMgr>();
    ASSERT_NE(nullptr, formTaskMgr);
    formTaskMgr->SetSerialQueue(nullptr);
    int64_t formId = 2;
    FormRecord record;
    sptr<IRemoteObject> remoteObject = nullptr;
    formTaskMgr->PostUpdateTaskToHost(formId, record, remoteObject);
    GTEST_LOG_(INFO) << "FormTaskMgr_0005 end";
}

/**
 * @tc.name: FormTaskMgr_0006
 * @tc.desc: test PostDeleteTask function and eventHandler_ is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(FormTaskMgrTest, FormTaskMgr_0006, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FormTaskMgr_0006 start";
    std::shared_ptr<FormTaskMgr> formTaskMgr = std::make_shared<FormTaskMgr>();
    ASSERT_NE(nullptr, formTaskMgr);
    int64_t formId = 2;
    Want want;
    sptr<IRemoteObject> remoteObject = nullptr;
    formTaskMgr->PostDeleteTask(formId, want, remoteObject);
    GTEST_LOG_(INFO) << "FormTaskMgr_0006 end";
}

/**
 * @tc.name: FormTaskMgr_0007
 * @tc.desc: test PostRefreshTask function and eventHandler_ is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(FormTaskMgrTest, FormTaskMgr_0007, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FormTaskMgr_0007 start";
    std::shared_ptr<FormTaskMgr> formTaskMgr = std::make_shared<FormTaskMgr>();
    ASSERT_NE(nullptr, formTaskMgr);
    int64_t formId = 2;
    Want want;
    sptr<IRemoteObject> remoteObject = nullptr;
    formTaskMgr->PostRefreshTask(formId, want, remoteObject);
    GTEST_LOG_(INFO) << "FormTaskMgr_0007 end";
}

/**
 * @tc.name: FormTaskMgr_0008
 * @tc.desc: test PostRefreshTask function and eventHandler_ is not nullptr
 * @tc.type: FUNC
 */
HWTEST_F(FormTaskMgrTest, FormTaskMgr_0008, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FormTaskMgr_0008 start";
    std::shared_ptr<FormTaskMgr> formTaskMgr = std::make_shared<FormTaskMgr>();
    ASSERT_NE(nullptr, formTaskMgr);
    formTaskMgr->SetSerialQueue(nullptr);
    int64_t formId = 2;
    Want want;
    sptr<IRemoteObject> remoteObject = nullptr;
    formTaskMgr->PostRefreshTask(formId, want, remoteObject);
    GTEST_LOG_(INFO) << "FormTaskMgr_0008 end";
}

/**
 * @tc.name: FormTaskMgr_0009
 * @tc.desc: test PostHostDiedTask function and eventHandler_ is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(FormTaskMgrTest, FormTaskMgr_0009, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FormTaskMgr_0009 start";
    std::shared_ptr<FormTaskMgr> formTaskMgr = std::make_shared<FormTaskMgr>();
    ASSERT_NE(nullptr, formTaskMgr);
    sptr<IRemoteObject> remoteObject = nullptr;
    formTaskMgr->PostHostDiedTask(remoteObject);
    GTEST_LOG_(INFO) << "FormTaskMgr_0009 end";
}

/**
 * @tc.name: FormTaskMgr_0010
 * @tc.desc: test PostEventNotifyTask function and eventHandler_ is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(FormTaskMgrTest, FormTaskMgr_0010, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FormTaskMgr_0010 start";
    std::shared_ptr<FormTaskMgr> formTaskMgr = std::make_shared<FormTaskMgr>();
    ASSERT_NE(nullptr, formTaskMgr);
    int64_t formId = 2;
    std::vector<int64_t> formEvent;
    formEvent.emplace_back(formId);
    int32_t formVisibleType = 1;
    Want want;
    sptr<IRemoteObject> remoteObject = nullptr;
    formTaskMgr->PostEventNotifyTask(formEvent, formVisibleType, want, remoteObject);
    GTEST_LOG_(INFO) << "FormTaskMgr_0010 end";
}

/**
 * @tc.name: FormTaskMgr_0011
 * @tc.desc: test PostEventNotifyTask function and eventHandler_ is not nullptr
 * @tc.type: FUNC
 */
HWTEST_F(FormTaskMgrTest, FormTaskMgr_0011, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FormTaskMgr_0011 start";
    std::shared_ptr<FormTaskMgr> formTaskMgr = std::make_shared<FormTaskMgr>();
    ASSERT_NE(nullptr, formTaskMgr);
    formTaskMgr->SetSerialQueue(nullptr);
    int64_t formId = 2;
    std::vector<int64_t> formEvent;
    formEvent.emplace_back(formId);
    int32_t formVisibleType = 1;
    Want want;
    sptr<IRemoteObject> remoteObject = nullptr;
    formTaskMgr->PostEventNotifyTask(formEvent, formVisibleType, want, remoteObject);
    GTEST_LOG_(INFO) << "FormTaskMgr_0011 end";
}

/**
 * @tc.name: FormTaskMgr_0012
 * @tc.desc: test PostProviderBatchDeleteTask function and eventHandler_ is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(FormTaskMgrTest, FormTaskMgr_0012, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FormTaskMgr_0012 start";
    std::shared_ptr<FormTaskMgr> formTaskMgr = std::make_shared<FormTaskMgr>();
    ASSERT_NE(nullptr, formTaskMgr);
    int64_t formId = 2;
    std::set<int64_t> formIds;
    formIds.insert(formId);
    Want want;
    sptr<IRemoteObject> remoteObject = nullptr;
    formTaskMgr->PostProviderBatchDeleteTask(formIds, want, remoteObject);
    GTEST_LOG_(INFO) << "FormTaskMgr_0012 end";
}

/**
 * @tc.name: FormTaskMgr_0013
 * @tc.desc: test PostProviderBatchDeleteTask function and eventHandler_ is not nullptr
 * @tc.type: FUNC
 */
HWTEST_F(FormTaskMgrTest, FormTaskMgr_0013, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FormTaskMgr_0013 start";
    FormTaskMgr formTaskMgr;
    formTaskMgr.SetSerialQueue(nullptr);
    int64_t formId = 2;
    std::set<int64_t> formIds;
    formIds.insert(formId);
    Want want;
    sptr<IRemoteObject> remoteObject = nullptr;
    formTaskMgr.PostProviderBatchDeleteTask(formIds, want, remoteObject);
    GTEST_LOG_(INFO) << "FormTaskMgr_0013 end";
}

/**
 * @tc.name: FormTaskMgr_0014
 * @tc.desc: test PostFormEventTask function and eventHandler_ is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(FormTaskMgrTest, FormTaskMgr_0014, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FormTaskMgr_0014 start";
    std::shared_ptr<FormTaskMgr> formTaskMgr = std::make_shared<FormTaskMgr>();
    ASSERT_NE(nullptr, formTaskMgr);
    int64_t formId = 2;
    std::string message = "aa";
    Want want;
    sptr<IRemoteObject> remoteObject = nullptr;
    formTaskMgr->PostFormEventTask(formId, message, want, remoteObject);
    GTEST_LOG_(INFO) << "FormTaskMgr_0014 end";
}

/**
 * @tc.name: FormTaskMgr_0015
 * @tc.desc: test PostFormEventTask function and eventHandler_ is not nullptr
 * @tc.type: FUNC
 */
HWTEST_F(FormTaskMgrTest, FormTaskMgr_0015, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FormTaskMgr_0015 start";
    std::shared_ptr<FormTaskMgr> formTaskMgr = std::make_shared<FormTaskMgr>();
    ASSERT_NE(nullptr, formTaskMgr);
    formTaskMgr->SetSerialQueue(nullptr);
    int64_t formId = 2;
    std::string message = "aa";
    Want want;
    sptr<IRemoteObject> remoteObject = nullptr;
    formTaskMgr->PostFormEventTask(formId, message, want, remoteObject);
    GTEST_LOG_(INFO) << "FormTaskMgr_0015 end";
}

/**
 * @tc.name: FormTaskMgr_0016
 * @tc.desc: test PostAcquireStateTask function and eventHandler_ is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(FormTaskMgrTest, FormTaskMgr_0016, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FormTaskMgr_0016 start";
    std::shared_ptr<FormTaskMgr> formTaskMgr = std::make_shared<FormTaskMgr>();
    ASSERT_NE(nullptr, formTaskMgr);
    Want wantArg;
    std::string state = "aa";
    Want want;
    sptr<IRemoteObject> remoteObject = nullptr;
    formTaskMgr->PostAcquireStateTask(wantArg, state, want, remoteObject);
    GTEST_LOG_(INFO) << "FormTaskMgr_0016 end";
}

/**
 * @tc.name: FormTaskMgr_0017
 * @tc.desc: test PostAcquireStateTask function and eventHandler_ is not nullptr
 * @tc.type: FUNC
 */
HWTEST_F(FormTaskMgrTest, FormTaskMgr_0017, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FormTaskMgr_0017 start";
    std::shared_ptr<FormTaskMgr> formTaskMgr = std::make_shared<FormTaskMgr>();
    ASSERT_NE(nullptr, formTaskMgr);
    formTaskMgr->SetSerialQueue(nullptr);
    Want wantArg;
    std::string state = "aa";
    Want want;
    sptr<IRemoteObject> remoteObject = nullptr;
    formTaskMgr->PostAcquireStateTask(wantArg, state, want, remoteObject);
    GTEST_LOG_(INFO) << "FormTaskMgr_0017 end";
}

/**
 * @tc.name: FormTaskMgr_0018
 * @tc.desc: test PostUninstallTaskToHost function and eventHandler_ is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(FormTaskMgrTest, FormTaskMgr_0018, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FormTaskMgr_0018 start";
    std::shared_ptr<FormTaskMgr> formTaskMgr = std::make_shared<FormTaskMgr>();
    ASSERT_NE(nullptr, formTaskMgr);
    int64_t formId = 3;
    std::vector<int64_t> formIds;
    formIds.emplace_back(formId);
    sptr<IRemoteObject> remoteObject = nullptr;
    formTaskMgr->PostUninstallTaskToHost(formIds, remoteObject);
    GTEST_LOG_(INFO) << "FormTaskMgr_0018 end";
}

/**
 * @tc.name: FormTaskMgr_0019
 * @tc.desc: test PostAcquireStateTaskToHost function and eventHandler_ is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(FormTaskMgrTest, FormTaskMgr_0019, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FormTaskMgr_0019 start";
    std::shared_ptr<FormTaskMgr> formTaskMgr = std::make_shared<FormTaskMgr>();
    ASSERT_NE(nullptr, formTaskMgr);
    AppExecFwk::FormState state = AppExecFwk::FormState::UNKNOWN;
    AAFwk::Want want;
    sptr<IRemoteObject> remoteObject;
    formTaskMgr->PostAcquireStateTaskToHost(state, want, remoteObject);
    GTEST_LOG_(INFO) << "FormTaskMgr_0019 end";
}

/**
 * @tc.name: FormTaskMgr_0020
 * @tc.desc: test PostAcquireStateTaskToHost function and eventHandler_ is not nullptr
 * @tc.type: FUNC
 */
HWTEST_F(FormTaskMgrTest, FormTaskMgr_0020, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FormTaskMgr_0020 start";
    std::shared_ptr<FormTaskMgr> formTaskMgr = std::make_shared<FormTaskMgr>();
    ASSERT_NE(nullptr, formTaskMgr);
    formTaskMgr->SetSerialQueue(nullptr);
    AppExecFwk::FormState state = AppExecFwk::FormState::UNKNOWN;
    AAFwk::Want want;
    sptr<IRemoteObject> remoteObject;
    formTaskMgr->PostAcquireStateTaskToHost(state, want, remoteObject);
    GTEST_LOG_(INFO) << "FormTaskMgr_0020 end";
}

/**
 * @tc.name: FormTaskMgr_0021
 * @tc.desc: test PostFormShareSendResponse function and eventHandler_ is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(FormTaskMgrTest, FormTaskMgr_0021, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FormTaskMgr_0021 start";
    std::shared_ptr<FormTaskMgr> formTaskMgr = std::make_shared<FormTaskMgr>();
    ASSERT_NE(nullptr, formTaskMgr);
    int64_t formShareRequestCode = 1;
    int32_t result = 2;
    formTaskMgr->PostFormShareSendResponse(formShareRequestCode, result);
    GTEST_LOG_(INFO) << "FormTaskMgr_0021 end";
}

/**
 * @tc.name: FormTaskMgr_0022
 * @tc.desc: test PostFormShareSendResponse function and eventHandler_ is not nullptr
 * @tc.type: FUNC
 */
HWTEST_F(FormTaskMgrTest, FormTaskMgr_0022, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FormTaskMgr_0022 start";
    std::shared_ptr<FormTaskMgr> formTaskMgr = std::make_shared<FormTaskMgr>();
    ASSERT_NE(nullptr, formTaskMgr);
    formTaskMgr->SetSerialQueue(nullptr);
    int64_t formShareRequestCode = 1;
    int32_t result = 2;
    formTaskMgr->PostFormShareSendResponse(formShareRequestCode, result);
    GTEST_LOG_(INFO) << "FormTaskMgr_0022 end";
}

/**
 * @tc.name: FormTaskMgr_0023
 * @tc.desc: test NotifyFormUpdate function and formProviderProxy is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(FormTaskMgrTest, FormTaskMgr_0023, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FormTaskMgr_0023 start";
    std::shared_ptr<FormTaskMgr> formTaskMgr = std::make_shared<FormTaskMgr>();
    ASSERT_NE(nullptr, formTaskMgr);
    int64_t formId = 1;
    Want want;
    sptr<IRemoteObject> remoteObject = nullptr;
    formTaskMgr->NotifyFormUpdate(formId, want, remoteObject);
    GTEST_LOG_(INFO) << "FormTaskMgr_0023 end";
}

/**
 * @tc.name: FormTaskMgr_0024
 * @tc.desc: test NotifyFormUpdate function and formProviderProxy is not nullptr and error == ERR_OK
 * @tc.type: FUNC
 */
HWTEST_F(FormTaskMgrTest, FormTaskMgr_0024, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FormTaskMgr_0024 start";
    std::shared_ptr<FormTaskMgr> formTaskMgr = std::make_shared<FormTaskMgr>();
    ASSERT_NE(nullptr, formTaskMgr);
    int64_t formId = 1;
    Want want;
    sptr<IRemoteObject> remoteObject = new (std::nothrow) MockFormProviderClient();
    formTaskMgr->NotifyFormUpdate(formId, want, remoteObject);
    GTEST_LOG_(INFO) << "FormTaskMgr_0024 end";
}

/**
 * @tc.name: FormTaskMgr_0025
 * @tc.desc: test EventNotify function and formProviderProxy is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(FormTaskMgrTest, FormTaskMgr_0025, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FormTaskMgr_0025 start";
    FormTaskMgr formTaskMgr;
    int64_t formId = 1;
    std::vector<int64_t> formEvents;
    formEvents.emplace_back(formId);
    int32_t formVisibleType = 2;
    Want want;
    sptr<IRemoteObject> remoteObject = nullptr;
    formTaskMgr.EventNotify(formEvents, formVisibleType, want, remoteObject);
    GTEST_LOG_(INFO) << "FormTaskMgr_0025 end";
}

/**
 * @tc.name: FormTaskMgr_0026
 * @tc.desc: test EventNotify function and formProviderProxy is not nullptr and error == ERR_OK
 * @tc.type: FUNC
 */
HWTEST_F(FormTaskMgrTest, FormTaskMgr_0026, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FormTaskMgr_0026 start";
    FormTaskMgr formTaskMgr;
    int64_t formId = 1;
    std::vector<int64_t> formEvents;
    formEvents.emplace_back(formId);
    int32_t formVisibleType = 2;
    Want want;
    sptr<IRemoteObject> remoteObject = new (std::nothrow) MockFormProviderClient();
    formTaskMgr.EventNotify(formEvents, formVisibleType, want, remoteObject);
    GTEST_LOG_(INFO) << "FormTaskMgr_0026 end";
}

/**
 * @tc.name: FormTaskMgr_0027
 * @tc.desc: test NotifyCastTemp function and formProviderProxy is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(FormTaskMgrTest, FormTaskMgr_0027, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FormTaskMgr_0027 start";
    FormTaskMgr formTaskMgr;
    int64_t formId = 1;
    Want want;
    sptr<IRemoteObject> remoteObject = nullptr;
    formTaskMgr.NotifyCastTemp(formId, want, remoteObject);
    GTEST_LOG_(INFO) << "FormTaskMgr_0027 end";
}

/**
 * @tc.name: FormTaskMgr_0028
 * @tc.desc: test AcquireTaskToHost function and remoteFormHost is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(FormTaskMgrTest, FormTaskMgr_0028, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FormTaskMgr_0027 start";
    FormTaskMgr formTaskMgr;
    int64_t formId = 1;
    FormRecord record;
    sptr<IRemoteObject> remoteObject = nullptr;
    formTaskMgr.AcquireTaskToHost(formId, record, remoteObject);
    GTEST_LOG_(INFO) << "FormTaskMgr_0027 end";
}

/**
 * @tc.name: FormTaskMgr_0029
 * @tc.desc: test UpdateTaskToHost function and remoteFormHost is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(FormTaskMgrTest, FormTaskMgr_0029, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FormTaskMgr_0029 start";
    FormTaskMgr formTaskMgr;
    int64_t formId = 1;
    FormRecord record;
    sptr<IRemoteObject> remoteObject = nullptr;
    formTaskMgr.UpdateTaskToHost(formId, record, remoteObject);
    GTEST_LOG_(INFO) << "FormTaskMgr_0029 end";
}

/**
 * @tc.name: FormTaskMgr_0030
 * @tc.desc: test UpdateTaskToHost function and remoteFormHost is not nullptr
 * @tc.type: FUNC
 */
HWTEST_F(FormTaskMgrTest, FormTaskMgr_0030, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FormTaskMgr_0030 start";
    FormTaskMgr formTaskMgr;
    int64_t formId = 1;
    FormRecord record;
    sptr<IRemoteObject> remoteObject = new (std::nothrow) MockFormProviderClient();
    formTaskMgr.UpdateTaskToHost(formId, record, remoteObject);
    GTEST_LOG_(INFO) << "FormTaskMgr_0030 end";
}

/**
 * @tc.name: FormTaskMgr_0031
 * @tc.desc: test HostDied function and remoteHost is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(FormTaskMgrTest, FormTaskMgr_0031, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FormTaskMgr_0031 start";
    FormTaskMgr formTaskMgr;
    sptr<IRemoteObject> remoteHost = nullptr;
    formTaskMgr.HostDied(remoteHost);
    GTEST_LOG_(INFO) << "FormTaskMgr_0031 end";
}

/**
 * @tc.name: FormTaskMgr_0033
 * @tc.desc: test ProviderBatchDelete function and formProviderProxy is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(FormTaskMgrTest, FormTaskMgr_0033, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FormTaskMgr_0033 start";
    FormTaskMgr formTaskMgr;
    int64_t formId = 1;
    std::set<int64_t> formIds;
    formIds.insert(formId);
    Want want;
    sptr<IRemoteObject> remoteObject = nullptr;
    formTaskMgr.ProviderBatchDelete(formIds, want, remoteObject);
    GTEST_LOG_(INFO) << "FormTaskMgr_0033 end";
}

/**
 * @tc.name: FormTaskMgr_0034
 * @tc.desc: test ProviderBatchDelete function and formProviderProxy is not nullptr error == ERR_OK
 * @tc.type: FUNC
 */
HWTEST_F(FormTaskMgrTest, FormTaskMgr_0034, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FormTaskMgr_0034 start";
    FormTaskMgr formTaskMgr;
    int64_t formId = 1;
    std::set<int64_t> formIds;
    formIds.insert(formId);
    Want want;
    sptr<IRemoteObject> remoteObject = new (std::nothrow) MockFormProviderClient();
    formTaskMgr.ProviderBatchDelete(formIds, want, remoteObject);
    GTEST_LOG_(INFO) << "FormTaskMgr_0034 end";
}

/**
 * @tc.name: FormTaskMgr_0035
 * @tc.desc: test FireFormEvent function and formProviderProxy is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(FormTaskMgrTest, FormTaskMgr_0035, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FormTaskMgr_0035 start";
    FormTaskMgr formTaskMgr;
    int64_t formId = 1;
    std::string message = "aa";
    Want want;
    sptr<IRemoteObject> remoteObject = nullptr;
    formTaskMgr.FireFormEvent(formId, message, want, remoteObject);
    GTEST_LOG_(INFO) << "FormTaskMgr_0035 end";
}

/**
 * @tc.name: FormTaskMgr_0036
 * @tc.desc: test FireFormEvent function and formProviderProxy is not nullptr and error == ERR_OK
 * @tc.type: FUNC
 */
HWTEST_F(FormTaskMgrTest, FormTaskMgr_0036, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FormTaskMgr_0036 start";
    FormTaskMgr formTaskMgr;
    int64_t formId = 1;
    std::string message = "aa";
    Want want;
    sptr<IRemoteObject> remoteObject = new (std::nothrow) MockFormProviderClient();
    formTaskMgr.FireFormEvent(formId, message, want, remoteObject);
    GTEST_LOG_(INFO) << "FormTaskMgr_0036 end";
}

/**
 * @tc.name: FormTaskMgr_0037
 * @tc.desc: test AcquireState function and formProviderProxy is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(FormTaskMgrTest, FormTaskMgr_0037, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FormTaskMgr_0037 start";
    FormTaskMgr formTaskMgr;
    Want wantArg;
    std::string provider = "aa";
    Want want;
    sptr<IRemoteObject> remoteObject = nullptr;
    formTaskMgr.AcquireState(wantArg, provider, want, remoteObject);
    GTEST_LOG_(INFO) << "FormTaskMgr_0037 end";
}

/**
 * @tc.name: FormTaskMgr_0038
 * @tc.desc: test AcquireState function and formProviderProxy is not nullptr and error == ERR_OK
 * @tc.type: FUNC
 */
HWTEST_F(FormTaskMgrTest, FormTaskMgr_0038, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FormTaskMgr_0038 start";
    FormTaskMgr formTaskMgr;
    Want wantArg;
    std::string provider = "aa";
    Want want;
    sptr<IRemoteObject> remoteObject = new (std::nothrow) MockFormProviderClient();
    formTaskMgr.AcquireState(wantArg, provider, want, remoteObject);
    GTEST_LOG_(INFO) << "FormTaskMgr_0038 end";
}

/**
 * @tc.name: FormTaskMgr_0039
 * @tc.desc: test FormUninstall function and remoteFormHost is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(FormTaskMgrTest, FormTaskMgr_0039, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FormTaskMgr_0039 start";
    FormTaskMgr formTaskMgr;
    int64_t formId = 1;
    std::vector<int64_t> formIds;
    formIds.emplace_back(formId);
    sptr<IRemoteObject> remoteObject = nullptr;
    formTaskMgr.FormUninstall(formIds, remoteObject);
    GTEST_LOG_(INFO) << "FormTaskMgr_0039 end";
}

/**
 * @tc.name: FormTaskMgr_0040
 * @tc.desc: test FormUninstall function and remoteFormHost is not nullptr
 * @tc.type: FUNC
 */
HWTEST_F(FormTaskMgrTest, FormTaskMgr_0040, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FormTaskMgr_0040 start";
    FormTaskMgr formTaskMgr;
    int64_t formId = 1;
    std::vector<int64_t> formIds;
    formIds.emplace_back(formId);
    sptr<IRemoteObject> remoteObject = new (std::nothrow) MockFormProviderClient();
    formTaskMgr.FormUninstall(formIds, remoteObject);
    GTEST_LOG_(INFO) << "FormTaskMgr_0040 end";
}

/**
 * @tc.name: FormTaskMgr_0041
 * @tc.desc: test AcquireStateBack function and remoteFormHost is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(FormTaskMgrTest, FormTaskMgr_0041, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FormTaskMgr_0041 start";
    FormTaskMgr formTaskMgr;
    AppExecFwk::FormState state = AppExecFwk::FormState::UNKNOWN;
    AAFwk::Want want;
    sptr<IRemoteObject> remoteObject = nullptr;
    formTaskMgr.AcquireStateBack(state, want, remoteObject);
    GTEST_LOG_(INFO) << "FormTaskMgr_0041 end";
}

/**
 * @tc.name: FormTaskMgr_0042
 * @tc.desc: test AcquireStateBack function and remoteFormHost is not nullptr
 * @tc.type: FUNC
 */
HWTEST_F(FormTaskMgrTest, FormTaskMgr_0042, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FormTaskMgr_0042 start";
    FormTaskMgr formTaskMgr;
    AppExecFwk::FormState state = AppExecFwk::FormState::UNKNOWN;
    AAFwk::Want want;
    sptr<IRemoteObject> remoteObject = new (std::nothrow) MockFormProviderClient();
    formTaskMgr.AcquireStateBack(state, want, remoteObject);
    GTEST_LOG_(INFO) << "FormTaskMgr_0042 end";
}

/**
 * @tc.name: FormTaskMgr_0043
 * @tc.desc: test PostAcquireDataTask function and eventHandler_ is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(FormTaskMgrTest, FormTaskMgr_0043, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FormTaskMgr_0043 start";
    std::shared_ptr<FormTaskMgr> formTaskMgr = std::make_shared<FormTaskMgr>();
    ASSERT_NE(nullptr, formTaskMgr);
    int64_t formId = 1;
    Want want;
    sptr<IRemoteObject> remoteObject = nullptr;
    formTaskMgr->PostAcquireDataTask(formId, want, remoteObject);
    GTEST_LOG_(INFO) << "FormTaskMgr_0043 end";
}

/**
 * @tc.name: FormTaskMgr_0044
 * @tc.desc: test PostAcquireDataTask function and eventHandler_ is not nullptr
 * @tc.type: FUNC
 */
HWTEST_F(FormTaskMgrTest, FormTaskMgr_0044, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FormTaskMgr_0044 start";
    std::shared_ptr<FormTaskMgr> formTaskMgr = std::make_shared<FormTaskMgr>();
    ASSERT_NE(nullptr, formTaskMgr);
    formTaskMgr->SetSerialQueue(nullptr);
    int64_t formId = 1;
    Want want;
    sptr<IRemoteObject> remoteObject = nullptr;
    formTaskMgr->PostAcquireDataTask(formId, want, remoteObject);
    GTEST_LOG_(INFO) << "FormTaskMgr_0044 end";
}

/**
 * @tc.name: FormTaskMgr_0045
 * @tc.desc: test AcquireFormData function and formProviderProxy is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(FormTaskMgrTest, FormTaskMgr_0045, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FormTaskMgr_0045 start";
    FormTaskMgr formTaskMgr;
    int64_t formId = 1;
    Want want;
    sptr<IRemoteObject> remoteObject = nullptr;
    formTaskMgr.AcquireFormData(formId, want, remoteObject);
    GTEST_LOG_(INFO) << "FormTaskMgr_0045 end";
}

/**
 * @tc.name: FormTaskMgr_0046
 * @tc.desc: test AcquireFormData function and formProviderProxy is not nullptr and error == ERR_OK
 * @tc.type: FUNC
 */
HWTEST_F(FormTaskMgrTest, FormTaskMgr_0046, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FormTaskMgr_0046 start";
    FormTaskMgr formTaskMgr;
    int64_t formId = 1;
    Want want;
    sptr<IRemoteObject> remoteObject = new (std::nothrow) MockFormProviderClient();
    formTaskMgr.AcquireFormData(formId, want, remoteObject);
    GTEST_LOG_(INFO) << "FormTaskMgr_0046 end";
}

/**
 * @tc.name: FormTaskMgr_0047
 * @tc.desc: test PostAcquireDataTaskToHost function and eventHandler_ is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(FormTaskMgrTest, FormTaskMgr_0047, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FormTaskMgr_0047 start";
    std::shared_ptr<FormTaskMgr> formTaskMgr = std::make_shared<FormTaskMgr>();
    ASSERT_NE(nullptr, formTaskMgr);
    AAFwk::WantParams wantParams;
    int64_t requestCode = 1;
    sptr<IRemoteObject> remoteObject = nullptr;
    formTaskMgr->PostAcquireDataTaskToHost(wantParams, requestCode, remoteObject);
    GTEST_LOG_(INFO) << "FormTaskMgr_0047 end";
}

/**
 * @tc.name: FormTaskMgr_0048
 * @tc.desc: test PostAcquireDataTaskToHost function and eventHandler_ is not nullptr
 * @tc.type: FUNC
 */
HWTEST_F(FormTaskMgrTest, FormTaskMgr_0048, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FormTaskMgr_0048 start";
    std::shared_ptr<FormTaskMgr> formTaskMgr = std::make_shared<FormTaskMgr>();
    ASSERT_NE(nullptr, formTaskMgr);
    formTaskMgr->SetSerialQueue(nullptr);
    AAFwk::WantParams wantParams;
    int64_t requestCode = 1;
    sptr<IRemoteObject> remoteObject = nullptr;
    formTaskMgr->PostAcquireDataTaskToHost(wantParams, requestCode, remoteObject);
    GTEST_LOG_(INFO) << "FormTaskMgr_0048 end";
}

/**
 * @tc.name: FormTaskMgr_0049
 * @tc.desc: test AcquireFormDataBack function and formProviderProxy is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(FormTaskMgrTest, FormTaskMgr_0049, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FormTaskMgr_0049 start";
    FormTaskMgr formTaskMgr;
    AAFwk::WantParams wantParams;
    int64_t requestCode = 1;
    sptr<IRemoteObject> remoteObject = nullptr;
    formTaskMgr.AcquireFormDataBack(wantParams, requestCode, remoteObject);
    GTEST_LOG_(INFO) << "FormTaskMgr_0049 end";
}

/**
 * @tc.name: FormTaskMgr_0050
 * @tc.desc: test AcquireFormDataBack function and formProviderProxy is not nullptr and error == ERR_OK
 * @tc.type: FUNC
 */
HWTEST_F(FormTaskMgrTest, FormTaskMgr_0050, TestSize.Level0)
{
    GTEST_LOG_(INFO) << "FormTaskMgr_0050 start";
    FormTaskMgr formTaskMgr;
    AAFwk::WantParams wantParams;
    int64_t requestCode = 1;
    sptr<IRemoteObject> remoteObject = new (std::nothrow) MockFormProviderClient();
    formTaskMgr.AcquireFormDataBack(wantParams, requestCode, remoteObject);
    GTEST_LOG_(INFO) << "FormTaskMgr_0050 end";
}
}