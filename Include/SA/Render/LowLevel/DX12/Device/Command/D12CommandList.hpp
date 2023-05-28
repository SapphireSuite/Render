// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_DX12_COMMAND_LIST_GUARD
#define SAPPHIRE_RENDER_DX12_COMMAND_LIST_GUARD

#include <SA/Render/LowLevel/DX12/DX12API.hpp>

namespace SA::RND::DX12
{
	class CommandList
	{
		friend class CommandPool;

		MComPtr<ID3D12CommandList> mHande;
	public:
	};
}

#endif // SAPPHIRE_RENDER_DX12_COMMAND_LIST_GUARD