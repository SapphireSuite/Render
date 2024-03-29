// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_D12_SWAPCHAIN_GUARD
#define SAPPHIRE_RENDER_RHI_D12_SWAPCHAIN_GUARD

#include <SA/Render/RHI/Common/Surface/RHISwapchain.hpp>

#include <SA/Render/LowLevel/DX12/Surface/D12Swapchain.hpp>

namespace SA::RND::RHI
{
	class D12Swapchain : public Swapchain
	{
		DX12::Swapchain mHandle;

		const DX12::Device* mDevice = nullptr;

	public:
		void Create(const RenderInterface* _renderIntf,
			const Device* _device,
			const WindowSurface* _winSurface,
			const SwapchainSettings& _settings) override final;
		void Destroy(const RenderInterface* _renderIntf, const Device* _device) override final;
		
		Format GetFormat() const override final;
		uint32_t GetImageNum() const override final;
		const Vec2ui& GetExtents() const override final;

		uint32_t Begin() override final;
		void End(std::vector<CommandBuffer*> _cmds) override final;

		const DX12::Swapchain& API_DirectX12() const override final;
	};
}

#endif // SAPPHIRE_RENDER_RHI_D12_SWAPCHAIN_GUARD
