//
// Created by jakit on 2023/6/19.
//

#ifndef CHOCO_IO_H
#define CHOCO_IO_H

#include "choco/foundation/macros.h"

namespace Choco {
    struct IO {
        virtual Integer Read(char *buffer, Size size) = 0;

        virtual Integer Write(const char *buffer, Size size) = 0;
    };
}

#endif //CHOCO_IO_H
