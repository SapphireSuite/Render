// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Vulkan/VkRenderInterface.hpp>

#include <SA/Collections/Debug>

#include <Vulkan/Debug/VkValidationLayers.hpp>

namespace SA
{
	namespace VK
	{
		void RenderInterface::Create()
		{
#if SA_VK_VALIDATION_LAYERS

			SA_ASSERT(Default, SA/Render/Vulkan, ValidationLayers::CheckValidationSupport(), L"Validation Layers not supported!");

#endif

			mInstance.Create();

			SA_LOG(L"Render Interface created.", Infos, SA/Render/Vulkan);
		}

		void RenderInterface::Destroy()
		{
			mInstance.Destroy();

			SA_LOG(L"Render Interface destroyed.", Infos, SA/Render/Vulkan);
		}
	}
}
