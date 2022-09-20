# Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

# Executable

## Add executable target.
add_executable(SA_RenderProto_All "main.cpp")



# Dependencies

### Add library dependencies.
target_link_libraries(SA_RenderProto_All PRIVATE SA_RenderProto_Common)



# Tests

add_test(NAME CSA_RenderProto_All COMMAND SA_RenderProto_All)
