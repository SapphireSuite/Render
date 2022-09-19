// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SA_RENDER_DX12_RENDER_INTERFACE_GUARD
#define SA_RENDER_DX12_RENDER_INTERFACE_GUARD

#include <SA/Render/Base/ARenderInterface.hpp>

namespace SA
{
	namespace DX12
	{
		class RenderInterface : public ARenderInterface
		{
		public:
			void Create() override final;
			void Destroy() override final;
		};
	}
}

#endif // SA_RENDER_DX12_RENDER_INTERFACE_GUARD
