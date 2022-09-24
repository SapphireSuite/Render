// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_AWINDOW_SURFACE_GUARD
#define SAPPHIRE_RENDER_AWINDOW_SURFACE_GUARD

#include <SA/HI/Object.hpp>

namespace SA
{
	class AWindow;

    class AWindowSurface : protected HI::Object
	{
	protected:
		AWindow* mWindow = nullptr;
	};
}

#endif // GUARD
