// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <OpenGL/GLRenderInterface.hpp>

#include <SA/Collections/Debug>

namespace SA
{
	namespace GL
	{
		void RenderInterface::Create()
		{
			SA_LOG(L"Render Interface created.", Infos, SA/Render/OpenGL);
		}

		void RenderInterface::Destroy()
		{
			SA_LOG(L"Render Interface destroyed.", Infos, SA/Render/OpenGL);
		}	
	}
}
