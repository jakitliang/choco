//
// Created by jakit on 2023/11/23.
//

#ifndef CHOCO_GRAPHICS_HANDLE_H
#define CHOCO_GRAPHICS_HANDLE_H

#include "SDL.h"

namespace Choco {
    namespace Graphics {
        struct HWindow {
            SDL_Window *window;
        };

        struct HRenderer {
            SDL_Renderer *renderer;
        };

        struct HTexture {
            SDL_Texture *texture;
        };

        struct HSurface {
            SDL_Surface *surface;
        };
    }
}

#endif //CHOCO_GRAPHICS_HANDLE_H
