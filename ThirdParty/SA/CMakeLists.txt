# Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

# Entrypoints

SA_FetchModule(Logger)
SA_FetchModule(HI)

## Query SA_Windowing SCommon for SA_Render SCommon.
if(SA_RENDER_BUILD_TESTS_OPT OR SA_RENDER_SCOMMON_OPT)

	set(SA_WINDOWING_SCOMMON_OPT ON)

	SA_FetchModule(Windowing)

endif()
