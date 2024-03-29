// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_DX12_COMMAND_LIST_GUARD
#define SAPPHIRE_RENDER_DX12_COMMAND_LIST_GUARD

#include <SA/Render/LowLevel/DX12/DX12API.hpp>

namespace SA::RND::DX12
{
	class CommandList
	{
		friend class CommandAllocator;

		MComPtr<ID3D12GraphicsCommandList> mHandle;
	
	public:
		ID3D12GraphicsCommandList* Get() const;
		ID3D12GraphicsCommandList* operator->() const;
	};
}

#endif // SAPPHIRE_RENDER_DX12_COMMAND_LIST_GUARD
