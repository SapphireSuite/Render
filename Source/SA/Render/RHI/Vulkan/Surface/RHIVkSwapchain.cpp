// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Surface/RHIVkSwapchain.hpp>

#include <Device/RHIVkDevice.hpp>
#include <Surface/RHIVkWindowSurface.hpp>

#include <SA/Render/LowLevel/Vulkan/Device/Command/VkCommandBuffer.hpp>

namespace SA::RND::RHI
{
	void VkSwapchain::Create(const RenderInterface* _renderIntf,
		const Device* _device,
		const WindowSurface* _winSurface,
		const SwapchainSettings& _settings)
	{
		(void)_renderIntf;

		mDevice = &_device->API_Vulkan();
		
		mHandle.Create(*mDevice, _winSurface->API_Vulkan(), _settings.API_Vulkan());
	}

	void VkSwapchain::Destroy(const RenderInterface* _renderIntf, const Device* _device)
	{
		(void)_renderIntf;

		SA_ASSERT((Equals, mDevice, &_device->API_Vulkan()), SA.Render.RHI, L"Device ptr should match to ensure correct destroy.");

		mHandle.Destroy(*mDevice);
		mDevice = nullptr;
	}

	Format VkSwapchain::GetFormat() const
	{
		return VK::API_GetFormat(mHandle.GetFormat());
	}

	uint32_t VkSwapchain::GetImageNum() const
	{
		return mHandle.GetImageNum();
	}

	const Vec2ui& VkSwapchain::GetExtents() const
	{
		return mHandle.GetExtents();
	}


	uint32_t VkSwapchain::Begin()
	{
		SA_ASSERT((Nullptr, mDevice), SA.Render.RHI);

		return mHandle.Begin(*mDevice);
	}
	
	void VkSwapchain::End(std::vector<CommandBuffer*> _cmds)
	{
		SA_ASSERT((Nullptr, mDevice), SA.Render.RHI);

		std::vector<VK::CommandBuffer> vkCmds;
		vkCmds.reserve(_cmds.size());

		for (auto cmd : _cmds)
			vkCmds.emplace_back(cmd->API_Vulkan());

		mHandle.End(*mDevice, vkCmds);
	}


	const VK::Swapchain& VkSwapchain::API_Vulkan() const
	{
		return mHandle;
	}
}
