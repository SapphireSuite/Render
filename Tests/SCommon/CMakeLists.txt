# Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

# Library Sample Common.

add_library(SA_Render_SCommon STATIC)
SA_ConfigureTarget(SA_Render_SCommon)
SA_TargetSources(SA_Render_SCommon
	PUBLIC_SRC_DIR "Include/SCommon"
	PRIVATE_SRC_DIR "Source/SCommon"
)

target_link_libraries(SA_Render_SCommon
	PUBLIC SA_Render SA_Windowing_SCommon
)



# Options

## Add SA_Render SCommon selected window interface.
set(SA_RENDER_SCOMMON_SELECTED_INTERFACE_OPT "VK" CACHE STRING "Selected render interface for scommon implementation.")
message("SA_Render SCommon selected render interface: ${SA_RENDER_SCOMMON_SELECTED_INTERFACE_OPT}")

target_compile_definitions(SA_Render_SCommon PUBLIC SA_RENDER_SCOMMON_SELECTED_INTERFACE=${SA_RENDER_SCOMMON_SELECTED_INTERFACE_OPT})
