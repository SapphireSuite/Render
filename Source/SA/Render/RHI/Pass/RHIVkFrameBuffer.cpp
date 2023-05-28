// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pass/RHIVkFrameBuffer.hpp>

#include <Device/RHIDevice.hpp>

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

namespace SA::RND::RHI
{
	void VkFrameBuffer::Create(const Device* _device, const Pass* _pass)
	{
		// TODO: ADD Swapchain image handle.
		mHandle.Create(_device->API_Vulkan(), _pass->API_Vulkan(), _pass->GetInfo().API_Vulkan());
	}
	
	void VkFrameBuffer::Destroy(const Device* _device)
	{
		mHandle.Destroy(_device->API_Vulkan());
	}

	
	const const VK::FrameBuffer& VkFrameBuffer::API_Vulkan() const
	{
		return mHandle;
	}
}

#endif // SA_RENDER_LOWLEVEL_VULKAN_IMPL