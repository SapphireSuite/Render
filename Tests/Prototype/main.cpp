// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <list>
#include <thread>

#include <SA/Collections/Debug>

#include <SA/Render/RHI/RHIVkRenderInterface.hpp>
#include <SA/Render/RHI/RHID12RenderInterface.hpp>
#include <SA/Render/RHI/Compatibility/IRenderWindow.hpp>
#include <SA/Render/RHI/Compatibility/IWindowInterface.hpp>
using namespace SA::RND;

// Must be included after vulkan.
#include <GLFW/glfw3.h>

#if SA_RENDER_LOWLEVEL_DX12_IMPL

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#endif

void GLFWErrorCallback(int32_t error, const char* description)
{
	SA_LOG((L"GLFW Error [%1]: %2", error, description), Error, SA.Render.Proto.GLFW.API);
}

class WindowInterface : public RHI::IWindowInterface
{
public:
#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	std::vector<const char*> QueryVkRequiredExtensions() const override final
	{
		std::vector<const char*> vkExts;

		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions = nullptr;

		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		vkExts.reserve(glfwExtensionCount);
		vkExts.insert(vkExts.end(), glfwExtensions, glfwExtensions + glfwExtensionCount);

		return vkExts;
	}

#endif
};

class WindowHandle : public RHI::IRenderWindow
{
	GLFWwindow* mHandle = nullptr;

public:
	WindowHandle(GLFWwindow* _handle) noexcept :
		mHandle{ _handle }
	{
	}

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL

	VkSurfaceKHR CreateVkSurfaceKHR(const SA::RND::VK::Instance& _instance) const override final
	{
		VkSurfaceKHR glfwsurface;
		glfwCreateWindowSurface(_instance, mHandle, nullptr, &glfwsurface);

		return glfwsurface;
	}

#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL

	HWND GetHWNDHandle() const override final
	{
		return glfwGetWin32Window(mHandle);
	}

#endif
};

class Renderer
{
public:
	GLFWwindow* window = nullptr;

	RHI::RenderInterface* intf = nullptr;
	RHI::Device* device = nullptr;
	RHI::WindowSurface* winSurface = nullptr;
	RHI::Swapchain* swapchain = nullptr;
	RHI::Context* context = nullptr;
	RHI::Pass* pass = nullptr;

	struct CreateInfo
	{
		RHI::RenderInterface* intf = nullptr; 
		std::string winName;
		int winPosX = 0;
		int winPosY = 0;
	};

