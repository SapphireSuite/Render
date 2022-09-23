// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_SCOMMON_SELECTED_RENDER_INTERFACE_GUARD
#define SAPPHIRE_RENDER_SCOMMON_SELECTED_RENDER_INTERFACE_GUARD

#if SA_RENDER_VULKAN_IMPL

	#include <SA/Render/Vulkan/VkRenderInterface.hpp>

#endif // SA_RENDER_VULKAN_IMPL

#if SA_RENDER_DX12_IMPL

	#include <SA/Render/DX12/D12RenderInterface.hpp>

#endif // SA_RENDER_DX12_IMPL

#if SA_RENDER_OPENGL_IMPL

	#include <SA/Render/OpenGL/GLRenderInterface.hpp>

#endif // SA_RENDER_OPENGL_IMPL

namespace SA
{
	namespace SCommon
	{
		using SelectedRenderInterface = SA_RENDER_SCOMMON_SELECTED_INTERFACE::RenderInterface;
	}
}

#endif // SAPPHIRE_RENDER_SCOMMON_SELECTED_RENDER_INTERFACE_GUARD
