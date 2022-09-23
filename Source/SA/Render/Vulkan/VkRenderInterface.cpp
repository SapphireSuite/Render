// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include "VkRenderInterface.hpp"

#include "Debug/VkValidationLayers.hpp"

namespace SA
{
	namespace VK
	{
		void RenderInterface::Create()
		{
			ARenderInterface::Create();

#if SA_VK_VALIDATION_LAYERS

			SA_ASSERT(Default, SA/Render/Vulkan, ValidationLayers::CheckValidationSupport(), L"Validation Layers not supported!");

#endif

			mInstance.Create();

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
	}
}
