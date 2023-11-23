//
// Created by jakit on 2023/11/23.
//

#ifndef CHOCO_GRAPHICS_EVENT_H
#define CHOCO_GRAPHICS_EVENT_H

#include "choco/foundation/memory.h"

namespace Choco {
    namespace Graphics {
        struct HEvent;
        struct Event {
            struct Impl;
            Component<Impl, 64> impl_;
        };
    }
}

#endif //CHOCO_GRAPHICS_EVENT_H
