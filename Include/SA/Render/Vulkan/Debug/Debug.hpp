// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VULKAN_DEBUG_GUARD
#define SAPPHIRE_RENDER_VULKAN_DEBUG_GUARD

#include <SA/Collections/Debug>

#include "Exception_Vulkan.hpp"

#define SA_VK_VALIDATION_LAYERS (SA_DEBUG || SA_LOG_RELEASE_OPT) && 1

#define SA_VK_ASSERT(_pred, ...) SA_ASSERT_EXEC(Vulkan, SA/Render/Vulkan, (_pred), ##__VA_ARGS__)

#endif // SAPPHIRE_RENDER_VULKAN_DEBUG_GUARD
