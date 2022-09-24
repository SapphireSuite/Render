// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include "VkRenderInterface.hpp"

#include "Debug/VkValidationLayers.hpp"

#if SA_WINDOWING_IMPL

#include <SA/Windowing/Base/AWindowInterface.hpp>

#endif // SA_WINDOWING_IMPL

namespace SA
{
	namespace VK
	{
		void RenderInterface::Create(AWindowInterface* _win_intf)
		{
			ARenderInterface::Create(_win_intf);

#if SA_VK_VALIDATION_LAYERS

			SA_ASSERT(Default, SA/Render/Vulkan, ValidationLayers::CheckValidationSupport(), L"Validation Layers not supported!");

#endif

			std::vector<const char*> extensions;

		#if SA_WINDOWING_IMPL

			if (_win_intf)
				_win_intf->VkQueryRequiredExtensions(extensions);
		#else

			(void)_win_intf;

		#endif // SA_WINDOWING_IMPL

			mInstance.Create(std::move(extensions));

			SA_LOG(L"Render Interface created.", Infos, SA/Render/Vulkan);
		}

		void RenderInterface::Destroy()
		{
			ARenderInterface::Destroy();

			mInstance.Destroy();

			SA_LOG(L"Render Interface destroyed.", Infos, SA/Render/Vulkan);
		}

		void RenderInterface::Clear()
		{
			ARenderInterface::Clear();

			SA_LOG(L"Render Interface cleared.", Infos, SA/Render/Vulkan);
		}


#if SA_WINDOWING_IMPL

		AWindowSurface* RenderInterface::CreateWindowSurface(AWindow* _win)
		{
			CheckCreated();

			WindowSurface* winSurface = mWindowSurfaces.Emplace();

			winSurface->Create(_win, mInstance);

			return winSurface;
		}

		void RenderInterface::DestroyWindowSurface(AWindowSurface* _winSurface)
		{
			CheckCreated();

			mWindowSurfaces.Erase(_winSurface, WindowSurfaceDestroyer{ mInstance });
		}

#endif
	}
}
