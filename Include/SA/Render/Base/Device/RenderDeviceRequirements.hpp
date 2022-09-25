// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RENDER_DEVICE_REQUIREMENTS_GUARD
#define SAPPHIRE_RENDER_RENDER_DEVICE_REQUIREMENTS_GUARD

namespace SA
{
	struct RenderDeviceRequirements
	{
#if SA_RENDER_DX12_IMPL

		// Allow DX12 wrap GPU.
		bool bUseWrapAdapter = false;

#endif
	};
}

#endif // SAPPHIRE_RENDER_RENDER_DEVICE_REQUIREMENTS_GUARD
