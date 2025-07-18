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

import Want from '@ohos.app.ability.Want';

export namespace formInfo {
  interface FormInfo {
    bundleName: string;
    moduleName: string;
    abilityName: string;
    name: string;
    displayName: string;
    displayNameId: number;
    description: string;
    descriptionId: number;
    type: FormType;
    jsComponentName: string;
    colorMode: ColorMode;
    isDefault: boolean;
    updateEnabled: boolean;
    formVisibleNotify: boolean;
    scheduledUpdateTime: string;
    formConfigAbility: string;
    updateDuration: number;
    defaultDimension: number;
    supportDimensions: Array<number>;
    customizeData: Record<string, string>;
    isDynamic: boolean;
    transparencyEnabled: boolean;
    supportedShapes: Array<number>;
    readonly previewImages?: Array<number>;
    readonly enableBlurBackground?: boolean;
    readonly renderingMode?: RenderingMode;
  }

  enum RenderingMode {
    AUTO_COLOR = 0,
    FULL_COLOR = 1,
    SINGLE_COLOR = 2
  }

  enum FormType {
    JS = 1,
    eTS = 2
  }

  enum ColorMode {
    MODE_AUTO = -1,
    MODE_DARK = 0,
    MODE_LIGHT = 1
  }

  interface FormStateInfo {
    formState: FormState;
    want: Want;
  }

  enum FormState {
    UNKNOWN = -1,
    DEFAULT = 0,
    READY = 1
  }

  enum FormParam {
    IDENTITY_KEY = 'ohos.extra.param.key.form_identity',
    DIMENSION_KEY = 'ohos.extra.param.key.form_dimension',
    NAME_KEY = 'ohos.extra.param.key.form_name',
    MODULE_NAME_KEY = 'ohos.extra.param.key.module_name',
    WIDTH_KEY = 'ohos.extra.param.key.form_width',
    HEIGHT_KEY = 'ohos.extra.param.key.form_height',
    TEMPORARY_KEY = 'ohos.extra.param.key.form_temporary',
    BUNDLE_NAME_KEY = 'ohos.extra.param.key.bundle_name',
    ABILITY_NAME_KEY = 'ohos.extra.param.key.ability_name',
    THEME_KEY = 'ohos.extra.param.key.form_is_theme',
    DEVICE_ID_KEY = 'ohos.extra.param.key.device_id',
    LAUNCH_REASON_KEY = 'ohos.extra.param.key.form_launch_reason',
    PARAM_FORM_CUSTOMIZE_KEY = 'ohos.extra.param.key.form_customize',
    FORM_LOCATION_KEY = 'ohos.extra.param.key.form_location',
    FORM_RENDERING_MODE_KEY = 'ohos.extra.param.key.form_rendering_mode',
    HOST_BG_INVERSE_COLOR_KEY = 'ohos.extra.param.key.host_bg_inverse_color',
    FORM_PERMISSION_NAME_KEY = 'ohos.extra.param.key.permission_name',
    FORM_PERMISSION_GRANTED_KEY = 'ohos.extra.param.key.permission_granted',
  }

  interface FormInfoFilter {
    bundleName?: string;
    moduleName?: string;
    supportedDimensions?: Array<number>;
    supportedShapes?: Array<number>;
  }

  enum FormDimension {
    Dimension_1_2 = 1,
    Dimension_2_2 = 2,
    Dimension_2_4 = 3,
    Dimension_4_4 = 4,
    Dimension_2_1,
    DIMENSION_1_1 = 6,
    DIMENSION_6_4 = 7,
    DIMENSION_2_3 = 8,
    DIMENSION_3_3 = 9
  }

  enum FormShape {
    RECT = 1,
    CIRCLE = 2
  }

  enum VisibilityType {
    UNKNOWN = 0,
    FORM_VISIBLE = 1,
    FORM_INVISIBLE = 2
  }

  enum LaunchReason {
    FORM_DEFAULT = 1,
    FORM_SHARE = 2
  }

  interface PublishFormResult {
    code: PublishFormErrorCode;
    message: string;
  }

  enum PublishFormErrorCode {
    SUCCESS = 0,
    NO_SPACE = 1,
    PARAM_ERROR = 2,
    INTERNAL_ERROR = 3
  }

  interface FormProviderFilter {
    bundleName: string;
    formName?: string;
    moduleName?: string;
    abilityName?: string;
    isUnusedIncluded?: boolean;
  }

  interface RunningFormInfo {
    readonly formId: string;
    readonly bundleName: string;
    readonly hostBundleName: string;
    readonly formLocation: FormLocation;
    readonly visibilityType: VisibilityType;
    readonly moduleName: string;
    readonly abilityName: string;
    readonly formName: string;
    readonly dimension: number;
    readonly formUsageState: FormUsageState;
    readonly formDescription: string;
    readonly extraData?: Record<string, Object>;
  }

  enum FormUsageState {
    USED = 0,
    UNUSED = 1
  }

  enum FormLocation {
    OTHER = -1,
    DESKTOP = 0,
    FORM_CENTER = 1,
    FORM_MANAGER = 2,
    NEGATIVE_SCREEN = 3,
    FORM_CENTER_NEGATIVE_SCREEN = 4,
    FORM_MANAGER_NEGATIVE_SCREEN = 5,
    SCREEN_LOCK = 6,
    AI_SUGGESTION = 7,
  }
}
