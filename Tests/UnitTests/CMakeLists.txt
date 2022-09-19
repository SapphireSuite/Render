# Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.



# Project

project(SA_RenderUT)

SA_FetchGoogleTest()



# Executable

## Inputs

file(GLOB_RECURSE SA_RENDER_UT_SOURCES "*.cpp")

## Add executable target.
add_executable(SA_RenderUT ${SA_RENDER_UT_SOURCES})



# Dependencies

### Add library dependencies.
target_link_libraries(SA_RenderUT PRIVATE SA_Render)

### Google test module dependency.
target_link_libraries(SA_RenderUT PRIVATE gtest)



# Tests

add_test(NAME CSA_RenderUT COMMAND SA_RenderUT)
