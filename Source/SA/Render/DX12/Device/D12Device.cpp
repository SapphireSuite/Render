// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Device/D12Device.hpp>

#include <Debug/Debug.hpp>

#include "D12Factory.hpp"
#include "../Debug/D12ValidationLayers.hpp"

namespace SA
{
	namespace DX12
	{
		void Device::Create(const DeviceInfo& _info)
		{
			ARenderDevice::Create();

			mPhysicalDevice = _info.physicalDevice;

			SA_DX12_ASSERT(D3D12CreateDevice(mPhysicalDevice.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&mLogicalDevice)),
				L"Failed to create logical device!")

			SetDebugName(mLogicalDevice, "SA:: Device {" + _info.name + "} [" + SA::ToString(_info.ID) + "]");

#if SA_DX12_VALIDATION_LAYERS

			ID3D12InfoQueue* infoQueue = nullptr;

			if (mLogicalDevice->QueryInterface(IID_PPV_ARGS(&infoQueue)) == S_OK)
			{
				infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, true);
				infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, true);
				infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_WARNING, true);

				infoQueue->Release();
			}
			else
				SA_LOG(L"Device query info queue to enable validation layers failed.", Error, SA/Render/DX12);

#endif // SA_DX12_VALIDATION_LAYERS

			SA_DX12_CREATE_DETS_LOG(Device, mLogicalDevice, L"Name: " << _info.name << "\tID: " << _info.ID << "\tVendorID: " << _info.vendorID);
		}

		void Device::Destroy()
		{
			ARenderDevice::Destroy();

			{
				SA_DX12_POST_DESTROY_LOG(LogicalDevice, mLogicalDevice);

				mLogicalDevice->Release();
				mLogicalDevice = nullptr;
			}

			{
				SA_DX12_POST_DESTROY_LOG(PhysicalDevice, mPhysicalDevice);

				// ComPtr already call Release.
				mPhysicalDevice = nullptr;
			}
		}

	//{ Query

		bool CheckDX12Support(const PhysicalDevice& _adapter)
		{
			// Try create device to check whether the adapter supports Direct3D 12.
			return SUCCEEDED(D3D12CreateDevice(_adapter.Get(), D3D_FEATURE_LEVEL_11_0, _uuidof(ID3D12Device), nullptr));
		}

		bool IsPhysicalDeviceSuitable(const PhysicalDevice& _adapter, const RenderDeviceRequirements& _reqs, DeviceInfo& _info)
		{
			DXGI_ADAPTER_DESC1 desc;
			_adapter->GetDesc1(&desc);

			if (_reqs.bUseWrapAdapter ^ bool(desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE))
				return false;

			if (!CheckDX12Support(_adapter))
				return false;

			_info.ID = desc.DeviceId;
			_info.vendorID = desc.VendorId;

			const std::wstring wdesc = desc.Description;
			_info.name = std::string(wdesc.begin(), wdesc.end());
			
			_info.physicalDevice = _adapter;

			return true;
		}

		std::vector<DeviceInfo> Device::QueryDevices(const Factory& _factory, const RenderDeviceRequirements& _reqs)
		{
			std::vector<DeviceInfo> result;
			result.reserve(10);

			UINT index = 0;
			PhysicalDevice adapter = nullptr;

			if (_reqs.bUseWrapAdapter)
			{
				SA_DX12_ASSERT(_factory->EnumWarpAdapter(IID_PPV_ARGS(&adapter)), L"Query wrap adapter failed!");
				
				DeviceInfo info;

				if (IsPhysicalDeviceSuitable(adapter, _reqs, info))
					result.emplace_back(std::move(info));
			}
			else
			{
				while (SUCCEEDED(_factory->EnumAdapterByGpuPreference(index, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(&adapter))))
				{
					DeviceInfo info;

					if (IsPhysicalDeviceSuitable(adapter, _reqs, info))
						result.emplace_back(std::move(info));

					++index;
				}
			}

			SA_WARN(!result.empty(), SA/Render/DX12, L"No suitable graphic device found!");

			return result;
		}

	//}
	}
}
