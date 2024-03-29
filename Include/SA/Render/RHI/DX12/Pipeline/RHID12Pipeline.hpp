// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RHI_DX12_PIPELINE_GUARD
#define SAPPHIRE_RENDER_RHI_DX12_PIPELINE_GUARD

#include <SA/Render/RHI/Common/Pipeline/RHIPipeline.hpp>

#include <SA/Render/LowLevel/DX12/Pipeline/D12GraphicsPipeline.hpp>

namespace SA::RND::RHI
{
	class D12Pipeline : public Pipeline
	{
		DX12::Pipeline* mHandle = nullptr;

	public:
		void Create(const Device* _device, const GraphicsPipelineInfo& _info) override final;
		void Destroy(const Device* _device) override final;

		void Bind(const CommandBuffer* _cmd) override final;

		const DX12::Pipeline& API_DirectX12() const override final;
	};
}

#endif // SAPPHIRE_RENDER_RHI_DX12_PIPELINE_GUARD
