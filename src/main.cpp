//
// Created by jakit on 2023/6/18.
//

#include "choco/foundation/memory.h"
#include "choco/foundation/file.h"
#include "choco/graphics/graphics.h"

#include "glad/gladfuncs.hpp"
#include "GLFW/glfw3.h"

#include <iostream>
#include <cassert>
#include <vector>
#include <chrono>
#include <thread>
#include <vector>

void * runLoop(int * quit) {
//    Choco::Graphics::Line(-1, -1, 1, 1);
    return nullptr;
}

int main() {
//    SetUnhandledExceptionFilter(UnhandledHandler);

//    Choco::Render render;
////    render.Open("Hello", 800, 600);
//    Choco::Surface surface(0, 1920, 1080, 24, SDL_PIXELFORMAT_RGB24);
//    Choco::Graphics::Instance().SetColor(255, 0, 0, 255);
//
//    for (int i = 0; i < 36000; ++i) {
//        std::this_thread::sleep_for(std::chrono::nanoseconds(1));
//        for (int j = 0; j < 1920 / 10; ++j) {
//            surface.fillRect(j, j, 10, 10);
//        }
//    }
//    surface.save("nihao.png");

//    auto &drivers = Choco::Graphics::GetDrivers();
    bool ret = Choco::Graphics::Open("Test", 800, 600);

    if (!ret) {
        std::cout << "Start failed" << std::endl;
        return 0;
    }

    Choco::Graphics::Attach(runLoop);

    return 0;
}
