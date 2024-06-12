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

#include "form_record_report.h"
#include "fms_log_wrapper.h"
#include "form_event_report.h"

namespace OHOS {
namespace AppExecFwk {
FormRecordReport::FormRecordReport()
{
}

FormRecordReport::~FormRecordReport()
{
    ClearReportInfo();
}

std::map<int64_t, FormRecordReportInfo>& FormRecordReport::GetFormRecords()
{
    return formRecordReportMap_;
}

void FormRecordReport::SetFormRecordRecordInfo(int64_t formId, const Want &want)
{
    FormRecordReportInfo info;
    info.bundleName = want.GetElement().GetBundleName();
    info.moduleName = want.GetStringParam(Constants::PARAM_MODULE_NAME_KEY);
    info.formName = want.GetStringParam(Constants::PARAM_FORM_NAME_KEY);
    if (formRecordReportMap_.find(formId) == formRecordReportMap_.end()) {
        formRecordReportMap_[formId] = info;
    }
}

void FormRecordReport::IncreaseUpdateTimes(int64_t formId, HiSysEventPointType type)
{
    HILOG_INFO("IncreaseUpdateTimes start, formId [%{public}" PRId64 "]", formId);
    FormRecordReportInfo info;
    if (formRecordReportMap_.find(formId) != formRecordReportMap_.end()) {
        info = formRecordReportMap_[formId];
        switch (type) {
            case TYPE_DAILY_REFRESH:
                info.dailyRefreshTimes++;
                break;
            case TYPE_INVISIBLE_UPDATE:
                info.invisibleRefreshTimes++;
                break;
            case TYPE_HIGH_FREQUENCY:
                info.hfRefreshBlockTimes++;
                break;
            case TYPE_INVISIBLE_INTERCEPT:
                info.invisibleRefreshBlockTimes++;
                break;
            case TYPE_HIGH_LOAD:
                info.highLoadRefreshBlockTimes = 0;
                break;
            case TYPE_ACTIVE_RECVOER_UPDATE:
                info.activeRecoverRefreshTimes = 0;
                break;
            case TYPE_PASSIVE_RECOVER_UPDATE:
                info.passiveRecoverRefreshTimes++;
                break;
            case TYPE_HF_RECOVER_UPDATE:
                info.hfRecoverRefreshTimes++;
                break;
            case TYPE_OFFLOAD_RECOVER_UPDATE:
                info.offloadRecoverRefreshTimes = 0;
                break;
            default:
                break;
        }
        formRecordReportMap_[formId] = info;
    }
}

void FormRecordReport::HandleFormRefreshCount()
{
    for (const auto& entry : formRecordReportMap_) {
        int64_t formId = entry.first;
        if (formId <= 0) {
            return;
        }
        FormRecordReportInfo record = entry.second;
        NewFormEventInfo eventInfo;
        eventInfo.formId = formId;
        eventInfo.bundleName = record.bundleName;
        eventInfo.moduleName = record.moduleName;
        eventInfo.formName = record.formName;
        eventInfo.dailyRefreshTimes = record.dailyRefreshTimes;
        eventInfo.invisibleRefreshTimes = record.invisibleRefreshTimes;
        eventInfo.hfRefreshBlockTimes = record.hfRefreshBlockTimes;
        eventInfo.invisibleRefreshBlockTimes = record.invisibleRefreshBlockTimes;
        eventInfo.highLoadRefreshBlockTimes = record.highLoadRefreshBlockTimes;
        eventInfo.activeRecoverRefreshTimes = record.activeRecoverRefreshTimes;
        eventInfo.passiveRecoverRefreshTimes = record.passiveRecoverRefreshTimes;
        eventInfo.hfRecoverRefreshTimes = record.hfRecoverRefreshTimes;
        eventInfo.offloadRecoverRefreshTimes = record.offloadRecoverRefreshTimes;
        FormEventReport::SendFormRefreshCountEvent(FormEventName::UPDATE_FORM_REFRESH_TIMES,
            HiSysEventType::STATISTIC, eventInfo);
    }
    ClearReportInfo();
}

void FormRecordReport::ClearReportInfo()
{
    formRecordReportMap_.clear();
}
}  // namespace AppExecFwk
}  // namespace OHOS