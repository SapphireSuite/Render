// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_RENDER_DEFERRED_RENDERER_GUARD
#define SAPPHIRE_RENDER_DEFERRED_RENDERER_GUARD

#include <SA/Render/Renderer/Base/Renderer.hpp>

#include "DeferredSceneTextures.hpp"

namespace SA::RND
{
	class DeferredRenderer : public Renderer
	{
	protected:
	//{ Scene Textures

		SceneTextures* InstantiateSceneTexturesClass() override final;
		void DeleteSceneTexturesClass(SceneTextures* _sceneTextures) override final;

		void CreateSceneTextureResources(const RendererSettings::RenderPassSettings& _settings, RHI::RenderPassInfo& _outPassInfo, SceneTextures* _sceneTextures, uint32_t _frameIndex) override final;
		void DestroySceneTextureResources(SceneTextures* _sceneTextures) override final;

	//}
	};
}

#endif // SAPPHIRE_RENDER_DEFERRED_RENDERER_GUARD
