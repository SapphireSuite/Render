// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_VK_WINDOW_SURFACE_GUARD
#define SAPPHIRE_RENDER_RHI_VK_WINDOW_SURFACE_GUARD

#include <SA/Render/RHI/Common/Surface/RHIWindowSurface.hpp>

#include <SA/Render/LowLevel/Vulkan/Surface/VkWindowSurface.hpp>

namespace SA::RND::RHI
{
	class VkWindowSurface : public WindowSurface
	{
		VK::WindowSurface mHandle;

	public:
		void Create(const RenderInterface* _renderIntf, const IRenderWindow* _window) override final;
		void Destroy(const RenderInterface* _renderIntf) override final;

		const VK::WindowSurface& API_Vulkan() const override final;
	};
}

#endif // SAPPHIRE_RENDER_RHI_VK_WINDOW_SURFACE_GUARD
