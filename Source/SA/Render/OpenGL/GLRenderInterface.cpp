// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include "GLRenderInterface.hpp"

#include <SA/Collections/Debug>

namespace SA
{
	namespace GL
	{
		void RenderInterface::Create()
		{
			ARenderInterface::Create();

			SA_LOG(L"Render Interface created.", Infos, SA/Render/OpenGL);
		}

		void RenderInterface::Destroy()
		{
			ARenderInterface::Destroy();

			SA_LOG(L"Render Interface destroyed.", Infos, SA/Render/OpenGL);
		}

		void RenderInterface::Clear()
		{
			ARenderInterface::Clear();

			SA_LOG(L"Render Interface cleared.", Infos, SA/Render/OpenGL);
		}
	}
}
