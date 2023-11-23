//
// Created by jakit on 2023/6/19.
//

#ifndef CHOCO_FILE_H
#define CHOCO_FILE_H

#include "choco/foundation/io.h"
#include "choco/foundation/memory.h"

namespace Choco {
    struct FileData;
    struct File : IO {
        Component<FileData, 192> data_;

        ~File();

        Integer Read(char *buffer, Size size) override;

        Integer Write(const char *buffer, Size size) override;

        void Close();

        static File Open(const char *name, const char *flags);

    private:
        explicit File(const char *name, const char *flags);
    };
}

#endif //CHOCO_FILE_H
