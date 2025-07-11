/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#ifndef OHOS_FORM_FWK_FORM_SUPPLY_CALLBACK_H
#define OHOS_FORM_FWK_FORM_SUPPLY_CALLBACK_H

#include "common/connection/form_ability_connection.h"
#include "form_supply_stub.h"

namespace OHOS {
namespace AppExecFwk {
/**
 * @class FormSupplyCallback
 * form supply service stub.
 */
class FormSupplyCallback : public FormSupplyStub {
public:
    FormSupplyCallback() = default;
    virtual ~FormSupplyCallback() = default;
    static sptr<FormSupplyCallback> GetInstance();

    void ProcessFormAcquisition(int64_t formId);
    /**
     * @brief Accept form binding data from form provider.
     * @param providerFormInfo Form binding data.
     * @param want input data.
     * @return Returns ERR_OK on success, others on failure.
     */
    int OnAcquire(const FormProviderInfo &formInfo, const Want &want) override;

    /**
     * @brief Accept other event.
     * @param want input data.
     * @return Returns ERR_OK on success, others on failure.
     */
    int OnEventHandle(const Want &want) override;

    /**
     * @brief Accept form state from form provider.
     * @param state Form state.
     * @param provider provider info.
     * @param wantArg The want of onAcquireFormState.
     * @param want input data.
     * @return Returns ERR_OK on success, others on failure.
     */
    int OnAcquireStateResult(FormState state, const std::string &provider, const Want &wantArg,
                             const Want &want) override;
    
    /**
     * @brief Accept form data from form provider.
     * @param formId The Id of the from.
     * @param wantParams Indicates the data information acquired by the form.
     * @param requestCode Indicates the requested id.
     * @return Returns ERR_OK on success, others on failure.
     */
    int OnAcquireDataResult(const AAFwk::WantParams &wantParams, int64_t requestCode) override;

    /**
     * @brief Save ability Connection for the callback.
     * @param connection ability connection.
     */
    void AddConnection(sptr<FormAbilityConnection> connection);
    /**
     * @brief Delete ability connection after the callback come.
     * @param connectId The ability connection id generated when save.
     */
    void RemoveConnection(int32_t connectId);
    /**
     * @brief Delete ability connection by formId and hostToken.
     * @param formId Indicates the ID of the form.
     * @param hostToken Indicates the host token for matching connection.
     */
    void RemoveConnection(int64_t formId, const sptr<IRemoteObject> &hostToken);

    void OnShareAcquire(int64_t formId, const std::string &remoteDeviceId,
        const AAFwk::WantParams &wantParams, int64_t requestCode, const bool &result) override;

    /**
     * @brief Handle form host died.
     * @param hostToken Form host proxy object.
     */
    void HandleHostDied(const sptr<IRemoteObject> &hostToken);

    /**
     * @brief Accept form render task done from render service.
     * @param formId The Id of the form.
     * @param want input data.
     * @return Returns ERR_OK on success, others on failure.
     */
    int32_t OnRenderTaskDone(int64_t formId, const Want &want) override;

    /**
     * @brief Accept form stop rendering task done from render service.
     * @param formId The Id of the form.
     * @param want input data.
     * @return Returns ERR_OK on success, others on failure.
     */
    int32_t OnStopRenderingTaskDone(int64_t formId, const Want &want) override;

    /**
     * @brief Accept rendering block from render service.
     * @param bundleName The block of bundleName.
     * @return Returns ERR_OK on success, others on failure.
     */
    int32_t OnRenderingBlock(const std::string &bundleName) override;

    /**
     * @brief Accept status data of recycled form from render service
     * @param formId The Id of the form.
     * @param want Input data.
     * @return Returns ERR_OK on success, others on failure.
     */
    int32_t OnRecycleForm(const int64_t formId, const Want &want) override;

    /**
     * @brief Trigger card recover when configuration changes occur.
     * @param formIds The ids of the forms.
     * @return Returns ERR_OK on success, others on failure.
     */
    int32_t OnRecoverFormsByConfigUpdate(std::vector<int64_t> &formIds) override;

    int32_t OnNotifyRefreshForm(const int64_t formId) override;

    /**
     * @brief Accept form render done from form render service.
     * @param formId The Id of the form.
     * @param want Input data.
     * @return Returns ERR_OK on success, others on failure.
     */
    int32_t OnRenderFormDone(const int64_t formId, const Want &want) override;

    /**
     * @brief Accept form recover done from form render service.
     * @param formId The Id of the form.
     * @param want Input data.
     * @return Returns ERR_OK on success, others on failure.
     */
    int32_t OnRecoverFormDone(const int64_t formId, const Want &want) override;

    /**
     * @brief Accept form recycle done from form render service.
     * @param formId The Id of the form.
     * @param want Input data.
     * @return Returns ERR_OK on success, others on failure.
     */
    int32_t OnRecycleFormDone(const int64_t formId, const Want &want) override;

    /**
     * @brief Accept form delete done from form render service.
     * @param formId The Id of the form.
     * @param want Input data.
     * @return Returns ERR_OK on success, others on failure.
     */
    int32_t OnDeleteFormDone(const int64_t formId, const Want &want) override;

private:
    /**
     * @brief check if disconnect ability or not.
     * @param connection The ability connection.
     */
    bool CanDisconnect(sptr<FormAbilityConnection> &connection);

    bool IsRemoveConnection(int64_t formId, const sptr<IRemoteObject> &hostToken);
private:
    static std::mutex mutex_;
    static sptr<FormSupplyCallback> instance_;

    mutable std::mutex conMutex_;
    std::map<int32_t, sptr<FormAbilityConnection>> connections_;
    DISALLOW_COPY_AND_MOVE(FormSupplyCallback);
};
}  // namespace AppExecFwk
}  // namespace OHOS
#endif  // OHOS_FORM_FWK_FORM_SUPPLY_CALLBACK_H
