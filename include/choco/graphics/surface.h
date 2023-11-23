//
// Created by jakit on 2023/11/20.
//

#ifndef CHOCO_SURFACE_H
#define CHOCO_SURFACE_H

#include "choco/foundation/memory.h"

namespace Choco {
    struct SurfaceImpl;
    struct Surface {
        Component<SurfaceImpl, 128> impl_;

        Surface(UInt32 flags, int width, int height, int depth,
                UInt32 rMask, UInt32 gMask, UInt32 bMask, UInt32 aMask);

        Surface(UInt32 flags, int width, int height, int depth, UInt32 format);

        ~Surface();

        void fillRect(int x, int y, int w, int h);
        void save(const char *file);
    };
}

#endif //CHOCO_SURFACE_H
