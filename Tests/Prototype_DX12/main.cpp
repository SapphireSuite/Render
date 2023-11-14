// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <SA/Collections/Debug>

#include <SA/Maths/Transform/Transform.hpp>

#include <SA/Render/LowLevel/Common/Camera/CameraUBO.hpp>
#include <SA/Render/LowLevel/Common/Mesh/RawStaticMesh.hpp>
#include <SA/Render/LowLevel/DX12/D12Factory.hpp>
#include <SA/Render/LowLevel/DX12/Device/D12Device.hpp>
#include <SA/Render/LowLevel/DX12/Surface/D12WindowSurface.hpp>
#include <SA/Render/LowLevel/DX12/Surface/D12Swapchain.hpp>
#include <SA/Render/LowLevel/DX12/Device/Command/D12CommandPool.hpp>
#include <SA/Render/LowLevel/DX12/Pass/D12RenderPass.hpp>
#include <SA/Render/LowLevel/DX12/Pass/D12FrameBuffer.hpp>
#include <SA/Render/LowLevel/DX12/Pipeline/D12RootSignature.hpp>
#include <SA/Render/LowLevel/DX12/Pipeline/D12GraphicsPipeline.hpp>
#include <SA/Render/LowLevel/DX12/Shader/D12Shader.hpp>
#include <SA/Render/LowLevel/DX12/Mesh/D12StaticMesh.hpp>
#include <SA/Render/LowLevel/DX12/D12ResourceInitializer.hpp>
#include <SA/Render/ShaderCompiler/ShaderCompiler.hpp>
using namespace SA::RND;

#include <GLFW/glfw3.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

GLFWwindow* window = nullptr;

DX12::Factory factory;
DX12::WindowSurface winSurface;
DX12::Device device;
DX12::Swapchain swapchain;
DX12::CommandPool cmdPool;
DX12::PassInfo passInfo;
DX12::RenderPass renderPass;
std::vector<DX12::FrameBuffer> frameBuffers;
std::vector<DX12::CommandBuffer> cmdBuffers;
DX12::Shader vertexShader;
DX12::Shader fragmentShader;
DX12::RootSignature rootSign;
DX12::GraphicsPipeline pipeline;
RawStaticMesh quadRaw;
DX12::StaticMesh quadMesh;
RHI::ShaderDescriptor vsDesc;
RHI::ShaderDescriptor fsDesc;
std::vector<DX12::Buffer> cameraBuffers;
SA::TransformPRSf cameraTr;
D3D12_VIEWPORT d12Viewport;
D3D12_RECT d12Scissor;
std::vector<SA::MComPtr<ID3D12DescriptorHeap>> cameraCBVHeaps;
//DX12::DescriptorPool cameraDescPool;
//DX12::DescriptorSetLayout cameraDescSetLayout;
//std::vector<VK::DescriptorSet> cameraSets;
DX12::Buffer objectBuffer;
//DX12::DescriptorPool objectDescPool;
//DX12::DescriptorSetLayout objectDescSetLayout;
//DX12::DescriptorSet objectSet;


void GLFWErrorCallback(int32_t error, const char* description)
{
	SA_LOG((L"GLFW Error [%1]: %2", error, description), Error, SA.Render.Proto.GLFW.API);
}

float RandFloat(float min, float max)
{
	return min + static_cast <float> (rand()) / static_cast <float> (RAND_MAX / (max - min));
}

SA::Vec3f RandVec3Position()
{
	return SA::Vec3f(RandFloat(-10, 10), RandFloat(-10, 10), RandFloat(-10, 10));
}

SA::Quatf RandQuat()
{
	return SA::Quatf::FromEuler({ RandFloat(0, 360), RandFloat(0, 360), RandFloat(0, 360) });
}

SA::Vec3f RandVec3Scale()
{
	return SA::Vec3f(RandFloat(0.5, 2.5), RandFloat(0.5, 2.5), RandFloat(0.5, 2.5));
}

