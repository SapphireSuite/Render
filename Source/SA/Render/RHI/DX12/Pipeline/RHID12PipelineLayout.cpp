// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Pipeline/RHID12PipelineLayout.hpp>

#include <Device/RHID12Device.hpp>

namespace SA::RND::RHI
{
	void D12PipelineLayout::Create(const Device* _device, const PipelineLayoutDescriptor& _desc)
	{
		// TODO: Implement.
		D3D12_VERSIONED_ROOT_SIGNATURE_DESC desc
		{
			.Version = D3D_ROOT_SIGNATURE_VERSION_1_1,
			.Desc_1_1
			{
				.NumParameters = 0,
				.pParameters = nullptr,
				.NumStaticSamplers = 0,
				.pStaticSamplers = nullptr,
				.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT,
			}
		};

		mHandle.Create(_device->API_DirectX12(), desc);
	}
	
	void D12PipelineLayout::Destroy(const Device* _device)
	{
		(void)_device;

		mHandle.Destroy();
	}

	
	const DX12::RootSignature& D12PipelineLayout::API_DirectX12() const
	{
		return mHandle;
	}
}
