// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_RENDERER_SCENE_TEXTURES_GUARD
#define SAPPHIRE_RENDER_RENDERER_SCENE_TEXTURES_GUARD

#include <SA/Render/RHI/Common/Texture/RHITexture.hpp>

namespace SA::RND
{
	struct SceneTextures
	{
		struct DepthTextures
		{
			RHI::Texture* texture;
			RHI::Texture* resolved;
		} depth;

		struct ColorPresentTextures
		{
			RHI::Texture* texture;
			RHI::Texture* resolved;
		} colorPresent;
	};
}

#endif // SAPPHIRE_RENDER_RENDERER_SCENE_TEXTURES_GUARD
