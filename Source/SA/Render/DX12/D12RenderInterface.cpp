// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <D12RenderInterface.hpp>

#include <Debug/Debug.hpp>

namespace SA
{
	namespace DX12
	{
		void RenderInterface::Create(AWindowInterface* _win_intf)
		{
			ARenderInterface::Create(_win_intf);

			mFactory.Create();

			SA_LOG(L"Render Interface created.", Infos, SA/Render/DX12);
		}

		void RenderInterface::Destroy()
		{
			ARenderInterface::Destroy();

			mFactory.Destroy();

			SA_LOG(L"Render Interface destroyed.", Infos, SA/Render/DX12);
		}

		void RenderInterface::Clear()
		{
			ARenderInterface::Clear();

			SA_LOG(L"Render Interface cleared.", Infos, SA/Render/DX12);
		}


#if SA_WINDOWING_IMPL

		AWindowSurface* RenderInterface::CreateWindowSurface(AWindow* _win)
		{
			return nullptr;
		}

		void RenderInterface::DestroyWindowSurface(AWindowSurface* _winSurface)
		{
		}

#endif


	//{ Device

		HI::PolymorphicVector<ARenderDeviceInfo> RenderInterface::QueryDevices(const RenderDeviceRequirements& _reqs)
		{
			CheckCreated();

			return Device::QueryDevices(mFactory, _reqs);
		}

		ARenderDevice* RenderInterface::CreateDevice(const ARenderDeviceInfo* _info)
		{
			CheckCreated();

			Device* const device = mDevices.Emplace();

			device->Create(*dynamic_cast<const DeviceInfo*>(_info));

			return device;
		}

		void RenderInterface::DestroyDevice(ARenderDevice* _device)
		{
			CheckCreated();

			mDevices.Erase(_device);
		}

	//}
	}
}
