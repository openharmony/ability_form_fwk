/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

let UIExtensionContext = requireNapi('application.UIExtensionContext');

export class LiveFormExtensionContext extends UIExtensionContext {
  formId = '';
  constructor(obj) {
    super(obj);
  }

  setWindowBackgroundColor(color) {
    console.log(`setWindowBackgroundColor: ${JSON.stringify(color)}`);
    return this.__context_impl__.setWindowBackgroundColor(color);
  }

  startAbilityByLiveForm(want) {
    hilog.sLogI(domainID, TAG, `startAbilityByLiveForm: ${JSON.stringify(want)}`);
    return this.__context_impl__.startAbilityByLiveForm(want, this.formId);
  }
}