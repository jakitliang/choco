//
// Created by jakit on 2023/11/23.
//

#ifndef CHOCO_GRAPHICS_CONTEXT_H
#define CHOCO_GRAPHICS_CONTEXT_H

#include "choco/graphics/window.h"
#include "choco/graphics/renderer.h"
#include "choco/graphics/driver.h"
#include "choco/graphics/state.h"
#include "choco/graphics/common.h"

namespace Choco {
    namespace Graphics {
        typedef CHOCO_ENUM(int, ChocoGraphicsMode) {
            CHOCO_GRAPHICS_MODE_NONE = -1,
            CHOCO_GRAPHICS_MODE_HARDWARE = 0,
            CHOCO_GRAPHICS_MODE_HARDWARE_GL = 1,
            CHOCO_GRAPHICS_MODE_SOFTWARE = 2,
            CHOCO_GRAPHICS_MODE_HEADLESS = 3
        };

        struct Context {
            struct Impl;
            Component<Impl, 64> impl_;

            UInt32 mode;
            Slice <Driver> drivers;
            Driver * currentDriver;
            Renderer * renderer;
            Window * window;

            Context();

            ~Context();

            Context(const Context&) = delete;

            bool open(const char *title, Size width, Size height, UInt32 renderMode);

            void close();

            void *attach(RunLoop run);

            Color & getColor();

            void setColor(Byte r, Byte g, Byte b, Byte a);

            void translate(Int32 x, Int32 y);

            void origin();

            void push();

            void pop();
        };

        Context & GetContext();
    }
}

#endif //CHOCO_GRAPHICS_CONTEXT_H
