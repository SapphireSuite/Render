// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Device/RHID12DeviceInfo.hpp>

namespace SA::RND::RHI
{
	D12DeviceInfo::D12DeviceInfo(DX12::DeviceInfo&& _handle) :
		mHandle{ std::move(_handle) }
	{
	}


	uint32_t D12DeviceInfo::GetScore() const
	{
		return mHandle.score;
	}


	std::wstring D12DeviceInfo::GetName() const
	{
		return mHandle.desc.Description;
	}


	uint32_t D12DeviceInfo::GetID() const
	{
		return mHandle.desc.DeviceId;
	}
	
	uint32_t D12DeviceInfo::GetVendorID() const
	{
		return mHandle.desc.VendorId;
	}


	const DX12::DeviceInfo& D12DeviceInfo::API_DirectX12() const
	{
		return mHandle;
	}
}
