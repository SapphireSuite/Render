// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <main_common.hpp>

#include <SA/Collections/Debug>
using namespace SA;

#if SA_RENDER_VULKAN

	#include <SA/Render/Vulkan/VkRenderInterface.hpp>

#endif // SA_RENDER_VULKAN

#if SA_RENDER_OPENGL

	#include <SA/Render/OpenGL/GLRenderInterface.hpp>

#endif // SA_RENDER_OPENGL

#if SA_RENDER_DX12

	#include <SA/Render/DX12/D12RenderInterface.hpp>

#endif // SA_RENDER_DX12

#define MULTITHREAD_OPT 1

#if MULTITHREAD_OPT

#include <list>
#include <thread>

std::list<std::thread> threads;
LoggerThread logger;

#define SA_RENDER_THREAD_BEGIN(_renderInterfaceT) threads.emplace_back(std::thread([](){
#define SA_RENDER_THREAD_END() }));

#else

#define SA_RENDER_THREAD_BEGIN(_renderInterfaceT) SA_LOG()
#define SA_RENDER_THREAD_END()

#endif

template <typename RenderInterfaceT>
void main_render()
{
	SA_RENDER_THREAD_BEGIN(RenderInterfaceT)

	RenderInterfaceT interface;
	main_common(&interface, !MULTITHREAD_OPT);

	SA_RENDER_THREAD_END()
}

int main()
{
#if MULTITHREAD_OPT

	SA::Debug::logger = &logger;

	ConsoleLogStream cslStream;
	logger.Register(cslStream);

	FileLogStream fileStream;
	logger.Register(fileStream);

#endif // MULTITHREAD_OPT


#if SA_RENDER_VULKAN

	main_render<VK::RenderInterface>();

#endif // SA_RENDER_VULKAN


#if SA_RENDER_OPENGL

	main_render<GL::RenderInterface>();

#endif // SA_RENDER_OPENGL


#if SA_RENDER_DX12

	main_render<DX12::RenderInterface>();

#endif // SA_RENDER_DX12


#if MULTITHREAD_OPT

	// Join all.

	for(auto& _thread : threads)
	{
		if(_thread.joinable())
			_thread.join();
	}

	logger.Flush();

#endif // MULTITHREAD_OPT

	return 0;
}
