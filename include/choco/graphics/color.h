//
// Created by jakit on 2023/11/22.
//

#ifndef CHOCO_GRAPHICS_COLOR_H
#define CHOCO_GRAPHICS_COLOR_H

#include "choco/foundation/memory.h"

namespace Choco {
    namespace Graphics {
        struct Color {
            Byte r;
            Byte g;
            Byte b;
            Byte a;

            Color() : r(0), g(0), b(0), a(0) {}
        };
    }
}

#endif //CHOCO_GRAPHICS_COLOR_H
