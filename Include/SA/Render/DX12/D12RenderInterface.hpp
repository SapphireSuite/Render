// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SA_RENDER_DX12_RENDER_INTERFACE_GUARD
#define SA_RENDER_DX12_RENDER_INTERFACE_GUARD

#include <SA/Render/Base/ARenderInterface.hpp>

#include "D12Factory.hpp"

namespace SA
{
	namespace DX12
	{
		class RenderInterface : public ARenderInterface
		{
			Factory mFactory;
		
		public:
			void Create(AWindowInterface* _win_intf = nullptr) override final;
			void Destroy() override final;

			void Clear() override final;

#if SA_WINDOWING_IMPL

			AWindowSurface* CreateWindowSurface(AWindow* _win) override final;
			void DestroyWindowSurface(AWindowSurface* _winSurface) override final;

#endif
		};
	}
}

#endif // SA_RENDER_DX12_RENDER_INTERFACE_GUARD
