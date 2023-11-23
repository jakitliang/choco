//
// Created by jakit on 2023/11/23.
//

#ifndef CHOCO_GRAPHICS_TEXTURE_H
#define CHOCO_GRAPHICS_TEXTURE_H

#include "choco/foundation/memory.h"

namespace Choco {
    namespace Graphics {
        struct TextureImpl;
        struct Texture {
            Component<TextureImpl, 64> impl_;

            void finalize();

            static Texture * Create(Window * window, UInt32 width, UInt32 height, UInt32 mode);
        };
    }
}

#endif //CHOCO_GRAPHICS_TEXTURE_H
