/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#include "feature/ecological_rule/form_ecological_rule_service.h"
#undef private

#include "gmock/gmock.h"
#include "if_system_ability_manager.h"
#include "ipc_skeleton.h"
#include "iremote_stub.h"
#include "iservice_registry.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS;
using namespace OHOS::AppExecFwk;

namespace {
// Remote object that records AddDeathRecipient calls with controllable result.
class MockRemoteObject : public IPCObjectStub {
public:
    MockRemoteObject() : IPCObjectStub(u"mock.ecological.rule") {}
    ~MockRemoteObject() = default;

    bool AddDeathRecipient(const sptr<DeathRecipient> &recipient) override
    {
        addDeathRecipientCount_++;
        lastRecipient_ = recipient;
        return addDeathRecipientRet_;
    }

    bool addDeathRecipientRet_ = true;
    int32_t addDeathRecipientCount_ = 0;
    sptr<IRemoteObject::DeathRecipient> lastRecipient_;
};

class FmsFormEcologicalRuleClientTest : public testing::Test {
public:
    void SetUp() {}
    void TearDown() {}
};

/**
 * @tc.name: ConnectService_001
 * @tc.desc: Test ConnectService returns nullptr when samgr is unavailable.
 * @tc.type: FUNC
 */
HWTEST_F(FmsFormEcologicalRuleClientTest, ConnectService_001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "ConnectService_001 start";
    EXPECT_CALL(SystemAbilityManagerClient::GetInstance(), GetSystemAbilityManager())
        .WillOnce(Return(nullptr));
    EXPECT_EQ(nullptr, FormEcologicalRuleClient::ConnectService());
    GTEST_LOG_(INFO) << "ConnectService_001 end";
}

/**
 * @tc.name: ConnectService_002
 * @tc.desc: Test ConnectService returns nullptr when system ability is absent.
 * @tc.type: FUNC
 */
HWTEST_F(FmsFormEcologicalRuleClientTest, ConnectService_002, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "ConnectService_002 start";
    sptr<ISystemAbilityManager> samgr = new ISystemAbilityManager();
    EXPECT_CALL(SystemAbilityManagerClient::GetInstance(), GetSystemAbilityManager())
        .WillOnce(Return(samgr));
    EXPECT_CALL(*samgr, CheckSystemAbility(_)).WillOnce(Return(nullptr));
    EXPECT_EQ(nullptr, FormEcologicalRuleClient::ConnectService());
    GTEST_LOG_(INFO) << "ConnectService_002 end";
}

/**
 * @tc.name: ConnectService_003
 * @tc.desc: Test ConnectService registers recipient on the remote and returns a proxy bound to it.
 * @tc.type: FUNC
 */
HWTEST_F(FmsFormEcologicalRuleClientTest, ConnectService_003, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "ConnectService_003 start";
    sptr<MockRemoteObject> remote = new MockRemoteObject();
    remote->addDeathRecipientRet_ = true;
    sptr<ISystemAbilityManager> samgr = new ISystemAbilityManager();
    EXPECT_CALL(SystemAbilityManagerClient::GetInstance(), GetSystemAbilityManager())
        .WillOnce(Return(samgr));
    EXPECT_CALL(*samgr, CheckSystemAbility(_)).WillOnce(Return(remote));
    auto proxy = FormEcologicalRuleClient::ConnectService();
    ASSERT_NE(nullptr, proxy);
    // The proxy binds the system ability remote object.
    EXPECT_EQ(remote.GetRefPtr(), proxy->AsObject().GetRefPtr());
    // The recipient is registered on the remote exactly once and matches the cached one.
    EXPECT_EQ(1, remote->addDeathRecipientCount_);
    EXPECT_EQ(FormEcologicalRuleClient::deathRecipient_, remote->lastRecipient_);
    GTEST_LOG_(INFO) << "ConnectService_003 end";
}

/**
 * @tc.name: ConnectService_004
 * @tc.desc: Test ConnectService returns nullptr and clears recipient when AddDeathRecipient fails.
 * @tc.type: FUNC
 */
HWTEST_F(FmsFormEcologicalRuleClientTest, ConnectService_004, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "ConnectService_004 start";
    sptr<MockRemoteObject> remote = new MockRemoteObject();
    remote->addDeathRecipientRet_ = false;
    sptr<ISystemAbilityManager> samgr = new ISystemAbilityManager();
    EXPECT_CALL(SystemAbilityManagerClient::GetInstance(), GetSystemAbilityManager())
        .WillOnce(Return(samgr));
    EXPECT_CALL(*samgr, CheckSystemAbility(_)).WillOnce(Return(remote));
    EXPECT_EQ(nullptr, FormEcologicalRuleClient::ConnectService());
    EXPECT_EQ(nullptr, FormEcologicalRuleClient::deathRecipient_);
    GTEST_LOG_(INFO) << "ConnectService_004 end";
}
} // namespace
