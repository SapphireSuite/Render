// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_DESCRIPTOR_SET_LAYOUT_GUARD
#define SAPPHIRE_RENDER_VK_DESCRIPTOR_SET_LAYOUT_GUARD

#include <SA/Render/LowLevel/Vulkan/VulkanAPI.hpp>

namespace SA::RND::VK
{
	class Device;

	class DescriptorSetLayout
	{
		VkDescriptorSetLayout mHandle = VK_NULL_HANDLE;

	public:
		void Create(const Device& _device, const std::vector<VkDescriptorSetLayoutBinding>& _bindings);
		void Destroy(const Device& _device);

		operator VkDescriptorSetLayout() const noexcept;
	};

	static_assert(sizeof(DescriptorSetLayout) == sizeof(VkDescriptorSetLayout),
		"DescriptorSetLayout size must match VkDescriptorSetLayout. See utilization in VK::DescriptorPool.");
}

#endif // SAPPHIRE_RENDER_VK_DESCRIPTOR_SET_LAYOUT_GUARD
