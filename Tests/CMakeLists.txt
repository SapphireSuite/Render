# Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

# Entrypoints

add_subdirectory(SCommon)

if(SA_RENDER_BUILD_TESTS_OPT)

	## Prototypes
	add_subdirectory(Prototype)

	if(SA_RENDER_VULKAN_OPT)

		add_subdirectory(Prototype_VK)

	endif()

	if(SA_RENDER_OPENGL_OPT)

		add_subdirectory(Prototype_GL)

	endif()

	if(SA_RENDER_DX12_OPT)

		add_subdirectory(Prototype_DX12)

	endif()

endif(SA_RENDER_BUILD_TESTS_OPT)
