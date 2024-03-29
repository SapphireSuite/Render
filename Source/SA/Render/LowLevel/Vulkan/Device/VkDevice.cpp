// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <Device/VkDevice.hpp>

#include <VkInstance.hpp>

#include "../Debug/VkValidationLayers.hpp"

namespace SA::RND::VK
{
	const VkPhysicalDeviceMemoryProperties& Device::GetMemoryProperties() const noexcept
	{
		return mMemProperties;
	}


	void Device::Create(const DeviceInfo& _info)
	{
		mPhysical = _info.physicalDevice;
		mFeatures = _info.physicalFeatures;

		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos = _info.queueMgrIndex.GetQueueCreateInfos();

		VkDeviceCreateInfo deviceCreateInfo{};
		deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		deviceCreateInfo.pNext = nullptr;
		deviceCreateInfo.flags = 0u;
		deviceCreateInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
		deviceCreateInfo.pQueueCreateInfos = queueCreateInfos.data();

#if SA_VK_VALIDATION_LAYERS

		deviceCreateInfo.enabledLayerCount = ValidationLayers::GetLayerNum();
		deviceCreateInfo.ppEnabledLayerNames = ValidationLayers::GetLayerNames();

#else

		deviceCreateInfo.enabledLayerCount = 0u;
		deviceCreateInfo.ppEnabledLayerNames = nullptr;

#endif

		deviceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(_info.vkRequiredExtensions.size());
		deviceCreateInfo.ppEnabledExtensionNames = _info.vkRequiredExtensions.data();
		deviceCreateInfo.pEnabledFeatures = &mFeatures;

		SA_VK_API(vkCreateDevice(mPhysical, &deviceCreateInfo, nullptr, &mLogical),
			L"Failed to create logical device!");

		SA_VK_API(vkGetPhysicalDeviceMemoryProperties(mPhysical, &mMemProperties));

		queueMgr.Create(*this, _info.queueMgr);

		SA_LOG(L"Device created.", Info, SA.Render.Vulkan,
			(L"Physical {Name: %1, ID: %2, Handle: %3}, Logical [%4]",
			_info.physicalProperties.deviceName, _info.physicalProperties.deviceID, mPhysical, mLogical));
	}

	void Device::Destroy()
	{
		WaitIdle();

		queueMgr.Destroy();

		SA_VK_API(vkDestroyDevice(mLogical, nullptr));

		SA_LOG(L"Device destroyed.", Info, SA.Render.Vulkan, (L"Physical [%1], Logical [%2]", mPhysical, mLogical));

		mLogical = VK_NULL_HANDLE;
		mPhysical = VK_NULL_HANDLE;
	}


	void Device::WaitIdle() const
	{
		SA_VK_API(vkDeviceWaitIdle(mLogical));
	}


//{ Query Devices

	std::vector<DeviceInfo> Device::QueryDeviceInfos(const Instance& _inst, const DeviceRequirements& _reqs)
	{
		std::vector<DeviceInfo> deviceInfos;

	//{ Query Physical devices.
		uint32_t deviceCount = 0;
		SA_VK_API(vkEnumeratePhysicalDevices(_inst, &deviceCount, nullptr), L"Failed to query physical graphic device count.");

		SA_ASSERT((NotEquals0, deviceCount), SA.Render.Vulkan, L"No GPU with Vulkan support found!");

		std::vector<VkPhysicalDevice> physicalDevices(deviceCount);
		SA_VK_API(vkEnumeratePhysicalDevices(_inst, &deviceCount, physicalDevices.data()), L"Failed to enumerate physical graphic devices.");
	//}

		deviceInfos.reserve(deviceCount);

		for(auto& phDevice : physicalDevices)
		{
			DeviceInfo info;

			info.physicalDevice = phDevice;
			SA_VK_API(vkGetPhysicalDeviceFeatures(info.physicalDevice, &info.physicalFeatures));
			SA_VK_API(vkGetPhysicalDeviceProperties(info.physicalDevice, &info.physicalProperties));

			info.vkRequiredExtensions = _reqs.vkRequiredExtensions;

			// Is physical device suitable?
			if(info.CheckExtensionSupport() &&
				info.CheckFeatureSupport(_reqs.features) &&
				info.QueryQueueFamilies(_reqs.GetWindowSurface(), _reqs.queue) >= 0)
			{
				if(_reqs.bEnableRequiredFeaturesOnly)
					info.physicalFeatures = _reqs.features;

				info.Evaluate();
				deviceInfos.emplace_back(info);
			}
		}

		std::sort(deviceInfos.begin(), deviceInfos.end(), DeviceInfo::SortByScore);

		SA_WARN(!deviceInfos.empty(), SA.Render.Vulkan, L"No suitable graphic device found!");

		return deviceInfos;
	}

//}


	Device::operator VkDevice() const noexcept
	{
		return mLogical;
	}
	
	Device::operator VkPhysicalDevice() const noexcept
	{
		return mPhysical;
	}
}
