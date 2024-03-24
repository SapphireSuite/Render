// Copyright (c) 2024 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_VK_SAMPLED_TEXTURE_GUARD
#define SAPPHIRE_RENDER_RHI_VK_SAMPLED_TEXTURE_GUARD

#include <SA/Render/RHI/Common/Texture/RHISampledTexture.hpp>

#include <SA/Render/LowLevel/Vulkan/Texture/VkTexture.hpp>

namespace SA::RND::RHI
{
	class VkSampledTexture : public SampledTexture
	{
		VK::Texture mHandle;

	public:
		void Create(const Device* _device, ResourceInitializer* _init, const SA::RND::RawTexture& _raw) override final;
		void Destroy(const Device* _device) override final;
	};
}

#endif // SAPPHIRE_RENDER_RHI_VK_SAMPLED_TEXTURE_GUARD