	void Create(const CreateInfo& _info)
	{
		WindowInterface winIntf;

		intf = _info.intf;
		intf->Create(&winIntf);

		// GLFW
		{
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
			window = glfwCreateWindow(960, 540, _info.winName.c_str(), nullptr, nullptr);
			glfwSetWindowPos(window, _info.winPosX, _info.winPosY + 30);
			SA_ASSERT((Nullptr, window), SA.Render.Proto.GLFW, L"GLFW create window failed!");
		}

		// Win Surface
		{
			WindowHandle winHandle(window);

			winSurface = intf->CreateWindowSurface(&winHandle);
		}

		// Device
		{
			RHI::DeviceRequirements reqs;
			reqs.SetWindowSurface(winSurface);

			auto infos = intf->QueryDeviceInfos(reqs);

			for (auto& info : infos)
				SA_LOG((L"Device found: Name: [%1], ID: [%2], Vendor [%3], Score [%4]", info->GetName(), info->GetID(), info->GetVendorID(), info->GetScore()));

			device = intf->CreateDevice(infos[0].get());
		
		}
		
		// Swapchain
		{
			swapchain = intf->CreateSwapchain(device, winSurface);
		}

		// Context
		{
			context = device->CreateContext();
		}

		// RenderPass
		{
			// Info
			RHI::PassInfo passInfo;
			{
				constexpr bool bDepth = true;
				constexpr bool bMSAA = true;

				// Forward
				if (false)
				{
					auto& mainSubpass = passInfo.AddSubpass("Main");

					if(bMSAA)
						mainSubpass.sampling = RHI::Sampling::Sample8Bits;

					// Color and present attachment.
					auto& colorRT = mainSubpass.AddAttachment("Color");
					colorRT.format = swapchain->GetFormat();
					colorRT.usage = AttachmentUsage::Present;

					if(bDepth)
					{
						auto& depthRT = mainSubpass.AddAttachment("Depth");
						depthRT.format = RHI::Format::D16_UNORM;
						depthRT.type = AttachmentType::Depth;
					}
				}
				else if(true) // Deferred
				{
					passInfo.subpasses.reserve(2u);

					// GBuffer
					{
						auto& pbrSubpass = passInfo.AddSubpass("GBuffer Pass");

						if(bMSAA)
							pbrSubpass.sampling = RHI::Sampling::Sample8Bits;

						// Render Targets
						{
							// Deferred position attachment.
							auto& posRT = pbrSubpass.AddAttachment("GBuffer_Position");

							// Deferred normal attachment.
							auto& normRT = pbrSubpass.AddAttachment("GBuffer_Normal");

							// Deferred albedo attachment.
							auto& albedoRT = pbrSubpass.AddAttachment("GBuffer_Color");

							// Deferred PBR (Metallic, Roughness, Ambiant occlusion) attachment.
							auto& pbrRT = pbrSubpass.AddAttachment("GBuffer_PBR");

							if(bDepth)
							{
								auto& pbrDepthRT = pbrSubpass.AddAttachment("Depth");
								pbrDepthRT.format = RHI::Format::D16_UNORM;
								pbrDepthRT.type = AttachmentType::Depth;
							}
						}
					}

					// Present Subpass
					{
						auto& presentSubpass = passInfo.AddSubpass("Present Pass");

						if(bMSAA)
							presentSubpass.sampling = RHI::Sampling::Sample8Bits;

						auto& presentRT = presentSubpass.AddAttachment("Color");
						presentRT.format = swapchain->GetFormat();
						presentRT.usage = AttachmentUsage::Present;
					}
				}
			}

			pass = context->CreatePass(std::move(passInfo));
		}
	}

	void Destroy()
	{
		// Render
		{
			context->DestroyPass(pass);

			device->DestroyContext(context);

			intf->DestroySwapchain(device, swapchain);

			intf->DestroyWindowSurface(winSurface);
			intf->DestroyDevice(device);

			intf->Destroy();
			delete intf;
		}

		// GLFW
		{
			glfwDestroyWindow(window);
		}
	}

	void Loop()
	{
		while (!glfwWindowShouldClose(window))
		{
			glfwPollEvents();
		}
	}

	static void RenderThread(const CreateInfo& _info)
	{
		Renderer renderer;

		renderer.Create(_info);

		renderer.Loop();

		renderer.Destroy();
	}
};

int main()
{
	SA::Debug::InitDefaultLoggerThread();

	// GLFW
	{
		glfwSetErrorCallback(GLFWErrorCallback);
		glfwInit();
	}


	// Render
	{

		std::list<std::thread> renderThreads;

#if SA_RENDER_LOWLEVEL_VULKAN_IMPL
		renderThreads.emplace_back(std::thread(Renderer::RenderThread, Renderer::CreateInfo{ new RHI::VkRenderInterface, "Vulkan" }));
#endif

#if SA_RENDER_LOWLEVEL_DX12_IMPL
		renderThreads.emplace_back(std::thread(Renderer::RenderThread, Renderer::CreateInfo{ new RHI::D12RenderInterface, "DirectX12", 960, 0 }));
#endif

		for (auto& renderThread : renderThreads)
		{
			if (renderThread.joinable())
				renderThread.join();
		}
	}


	// GLFW
	{
		glfwTerminate();
	}

	return 0;
}
