# Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

# Entrypoints

add_subdirectory(Prototype_Common)

if(SA_RENDER_VULKAN_OPT)

	add_subdirectory(Prototype_VK)

endif()

if(SA_RENDER_OPENGL_OPT)

	add_subdirectory(Prototype_GL)

endif()

if(SA_RENDER_DX12_OPT)

	add_subdirectory(Prototype_DX12)

endif()

add_subdirectory(Prototype_All)

add_subdirectory(UnitTests)
