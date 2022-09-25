// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SA_RENDER_ARENDER_INTERFACE_GUARD
#define SA_RENDER_ARENDER_INTERFACE_GUARD

#include <SA/HI/Interface.hpp>
#include <SA/HI/InterfaceList.hpp>
#include <SA/HI/PolymorphicContainer.hpp>

#include "Surface/AWindowSurface.hpp"
#include "Device/ARenderDevice.hpp"
#include "Device/ARenderDeviceInfo.hpp"

namespace SA
{
	class AWindowInterface;

	class ARenderInterface : private HI::Interface
	{
		using HI::Interface::Create;

	protected:
		using HI::Interface::CheckCreated;

	public:
		virtual void Create(AWindowInterface* _win_intf = nullptr);
		void Destroy() override;

		void Clear() override;

#if SA_WINDOWING_IMPL

		virtual AWindowSurface* CreateWindowSurface(AWindow* _win) = 0;
		virtual void DestroyWindowSurface(AWindowSurface* _winSurface) = 0;

#endif

	//{ Device

		virtual HI::PolymorphicVector<ARenderDeviceInfo> QueryDevices() = 0;
		virtual ARenderDevice* CreateDevice(const ARenderDeviceInfo* _info) = 0;
		virtual void DestroyDevice(ARenderDevice* _device) = 0;

	//}
	};
}

#endif // SA_RENDER_ARENDER_INTERFACE_GUARD
