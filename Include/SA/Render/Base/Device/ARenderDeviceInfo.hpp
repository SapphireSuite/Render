// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_ARENDER_DEVICE_INFO_GUARD
#define SAPPHIRE_RENDER_ARENDER_DEVICE_INFO_GUARD

#include <cstdint>
#include <string>

#include "RenderDeviceRequirements.hpp"

namespace SA
{
	struct ARenderDeviceInfo
	{
		/// Device ID.
		uint32_t ID = uint32_t(-1);

		/// Vendor ID.
		uint32_t vendorID = uint32_t(-1);

		std::string name;

		virtual ~ARenderDeviceInfo() = default;
	};
}

#endif // SAPPHIRE_RENDER_ARENDER_DEVICE_INFO_GUARD
