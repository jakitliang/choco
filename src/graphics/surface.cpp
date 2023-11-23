//
// Created by jakit on 2023/11/20.
//

#include "choco/graphics/surface.h"
#include <SDL.h>
#include <cstdio>
#include "choco/graphics/context.h"

struct Choco::SurfaceImpl {
    SDL_Surface *surface;
};

Choco::Surface::Surface(Choco::UInt32 flags,
                        int width, int height, int depth,
                        Choco::UInt32 rMask, Choco::UInt32 gMask,
                        Choco::UInt32 bMask, Choco::UInt32 aMask) {
    auto & surface = *impl_;
    surface.surface = SDL_CreateRGBSurface(
            flags, width, height, depth, rMask, gMask, bMask, aMask);
}

Choco::Surface::Surface(Choco::UInt32 flags, int width, int height, int depth, Choco::UInt32 format) {
    auto & surface = *impl_;
    surface.surface = SDL_CreateRGBSurfaceWithFormat(flags, width, height, depth, format);
}

Choco::Surface::~Surface() {
    SDL_FreeSurface(impl_->surface);
}

void Choco::Surface::fillRect(int x, int y, int w, int h) {
    SDL_Rect rect = {x, y, w, h};
    auto & color = Choco::Graphics::Context::Instance().getColor();
    auto c = SDL_MapRGBA(impl_->surface->format, color.r, color.g, color.b, color.a);
    SDL_FillRect(impl_->surface, &rect, c);
}

void Choco::Surface::save(const char *file) {
    SDL_Rect rect = {0, 0, impl_->surface->w, impl_->surface->h};
    SDL_RenderReadPixels(nullptr, &rect, impl_->surface->format->format, impl_->surface->pixels, impl_->surface->pitch);
    SDL_SaveBMP(impl_->surface, file);
}
