// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_DX12_DEVICE_GUARD
#define SAPPHIRE_RENDER_DX12_DEVICE_GUARD

#include <SA/Render/Base/Device/ARenderDevice.hpp>

#include <SA/Render/DX12/Device/D12DeviceInfo.hpp>

namespace SA
{
	namespace DX12
	{
		class Factory;

		class Device : public ARenderDevice
		{
			/// Physical device.
			PhysicalDevice mPhysicalDevice = nullptr;

			/// Logical device.
			ID3D12Device* mLogicalDevice = nullptr;

			using ARenderDevice::Create;

		public:
			void Create(const DeviceInfo& _info);
			void Destroy() override;

			static std::vector<DeviceInfo> QueryDevices(const Factory& _factory, const RenderDeviceRequirements& _reqs = RenderDeviceRequirements());
		};
	}
}

#endif // SAPPHIRE_RENDER_DX12_DEVICE_GUARD
