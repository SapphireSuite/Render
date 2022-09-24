// Copyright (c) 2022 Sapphire development team. All Rights Reserved.

#include <Surface/VkWindowSurface.hpp>

#if SA_WINDOWING_IMPL

#include <SA/Windowing/Base/AWindow.hpp>

#endif // SA_WINDOWING_IMPL

namespace SA
{
	namespace VK
	{
#if SA_WINDOWING_IMPL

		void WindowSurface::Create(AWindow* _win, const Instance& _inst)
		{
			AWindowSurface::Create();

			mWindow = _win;
			mHandle = _win->VkCreateWindowSurfaceHandle(_inst);

			SA_LOG(L"Window Surface [" << mHandle << L"] created.", Infos, SA/Render/Vulkan);
		}

		void WindowSurface::Destroy(const Instance& _inst)
		{
			AWindowSurface::Destroy();

			mWindow->VkDestroyWindowSurfaceHandle(_inst, mHandle);
			mWindow = nullptr;
		
			SA_LOG(L"Window Surface [" << mHandle << L"] destroyed.", Infos, SA/Render/Vulkan);

			mHandle = VK_NULL_HANDLE;
		}

#endif // SA_WINDOWING_IMPL
	}
}
