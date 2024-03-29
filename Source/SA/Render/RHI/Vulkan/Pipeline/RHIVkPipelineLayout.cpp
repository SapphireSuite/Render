// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pipeline/RHIVkPipelineLayout.hpp>

#include <Device/RHIVkDevice.hpp>

namespace SA::RND::RHI
{
	void VkPipelineLayout::Create(const Device* _device, const PipelineLayoutDescriptor& _desc)
	{
		// TODO: Implement.
		VkPipelineLayoutCreateInfo info
		{
			.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0u,
			.setLayoutCount = 0,
			.pSetLayouts = nullptr,
			.pushConstantRangeCount = 0,
			.pPushConstantRanges = nullptr,
		};

		mHandle.Create(_device->API_Vulkan(), info);
	}
	
	void VkPipelineLayout::Destroy(const Device* _device)
	{
		mHandle.Destroy(_device->API_Vulkan());
	}

	
	const VK::PipelineLayout& VkPipelineLayout::API_Vulkan() const
	{
		return mHandle;
	}
}
