// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <VkInstance.hpp>

#include "Debug/VkValidationLayers.hpp"

namespace SA::VK
{
	void Instance::Create(std::vector<const char*> _extensions)
	{
		VkApplicationInfo appInfos{};
		appInfos.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfos.pNext = nullptr;
		appInfos.pApplicationName = "Main Application";
		appInfos.applicationVersion = VK_MAKE_VERSION(1, 0, 0); // TODO:
		appInfos.pEngineName = "Sapphire Engine";
		appInfos.engineVersion = VK_MAKE_VERSION(1, 0, 0); // TODO:
		appInfos.apiVersion = VK_API_VERSION_1_0;

	#if SA_VK_VALIDATION_LAYERS

		_extensions.push_back("VK_EXT_debug_utils");

	#endif

		VkInstanceCreateInfo instanceInfos{};
		instanceInfos.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		instanceInfos.pNext = nullptr;
		instanceInfos.flags = 0;
		instanceInfos.pApplicationInfo = &appInfos;

		instanceInfos.enabledLayerCount = 0;
		instanceInfos.ppEnabledLayerNames = nullptr;

		instanceInfos.enabledExtensionCount = static_cast<uint32_t>(_extensions.size());
		instanceInfos.ppEnabledExtensionNames = _extensions.data();

#if SA_VK_VALIDATION_LAYERS

		// Debug Messenger Info.
		const VkDebugUtilsMessengerCreateInfoEXT debugUtilscreateInfo = ValidationLayers::GetDebugUtilsMessengerCreateInfo();

		instanceInfos.pNext = &debugUtilscreateInfo;

		instanceInfos.enabledLayerCount = ValidationLayers::GetLayerNum();
		instanceInfos.ppEnabledLayerNames = ValidationLayers::GetLayerNames();

#endif

		SA_VK_ASSERT(vkCreateInstance(&instanceInfos, nullptr, &mHandle), L"Failed to create vulkan instance!");

#if SA_VK_VALIDATION_LAYERS

		auto createDebugFunc = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(mHandle, "vkCreateDebugUtilsMessengerEXT");
		SA_ASSERT(Nullptr, SA/Engine/Vulkan, createDebugFunc, L"Extension PFN_vkCreateDebugUtilsMessengerEXT missing!");

		SA_VK_ASSERT(createDebugFunc(mHandle, &debugUtilscreateInfo, nullptr, &mDebugMessenger), L"Failed to create vulkan debug messenger!");

#endif

		SA_LOG(L"Render Instance created.", Infos, SA/Render/Vulkan);
	}

	void Instance::Destroy()
	{
#if SA_VK_VALIDATION_LAYERS

		auto destroyDebugFunc = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(mHandle, "vkDestroyDebugUtilsMessengerEXT");
		SA_ASSERT(Nullptr, SA/Render/Vulkan, destroyDebugFunc, L"Extension PFN_vkDestroyDebugUtilsMessengerEXT missing!");

		destroyDebugFunc(mHandle, mDebugMessenger, nullptr);

#endif

		vkDestroyInstance(mHandle, nullptr);

		SA_LOG(L"Render Instance destroyed.", Infos, SA/Render/Vulkan);
	}


	Instance::operator VkInstance() const noexcept
	{
		return mHandle;
	}
}
