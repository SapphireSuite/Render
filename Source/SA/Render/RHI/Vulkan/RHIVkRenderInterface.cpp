// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <RHIVkRenderInterface.hpp>

#include <Device/RHIVkDevice.hpp>
#include <Surface/RHIVkWindowSurface.hpp>
#include <Surface/RHIVkSwapchain.hpp>

namespace SA::RND::RHI
{
	void VkRenderInterface::Create(const IWindowInterface* _winIntf)
	{
		RenderInterface::Create(_winIntf);

		mShaderCompiler.defines.emplace_back("SA_VULKAN_API=1");


		std::vector<const char*> vkExtensions;

		if(_winIntf)
			vkExtensions = _winIntf->QueryVkRequiredExtensions();

		mInstance.Create(vkExtensions);
	}
	
	void VkRenderInterface::Destroy()
	{
		RenderInterface::Destroy();

		mInstance.Destroy();
	}

//{ WindowSurface

	WindowSurface* VkRenderInterface::InstantiateWindowSurfaceClass() const
	{
		return new VkWindowSurface();
	}
	
//}


//{ Device

	Device* VkRenderInterface::InstantiateDeviceClass() const
	{
		return new VkDevice();
	}

	std::vector<std::shared_ptr<DeviceInfo>> VkRenderInterface::QueryDeviceInfos(const DeviceRequirements& _reqs) const
	{
		std::vector<VK::DeviceInfo> vkInfos = mInstance.QueryDeviceInfos(_reqs.API_Vulkan());

		std::vector<std::shared_ptr<DeviceInfo>> result;
		result.reserve(vkInfos.size());

		for(auto& vkInfo : vkInfos)
			result.emplace_back(new VkDeviceInfo(std::move(vkInfo)));

		return result;
	}

//}


//{ Swapchain

	Swapchain* VkRenderInterface::InstantiateSwapchainClass() const
	{
		return new VkSwapchain();
	}
	
//}


//{ ShaderCompiler

	ShaderCompileResult VkRenderInterface::CompileShader(const ShaderCompileInfo& _info)
	{
		return mShaderCompiler.CompileSPIRV(_info);
	}

//}


	const VK::Instance& VkRenderInterface::API_Vulkan() const
	{
		return mInstance;
	}
}
