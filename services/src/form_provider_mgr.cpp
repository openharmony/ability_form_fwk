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

#include "form_provider_mgr.h"

#include <cinttypes>

#include "fms_log_wrapper.h"
#include "form_ams_helper.h"
#include "form_batch_delete_connection.h"
#include "form_cache_mgr.h"
#include "form_constants.h"
#include "form_data_mgr.h"
#include "form_delete_connection.h"
#include "form_mgr_errors.h"
#include "form_msg_event_connection.h"
#include "form_record.h"
#include "form_refresh_connection.h"
#include "form_timer_mgr.h"
#include "form_report.h"
#include "form_record_report.h"
#ifdef SUPPORT_POWER
#include "power_mgr_client.h"
#endif
namespace OHOS {
namespace AppExecFwk {
FormProviderMgr::FormProviderMgr() {}
FormProviderMgr::~FormProviderMgr() {}
/**
 * @brief handle for acquire back from ams.
 * @param formId The id of the form.
 * @param formProviderInfo provider form info.
 * @return Returns ERR_OK on success, others on failure.
 */
ErrCode FormProviderMgr::AcquireForm(const int64_t formId, const FormProviderInfo &formProviderInfo)
{
    HILOG_DEBUG("%{public}s start, formId:%{public}" PRId64 "", __func__, formId);

    if (formId <= 0) {
        HILOG_ERROR("%{public}s fail, formId should be greater than 0", __func__);
        return ERR_APPEXECFWK_FORM_INVALID_PARAM;
    }

    FormRecord formRecord;
    bool isGetFormRecord = FormDataMgr::GetInstance().GetFormRecord(formId, formRecord);
    if (!isGetFormRecord) {
        HILOG_ERROR("%{public}s fail, not exist such form, formId:%{public}" PRId64 "", __func__, formId);
        return ERR_APPEXECFWK_FORM_NOT_EXIST_ID;
    }

    std::vector<FormHostRecord> clientHosts;
    FormDataMgr::GetInstance().GetFormHostRecord(formId, clientHosts);
    if (clientHosts.empty()) {
        HILOG_ERROR("%{public}s fail, clientHosst is empty", __func__);
        return ERR_APPEXECFWK_FORM_COMMON_CODE;
    }

    if (formRecord.isInited) {
        if (IsFormCached(formRecord)) {
            formRecord.formProviderInfo = formProviderInfo;
            for (auto &iter : clientHosts) {
                iter.OnAcquire(formId, formRecord);
            }
        } else {
            Want want;
            RefreshForm(formId, want, true);
        }
        return ERR_OK;
    }
    formRecord.isInited = true;
    formRecord.needRefresh = false;
    FormDataMgr::GetInstance().SetFormCacheInited(formId, true);

    formRecord.formProviderInfo = formProviderInfo;
    for (auto &iter : clientHosts) {
        iter.OnAcquire(formId, formRecord);
    }

    if (formProviderInfo.NeedCache()) {
        HILOG_WARN("%{public}s, acquire js card, cache the card", __func__);
        FormCacheMgr::GetInstance().AddData(formId, formProviderInfo.GetFormData());
    }
    return ERR_OK;
}

/**
 * @brief Refresh form.
 *
 * @param formId The form id.
 * @param want The want of the form to request.
 * @param isVisibleToFresh The form is visible to fresh.
 * @return Returns ERR_OK on success, others on failure.
 */
ErrCode FormProviderMgr::RefreshForm(const int64_t formId, const Want &want, bool isVisibleToFresh)
{
    FormRecord record;
    ErrCode result = RefreshCheck(record, formId, want);
    if (result != ERR_OK) {
        return result;
    }

    bool isCountTimerRefresh = want.GetBoolParam(Constants::KEY_IS_TIMER, false);
    Want newWant(want);
    newWant.RemoveParam(Constants::KEY_IS_TIMER);

    if (isCountTimerRefresh) {
        FormDataMgr::GetInstance().SetCountTimerRefresh(formId, true);
    }

    bool isTimerRefresh = want.GetBoolParam(Constants::KEY_TIMER_REFRESH, false);
    newWant.RemoveParam(Constants::KEY_TIMER_REFRESH);

    if (isTimerRefresh) {
        FormDataMgr::GetInstance().SetTimerRefresh(formId, true);
        bool isFormVisible = record.formVisibleNotifyState == Constants::FORM_VISIBLE;
        if (!isFormVisible) {
            HILOG_DEBUG("form is invisible.");
            FormDataMgr::GetInstance().SetNeedRefresh(formId, true);
            FormRecordReport::GetInstance().IncreaseUpdateTimes(formId, HiSysEventPointType::TYPE_INVISIBLE_INTERCEPT);
            return ERR_OK;
        }
    }

#ifdef SUPPORT_POWER
    bool screenOnFlag = PowerMgr::PowerMgrClient::GetInstance().IsScreenOn();
    if (!screenOnFlag) {
        FormDataMgr::GetInstance().SetNeedRefresh(formId, true);
        HILOG_DEBUG("%{public}s fail, screen off, set refresh flag, do not refresh now", __func__);
        return ERR_OK;
    }
#endif

    bool needRefresh = IsNeedToFresh(record, formId, isVisibleToFresh);
    if (!needRefresh) {
        FormDataMgr::GetInstance().SetNeedRefresh(formId, true);
        HILOG_ERROR("%{public}s fail, no one needReresh, set refresh flag, do not refresh now", __func__);
        return ERR_OK;
    }

    FormRecord refreshRecord = GetFormAbilityInfo(record);
    refreshRecord.isCountTimerRefresh = isCountTimerRefresh;
    refreshRecord.isTimerRefresh = isTimerRefresh;
    return ConnectAmsForRefresh(formId, refreshRecord, newWant, isCountTimerRefresh);
}

ErrCode FormProviderMgr::RefreshCheck(FormRecord &record, const int64_t formId, const Want &want)
{
    bool bGetRecord = FormDataMgr::GetInstance().GetFormRecord(formId, record);
    if (!bGetRecord) {
        HILOG_ERROR("%{public}s fail, not exist such form:%{public}" PRId64 "", __func__, formId);
        return ERR_APPEXECFWK_FORM_NOT_EXIST_ID;
    }

    // get current userId
    int32_t currentActiveUserId = want.GetIntParam(Constants::PARAM_FORM_USER_ID, Constants::DEFAULT_PROVIDER_USER_ID);
    if (currentActiveUserId != record.providerUserId) {
        FormDataMgr::GetInstance().SetNeedRefresh(formId, true);
        HILOG_ERROR("%{public}s, not current user, just set refresh flag, userId:%{public}d",
            __func__, record.providerUserId);
        return ERR_APPEXECFWK_FORM_OPERATION_NOT_SELF;
    }
    HILOG_INFO("formId:%{public}" PRId64 ", enableForm:%{public}d",
        formId, record.enableForm);
    if (!record.enableForm) {
        FormDataMgr::GetInstance().SetRefreshDuringDisableForm(formId, true);
        return ERR_APPEXECFWK_FORM_DISABLE_REFRESH;
    }

    return ERR_OK;
}

/**
 * @brief Connect ams for refresh form
 *
 * @param formId The form id.
 * @param record Form data.
 * @param want The want of the form.
 * @param isTimerRefresh The flag of timer refresh.
 * @return Returns ERR_OK on success, others on failure.
 */
ErrCode FormProviderMgr::ConnectAmsForRefresh(const int64_t formId,
    const FormRecord &record, const Want &want, const bool isCountTimerRefresh)
{
    HILOG_DEBUG("%{public}s called, bundleName:%{public}s, abilityName:%{public}s, needFreeInstall:%{public}d.",
        __func__, record.bundleName.c_str(), record.abilityName.c_str(), record.needFreeInstall);

    sptr<IAbilityConnection> formRefreshConnection = new (std::nothrow) FormRefreshConnection(formId, want,
        record.bundleName, record.abilityName, record.needFreeInstall);
    if (formRefreshConnection == nullptr) {
        HILOG_ERROR("failed to create FormRefreshConnection.");
        return ERR_APPEXECFWK_FORM_COMMON_CODE;
    }
    Want connectWant;
    connectWant.AddFlags(Want::FLAG_ABILITY_FORM_ENABLED);
    connectWant.SetElementName(record.bundleName, record.abilityName);

    if (record.needFreeInstall) {
        return RebindByFreeInstall(record, connectWant, formRefreshConnection);
    }

    if (isCountTimerRefresh) {
        if (!FormTimerMgr::GetInstance().IsLimiterEnableRefresh(formId)) {
            HILOG_ERROR("%{public}s, timer refresh, already limit.", __func__);
            return ERR_APPEXECFWK_FORM_PROVIDER_DEL_FAIL;
        }
    }

    ErrCode errorCode = FormAmsHelper::GetInstance().ConnectServiceAbility(connectWant, formRefreshConnection);
    if (errorCode != ERR_OK) {
        HILOG_ERROR("%{public}s, ConnectServiceAbility failed.", __func__);
        return ERR_APPEXECFWK_FORM_BIND_PROVIDER_FAILED;
    }

    if (record.isCountTimerRefresh) {
        IncreaseTimerRefreshCount(formId);
    }

    if (record.isTimerRefresh) {
        FormDataMgr::GetInstance().SetTimerRefresh(formId, false);
    }

    return ERR_OK;
}

/**
 * @brief Connect ability manager service for refresh app permission
 *
 * @param formId The form id.
 * @param want The want of the form.
 * @return Returns ERR_OK on success, others on failure.
 */
ErrCode FormProviderMgr::ConnectAmsForRefreshPermission(const int64_t formId, Want &want)
{
    HILOG_DEBUG("ConnectAmsForRefreshPermission start, form id: %{public}" PRId64 "", formId);
    if (!want.HasParameter(Constants::FORM_PERMISSION_NAME_KEY) ||
        !want.HasParameter(Constants::FORM_PERMISSION_GRANTED_KEY)) {
        HILOG_ERROR("permission info is not exist, form:%{public}" PRId64 "", formId);
        return ERR_APPEXECFWK_FORM_INVALID_PARAM;
    }
    FormRecord record;
    bool result = FormDataMgr::GetInstance().GetFormRecord(formId, record);
    if (!result) {
        HILOG_ERROR("get form record fail, not exist such form:%{public}" PRId64 "", formId);
        return ERR_APPEXECFWK_FORM_NOT_EXIST_ID;
    }
    want.RemoveParam(Constants::KEY_IS_TIMER);
    want.RemoveParam(Constants::KEY_TIMER_REFRESH);

    sptr<IAbilityConnection> formRefreshConnection = new (std::nothrow) FormRefreshConnection(formId, want,
        record.bundleName, record.abilityName, record.needFreeInstall);
    if (formRefreshConnection == nullptr) {
        HILOG_ERROR("failed to create FormRefreshConnection.");
        return ERR_APPEXECFWK_FORM_COMMON_CODE;
    }

    Want connectWant;
    connectWant.AddFlags(Want::FLAG_ABILITY_FORM_ENABLED);
    connectWant.SetElementName(record.bundleName, record.abilityName);

    if (record.needFreeInstall) {
        connectWant.AddFlags(Want::FLAG_INSTALL_ON_DEMAND | Want::FLAG_INSTALL_WITH_BACKGROUND_MODE);
        connectWant.SetModuleName(record.moduleName);
    }

    ErrCode errorCode = FormAmsHelper::GetInstance().ConnectServiceAbility(connectWant, formRefreshConnection);
    if (errorCode != ERR_OK) {
        HILOG_ERROR("ConnectServiceAbility failed.");
        return ERR_APPEXECFWK_FORM_BIND_PROVIDER_FAILED;
    }

    return ERR_OK;
}

/**
 * @brief Notify provider form delete.
 * @param formId The form id.
 * @param record Form information.
 * @return Function result and has other host flag.
 */
ErrCode FormProviderMgr::NotifyProviderFormDelete(const int64_t formId, const FormRecord &formRecord)
{
    if (formRecord.abilityName.empty()) {
        HILOG_ERROR("%{public}s, formRecord.abilityName is empty.", __func__);
        return ERR_APPEXECFWK_FORM_INVALID_PARAM;
    }

    if (formRecord.bundleName.empty()) {
        HILOG_ERROR("%{public}s, formRecord.bundleName is empty.", __func__);
        return ERR_APPEXECFWK_FORM_INVALID_PARAM;
    }

    HILOG_DEBUG("%{public}s, connectAbility,bundleName:%{public}s, abilityName:%{public}s",
        __func__, formRecord.bundleName.c_str(), formRecord.abilityName.c_str());
    sptr<IAbilityConnection> formDeleteConnection = new (std::nothrow) FormDeleteConnection(formId,
        formRecord.bundleName, formRecord.abilityName);
    if (formDeleteConnection == nullptr) {
        HILOG_ERROR("failed to create FormDeleteConnection.");
        return ERR_APPEXECFWK_FORM_COMMON_CODE;
    }
    Want want;
    want.SetElementName(formRecord.bundleName, formRecord.abilityName);
    want.SetFlags(Want::FLAG_ABILITY_FORM_ENABLED);

    ErrCode errorCode = FormAmsHelper::GetInstance().ConnectServiceAbility(want, formDeleteConnection);
    if (errorCode != ERR_OK) {
        HILOG_ERROR("%{public}s, ConnectServiceAbility failed.", __func__);
        return ERR_APPEXECFWK_FORM_BIND_PROVIDER_FAILED;
    }
    return ERR_OK;
}

/**
 * @brief Notify provider forms batch delete.
 * @param bundleName BundleName.
 * @param bundleName AbilityName.
 * @param formIds form id list.
 * @return Returns ERR_OK on success, others on failure.
 */
ErrCode FormProviderMgr::NotifyProviderFormsBatchDelete(const std::string &bundleName,
    const std::string &abilityName, const std::set<int64_t> &formIds)
{
    if (abilityName.empty()) {
        HILOG_ERROR("%{public}s error, abilityName is empty.",  __func__);
        return ERR_APPEXECFWK_FORM_INVALID_PARAM;
    }

    if (bundleName.empty()) {
        HILOG_ERROR("%{public}s error, bundleName is empty.",  __func__);
        return ERR_APPEXECFWK_FORM_INVALID_PARAM;
    }

    HILOG_DEBUG("%{public}s, bundleName:%{public}s, abilityName:%{public}s",
        __func__, bundleName.c_str(), abilityName.c_str());
    sptr<IAbilityConnection> batchDeleteConnection = new FormBatchDeleteConnection(formIds, bundleName, abilityName);
    if (batchDeleteConnection == nullptr) {
        HILOG_ERROR("failed to create FormBatchDeleteConnection.");
        return ERR_APPEXECFWK_FORM_COMMON_CODE;
    }
    Want want;
    want.AddFlags(Want::FLAG_ABILITY_FORM_ENABLED);
    want.SetElementName(bundleName, abilityName);

    ErrCode errorCode = FormAmsHelper::GetInstance().ConnectServiceAbility(want, batchDeleteConnection);
    if (errorCode != ERR_OK) {
        HILOG_ERROR("%{public}s, ConnectServiceAbility failed.", __func__);
        return ERR_APPEXECFWK_FORM_BIND_PROVIDER_FAILED;
    }
    return ERR_OK;
}
/**
 * @brief Update form.
 * @param formId The form's id.
 * @param formProviderData form provider data.
 * @return Returns ERR_OK on success, others on failure.
 */
ErrCode FormProviderMgr::UpdateForm(const int64_t formId, const FormProviderInfo &formProviderInfo)
{
    // check exist and get the formRecord
    FormRecord formRecord;
    if (!FormDataMgr::GetInstance().GetFormRecord(formId, formRecord)) {
        HILOG_ERROR("%{public}s error, not exist such form:%{public}" PRId64 ".", __func__, formId);
        return ERR_APPEXECFWK_FORM_NOT_EXIST_ID;
    }
    return UpdateForm(formId, formRecord, formProviderInfo.GetFormData());
}
/**
 * handle for update form event from provider.
 *
 * @param formId The id of the form.
 * @param formRecord The form's record.
 * @param formProviderData provider form info.
 * @return Returns ERR_OK on success, others on failure.
 */
ErrCode FormProviderMgr::UpdateForm(const int64_t formId,
    FormRecord &formRecord, const FormProviderData &formProviderData)
{
    HILOG_INFO("imageDateState is %{public}d", formProviderData.GetImageDataState());
    if (formRecord.versionUpgrade) {
        formRecord.formProviderInfo.SetFormData(formProviderData);
        formRecord.formProviderInfo.SetUpgradeFlg(true);
    } else {
        nlohmann::json addJsonData = formProviderData.GetData();
        formRecord.formProviderInfo.MergeData(addJsonData);
        // merge image
        auto formData = formRecord.formProviderInfo.GetFormData();
        formData.SetImageDataState(formProviderData.GetImageDataState());
        formData.SetImageDataMap(formProviderData.GetImageDataMap());
        formRecord.formProviderInfo.SetFormData(formData);
    }

    // formRecord init
    formRecord.isInited = true;
    formRecord.needRefresh = false;
    FormDataMgr::GetInstance().SetFormCacheInited(formId, true);

    // update form for host clients
    FormDataMgr::GetInstance().UpdateHostNeedRefresh(formId, true);

#ifdef SUPPORT_POWER
    bool screenOnFlag = PowerMgr::PowerMgrClient::GetInstance().IsScreenOn();
    if (screenOnFlag) {
        if (FormDataMgr::GetInstance().UpdateHostForm(formId, formRecord)) {
            FormDataMgr::GetInstance().SetVersionUpgrade(formId, false);
            formRecord.formProviderInfo.SetUpgradeFlg(false);
        }
    }
    HILOG_DEBUG("%{public}s screenOn:%{public}d.", __func__, screenOnFlag);
#endif

    if (formRecord.formProviderInfo.NeedCache()) {
        HILOG_INFO("updateJsForm, data is less than 1k, cache data.");
        FormCacheMgr::GetInstance().AddData(formId, formRecord.formProviderInfo.GetFormData());
    } else {
        FormCacheMgr::GetInstance().DeleteData(formId);
    }

    // the update form is successfully
    return ERR_OK;
}
/**
 * @brief Process js message event.
 * @param formId Indicates the unique id of form.
 * @param record Form record.
 * @param want information passed to supplier.
 * @return Returns true if execute success, false otherwise.
 */
int FormProviderMgr::MessageEvent(const int64_t formId, const FormRecord &record, const Want &want)
{
    HILOG_INFO("formId:%{public}" PRId64, formId);

#ifdef SUPPORT_POWER
    bool screenOnFlag = PowerMgr::PowerMgrClient::GetInstance().IsScreenOn();
    if (!screenOnFlag) {
        HILOG_WARN("%{public}s fail, screen off now", __func__);
        return ERR_APPEXECFWK_FORM_COMMON_CODE;
    }
#endif

    sptr<IAbilityConnection> formMsgEventConnection = new (std::nothrow) FormMsgEventConnection(formId, want,
        record.bundleName, record.abilityName);
    if (formMsgEventConnection == nullptr) {
        HILOG_ERROR("failed to create FormMsgEventConnection.");
        return ERR_APPEXECFWK_FORM_COMMON_CODE;
    }
    Want connectWant;
    connectWant.AddFlags(Want::FLAG_ABILITY_FORM_ENABLED);
    connectWant.SetElementName(record.bundleName, record.abilityName);

    ErrCode errorCode = FormAmsHelper::GetInstance().ConnectServiceAbility(connectWant, formMsgEventConnection);
    if (errorCode != ERR_OK) {
        HILOG_ERROR("%{public}s, ConnectServiceAbility failed.", __func__);
        return ERR_APPEXECFWK_FORM_BIND_PROVIDER_FAILED;
    }

    return ERR_OK;
}

/**
 * @brief Increase the timer refresh count.
 *
 * @param formId The form id.
 */
void FormProviderMgr::IncreaseTimerRefreshCount(const int64_t formId)
{
    FormRecord record;
    if (!FormDataMgr::GetInstance().GetFormRecord(formId, record)) {
        HILOG_ERROR("%{public}s failed, not exist such form:%{public}" PRId64 ".", __func__, formId);
        return;
    }

    if (record.isCountTimerRefresh) {
        FormDataMgr::GetInstance().SetCountTimerRefresh(formId, false);
        FormTimerMgr::GetInstance().IncreaseRefreshCount(formId);
    }
}

/**
 * @brief Acquire form state.
 * @param state form state.
 * @param provider provider info.
 * @param wantArg The want of onAcquireFormState.
 * @return Returns ERR_OK on success, others on failure.
 */
ErrCode FormProviderMgr::AcquireFormStateBack(FormState state, const std::string& provider, const Want &wantArg)
{
    HILOG_DEBUG("AcquireFormState start: %{public}d, provider: %{public}s", state, provider.c_str());
    FormDataMgr::GetInstance().AcquireFormStateBack(state, provider, wantArg);
    return ERR_OK;
}

ErrCode FormProviderMgr::AcquireFormDataBack(const AAFwk::WantParams &wantParams,
    int64_t requestCode)
{
    HILOG_DEBUG("start.");
    FormDataMgr::GetInstance().AcquireFormDataBack(wantParams, requestCode);
    return ERR_OK;
}

bool FormProviderMgr::IsNeedToFresh(FormRecord &record, int64_t formId, bool isVisibleToFresh)
{
    bool isEnableRefresh = FormDataMgr::GetInstance().IsEnableRefresh(formId);
    HILOG_DEBUG("isEnableRefresh is %{public}d", isEnableRefresh);
    if (isEnableRefresh) {
        return true;
    }

    HILOG_DEBUG("isVisibleToFresh is %{public}d, record.isVisible is %{public}d", isVisibleToFresh, record.isVisible);
    if (isVisibleToFresh) {
        if (!record.isVisible) {
            FormRecordReport::GetInstance().IncreaseUpdateTimes(formId, HiSysEventPointType::TYPE_INVISIBLE_INTERCEPT);
        }
        return record.isVisible;
    }

    bool isEnableUpdate = FormDataMgr::GetInstance().IsEnableUpdate(formId);
    HILOG_DEBUG("isEnableUpdate is %{public}d", isEnableUpdate);
    return isEnableUpdate;
}

FormRecord FormProviderMgr::GetFormAbilityInfo(const FormRecord &record) const
{
    FormRecord newRecord;
    newRecord.bundleName = record.bundleName;
    newRecord.moduleName = record.moduleName;
    newRecord.abilityName = record.abilityName;
    newRecord.isInited = record.isInited;
    newRecord.versionUpgrade = record.versionUpgrade;
    newRecord.needFreeInstall = record.needFreeInstall;
    return newRecord;
}

bool FormProviderMgr::IsFormCached(const FormRecord &record)
{
    if (record.versionUpgrade) {
        return false;
    }
    return FormCacheMgr::GetInstance().NeedAcquireProviderData(record.formId);
}

ErrCode FormProviderMgr::RebindByFreeInstall(const FormRecord &record, Want &want,
    const sptr<AAFwk::IAbilityConnection> formRefreshConnection)
{
    HILOG_INFO("start");
    want.AddFlags(Want::FLAG_INSTALL_ON_DEMAND | Want::FLAG_INSTALL_WITH_BACKGROUND_MODE);
    want.SetModuleName(record.moduleName);
    ErrCode errorCode = FormAmsHelper::GetInstance().ConnectServiceAbility(want, formRefreshConnection);
    if (errorCode != ERR_OK) {
        HILOG_ERROR("%{public}s, ConnectServiceAbility failed, err: %{public}d", __func__, errorCode);
        return ERR_APPEXECFWK_FORM_BIND_PROVIDER_FAILED;
    }
    return ERR_OK;
}
}  // namespace AppExecFwk
}  // namespace OHOS
