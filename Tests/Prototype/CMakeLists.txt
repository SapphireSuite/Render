# Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

# Executable

## Add executable target.
add_executable(SA_RenderProto "main.cpp")



# Dependencies

### Add library dependencies.
target_link_libraries(SA_RenderProto PRIVATE SA_Render_SCommon)



# Tests

add_test(NAME CSA_RenderProto COMMAND SA_RenderProto)
