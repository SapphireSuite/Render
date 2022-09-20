// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <SA/Collections/Debug>
using namespace SA;

#include <main_common.hpp>
#include <SA/Render/OpenGL/GLRenderInterface.hpp>

int main()
{
	GL::RenderInterface interface;

	return main_common(&interface);
}
