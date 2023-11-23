//
// Created by jakit on 2023/11/22.
//

#ifndef CHOCO_GRAPHICS_STATE_H
#define CHOCO_GRAPHICS_STATE_H

#include "choco/graphics/color.h"

namespace Choco {
    namespace Graphics {
        struct State {
            double x;
            double y;
            double scaleX;
            double scaleY;
            Byte origin;
            Color color;

            State() : x(0), y(0), scaleX(0), scaleY(0), origin(0), color() {}
        };
    }
}

#endif //CHOCO_GRAPHICS_STATE_H
