/*
 * Copyright (C) 2023 SHIFT GmbH
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "Lights.h"

#include <android-base/file.h>
#include <android-base/logging.h>
#include <android-base/strings.h>
#include <android/binder_status.h>
#include <fstream>
#include "android/binder_auto_utils.h"

#define LOG_TAG "hardware.shift.light-service.default"

namespace aidl {
namespace hardware {
namespace shift {
namespace light {

static bool fileExists(const std::string& path) {
    if (path.empty()) {
        return false;
    }

    int retries = 10;

    while (retries--) {
        android::base::unique_fd fd(TEMP_FAILURE_RETRY(open(path.c_str(), O_RDWR)));

        if (fd > -1) {
            return true;
        }

        usleep(100000);
    }

    return false;
}

static const std::vector<TorchNode> kTorchNodes = {
        {0, TorchType::COLD, "/sys/class/leds/led:torch_0/brightness",
         "/sys/class/leds/led:torch_0/max_brightness", "/sys/class/leds/led:torch_0/trigger"},
        {1, TorchType::WARM, "/sys/class/leds/led:torch_1/brightness",
         "/sys/class/leds/led:torch_1/max_brightness", "/sys/class/leds/led:torch_1/trigger"},
};

ndk::ScopedAStatus Lights::setTorchState(const Torch& in_torch, const TorchState& in_state) {
    for (const auto& node : kTorchNodes) {
        if (node.id != in_torch.id) {
            continue;
        }

        const auto& brightnessValue = std::to_string(in_state.brightness);
        if (!android::base::WriteStringToFile(brightnessValue, node.brightnessPath, true)) {
            LOG(ERROR) << "Failed to write to torch brightness node: " << strerror(errno);
            return ndk::ScopedAStatus::fromExceptionCode(EX_ILLEGAL_STATE);
        }

        const auto& triggerValue = "torch0_trigger";
        if (!android::base::WriteStringToFile(triggerValue, node.triggerPath, true)) {
            LOG(ERROR) << "Failed to write to torch trigger node: " << strerror(errno);
            return ndk::ScopedAStatus::fromExceptionCode(EX_ILLEGAL_STATE);
        }

        return ndk::ScopedAStatus::ok();
    }
    return ndk::ScopedAStatus::fromExceptionCode(EX_UNSUPPORTED_OPERATION);
}

ndk::ScopedAStatus Lights::getTorches(std::vector<Torch>* torches) {
    for (const auto& node : kTorchNodes) {
        if (!fileExists(node.brightnessPath) || !fileExists(node.brightnessMaxPath) ||
            !fileExists(node.triggerPath)) {
            continue;
        }

        std::string maxBrightnessStr;
        if (!android::base::ReadFileToString(node.brightnessMaxPath, &maxBrightnessStr, true)) {
            LOG(ERROR) << "Failed to read max brightness value value for torch with id " << node.id;
            continue;
        }
        maxBrightnessStr = android::base::Trim(maxBrightnessStr);

        Torch torch;
        torch.id = node.id;
        torch.type = node.type;
        torch.maxBrightness = std::stoi(maxBrightnessStr);
        torches->push_back(torch);
    }

    return ndk::ScopedAStatus::ok();
}

binder_status_t Lights::dump(int fd, const char** /* args */, uint32_t /* numArgs */) {
    std::vector<Torch> torches;
    getTorches(&torches);

    dprintf(fd, "Torches:\n");
    for (const auto& torch : torches) {
        dprintf(fd, "\t- ID: %d, Type: %s, Max Brightness: %d\n", torch.id,
                toString(torch.type).c_str(), torch.maxBrightness);
    }

    return STATUS_OK;
}

}  // namespace light
}  // namespace shift
}  // namespace hardware
}  // namespace aidl
