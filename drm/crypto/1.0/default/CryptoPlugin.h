/*
 * Copyright (C) 2016 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ANDROID_HARDWARE_DRM_CRYPTO_V1_0__CRYPTOPLUGIN_H
#define ANDROID_HARDWARE_DRM_CRYPTO_V1_0__CRYPTOPLUGIN_H

#include <media/hardware/CryptoAPI.h>
#include <android/hardware/drm/crypto/1.0/ICryptoPlugin.h>
#include <hidl/Status.h>

namespace android {
namespace hardware {
namespace drm {
namespace crypto {
namespace V1_0 {
namespace implementation {

using ::android::hardware::drm::crypto::V1_0::DestinationBuffer;
using ::android::hardware::drm::crypto::V1_0::ICryptoPlugin;
using ::android::hardware::drm::crypto::V1_0::Mode;
using ::android::hardware::drm::crypto::V1_0::Pattern;
using ::android::hardware::drm::crypto::V1_0::SubSample;
using ::android::hardware::hidl_array;
using ::android::hardware::hidl_string;
using ::android::hardware::hidl_vec;
using ::android::hardware::Return;
using ::android::hardware::Void;
using ::android::sp;

struct CryptoPlugin : public ICryptoPlugin {
    CryptoPlugin(android::CryptoPlugin *plugin) : mLegacyPlugin(plugin) {}
    ~CryptoPlugin() {delete mLegacyPlugin;}

    // Methods from ::android::hardware::drm::crypto::V1_0::ICryptoPlugin
    // follow.

    Return<bool> requiresSecureDecoderComponent(const hidl_string& mime)
            override;

    Return<void> notifyResolution(uint32_t width, uint32_t height) override;

    Return<Status> setMediaDrmSession(const hidl_vec<uint8_t>& sessionId)
            override;

    Return<void> decrypt(bool secure, const hidl_array<uint8_t, 16>& keyId,
            const hidl_array<uint8_t, 16>& iv, Mode mode, const Pattern& pattern,
            const hidl_vec<SubSample>& subSamples, const hidl_memory& source,
            const DestinationBuffer& destination, decrypt_cb _hidl_cb) override;

private:
    android::CryptoPlugin *mLegacyPlugin;

    CryptoPlugin() = delete;
    CryptoPlugin(const CryptoPlugin &) = delete;
    void operator=(const CryptoPlugin &) = delete;
};

}  // namespace implementation
}  // namespace V1_0
}  // namespace crypto
}  // namespace drm
}  // namespace hardware
}  // namespace android

#endif  // ANDROID_HARDWARE_DRM_CRYPTO_V1_0__CRYPTOPLUGIN_H
