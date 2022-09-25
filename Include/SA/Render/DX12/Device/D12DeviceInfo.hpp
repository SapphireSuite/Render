// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_D12_DEVICE_INFO_GUARD
#define SAPPHIRE_RENDER_D12_DEVICE_INFO_GUARD

#include <SA/Render/Base/Device/ARenderDeviceInfo.hpp>

#include "D12PhysicalDevice.hpp"

namespace SA
{
	namespace DX12
	{
		struct DeviceInfo : public ARenderDeviceInfo
		{
			PhysicalDevice physicalDevice = nullptr;
		};
	}
}

#endif // SAPPHIRE_RENDER_D12_DEVICE_INFO_GUARD
