// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_SCOMMON_WINDOW_RENDER_APPLICATION_GUARD
#define SAPPHIRE_RENDER_SCOMMON_WINDOW_RENDER_APPLICATION_GUARD

// SA_Window SCommon.
#include <SCommon/WindowApplication.hpp>

#include "SelectedRenderInterface.hpp"

#include <SA/Render/Base/ARenderInterface.hpp>

namespace SA
{
	namespace SCommon
	{
		class WindowRenderApplication : protected WindowApplication
		{
			using WindowApplication::Run;

		protected:
			ARenderInterface* mRenderIntf = nullptr;

			void Init() override;
			void UnInit() override;

			void Loop() override;
			void Update() override;

		public:
			int Run(AWindowInterface* _win_intf, ARenderInterface* _render_intf);

			template <typename WindowInterfaceT = SelectedWindowInterface, typename RenderInterfaceT = SelectedRenderInterface>
			int CreateAndRun()
			{
				WindowInterfaceT win_intf;
				win_intf.Create();

				RenderInterfaceT render_intf;
				render_intf.Create(&win_intf);

				const int res = Run(&win_intf, &render_intf);

				render_intf.Destroy();

				win_intf.Destroy();

				return res;
			}
		};
	}
}

#endif // SAPPHIRE_RENDER_SCOMMON_WINDOW_RENDER_APPLICATION_GUARD
