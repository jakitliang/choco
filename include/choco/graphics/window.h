//
// Created by jakit on 2023/11/23.
//

#ifndef CHOCO_GRAPHICS_WINDOW_H
#define CHOCO_GRAPHICS_WINDOW_H

#include "choco/foundation/memory.h"

namespace Choco {
    namespace Graphics {
        struct HWindow;
        struct Window {
            struct Impl;
            Component<Impl, 64> impl_;

            ~Window();

            HWindow getHandle();

            static Window * Create(const char * title, UInt32 width, UInt32 height);

        private:
            Window();
        };
    }
}

#endif //CHOCO_GRAPHICS_WINDOW_H
