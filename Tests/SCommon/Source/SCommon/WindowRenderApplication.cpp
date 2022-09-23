// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include "WindowRenderApplication.hpp"

namespace SA
{
	namespace SCommon
	{
		void WindowRenderApplication::Init()
		{
			WindowApplication::Init();
		}

		void WindowRenderApplication::UnInit()
		{
			WindowApplication::UnInit();
		}

		void WindowRenderApplication::Loop()
		{
			WindowApplication::Loop();
		}

		void WindowRenderApplication::Update()
		{
			WindowApplication::Update();
		}

		int WindowRenderApplication::Run(AWindowInterface* _win_intf, ARenderInterface* _render_intf)
		{
			mRenderIntf = _render_intf;

			return WindowApplication::Run(_win_intf);
		}
	}
}
