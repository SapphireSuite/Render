// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_DX12_DEBUG_GUARD
#define SAPPHIRE_RENDER_DX12_DEBUG_GUARD

#include <SA/Collections/Debug>

#include "Exception_DX12.hpp"

#define SA_DX12_ASSERT(_pred, ...) SA_ASSERT_EXEC(DX12, SA/Render/DX12, (_pred), ##__VA_ARGS__)

#endif // SAPPHIRE_RENDER_DX12_DEBUG_GUARD
