// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SA_RENDER_ARENDER_INTERFACE_GUARD
#define SA_RENDER_ARENDER_INTERFACE_GUARD

#include <SA/HI/Interface.hpp>
#include <SA/HI/InterfaceList.hpp>

#include "Surface/AWindowSurface.hpp"

namespace SA
{
	class AWindowInterface;

	class ARenderInterface : private HI::Interface
	{
		using HI::Interface::Create;

	protected:
		using HI::Interface::CheckCreated;

	public:
		virtual void Create(AWindowInterface* _win_intf = nullptr);
		void Destroy() override;

		void Clear() override;

#if SA_WINDOWING_IMPL

		virtual AWindowSurface* CreateWindowSurface(AWindow* _win) = 0;
		virtual void DestroyWindowSurface(AWindowSurface* _winSurface) = 0;

#endif
	};
}

#endif // SA_RENDER_ARENDER_INTERFACE_GUARD
