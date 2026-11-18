#!/bin/bash
set -e

export PLATFORM_VERSION=11
export ANDROID_MAJOR_VERSION=r
export ARCH=arm64
export SEC_BUILD_CONF_VENDOR_BUILD_OS=13

# Default to the unified build for all supported Exynos 990 models.
# Per-device build: ./build_kernel.sh z3s
DEVICE="${1:-unified}"

make exynos9830_defconfig
make "${DEVICE}.config"
make
