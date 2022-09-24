#pragma once

#ifndef SA_RENDER_VK_RENDER_INTERFACE_GUARD
#define SA_RENDER_VK_RENDER_INTERFACE_GUARD

#include <SA/Render/Base/ARenderInterface.hpp>

#include "VkInstance.hpp"

#if SA_WINDOWING_IMPL

#include "Surface/VkWindowSurface.hpp"

#endif

namespace SA
{
	namespace VK
	{
		class RenderInterface : public ARenderInterface
		{
			Instance mInstance;

#if SA_WINDOWING_IMPL

			HI::InterfaceList<WindowSurface> mWindowSurfaces;

#endif

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

#endif // SA_RENDER_VK_RENDER_INTERFACE_GUARD
