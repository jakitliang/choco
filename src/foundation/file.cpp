//
// Created by jakit on 2023/6/19.
//

#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "choco/foundation/file.h"

#include <Windows.h>
#include <cstring>
#include <cstdio>

namespace Choco {
    struct FileData {
        char * name;
        char flags[2];
        FILE * ref;
    };
}

Choco::File Choco::File::Open(const char *name, const char *flags) {
    Choco::File file(name, flags);
    Size lenOfFlags = std::strlen(flags);
    file.data_->ref = fopen(file.data_->name, file.data_->flags);
    return file;
}

Choco::File::File(const char *name, const char *flags) {
    Size lenOfName = std::strlen(name);
    this->data_->name = new char[lenOfName + 1];
    std::strncpy(this->data_->name, name, lenOfName);

    if (std::strlen(flags) > 0) {
        this->data_->flags[0] = flags[0];

        if (std::strlen(flags) > 1) {
            this->data_->flags[1] = flags[1];
        }
    }
}

Choco::Integer Choco::File::Read(char *buffer, Choco::Size size) {
    return 0;
}

Choco::Integer Choco::File::Write(const char *buffer, Choco::Size size) {
    return 0;
}

void Choco::File::Close() {

}

Choco::File::~File() {
    Close();
}
