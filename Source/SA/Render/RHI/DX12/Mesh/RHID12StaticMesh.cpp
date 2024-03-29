// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Mesh/RHID12StaticMesh.hpp>

#include <Device/RHID12Device.hpp>
#include <RHID12ResourceInitializer.hpp>

namespace SA::RND::RHI
{
	void D12StaticMesh::Create(const Device* _device, ResourceInitializer* _init, const SA::RND::RawStaticMesh& _raw)
	{
		mHandle.Create(_device->API_DirectX12(), _init->API_DirectX12(), _raw);
	}
	
	void D12StaticMesh::Destroy(const Device* _device)
	{
		(void)_device;
		mHandle.Destroy();
	}

	void D12StaticMesh::Draw(const CommandBuffer* _cmd, uint32_t _instanceNum)
	{
		mHandle.Draw(_cmd->API_DirectX12(), _instanceNum);
	}

	const DX12::StaticMesh& D12StaticMesh::API_DirectX12() const
	{
		return mHandle;
	}
}
