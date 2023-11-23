//
// Created by jakit on 2023/11/23.
//

#ifndef CHOCO_GRAPHICS_RENDERER_H
#define CHOCO_GRAPHICS_RENDERER_H

#include "choco/graphics/window.h"

namespace Choco {
    namespace Graphics {
        struct HRenderer;
        struct Renderer {
            struct Impl;
            Component<Impl, 64> impl_;

            ~Renderer();

            HRenderer getHandle();

            void line(Int32 x1, Int32 y1, Int32 x2, Int32 y2);

            void clear();

            void draw();

            static Renderer * Create(Window * window, UInt32 index);

            static Renderer * Create(Choco::Size width, Choco::Size height);

        private:
            Renderer();
        };
    }
}

#endif //CHOCO_GRAPHICS_RENDERER_H
