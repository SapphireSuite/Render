# Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

cmake_minimum_required(VERSION 3.16)

# Sapphire Suite's CMake tools.
add_subdirectory(CMake)



# Project

project(SA_Render)
SA_ConfigureProject(SA_Render)



# Library

add_library(SA_Render STATIC)
SA_ConfigureTarget(TARGET SA_Render)
SA_TargetSources(TARGET SA_Render
	PUBLIC_FOLDER "Include/SA/Base"
	PRIVATE_FOLDER "Source/SA/Base"
	TOGGLE_INCLUDE_DIR OFF
)

## Manual include directory: custom target sources
target_include_directories(SA_Render PUBLIC Include)
target_include_directories(SA_Render PRIVATE Include/SA/Render)

### Link dependencies.
target_link_libraries(SA_Render PUBLIC SA_Logger)



# Options

## Add SA_Render's tests to build tree.
option(SA_RENDER_BUILD_TESTS_OPT "Should build SA_Render tests" OFF)


## Vulkan
option(SA_RENDER_VULKAN_OPT "Should compile Vulkan wrapper" ON)

if(SA_RENDER_VULKAN_OPT)

	find_package(Vulkan REQUIRED FATAL_ERROR)
	target_link_libraries(SA_Render PUBLIC Vulkan::Vulkan)

	target_compile_definitions(SA_Render PUBLIC SA_RENDER_VULKAN)
	SA_TargetSources(TARGET SA_Render
		PUBLIC_FOLDER "Include/SA/Render/Vulkan"
		PRIVATE_FOLDER "Source/SA/Render/Vulkan"
		TOGGLE_INCLUDE_DIR OFF
	)

endif()


## DX12
option(SA_RENDER_DX12_OPT "Should compile DirectX12 wrapper" OFF)

if(SA_RENDER_DX12_OPT)

	target_link_libraries(SA_Render PUBLIC d3d12.lib dxgi.lib)

	target_compile_definitions(SA_Render PUBLIC SA_RENDER_DX12)
	SA_TargetSources(TARGET SA_Render
		PUBLIC_FOLDER "Include/SA/Render/DX12"
		PRIVATE_FOLDER "Source/SA/Render/DX12"
		TOGGLE_INCLUDE_DIR OFF
	)

endif()


## OpenGL
option(SA_RENDER_OPENGL_OPT "Should compile OpenGL wrapper" OFF)

if(SA_RENDER_OPENGL_OPT)

	find_package(OpenGL REQUIRED)
	target_link_libraries(SA_Render PUBLIC OpenGL::GL)

	target_compile_definitions(SA_Render PUBLIC SA_RENDER_OPENGL)
	SA_TargetSources(TARGET SA_Render
		PUBLIC_FOLDER "Include/SA/Render/OpenGL"
		PRIVATE_FOLDER "Source/SA/Render/OpenGL"
		TOGGLE_INCLUDE_DIR OFF
	)

endif()



# Entrypoints

add_subdirectory(ThirdParty)

if(SA_RENDER_BUILD_TESTS_OPT)

	### Enable testing for this directory and below.
	enable_testing()

	add_subdirectory(Tests)

endif()
