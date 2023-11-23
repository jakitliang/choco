
add_subdirectory(./foundation)

option(GRAPHICS_ENABLED "Enable graphics library" OFF)

add_executable(
        choco
        main.cpp
        test_hidden.h
        test_hidden_parent.h
)

target_link_libraries(choco choco_foundation)

if(GRAPHICS_ENABLED)
    message("Graphics Enabled")
    find_package(glfw3 REQUIRED)
    add_library(glad glad.cpp)
    target_link_libraries(choco glfw glad)

    add_subdirectory(./graphics)
    target_link_libraries(choco choco_graphics)
endif()


