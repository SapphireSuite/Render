// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_DX12_VALIDATION_LAYERS_GUARD
#define SAPPHIRE_RENDER_DX12_VALIDATION_LAYERS_GUARD

namespace SA
{
	namespace DX12
	{
		class ValidationLayers
		{
		public:
			static void Initialize();
			static void Uninitialize();
		};
	}
}

#endif // SAPPHIRE_RENDER_DX12_VALIDATION_LAYERS_GUARD
