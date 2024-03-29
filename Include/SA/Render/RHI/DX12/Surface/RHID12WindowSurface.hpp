// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_DX12_WINDOW_SURFACE_GUARD
#define SAPPHIRE_RENDER_RHI_DX12_WINDOW_SURFACE_GUARD

#include <SA/Render/RHI/Common/Surface/RHIWindowSurface.hpp>

#include <SA/Render/LowLevel/DX12/Surface/D12WindowSurface.hpp>

namespace SA::RND::RHI
{
	class D12WindowSurface : public WindowSurface
	{
		DX12::WindowSurface mHandle;

	public:
		void Create(const RenderInterface* _renderIntf, const IRenderWindow* _window) override final;
		void Destroy(const RenderInterface* _renderIntf) override final;

		const DX12::WindowSurface& API_DirectX12() const override final;
	};
}

#endif // SAPPHIRE_RENDER_RHI_DX12_WINDOW_SURFACE_GUARD
