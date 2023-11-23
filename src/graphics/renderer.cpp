//
// Created by jakit on 2023/11/23.
//

#include "choco/graphics/renderer.h"
#include "choco/graphics/context.h"
#include "handle.h"
#include "SDL.h"

struct Choco::Graphics::Renderer::Impl {
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    SDL_Surface *surface;
};

Choco::Graphics::Renderer::Renderer() {
    impl_->renderer = nullptr;
}

Choco::Graphics::Renderer::~Renderer() {
    if (impl_->renderer) {
        SDL_DestroyRenderer(impl_->renderer);
    }

    if (impl_->texture) {
        SDL_DestroyTexture(impl_->texture);
    }

    if (impl_->surface) {
        SDL_FreeSurface(impl_->surface);
    }
}

Choco::Graphics::Renderer *
Choco::Graphics::Renderer::Create(Choco::Graphics::Window *window, Choco::UInt32 index) {
    auto renderer = new Renderer();
    renderer->impl_->renderer = SDL_CreateRenderer(
            window->getHandle().window,
            index,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
    if (!renderer->impl_->renderer) {
        delete renderer;
        return nullptr;
    }
    renderer->impl_->texture = SDL_CreateTexture(
            renderer->impl_->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 800, 600);

    if (!renderer->impl_->texture) {
        delete renderer;
        return nullptr;
    }

    return renderer;
}

Choco::Graphics::Renderer *Choco::Graphics::Renderer::Create(Choco::Size width, Choco::Size height) {
    auto surface = SDL_CreateRGBSurface(
            SDL_PIXELFORMAT_RGBA8888, width, height, 32, 0, 0, 0, 0);
    if (!surface) {
        return nullptr;
    }

    auto renderer = new Renderer();

    renderer->impl_->renderer = SDL_CreateSoftwareRenderer(surface);
    if (renderer->impl_->renderer) {
        return renderer;
    }

    delete renderer;
    return nullptr;
}

Choco::Graphics::HRenderer Choco::Graphics::Renderer::getHandle() {
    HRenderer renderer{impl_->renderer};
    return renderer;
}

void Choco::Graphics::Renderer::line(Choco::Int32 x1, Choco::Int32 y1, Choco::Int32 x2, Choco::Int32 y2) {
    SDL_RenderDrawLine(impl_->renderer, x1, y1, x2, y2);
}

void Choco::Graphics::Renderer::clear() {
    SDL_SetRenderDrawColor(impl_->renderer,0,0,0,0);
    SDL_RenderClear(impl_->renderer);

    if (GetContext().mode != CHOCO_GRAPHICS_MODE_HEADLESS) {
        SDL_SetRenderTarget(impl_->renderer, impl_->texture);
    }
}

void Choco::Graphics::Renderer::draw() {
    SDL_SetRenderDrawColor(impl_->renderer, 255, 0, 255, 255);
    for (int i = 0; i < 200; i += 5) {
        SDL_Rect rect{i, i, 50, 50};
        SDL_RenderDrawRect(impl_->renderer, &rect);
    }
    if (GetContext().mode != CHOCO_GRAPHICS_MODE_HEADLESS) {
        SDL_SetRenderTarget(impl_->renderer, nullptr);
        SDL_RenderCopy(impl_->renderer, impl_->texture, nullptr, nullptr);
    }
    SDL_RenderPresent(impl_->renderer);
}
