// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_DX12_PHYSICAL_DEVICE_GUARD
#define SAPPHIRE_RENDER_DX12_PHYSICAL_DEVICE_GUARD

#include <d3d12.h>
#include <dxgi.h>

#include <wrl.h>

namespace SA
{
	namespace DX12
	{
		using PhysicalDevice = Microsoft::WRL::ComPtr<IDXGIAdapter1>;
	}
}

#endif // SAPPHIRE_RENDER_DX12_PHYSICAL_DEVICE_GUARD
