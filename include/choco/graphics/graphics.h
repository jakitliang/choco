//
// Created by jakit on 2023/11/22.
//

#ifndef CHOCO_GRAPHICS_H
#define CHOCO_GRAPHICS_H

#include "choco/foundation/memory.h"
#include "choco/graphics/state.h"
#include "choco/graphics/color.h"
#include "choco/graphics/driver.h"
#include "choco/graphics/common.h"

namespace Choco {
    namespace Graphics {
        const Driver & GetCurrentDriver();
        const Slice<Driver> & GetDrivers();

        Color & GetColor();
        void SetColor(Byte r, Byte g, Byte b, Byte a);

        bool Open(const char * title, Size width, Size height, UInt32 renderMode = 0);
        bool Open(UInt32 width, UInt32 height);

        void Close();

        void * Attach(RunLoop run);

        void Line(Int32 x1, Int32 y1, Int32 x2, Int32 y2);

        void Push();
        void Pop();
    }
}

#endif //CHOCO_GRAPHICS_H
