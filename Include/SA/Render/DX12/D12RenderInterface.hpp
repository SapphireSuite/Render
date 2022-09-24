// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SA_RENDER_DX12_RENDER_INTERFACE_GUARD
#define SA_RENDER_DX12_RENDER_INTERFACE_GUARD

#include <SA/Render/Base/ARenderInterface.hpp>

struct IDXGIFactory4;

namespace SA
{
	namespace DX12
	{
		class RenderInterface : public ARenderInterface
		{
		//{ Factory

			IDXGIFactory4* mFactory = nullptr;

			void CreateFactory();
			void DestroyFactory();

		//}
		
		public:
			void Create(AWindowInterface* _win_intf = nullptr) override final;
			void Destroy() override final;

			void Clear() override final;
		};
	}
}

#endif // SA_RENDER_DX12_RENDER_INTERFACE_GUARD
