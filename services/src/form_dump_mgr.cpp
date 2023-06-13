/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "form_dump_mgr.h"

#include "fms_log_wrapper.h"
#include "form_cache_mgr.h"

namespace OHOS {
namespace AppExecFwk {
const std::string LINE_SEPARATOR = "\n";

FormDumpMgr::FormDumpMgr() {}
FormDumpMgr::~FormDumpMgr() {}
/**
 * @brief Dump all of form storage infos.
 * @param storageInfos Form storage infos
 * @param formInfos Form storage dump info.
 */
void FormDumpMgr::DumpStorageFormInfos(const std::vector<FormDBInfo> &storageInfos, std::string &formInfos) const
{
    formInfos += "  Total Storage-Form count is " + std::to_string(storageInfos.size()) + "\n" + LINE_SEPARATOR;
    for (const auto &info : storageInfos) {
        formInfos += "  FormId #" + std::to_string(info.formId) + "\n";
        formInfos += "    formName [" + info.formName + "]\n";
        formInfos += "    userId [" + std::to_string(info.userId) + "]\n";
        formInfos += "    bundleName [" + info.bundleName + "]\n";
        formInfos += "    moduleName [" + info.moduleName + "]\n";
        formInfos += "    abilityName [" + info.abilityName + "]\n";
        formInfos += "    formUserUids [";
        for (const auto &uId : info.formUserUids) {
            formInfos += " Uid[" + std::to_string(uId) + "] ";
        }
        formInfos += "]\n" + LINE_SEPARATOR;
    }
}
/**
 * @brief Dump all of temporary form infos.
 * @param formRecordInfos Form record infos.
 * @param formInfos Form dump infos.
 */
void FormDumpMgr::DumpTemporaryFormInfos(const std::vector<FormRecord> &formRecordInfos, std::string &formInfos) const
{
    formInfos += "  Total Temporary-Form count is " + std::to_string(formRecordInfos.size()) + "\n" + LINE_SEPARATOR;
    for (const auto &info : formRecordInfos) {
        formInfos += "  FormId #" + std::to_string(info.formId) + "\n";
        formInfos += "    formName [" + info.formName + "]\n";
        formInfos += "    userId [" + std::to_string(info.userId) + "]\n";
        formInfos += "    bundleName [" + info.bundleName + "]\n";
        formInfos += "    moduleName [" + info.moduleName + "]\n";
        formInfos += "    abilityName [" + info.abilityName + "]\n";
        formInfos += "    formUserUids [";
        for (const auto &uId : info.formUserUids) {
            formInfos += " Uid[" + std::to_string(uId) + "] ";
        }
        formInfos += "]\n" + LINE_SEPARATOR;
    }
}

void FormDumpMgr::DumpStaticBundleFormInfos(const std::vector<FormInfo> &bundleFormInfos, std::string &formInfos) const
{
    formInfos += "  These are static-form-infos, it means un-added form's info will also be dumped\n" + LINE_SEPARATOR;
    for (const auto &info : bundleFormInfos) {
        formInfos += "  bundleName #" + info.bundleName + "\n";
        formInfos += "    moduleName [" + info.moduleName + "]\n";
        formInfos += "    abilityName [" + info.abilityName + "]\n";
        formInfos += "    formName [" + info.name + "]\n" + LINE_SEPARATOR;
    }
}
/**
 * @brief Dump form infos.
 * @param formRecordInfos Form record infos.
 * @param formInfos Form dump infos.
 */
void FormDumpMgr::DumpFormInfos(const std::vector<FormRecord> &formRecordInfos, std::string &formInfos) const
{
    HILOG_INFO("%{public}s called.", __func__);
    for (const auto &info : formRecordInfos) {
        formInfos += "  FormId [" + std::to_string(info.formId)  + "]\n";
        formInfos += "    formName [" + info.formName + "]\n";
        formInfos += "    bundleName [" + info.bundleName + "]\n";
        formInfos += "    moduleName [" + info.moduleName + "]\n";
        formInfos += "    abilityName [" + info.abilityName + "]\n";
        formInfos += "    isInited [" + std::to_string(info.isInited) + "]\n";
        formInfos += "    needRefresh [" + std::to_string(info.needRefresh) + "]\n";
        formInfos += "    isEnableUpdate [" + std::to_string(info.isEnableUpdate) + "]\n";
        formInfos += "    isCountTimerRefresh [" + std::to_string(info.isCountTimerRefresh) + "]\n";
        formInfos += "    specification [" + std::to_string(info.specification) + "]\n";
        formInfos += "    updateDuration [" + std::to_string(info.updateDuration) + "]\n";
        formInfos += "    updateAtHour [" + std::to_string(info.updateAtHour) + "]\n";
        formInfos += "    updateAtMin [" + std::to_string(info.updateAtMin) + "]\n";
        formInfos += "    formTempFlag [" + std::to_string(info.formTempFlag) + "]\n";
        formInfos += "    formVisibleNotify [" + std::to_string(info.formVisibleNotify) + "]\n";
        formInfos += "    formVisibleNotifyState [" + std::to_string(info.formVisibleNotifyState) + "]\n";
        formInfos += "    userId [" + std::to_string(info.userId) + "]\n";
        formInfos += "    type [" + std::to_string(static_cast<int32_t>(info.type)) + "]\n";

        if (!info.hapSourceDirs.empty()) {
            formInfos += "    hapSourceDirs [";
            for (const auto &hapDir : info.hapSourceDirs) {
                formInfos += " hapSourceDir[" + hapDir + "]";
            }
            formInfos += "]\n";
        }

        if (!info.formUserUids.empty()) {
            formInfos += "    formUserUids [";
            for (const auto &uId : info.formUserUids) {
                formInfos += " Uid[" + std::to_string(uId) + "] ";
            }
            formInfos += "]\n";
        }

        AppendBundleFormInfo(info, formInfos);
        formInfos += LINE_SEPARATOR;
    }

    HILOG_DEBUG("%{public}s success. Form infos:%{private}s", __func__, formInfos.c_str());
}
/**
 * @brief Dump form infos.
 * @param formRecordInfo Form Host record info.
 * @param formInfo Form dump info.
 */
void FormDumpMgr::DumpFormHostInfo(const FormHostRecord &formHostRecord, std::string &formInfo) const
{
    HILOG_INFO("%{public}s called.", __func__);
    formInfo += "  ================FormHostRecord=================\n";
    formInfo += "  callerUid [" + std::to_string(formHostRecord.GetCallerUid()) + "]\n";
    formInfo += "  hostBundleName [" + formHostRecord.GetHostBundleName() + "]\n";
    HILOG_DEBUG("%{public}s success. Host Form infos:%{private}s", __func__, formInfo.c_str());
}

/**
 * @brief Dump form infos.
 * @param formRecordInfo Form record info.
 * @param formInfo Form dump info.
 */
void FormDumpMgr::DumpFormInfo(const FormRecord &formRecordInfo, std::string &formInfo) const
{
    HILOG_INFO("%{public}s called.", __func__);
    formInfo += "  ================FormRecord=================\n";
    formInfo += "  FormId [" + std::to_string(formRecordInfo.formId) + "]\n";
    formInfo += "    formName [" + formRecordInfo.formName + "]\n";
    formInfo += "    bundleName [" + formRecordInfo.bundleName + "]\n";
    formInfo += "    moduleName [" + formRecordInfo.moduleName + "]\n";
    formInfo += "    abilityName [" + formRecordInfo.abilityName + "]\n";
    formInfo += "    isInited [" + std::to_string(formRecordInfo.isInited) + "]\n";
    formInfo += "    needRefresh [" + std::to_string(formRecordInfo.needRefresh) + "]\n";
    formInfo += "    isEnableUpdate [" + std::to_string(formRecordInfo.isEnableUpdate) + "]\n";
    formInfo += "    isCountTimerRefresh [" + std::to_string(formRecordInfo.isCountTimerRefresh) + "]\n";
    formInfo += "    specification [" + std::to_string(formRecordInfo.specification) + "]\n";
    formInfo += "    updateDuration [" + std::to_string(formRecordInfo.updateDuration) + "]\n";
    formInfo += "    updateAtHour [" + std::to_string(formRecordInfo.updateAtHour) + "]\n";
    formInfo += "    updateAtMin [" + std::to_string(formRecordInfo.updateAtMin) + "]\n";
    formInfo += "    formTempFlag [" + std::to_string(formRecordInfo.formTempFlag) + "]\n";
    formInfo += "    formVisibleNotify [" + std::to_string(formRecordInfo.formVisibleNotify) + "]\n";
    formInfo += "    formVisibleNotifyState [" + std::to_string(formRecordInfo.formVisibleNotifyState) + "]\n";
    formInfo += "    formSrc [" + formRecordInfo.formSrc + "]\n";
    formInfo += "    designWidth [" + std::to_string(formRecordInfo.formWindow.designWidth) + "]\n";
    formInfo += "    autoDesignWidth [" + std::to_string(formRecordInfo.formWindow.autoDesignWidth) + "]\n";
    formInfo += "    versionCode [" + std::to_string(formRecordInfo.versionCode) + "]\n";
    formInfo += "    versionName [" + formRecordInfo.versionName + "]\n";
    formInfo += "    compatibleVersion [" + std::to_string(formRecordInfo.compatibleVersion) + "]\n";
    formInfo += "    userId [" + std::to_string(formRecordInfo.userId) + "]\n";

    if (!formRecordInfo.hapSourceDirs.empty()) {
        formInfo += "    hapSourceDirs [";
        for (const auto &hapDir : formRecordInfo.hapSourceDirs) {
            formInfo += " hapSourceDir[" + hapDir + "] ";
        }
        formInfo += "]\n";
    }

    if (!formRecordInfo.formUserUids.empty()) {
        formInfo += "    formUserUids [";
        for (const auto &uId : formRecordInfo.formUserUids) {
            formInfo += " Uid[" + std::to_string(uId) + "] ";
        }
        formInfo += "]\n";
    }

    AppendBundleFormInfo(formRecordInfo, formInfo);
    formInfo += LINE_SEPARATOR;

    HILOG_DEBUG("%{public}s success. Form infos:%{private}s", __func__, formInfo.c_str());
}

void FormDumpMgr::AppendBundleFormInfo(const FormRecord &formRecordInfo, std::string &formInfo) const
{
    FormInfo bundleFormInfo;
    if (FormInfoMgr::GetInstance().GetFormsInfoByRecord(formRecordInfo, bundleFormInfo) != ERR_OK) {
        formInfo += "    ERROR! Can not get formInfo from BMS! \n";
    }
    formInfo += "    colorMode [" + std::to_string(static_cast<int32_t>(bundleFormInfo.colorMode)) + "]\n";
    formInfo += "    defaultDimension [" + std::to_string(bundleFormInfo.defaultDimension) + "]\n";
    if (!bundleFormInfo.supportDimensions.empty()) {
        formInfo += "    supportDimensions [";
        for (const auto &dimension : bundleFormInfo.supportDimensions) {
            formInfo += " [" + std::to_string(dimension) + "] ";
        }
        formInfo += "]\n";
    }
}
}  // namespace AppExecFwk
}  // namespace OHOS
