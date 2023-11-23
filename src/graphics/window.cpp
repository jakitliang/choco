//
// Created by jakit on 2023/11/23.
//

#include "choco/graphics/window.h"
#include "handle.h"
#include "SDL.h"

struct Choco::Graphics::Window::Impl {
    SDL_Window *window;
};

Choco::Graphics::Window::Window() {
    impl_->window = nullptr;
}

Choco::Graphics::Window::~Window() {
    if (impl_->window) {
        SDL_DestroyWindow(impl_->window);
    }
}

Choco::Graphics::Window *Choco::Graphics::Window::Create(const char *title, Choco::UInt32 width, Choco::UInt32 height) {
    auto window = new Window();
    window->impl_->window = SDL_CreateWindow(
            title,
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            width,
            height,
            0);

    if (window->impl_->window) {
        return window;
    }

    delete window;
    return nullptr;
}

Choco::Graphics::HWindow Choco::Graphics::Window::getHandle() {
    HWindow window;
    window.window = impl_->window;
    return window;
}