void Init()
{
	SA::Debug::InitDefaultLogger();

	srand(time(nullptr));

	// GLFW
	{
		glfwSetErrorCallback(GLFWErrorCallback);
		glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		window = glfwCreateWindow(1200, 900, "Vulkan Prototype", nullptr, nullptr);
		SA_ASSERT((Nullptr, window), SA.Render.Proto.GLFW, L"GLFW create window failed!");

		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	// Render
	{
		factory.Create();

		DX12::DeviceRequirements deviceReqs;

		// WinSurface
		winSurface.Create(glfwGetWin32Window(window));

		// Device
		{
			std::vector<DX12::DeviceInfo> deviceInfos = factory.QueryDeviceInfos(deviceReqs);
			device.Create(deviceInfos[0]);
		}

		// Swapchain
		{
			swapchain.Create(factory, device, winSurface);
		}

		// Cmd Buffers
		{
			cmdPool.Create(device);

			cmdBuffers = cmdPool.AllocateMultiple(device, swapchain.GetImageNum());
		}

		// Render Pass
		{
			constexpr bool bDepth = true;
			constexpr bool bMSAA = true;

			// Forward
			if (true)
			{
				auto& mainSubpass = passInfo.AddSubpass("Main");

				if (bMSAA)
					mainSubpass.sampling = VK_SAMPLE_COUNT_8_BIT;

				// Color and present attachment.
				auto& colorRT = mainSubpass.AddAttachment("Color");
				colorRT.format = swapchain.GetFormat();
				colorRT.usage = AttachmentUsage::Present;

				if (bDepth)
				{
					auto& depthRT = mainSubpass.AddAttachment("Depth");
					depthRT.format = DXGI_FORMAT_D16_UNORM;
					depthRT.type = AttachmentType::Depth;
					depthRT.clearColor = SA::RND::Color::white;
				}

				mainSubpass.SetAllAttachmentExtents(swapchain.GetExtents());
			}

			renderPass.Create(passInfo);


			// FrameBuffers
			{
				uint32_t num = swapchain.GetImageNum();
				frameBuffers.resize(num);

				for (uint32_t i = 0; i < num; ++i)
					frameBuffers[i].Create(device, passInfo, swapchain.GetBackBufferHandle(i));
			}
		}

		DX12::ResourceInitializer init;
		init.Create(device);

		// Mesh
		{
			quadRaw.vertices.BuildVertexBuffer(
				VertexComponent<SA::Vec3f>{
				"POSITION",
				{
					{-0.5f, 0.5f, 0.0f},
					{0.5f, 0.5f, 0.0},
					{-0.5f, -0.5f, 0.0},
					{0.5f, -0.5f, 0.0}
				}
			},

				VertexComponent<Color>{
				"COLOR",
				{
					Color::red,
					Color::green,
					Color::blue,
					Color::white
				}
			}
			);

			quadRaw.indices.U16({ 0, 1, 2, 1, 3, 2 });

			quadMesh.Create(device, init, quadRaw);


			// Object
			{

				// Instanting
				std::vector<SA::Mat4f> objectsMats;
				objectsMats.resize(100);

				for (auto& mat : objectsMats)
					mat = SA::TransformPRSf(RandVec3Position(), RandQuat(), RandVec3Scale()).Matrix();

				objectBuffer.Create(device, sizeof(SA::Mat4f) * 100, D3D12_RESOURCE_STATE_COMMON,
					D3D12_HEAP_TYPE_UPLOAD, objectsMats.data());
			}
		}

		init.Submit();
		init.Destroy();

		// Shaders
		{
			ShaderCompiler compiler;

			compiler.Create();

			// Vertex
			{
				ShaderCompileInfo vsInfo
				{
					.path = L"Resources/Shaders/Passes/MainPass.hlsl",
					.entrypoint = "mainVS",
					.target = "vs_6_5",
				};

				vsInfo.defines.push_back("SA_CAMERA_BUFFER_ID=0");
				vsInfo.defines.push_back("SA_OBJECT_BUFFER_ID=0");

				quadRaw.vertices.AppendDefines(vsInfo.defines);

				ShaderCompileResult vsShaderRes = compiler.CompileDX(vsInfo);
				vsDesc = vsShaderRes.desc;

				vertexShader.Create(vsShaderRes.dxShader);
			}


			// Fragment
			{
				ShaderCompileInfo psInfo
				{
					.path = L"Resources/Shaders/Passes/MainPass.hlsl",
					.entrypoint = "mainPS",
					.target = "ps_6_5",
				};

				quadRaw.vertices.AppendDefines(psInfo.defines);

				ShaderCompileResult psShaderRes = compiler.CompileDX(psInfo);
				fsDesc = psShaderRes.desc;

				fragmentShader.Create(psShaderRes.dxShader);
			}


			compiler.Destroy();
		}

		// Camera
		{
			cameraBuffers.resize(swapchain.GetImageNum());
			cameraCBVHeaps.resize(swapchain.GetImageNum());

			for (uint32_t i = 0; i < swapchain.GetImageNum(); ++i)
			{
				uint32_t bufferSize = sizeof(CameraUBO) + 116; // padding for 256 bytes alignment

				auto& cameraBuffer = cameraBuffers[i];
				cameraBuffer.Create(device, bufferSize, D3D12_RESOURCE_STATE_COMMON, D3D12_HEAP_TYPE_UPLOAD);


				//auto& cameraCBVHeap = cameraCBVHeaps[i];
				//D3D12_DESCRIPTOR_HEAP_DESC cbvHeapDesc = {};
				//cbvHeapDesc.NumDescriptors = 1;
				//cbvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
				//cbvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
				//SA_DX12_API(device->CreateDescriptorHeap(&cbvHeapDesc, IID_PPV_ARGS(&cameraCBVHeap)));

				//D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
				//cbvDesc.BufferLocation = cameraBuffer->GetGPUVirtualAddress();
				//cbvDesc.SizeInBytes = bufferSize;
				//SA_DX12_API(device->CreateConstantBufferView(&cbvDesc, cameraCBVHeap->GetCPUDescriptorHandleForHeapStart()));
			}
		}

		// Root Signature
		{
			std::vector<D3D12_ROOT_PARAMETER1> params;

			params.push_back(D3D12_ROOT_PARAMETER1{
				.ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV,
				.Descriptor{
					.ShaderRegister = 0,
					.RegisterSpace = 0,
					.Flags = D3D12_ROOT_DESCRIPTOR_FLAG_DATA_STATIC_WHILE_SET_AT_EXECUTE,
				},
				.ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX,
			});

			params.push_back(D3D12_ROOT_PARAMETER1{
				.ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV,
				.Descriptor{
					.ShaderRegister = 0,
					.RegisterSpace = 1,
					.Flags = D3D12_ROOT_DESCRIPTOR_FLAG_DATA_STATIC,
				},
				.ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX,
			});

			D3D12_VERSIONED_ROOT_SIGNATURE_DESC info{
				.Version = D3D_ROOT_SIGNATURE_VERSION_1_1,
				.Desc_1_1
				{
					.NumParameters = (uint32_t)params.size(),
					.pParameters = params.data(),
					.NumStaticSamplers = 0u,
					.pStaticSamplers = nullptr,
					.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT,
				}
			};

			rootSign.Create(device, info);
		}

		// Pipeline
		{
			DX12::GraphicsPipelineInfo info
			{
				.rootSign = &rootSign,

				.shaderStages
				{
					.vs {.pShaderBytecode = vertexShader->GetBufferPointer(), .BytecodeLength = vertexShader->GetBufferSize()},
					.ps {.pShaderBytecode = fragmentShader->GetBufferPointer(), .BytecodeLength = fragmentShader->GetBufferSize()},
				},

				.raster
				{
					.FillMode = D3D12_FILL_MODE_SOLID,
					.CullMode = D3D12_CULL_MODE_NONE,
					.FrontCounterClockwise = FALSE,
					.DepthBias = D3D12_DEFAULT_DEPTH_BIAS,
					.DepthBiasClamp = D3D12_DEFAULT_DEPTH_BIAS_CLAMP,
					.SlopeScaledDepthBias = D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS,
					.DepthClipEnable = TRUE,
					.MultisampleEnable = passInfo.subpasses[0].sampling != 1,
					.AntialiasedLineEnable = FALSE,
					.ForcedSampleCount = 0,
					.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF,
				},

				.depthStencil
				{
					.DepthEnable = TRUE,
					.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL,
					.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL,
					.StencilEnable = FALSE,
					.StencilReadMask = D3D12_DEFAULT_STENCIL_READ_MASK,
					.StencilWriteMask = D3D12_DEFAULT_STENCIL_WRITE_MASK,
					.FrontFace
					{
						.StencilFailOp = D3D12_STENCIL_OP_KEEP,
						.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP,
						.StencilPassOp = D3D12_STENCIL_OP_KEEP,
						.StencilFunc = D3D12_COMPARISON_FUNC_ALWAYS,
					},
					.BackFace
					{
						.StencilFailOp = D3D12_STENCIL_OP_KEEP,
						.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP,
						.StencilPassOp = D3D12_STENCIL_OP_KEEP,
						.StencilFunc = D3D12_COMPARISON_FUNC_ALWAYS,
					}
				},

				.vertexInputElements = vsDesc.MakeDX12VertexInputElementDescsSingleVertexBuffer(),

				.rtvFormats = { swapchain.GetFormat() },
				.dsvFormat = DXGI_FORMAT_D16_UNORM,

				.sampling = passInfo.subpasses[0].sampling,
			};


			pipeline.Create(device, info);
		}

		// Viewport
		{
			d12Viewport = D3D12_VIEWPORT{
				.TopLeftX = 0,
				.TopLeftY = 0,
				.Width = float(swapchain.GetExtents().x),
				.Height = float(swapchain.GetExtents().y),
			};

			d12Scissor = D3D12_RECT{
				.left = 0,
				.top = 0,
				.right = static_cast<LONG>(swapchain.GetExtents().x),
				.bottom = static_cast<LONG>(swapchain.GetExtents().y),
			};
		}
	}
}

void Uninit()
{
	// Render
	{
		device.WaitIdle();

		pipeline.Destroy();
		rootSign.Destroy();

		fragmentShader.Destroy();
		vertexShader.Destroy();

		quadMesh.Destroy();

		for (auto& cameraBuffer : cameraBuffers)
			cameraBuffer.Destroy();

		//for (auto& cameraCBVHeap : cameraCBVHeaps)
		//	cameraCBVHeap.Reset();

		objectBuffer.Destroy();

		for (auto& frameBuffer : frameBuffers)
			frameBuffer.Destroy();

		renderPass.Destroy();

		cmdPool.FreeMultiple(cmdBuffers);
		cmdPool.Destroy();

		swapchain.Destroy();

		device.Destroy();

		winSurface.Destroy();

		factory.Destroy();
	}

	// GLFW
	{
		glfwTerminate();
	}
}

void Loop()
{
	const uint32_t frameIndex = swapchain.Begin();

	// Update camera.
	{
		CameraUBO cameraUBO;

		cameraUBO.position = cameraTr.position;
		cameraUBO.inverseView = cameraTr.Matrix().GetInversed();
		cameraUBO.projection = SA::Mat4f::MakePerspective(90, 1200.0f / 900.0f, 0.1f, 1000.0f);

		cameraBuffers[frameIndex].UploadData(&cameraUBO, sizeof(CameraUBO));
	}

	DX12::CommandBuffer& cmd = cmdBuffers[frameIndex];
	DX12::FrameBuffer& fbuff = frameBuffers[frameIndex];

	cmd.Begin();

	renderPass.Begin(cmd, fbuff);

	cmd->RSSetViewports(1, &d12Viewport);
	cmd->RSSetScissorRects(1, &d12Scissor);
	pipeline.Bind(cmd);

	//ID3D12DescriptorHeap* ppHeaps[] = { cameraCBVHeaps[frameIndex].Get() };
	//cmd->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);

	cmd->SetGraphicsRootConstantBufferView(0, cameraBuffers[frameIndex]->GetGPUVirtualAddress());
	cmd->SetGraphicsRootConstantBufferView(1, objectBuffer->GetGPUVirtualAddress());

	quadMesh.Draw(cmd, 100u);

	renderPass.End(cmd);

	cmd.End();

	swapchain.End(device, { cmd });
}

int main()
{
	Init();

	double oldMouseX = 0.0f;
	double oldMouseY = 0.0f;
	float dx = 0.0f;
	float dy = 0.0f;

	const float moveSpeed = 4.0f;
	const float rotSpeed = 16.0f;

	glfwGetCursorPos(window, &oldMouseX, &oldMouseY);

	const float fixedTime = 0.0025f;
	float accumulateTime = 0.0f;
	auto start = std::chrono::steady_clock::now();

	cameraTr.position.z = 1.0f;

	while (!glfwWindowShouldClose(window))
	{
		auto end = std::chrono::steady_clock::now();
		float deltaTime = std::chrono::duration_cast<std::chrono::duration<float, std::ratio<1, 1>>>(end - start).count();
		accumulateTime += deltaTime;
		start = end;

		// Fixed Update
		if (accumulateTime >= fixedTime)
		{
			accumulateTime -= fixedTime;

			glfwPollEvents();

			// Process input
			{
				if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
					glfwSetWindowShouldClose(window, true);
				if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
					cameraTr.position += fixedTime * moveSpeed * cameraTr.Right();
				if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
					cameraTr.position -= fixedTime * moveSpeed * cameraTr.Right();
				if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
					cameraTr.position -= fixedTime * moveSpeed * cameraTr.Up();
				if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
					cameraTr.position += fixedTime * moveSpeed * cameraTr.Up();
				if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
					cameraTr.position -= fixedTime * moveSpeed * cameraTr.Forward();
				if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
					cameraTr.position += fixedTime * moveSpeed * cameraTr.Forward();

				double mouseX = 0.0f;
				double mouseY = 0.0f;

				glfwGetCursorPos(window, &mouseX, &mouseY);

				if (mouseX != oldMouseX || mouseY != oldMouseY)
				{
					dx -= static_cast<float>(mouseX - oldMouseX) * fixedTime * rotSpeed * SA::Maths::DegToRad<float>;
					dy -= static_cast<float>(mouseY - oldMouseY) * fixedTime * rotSpeed * SA::Maths::DegToRad<float>;

					oldMouseX = mouseX;
					oldMouseY = mouseY;

					dx = dx > SA::Maths::Pi<float> ?
						dx - SA::Maths::Pi<float> :
						dx < -SA::Maths::Pi<float> ? dx + SA::Maths::Pi<float> : dx;
					dy = dy > SA::Maths::Pi<float> ?
						dy - SA::Maths::Pi<float> :
						dy < -SA::Maths::Pi<float> ? dy + SA::Maths::Pi<float> : dy;

					cameraTr.rotation = SA::Quatf(cos(dx), 0, sin(dx), 0) * SA::Quatf(cos(dy), sin(dy), 0, 0);
				}
			}
		}

		Loop();
	}

	Uninit();

	return 0;
}
