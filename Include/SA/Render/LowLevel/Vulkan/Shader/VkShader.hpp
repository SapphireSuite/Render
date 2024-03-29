// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_SHADER_GUARD
#define SAPPHIRE_RENDER_VK_SHADER_GUARD

#include <SA/Render/LowLevel/Vulkan/VulkanAPI.hpp>

#include <SA/Render/LowLevel/Common/Shader/RawShader.hpp>

namespace SA::RND::VK
{
	class Device;

	class Shader
	{
		VkShaderModule mHandle = VK_NULL_HANDLE;

	public:
		void Create(const Device& _device, const RawShader& _raw);
		void Destroy(const Device& _device);

		operator VkShaderModule() const noexcept;
	};
}

#endif // SAPPHIRE_RENDER_VK_SHADER_GUARD
