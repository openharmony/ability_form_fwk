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
#include <chrono>
#include <gtest/gtest.h>

#include "common_event.h"
#include "common_event_manager.h"
#include "common_event_support.h"
#include "form_constants.h"
#define private public
#include "common/timer_mgr/form_refresh_limiter.h"
#include "common/timer_mgr/form_timer_mgr.h"
#undef private
#include "remote_native_token.h"

using namespace testing::ext;
using namespace OHOS;
using namespace OHOS::AppExecFwk;

namespace {
class FmsFormTimerMgrTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp();
    void TearDown();

protected:
};

void FmsFormTimerMgrTest::SetUpTestCase()
{
    RemoteNativeToken::SetNativeToken();
}
void FmsFormTimerMgrTest::TearDownTestCase() {}
void FmsFormTimerMgrTest::SetUp() {}
void FmsFormTimerMgrTest::TearDown() {}

/**
 * @tc.number: Fms_FormTimerMgr_0091
 * @tc.name: IsLimiterEnableRefresh.
 * @tc.desc: Verify that the IsLimiterEnableRefresh interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0091, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0091 start";
    std::shared_ptr<FormTimerMgr> formTimerMgr = std::make_shared<FormTimerMgr>();
    ASSERT_NE(nullptr, formTimerMgr);
    int64_t formId = 0;
    formTimerMgr->IsLimiterEnableRefresh(formId);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0091 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0092
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0092, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0092 start";
    EventFwk::CommonEventData eventData;
    std::string action = "fms.time_speed";
    AAFwk::Want want;
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0092 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0093
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0093, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0093 start";
    EventFwk::CommonEventData eventData;
    std::string action = "usual.event.TIME_CHANGED";
    AAFwk::Want want;
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0093 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0094
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0094, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0094 start";
    EventFwk::CommonEventData eventData;
    std::string action = "usual.event.TIMEZONE_CHANGED";
    AAFwk::Want want;
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0094 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0095
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0095, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0095 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0095 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0096
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0096, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0096 start";
    EventFwk::CommonEventData eventData;
    std::string action = "abc";
    AAFwk::Want want;
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0096 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0097
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0097, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0097 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    want.SetParam(Constants::KEY_ACTION_TYPE, Constants::TYPE_RESET_LIMIT);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0097 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0098
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0098, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0098 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    want.SetParam(Constants::KEY_ACTION_TYPE, Constants::TYPE_DYNAMIC_UPDATE);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0098 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0099
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0099, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0099 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    constexpr int32_t typeStaticUpdate = Constants::TYPE_STATIC_UPDATE + 100;  // 100: static update
    want.SetParam(Constants::KEY_ACTION_TYPE, typeStaticUpdate);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0099 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0100
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0100, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0100 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    constexpr int32_t typeStaticUpdate = Constants::TYPE_STATIC_UPDATE + 100;  // 100: static update
    want.SetParam(Constants::KEY_ACTION_TYPE, typeStaticUpdate);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0100 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0101
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0101, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0101 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    constexpr int32_t typeStaticUpdate = Constants::TYPE_STATIC_UPDATE + 100;  // 100: static update
    want.SetParam(Constants::KEY_ACTION_TYPE, typeStaticUpdate);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0101 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0102
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0102, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0102 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    constexpr int32_t typeStaticUpdate = Constants::TYPE_STATIC_UPDATE + 100;  // 100: static update
    want.SetParam(Constants::KEY_ACTION_TYPE, typeStaticUpdate);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0102 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0103
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0103, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0103 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    constexpr int32_t typeStaticUpdate = Constants::TYPE_STATIC_UPDATE + 100;  // 100: static update
    want.SetParam(Constants::KEY_ACTION_TYPE, typeStaticUpdate);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0103 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0104
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0104, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0104 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    constexpr int32_t typeStaticUpdate = Constants::TYPE_STATIC_UPDATE + 100;  // 100: static update
    want.SetParam(Constants::KEY_ACTION_TYPE, typeStaticUpdate);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0104 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0105
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0105, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0105 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    constexpr int32_t typeStaticUpdate = Constants::TYPE_STATIC_UPDATE + 100;  // 100: static update
    want.SetParam(Constants::KEY_ACTION_TYPE, typeStaticUpdate);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0105 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0106
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0106, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0106 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    constexpr int32_t typeStaticUpdate = Constants::TYPE_STATIC_UPDATE + 100;  // 100: static update
    want.SetParam(Constants::KEY_ACTION_TYPE, typeStaticUpdate);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0106 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0107
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0107, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0107 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    constexpr int32_t typeStaticUpdate = Constants::TYPE_STATIC_UPDATE + 100;  // 100: static update
    want.SetParam(Constants::KEY_ACTION_TYPE, typeStaticUpdate);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0107 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0108
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0108, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0108 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    constexpr int32_t typeStaticUpdate = Constants::TYPE_STATIC_UPDATE + 100;  // 100: static update
    want.SetParam(Constants::KEY_ACTION_TYPE, typeStaticUpdate);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0108 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0109
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0109, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0109 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    constexpr int32_t typeStaticUpdate = Constants::TYPE_STATIC_UPDATE + 100;  // 100: static update
    want.SetParam(Constants::KEY_ACTION_TYPE, typeStaticUpdate);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0109 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0110
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0110, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0110 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    constexpr int32_t typeStaticUpdate = Constants::TYPE_STATIC_UPDATE + 100;  // 100: static update
    want.SetParam(Constants::KEY_ACTION_TYPE, typeStaticUpdate);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0110 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0111
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0111, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0111 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    constexpr int32_t typeStaticUpdate = Constants::TYPE_STATIC_UPDATE + 100;  // 100: static update
    want.SetParam(Constants::KEY_ACTION_TYPE, typeStaticUpdate);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0111 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0112
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0112, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0112 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    constexpr int32_t typeStaticUpdate = Constants::TYPE_STATIC_UPDATE + 100;  // 100: static update
    want.SetParam(Constants::KEY_ACTION_TYPE, typeStaticUpdate);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0112 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0113
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0113, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0113 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    constexpr int32_t typeStaticUpdate = Constants::TYPE_STATIC_UPDATE + 100;  // 100: static update
    want.SetParam(Constants::KEY_ACTION_TYPE, typeStaticUpdate);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0113 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0114
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0114, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0114 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    constexpr int32_t typeStaticUpdate = Constants::TYPE_STATIC_UPDATE + 100;  // 100: static update
    want.SetParam(Constants::KEY_ACTION_TYPE, typeStaticUpdate);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0114 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0115
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0115, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0115 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    constexpr int32_t typeStaticUpdate = Constants::TYPE_STATIC_UPDATE + 100;  // 100: static update
    want.SetParam(Constants::KEY_ACTION_TYPE, typeStaticUpdate);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0115 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0116
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0116, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0116 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    constexpr int32_t typeStaticUpdate = Constants::TYPE_STATIC_UPDATE + 100;  // 100: static update
    want.SetParam(Constants::KEY_ACTION_TYPE, typeStaticUpdate);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0116 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0117
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0117, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0117 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    constexpr int32_t typeStaticUpdate = Constants::TYPE_STATIC_UPDATE + 100;  // 100: static update
    want.SetParam(Constants::KEY_ACTION_TYPE, typeStaticUpdate);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0117 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0118
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0118, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0118 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    constexpr int32_t typeStaticUpdate = Constants::TYPE_STATIC_UPDATE + 100;  // 100: static update
    want.SetParam(Constants::KEY_ACTION_TYPE, typeStaticUpdate);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0118 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0119
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0119, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0119 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    constexpr int32_t typeStaticUpdate = Constants::TYPE_STATIC_UPDATE + 100;  // 100: static update
    want.SetParam(Constants::KEY_ACTION_TYPE, typeStaticUpdate);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0119 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0120
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0120, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0120 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    constexpr int32_t typeStaticUpdate = Constants::TYPE_STATIC_UPDATE + 100;  // 100: static update
    want.SetParam(Constants::KEY_ACTION_TYPE, typeStaticUpdate);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0120 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0121
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0121, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0121 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    constexpr int32_t typeStaticUpdate = Constants::TYPE_STATIC_UPDATE + 100;  // 100: static update
    want.SetParam(Constants::KEY_ACTION_TYPE, typeStaticUpdate);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0121 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0122
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0122, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0122 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    constexpr int32_t typeStaticUpdate = Constants::TYPE_STATIC_UPDATE + 100;  // 100: static update
    want.SetParam(Constants::KEY_ACTION_TYPE, typeStaticUpdate);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0122 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0123
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0123, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0123 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    constexpr int32_t typeStaticUpdate = Constants::TYPE_STATIC_UPDATE + 100;  // 100: static update
    want.SetParam(Constants::KEY_ACTION_TYPE, typeStaticUpdate);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0123 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0124
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0124, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0124 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    constexpr int32_t typeStaticUpdate = Constants::TYPE_STATIC_UPDATE + 100;  // 100: static update
    want.SetParam(Constants::KEY_ACTION_TYPE, typeStaticUpdate);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0124 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0125
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0125, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0125 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    constexpr int32_t typeStaticUpdate = Constants::TYPE_STATIC_UPDATE + 100;  // 100: static update
    want.SetParam(Constants::KEY_ACTION_TYPE, typeStaticUpdate);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0125 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0126
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0126, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0126 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    constexpr int32_t typeStaticUpdate = Constants::TYPE_STATIC_UPDATE + 100;  // 100: static update
    want.SetParam(Constants::KEY_ACTION_TYPE, typeStaticUpdate);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0126 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0127
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0127, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0127 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    constexpr int32_t typeStaticUpdate = Constants::TYPE_STATIC_UPDATE + 100;  // 100: static update
    want.SetParam(Constants::KEY_ACTION_TYPE, typeStaticUpdate);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0127 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0128
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0128, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0128 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    constexpr int32_t typeStaticUpdate = Constants::TYPE_STATIC_UPDATE + 100;  // 100: static update
    want.SetParam(Constants::KEY_ACTION_TYPE, typeStaticUpdate);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0128 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0129
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0129, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0129 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    constexpr int32_t typeStaticUpdate = Constants::TYPE_STATIC_UPDATE + 100;  // 100: static update
    want.SetParam(Constants::KEY_ACTION_TYPE, typeStaticUpdate);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0129 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0130
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0130, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0130 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    constexpr int32_t typeStaticUpdate = Constants::TYPE_STATIC_UPDATE + 100;  // 100: static update
    want.SetParam(Constants::KEY_ACTION_TYPE, typeStaticUpdate);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0130 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0131
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0131, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0131 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    constexpr int32_t typeStaticUpdate = Constants::TYPE_STATIC_UPDATE + 100;  // 100: static update
    want.SetParam(Constants::KEY_ACTION_TYPE, typeStaticUpdate);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0131 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0132
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0132, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0132 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    constexpr int32_t typeStaticUpdate = Constants::TYPE_STATIC_UPDATE + 100;  // 100: static update
    want.SetParam(Constants::KEY_ACTION_TYPE, typeStaticUpdate);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0132 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0133
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0133, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0133 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    constexpr int32_t typeStaticUpdate = Constants::TYPE_STATIC_UPDATE + 100;  // 100: static update
    want.SetParam(Constants::KEY_ACTION_TYPE, typeStaticUpdate);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0133 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0134
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0134, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0134 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    constexpr int32_t typeStaticUpdate = Constants::TYPE_STATIC_UPDATE + 100;  // 100: static update
    want.SetParam(Constants::KEY_ACTION_TYPE, typeStaticUpdate);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0134 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0135
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0135, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0135 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    constexpr int32_t typeStaticUpdate = Constants::TYPE_STATIC_UPDATE + 100;  // 100: static update
    want.SetParam(Constants::KEY_ACTION_TYPE, typeStaticUpdate);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0135 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0136
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0136, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0136 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    constexpr int32_t typeStaticUpdate = Constants::TYPE_STATIC_UPDATE + 100;  // 100: static update
    want.SetParam(Constants::KEY_ACTION_TYPE, typeStaticUpdate);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0136 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0137
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0137, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0137 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    constexpr int32_t typeStaticUpdate = Constants::TYPE_STATIC_UPDATE + 100;  // 100: static update
    want.SetParam(Constants::KEY_ACTION_TYPE, typeStaticUpdate);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0137 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0138
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0138, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0138 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    constexpr int32_t typeStaticUpdate = Constants::TYPE_STATIC_UPDATE + 100;  // 100: static update
    want.SetParam(Constants::KEY_ACTION_TYPE, typeStaticUpdate);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0138 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0139
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0139, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0139 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    constexpr int32_t typeStaticUpdate = Constants::TYPE_STATIC_UPDATE + 100;  // 100: static update
    want.SetParam(Constants::KEY_ACTION_TYPE, typeStaticUpdate);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0139 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0140
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0140, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0140 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    constexpr int32_t typeStaticUpdate = Constants::TYPE_STATIC_UPDATE + 100;  // 100: static update
    want.SetParam(Constants::KEY_ACTION_TYPE, typeStaticUpdate);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0140 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0141
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0141, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0141 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    constexpr int32_t typeStaticUpdate = Constants::TYPE_STATIC_UPDATE + 100;  // 100: static update
    want.SetParam(Constants::KEY_ACTION_TYPE, typeStaticUpdate);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0141 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0142
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0142, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0142 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    constexpr int32_t typeStaticUpdate = Constants::TYPE_STATIC_UPDATE + 100;  // 100: static update
    want.SetParam(Constants::KEY_ACTION_TYPE, typeStaticUpdate);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0142 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0143
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0143, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0143 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    constexpr int32_t typeStaticUpdate = Constants::TYPE_STATIC_UPDATE + 100;  // 100: static update
    want.SetParam(Constants::KEY_ACTION_TYPE, typeStaticUpdate);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0143 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0144
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0144, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0144 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    constexpr int32_t typeStaticUpdate = Constants::TYPE_STATIC_UPDATE + 100;  // 100: static update
    want.SetParam(Constants::KEY_ACTION_TYPE, typeStaticUpdate);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0144 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0145
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0145, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0145 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    constexpr int32_t typeStaticUpdate = Constants::TYPE_STATIC_UPDATE + 100;  // 100: static update
    want.SetParam(Constants::KEY_ACTION_TYPE, typeStaticUpdate);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0145 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0146
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0146, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0146 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    constexpr int32_t typeStaticUpdate = Constants::TYPE_STATIC_UPDATE + 100;  // 100: static update
    want.SetParam(Constants::KEY_ACTION_TYPE, typeStaticUpdate);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0146 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0147
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0147, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0147 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    constexpr int32_t typeStaticUpdate = Constants::TYPE_STATIC_UPDATE + 100;  // 100: static update
    want.SetParam(Constants::KEY_ACTION_TYPE, typeStaticUpdate);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0147 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0148
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0148, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0148 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    constexpr int32_t typeStaticUpdate = Constants::TYPE_STATIC_UPDATE + 100;  // 100: static update
    want.SetParam(Constants::KEY_ACTION_TYPE, typeStaticUpdate);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0148 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0149
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0149, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0149 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    constexpr int32_t typeStaticUpdate = Constants::TYPE_STATIC_UPDATE + 100;  // 100: static update
    want.SetParam(Constants::KEY_ACTION_TYPE, typeStaticUpdate);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0149 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0150
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0150, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0150 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    constexpr int32_t typeStaticUpdate = Constants::TYPE_STATIC_UPDATE + 100;  // 100: static update
    want.SetParam(Constants::KEY_ACTION_TYPE, typeStaticUpdate);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0150 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0151
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0151, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0151 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    constexpr int32_t typeStaticUpdate = Constants::TYPE_STATIC_UPDATE + 100;  // 100: static update
    want.SetParam(Constants::KEY_ACTION_TYPE, typeStaticUpdate);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0151 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0152
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0152, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0152 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    constexpr int32_t typeStaticUpdate = Constants::TYPE_STATIC_UPDATE + 100;  // 100: static update
    want.SetParam(Constants::KEY_ACTION_TYPE, typeStaticUpdate);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0152 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0153
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0153, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0153 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    constexpr int32_t typeStaticUpdate = Constants::TYPE_STATIC_UPDATE + 100;  // 100: static update
    want.SetParam(Constants::KEY_ACTION_TYPE, typeStaticUpdate);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0153 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0154
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0154, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0154 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    constexpr int32_t typeStaticUpdate = Constants::TYPE_STATIC_UPDATE + 100;  // 100: static update
    want.SetParam(Constants::KEY_ACTION_TYPE, typeStaticUpdate);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0154 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0155
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0155, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0155 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    constexpr int32_t typeStaticUpdate = Constants::TYPE_STATIC_UPDATE + 100;  // 100: static update
    want.SetParam(Constants::KEY_ACTION_TYPE, typeStaticUpdate);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0155 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0156
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0156, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0156 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    constexpr int32_t typeStaticUpdate = Constants::TYPE_STATIC_UPDATE + 100;  // 100: static update
    want.SetParam(Constants::KEY_ACTION_TYPE, typeStaticUpdate);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0156 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0157
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0157, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0157 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    constexpr int32_t typeStaticUpdate = Constants::TYPE_STATIC_UPDATE + 100;  // 100: static update
    want.SetParam(Constants::KEY_ACTION_TYPE, typeStaticUpdate);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0157 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0158
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0158, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0158 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    constexpr int32_t typeStaticUpdate = Constants::TYPE_STATIC_UPDATE + 100;  // 100: static update
    want.SetParam(Constants::KEY_ACTION_TYPE, typeStaticUpdate);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0158 end";
}

/**
 * @tc.number: Fms_FormTimerMgr_0159
 * @tc.name: TimerReceiver::OnReceiveEvent.
 * @tc.desc: Verify that the OnReceiveEvent interface executes normally and exits without exception.
 */
HWTEST_F(FmsFormTimerMgrTest, Fms_FormTimerMgr_0159, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0159 start";
    EventFwk::CommonEventData eventData;
    std::string action = "form_update_at_timer";
    AAFwk::Want want;
    constexpr int32_t typeStaticUpdate = Constants::TYPE_STATIC_UPDATE + 100;  // 100: static update
    want.SetParam(Constants::KEY_ACTION_TYPE, typeStaticUpdate);
    want.SetAction(action);
    eventData.SetWant(want);
    std::shared_ptr<FormTimerMgr::TimerReceiver> timeReceiver = std::make_shared<FormTimerMgr::TimerReceiver>();
    ASSERT_NE(nullptr, timeReceiver);
    timeReceiver->OnReceiveEvent(eventData);
    GTEST_LOG_(INFO) << "Fms_FormTimerMgr_0159 end";
}
}