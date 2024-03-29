// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_COMMAND_POOL_GUARD
#define SAPPHIRE_RENDER_VK_COMMAND_POOL_GUARD

#include "VkCommandBuffer.hpp"

namespace SA::RND::VK
{
	class Device;

	class CommandPool
	{
		VkCommandPool mHandle = VK_NULL_HANDLE;

	public:
		void Create(const Device& _device, uint32_t _queueFamilyIndex);
		void Destroy(const Device& _device);

		void Reset(const Device& _device);

//{ Allocation

		CommandBuffer Allocate(const Device& _device, VkCommandBufferLevel _level = VK_COMMAND_BUFFER_LEVEL_PRIMARY);
		std::vector<CommandBuffer> AllocateMultiple(const Device& _device, uint32_t _num, VkCommandBufferLevel _level = VK_COMMAND_BUFFER_LEVEL_PRIMARY);

		void Free(const Device& _device, CommandBuffer& _buffer);
		void FreeMultiple(const Device& _device, std::vector<CommandBuffer>& _buffers);

//}

		operator VkCommandPool() const;
	};
}

#endif // SAPPHIRE_RENDER_VK_COMMAND_POOL_GUARD
