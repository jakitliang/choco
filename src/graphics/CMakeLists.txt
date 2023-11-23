
find_package(SDL2 REQUIRED)

#add_library(choco_graphics_objs OBJECT render.cpp surface.cpp graphics.cpp)
#target_link_libraries(choco_graphics_objs ${SDL2_LIBRARIES})

add_library(choco_graphics OBJECT graphics.cpp canvas.cpp context.cpp window.cpp renderer.cpp)
target_link_libraries(choco_graphics ${SDL2_LIBRARIES})