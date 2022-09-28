// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_DX12_VALIDATION_LAYERS_GUARD
#define SAPPHIRE_RENDER_DX12_VALIDATION_LAYERS_GUARD

#include <d3d12.h>

#include "Debug/Debug.hpp"

#if SA_DX12_VALIDATION_LAYERS

namespace SA
{
	namespace DX12
	{
		class ValidationLayers
		{
			ID3D12Debug1* mDebugController = nullptr;

		public:
			void Create();
			void Destroy();
		};
	}
}

#endif // SA_DX12_VALIDATION_LAYERS

#endif // SAPPHIRE_RENDER_DX12_VALIDATION_LAYERS_GUARD
