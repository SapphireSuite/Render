// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Debug/Exception_Vulkan.hpp>

#include <VulkanAPI.hpp>

#include <SA/Logger/Misc/ToString.hpp>

namespace SA
{
	namespace VK
	{
		Exception_Vulkan::Exception_Vulkan(
			BaseInfos&& _infos,
			VkResult _vkRes,
			std::string&& _predStr,
			std::wstring&& _details
		) noexcept :
			Exception(std::move(_infos),
				_vkRes == VkResult::VK_SUCCESS,
				ToWString(std::move(_predStr)) + L" == VkResult::VK_SUCCESS",
				std::move(_details))
		{
		}
	}
}
