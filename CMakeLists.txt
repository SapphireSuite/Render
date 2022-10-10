# Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

cmake_minimum_required(VERSION 3.16)

# Sapphire Suite's CMake tools.
add_subdirectory(CMake)



# Project

project(SA_Render)
SA_ConfigureProject(SA_Render)



# Library

## Main
add_library(SA_Render INTERFACE)
SA_ConfigureTarget(SA_Render LINK INTERFACE)


## Base
add_library(SA_Render_Base STATIC)
SA_ConfigureTarget(SA_Render_Base)
SA_TargetSources(SA_Render_Base
	PUBLIC_SRC_DIR "Include/SA/Render/Base"
	PRIVATE_SRC_DIR "Source/SA/Render/Base"
)

### Link dependencies.
target_link_libraries(SA_Render_Base PUBLIC SA_Logger SA_HI)

### Link to main lib.
target_link_libraries(SA_Render INTERFACE SA_Render_Base)



# Options

## Validation layers
option(SA_RENDER_VALIDATION_LAYER_RELEASE_OPT "Enable render validation layers in release" OFF)

if(SA_RENDER_VALIDATION_LAYER_RELEASE_OPT)

	target_compile_definitions(SA_Render_Base PUBLIC SA_RENDER_VALIDATION_LAYER_RELEASE=1)

endif()


## Add SA_Render's tests to build tree.
option(SA_RENDER_BUILD_TESTS_OPT "Should build SA_Render tests" OFF)

## Add SA_Render's sample common to build tree.
option(SA_RENDER_SCOMMON_OPT "Should build SA_Render sample common" OFF)


## Vulkan
option(SA_RENDER_VULKAN_OPT "Should compile Vulkan wrapper" ON)

if(SA_RENDER_VULKAN_OPT)

	find_package(Vulkan REQUIRED FATAL_ERROR)

	add_library(SA_Render_Vulkan STATIC)
	SA_ConfigureTarget(SA_Render_Vulkan)
	SA_TargetSources(SA_Render_Vulkan
		PUBLIC_SRC_DIR "Include/SA/Render/Vulkan"
		PUBLIC_INCL_DIR "OFF"
		PRIVATE_SRC_DIR "Source/SA/Render/Vulkan"
	)

	target_link_libraries(SA_Render_Vulkan
		PUBLIC SA_Render_Base
		PUBLIC Vulkan::Vulkan # Set to public for easier wrapping.
		PRIVATE 
	)

	### Link to main lib.
	target_link_libraries(SA_Render INTERFACE SA_Render_Vulkan)

endif()


## DX12
option(SA_RENDER_DX12_OPT "Should compile DirectX12 wrapper" OFF)

if(SA_RENDER_DX12_OPT)

	add_library(SA_Render_DX12 STATIC)
	SA_ConfigureTarget(SA_Render_DX12)
	SA_TargetSources(SA_Render_DX12
		PUBLIC_SRC_DIR "Include/SA/Render/DX12"
		PUBLIC_INCL_DIR "OFF"
		PRIVATE_SRC_DIR "Source/SA/Render/DX12"
	)

	target_link_libraries(SA_Render_DX12
		PUBLIC SA_Render_Base
		PUBLIC d3d12.lib dxgi.lib # Set to public for easier wrapping.
		PRIVATE dxguid.lib
	)

	### Link to main lib.
	target_link_libraries(SA_Render INTERFACE SA_Render_DX12)

endif()


## OpenGL
option(SA_RENDER_OPENGL_OPT "Should compile OpenGL wrapper" OFF)

if(SA_RENDER_OPENGL_OPT)

	find_package(OpenGL REQUIRED)

	add_library(SA_Render_OpenGL STATIC)
	SA_ConfigureTarget(SA_Render_OpenGL)
	SA_TargetSources(SA_Render_OpenGL
		PUBLIC_SRC_DIR "Include/SA/Render/OpenGL"
		PUBLIC_INCL_DIR "OFF"
		PRIVATE_SRC_DIR "Source/SA/Render/OpenGL"
	)

	target_link_libraries(SA_Render_OpenGL
		PUBLIC SA_Render_Base
		PRIVATE OpenGL::GL
	)

	### Link to main lib.
	target_link_libraries(SA_Render INTERFACE SA_Render_OpenGL)

endif()



# Entrypoints

add_subdirectory(ThirdParty)

### SA_Windowing target already in build-tree: add link for custom implementations.
### Must be done after ThirdParty include in case of SA_Windowing module fetching.
if(TARGET SA_Windowing)
	target_link_libraries(SA_Render_Base PUBLIC SA_Windowing)
endif()

if(SA_RENDER_BUILD_TESTS_OPT OR SA_RENDER_SCOMMON_OPT)

	### Enable testing for this directory and below.
	enable_testing()

	add_subdirectory(Tests)

endif()
