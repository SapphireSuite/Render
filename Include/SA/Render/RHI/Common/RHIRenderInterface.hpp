// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_RENDER_INTERFACE_GUARD
#define SAPPHIRE_RENDER_RHI_RENDER_INTERFACE_GUARD

#include <vector>
#include <memory>
#include <forward_list>

#include "Device/RHIDevice.hpp"
#include "Device/RHIDeviceRequirements.hpp"
#include "Surface/RHIWindowSurface.hpp"
#include "Surface/RHISwapchain.hpp"
#include "Compatibility/IWindowInterface.hpp"

#include <SA/Render/ShaderCompiler/ShaderCompiler.hpp>

namespace SA::RND
{
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	namespace VK
	{
		class Instance;
	}

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

	namespace DX12
	{
		class Factory;
	}

#endif

	namespace RHI
	{
		class RenderInterface
		{
		public:
			virtual ~RenderInterface() = default;

			virtual void Create(const IWindowInterface* _winIntf = nullptr);
			virtual void Destroy();

	//{ WindowSurface

		private:
			std::forward_list<WindowSurface*> mWindowSurfaces;

		protected:
			virtual WindowSurface* InstantiateWindowSurfaceClass() const = 0;
			virtual void DeleteWindowSurfaceClass(WindowSurface* _winSurface) const;

		public:
			WindowSurface* CreateWindowSurface(const IRenderWindow* _window);
			void DestroyWindowSurface(WindowSurface* _winSurface);
			void DestroyAllWindowSurfaces();

	//}
	

	//{ Device

		private:
			std::forward_list<Device*> mDevices;

		protected:
			virtual Device* InstantiateDeviceClass() const = 0;
			virtual void DeleteDeviceClass(Device* _device) const;

		public:
			Device* CreateDevice(const DeviceInfo* _info);
			void DestroyDevice(Device* _device);
			void DestroyAllDevices();

			virtual std::vector<std::shared_ptr<DeviceInfo>> QueryDeviceInfos(const DeviceRequirements& _reqs = DeviceRequirements()) const = 0;

	//}


	//{ Swapchain

		private:
			std::forward_list<Swapchain*> mSwapchains;

		protected:
			virtual Swapchain* InstantiateSwapchainClass() const = 0;
			virtual void DeleteSwapchainClass(Swapchain* _swapchain) const;

		public:
			Swapchain* CreateSwapchain(const Device* _device,
				const WindowSurface* _winSurface,
				const SwapchainSettings& _settings = SwapchainSettings());
			void DestroySwapchain(const Device* _device, Swapchain* _swapchain);
			// void DestroyAllSwapchains();

	//}

	//{ ShaderCompiler

		protected:
			ShaderCompiler mShaderCompiler;

		public:
			virtual ShaderCompileResult CompileShader(const ShaderCompileInfo& _info) = 0;

	//}

		public:
		#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

			virtual const VK::Instance& API_Vulkan() const;

		#endif

		#if SA_RENDER_LOWLEVEL_DX12_IMPL

			virtual const DX12::Factory& API_DirectX12() const;

		#endif
		};
	}
}

#endif // SAPPHIRE_RENDER_RHI_RENDER_INTERFACE_GUARD
