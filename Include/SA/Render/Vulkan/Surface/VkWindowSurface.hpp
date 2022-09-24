// Copyright (c) 2022 Sapphire development team. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_VK_WINDOW_SURFACE_GUARD
#define SAPPHIRE_RENDER_VK_WINDOW_SURFACE_GUARD

#include <SA/Render/Base/Surface/AWindowSurface.hpp>

#include "VkWindowSurfaceHandle.hpp"

namespace SA
{
	namespace VK
	{
		class Instance;

		class WindowSurface : public AWindowSurface
		{
			WindowSurfaceHandle mHandle = VK_NULL_HANDLE;

			using AWindowSurface::Create;
			using AWindowSurface::Destroy;

		public:
#if SA_WINDOWING_IMPL

			void Create(AWindow* _win, const Instance& _inst);
			void Destroy(const Instance& _inst);

#endif // SA_WINDOWING_IMPL
		};

#if SA_WINDOWING_IMPL

		struct WindowSurfaceDestroyer
		{
			Instance& intf;

			void operator()(WindowSurface& _in)
			{
				_in.Destroy(intf);
			}
		};

#endif // SA_WINDOWING_IMPL
	}
}

#endif // SAPPHIRE_RENDER_VK_WINDOW_SURFACE_GUARD
