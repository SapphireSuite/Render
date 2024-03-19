// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_TEXTURE_GUARD
#define SAPPHIRE_RENDER_VK_TEXTURE_GUARD

#include <SA/Render/LowLevel/Vulkan/VulkanAPI.hpp>

#include <SA/Render/LowLevel/Common/Texture/RawTexture.hpp>
#include <SA/Render/LowLevel/Common/Texture/TextureDescriptor.hpp>

namespace SA::RND::VK
{
	class Device;
	class ResourceInitializer;
	class Swapchain;

	class Texture
	{
		VkImage mImage = VK_NULL_HANDLE;
		VkDeviceMemory mMemory = VK_NULL_HANDLE;

		TextureDescriptor mDescriptor;

	public:
		const TextureDescriptor& GetDescriptor() const noexcept;

		/**
		* Create Texture from descriptor
		* Used as framebuffer attachment.
		*/
		void Create(const Device& _device, const TextureDescriptor& _desc);
		
		/**
		* Create Texture from raw texture input.
		* Used as input texture for sampling.
		*/
		void Create(const Device& _device, ResourceInitializer& _init, const RawTexture& _raw);
		
		/**
		* Create texture from swapchain backbuffer image handle.
		* Used as frambuffer present attachment.
		*/
		void CreateFromImage(const Device& _device, const Swapchain& _swapchain, uint32_t _imageIndex);
		
		void Destroy(const Device& _device);
	};
}

#endif // SAPPHIRE_RENDER_VK_TEXTURE_GUARD
