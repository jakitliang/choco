//
// Created by jakit on 2023/11/23.
//

#ifndef CHOCO_GRAPHICS_CANVAS_H
#define CHOCO_GRAPHICS_CANVAS_H

#include "choco/foundation/memory.h"

namespace Choco {
    namespace Graphics {
        struct CanvasImpl;
        struct Canvas {
            Component<CanvasImpl, 128> impl_;

            bool initialize();
            void finalize();

            static void SetCurrent(Canvas * canvas);
        };
    }
}

#endif //CHOCO_GRAPHICS_CANVAS_H
