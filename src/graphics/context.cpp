//
// Created by jakit on 2023/11/23.
//

#include "choco/graphics/context.h"
#include "choco/graphics/window.h"
#include "SDL.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

static Choco::Graphics::Context context;

struct Choco::Graphics::Context::Impl {
    std::vector<State> state;

    void initialize() {
        state = std::vector<State>();
    }

    void finalize() {
        state.clear();
    }
};

Choco::Graphics::Context::Context() {
    mode = CHOCO_GRAPHICS_MODE_NONE;
    renderer = nullptr;
    window = nullptr;

    auto ret = SDL_GetNumRenderDrivers();
    for (int i = 0; i < ret; ++i) {
        SDL_RendererInfo info;
        SDL_GetRenderDriverInfo(i, &info);
        Driver driver{};
        driver.index = i;
        driver.name = info.name;
        drivers.append(driver);
//        std::cout << i << ':' << info.name << ',' << info.flags << std::endl;
    }

    currentDriver = &drivers[0];

    impl_->initialize();
}

Choco::Graphics::Context::~Context() {
    close();
}

bool Choco::Graphics::Context::open(const char *title, Choco::Size width, Choco::Size height, Choco::UInt32 renderMode) {
    if (mode != 0) {
        std::cout << "Graphics had been opened" << std::endl;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "Context init failed" << std::endl;
        return false;
    }

#if defined(_WIN32)
    const char * driverName = "direct3d";
    if (renderMode == CHOCO_GRAPHICS_MODE_HARDWARE_GL) {
        driverName = "opengl";
    }
#elif defined(ANDROID) || defined(__ANDROID__)
    const char * driverName = "opengles";
#elif defined(TARGET_OS_IPHONE)
    const char * driverName = "opengles";
#else
    const char * driverName = "opengl";
#endif

    mode = CHOCO_GRAPHICS_MODE_HARDWARE;

    if (renderMode == CHOCO_GRAPHICS_MODE_SOFTWARE) {
        driverName = "software";
        mode = renderMode;
    }

    if (renderMode == CHOCO_GRAPHICS_MODE_HEADLESS) {
        renderer = Choco::Graphics::Renderer::Create(width, height);

        if (!renderer) {
            SDL_Quit();
        }

        mode = renderMode;
        return true;
    }

    for (int i = 0; i < drivers.count(); ++i) {
        if (strstr(drivers[i].name, driverName)) {
            currentDriver = &drivers[i];
            std::cout << "Using: " << drivers[i].index << ", " << drivers[i].name << std::endl;
            break;
        }
    }

    window = Choco::Graphics::Window::Create(title, width, height);

    if (!window)
    {
        std::cout << "Failed to Open window: "
                  << width
                  << ", "
                  << height
                  << "\n"
                  << SDL_GetError()
                  << std::endl;
        SDL_Quit();
        mode = CHOCO_GRAPHICS_MODE_NONE;
        return false;
    }

//    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    renderer = Choco::Graphics::Renderer::Create(window, currentDriver->index);

    if (!renderer)
    {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        delete window;
        SDL_Quit();
        mode = CHOCO_GRAPHICS_MODE_NONE;
        return false;
    }

    return true;
}

void Choco::Graphics::Context::close() {
    if (mode == CHOCO_GRAPHICS_MODE_NONE) {
        return;
    }

    delete renderer;
    delete window;

    mode = CHOCO_GRAPHICS_MODE_NONE;
    SDL_Quit();

    impl_->finalize();
}

Choco::Graphics::Color &Choco::Graphics::Context::getColor() {
    return impl_->state.back().color;
}

void Choco::Graphics::Context::setColor(Choco::Byte r, Choco::Byte g, Choco::Byte b, Choco::Byte a) {
    auto & color = impl_->state.back().color;
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = a;
}

void Choco::Graphics::Context::translate(Choco::Int32 x, Choco::Int32 y) {
    auto & state = impl_->state.back();
    state.x = x;
    state.y = y;
}

void Choco::Graphics::Context::origin() {
    push();
    auto & state = impl_->state.back();
    state.origin = 1;
}

void Choco::Graphics::Context::push() {
    impl_->state.emplace_back();
}

void Choco::Graphics::Context::pop() {
    impl_->state.pop_back();
}

void *Choco::Graphics::Context::attach(Choco::Graphics::RunLoop run) {
    void * ret = nullptr;
    int quit = 0;
    SDL_Event event;
    UInt32 a = 0, b = 0;
    double delta = 0;

    while (quit == 0) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return nullptr;
            } else if (event.type == SDL_TEXTINPUT) {
                int x = 0, y = 0;
//                SDL_GetMouseState( &x, &y );
//                handleKeys( event.text.text[0], x, y );
            }
        }

        a = SDL_GetTicks();
        delta = a - b;

        if (delta > 1000 / 60.0) {
//            std::cout << "fps: " << 1000 / delta << std::endl;
            b = a;

            // Update game state

            renderer->clear();

            // Render game graphics
            ret = run(&quit);

            renderer->draw();

        } else {
            std::this_thread::sleep_for(std::chrono::nanoseconds(1));
        }
    }

    return ret;
}

Choco::Graphics::Context & Choco::Graphics::GetContext() {
    return context;
}
