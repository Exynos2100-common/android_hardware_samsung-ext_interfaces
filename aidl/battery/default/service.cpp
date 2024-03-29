/*
 * Copyright (C) 2023 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "SmartCharge.h"

#include <android/binder_manager.h>
#include <android/binder_process.h>
#include <android-base/logging.h>

using ::aidl::vendor::samsung_ext::framework::battery::SmartCharge;

int main() {
    ABinderProcess_setThreadPoolMaxThreadCount(8);
    std::shared_ptr<SmartCharge> smartcharge = ndk::SharedRefBase::make<SmartCharge>();

    const std::string instance = std::string() + SmartCharge::descriptor + "/default";
    binder_status_t status = AServiceManager_addService(smartcharge->asBinder().get(), instance.c_str());
    CHECK(status == STATUS_OK);

    ABinderProcess_joinThreadPool();
    return EXIT_FAILURE; // should not reach
}
