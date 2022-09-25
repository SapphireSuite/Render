// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_DX12_FACTORY_GUARD
#define SAPPHIRE_RENDER_DX12_FACTORY_GUARD

#include <d3d12.h>
#include <dxgi1_6.h>

namespace SA
{
	namespace DX12
	{
		class Factory
		{
			IDXGIFactory6* mHandle = nullptr;

		public:
			void Create();
			void Destroy();
		};
	}
}

#endif	// SAPPHIRE_RENDER_DX12_FACTORY_GUARD
