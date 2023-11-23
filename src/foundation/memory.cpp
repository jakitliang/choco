//
// Created by jakit on 2023/6/18.
//

#include "choco/foundation/memory.h"

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <new>
#ifndef NDEBUG
#include <cassert>
#endif

namespace Choco {
    struct SliceImpl {
        std::vector<Byte> data;

        void initialize() {
            data = std::vector<Byte>();
        }

        void finalize() {
            data.clear();
        }
    };
}

void Choco::Fill(Byte *src, Choco::Size size, Choco::Byte value) {
    std::fill(src, src + size, value);
}

void Choco::Copy(const Byte * src, Size size, Byte * dst) {
    std::memcpy(dst, src, size);
}

void Choco::BlockCopy(const Byte * src, Choco::Integer srcOffset, Byte * dst, Choco::Integer dstOffset,
                            Choco::Integer count) {
    // The reason not to check the tail and beginning
    // is to allow coders freely copy any data from and to any address.
    std::memmove(dst + dstOffset, src + srcOffset, count);
}

Choco::ComponentImpl::ComponentImpl(Choco::Size T, Choco::Size N) {
    CHOCO_ASSERT(N >= T);
}

Choco::ByteSlice::ByteSlice() {
    this->impl_->initialize();
}

Choco::ByteSlice::~ByteSlice() {
    this->impl_->finalize();
}

void Choco::ByteSlice::append(const Choco::Byte &element) {
    this->impl_->data.insert(
            this->impl_->data.end(),
            &element,
            &element + this->sizeOfElement());
}

void Choco::ByteSlice::append(const Choco::Byte *element) {
    this->impl_->data.insert(
            this->impl_->data.end(),
            element,
            element + this->sizeOfElement());
}

void Choco::ByteSlice::append(const Choco::Byte *element, Choco::SSize blockSize) {
    this->impl_->data.insert(
            this->impl_->data.end(),
            element,
            element + blockSize);
}

Choco::Byte & Choco::ByteSlice::at(Choco::SSize position) {
    return this->impl_->data.at(position * this->sizeOfElement());
}

Choco::Byte &Choco::ByteSlice::at(Choco::SSize position, Choco::SSize blockSize) {
    return this->impl_->data.at(position * blockSize);
}

void Choco::ByteSlice::clear() {
    auto & data = this->impl_->data;
    data.clear();
}

Choco::Size Choco::ByteSlice::count() {
    return this->impl_->data.size();
}

Choco::Size Choco::ByteSlice::count(Choco::SSize blockSize) {
    return this->impl_->data.size() / blockSize;
}

void Choco::ByteSlice::erase(Choco::SSize index) {
    auto & data = this->impl_->data;
    SSize size = this->sizeOfElement();
    data.erase(
            data.begin() + size * index,
            data.begin() + size * (index + 1));
}

void Choco::ByteSlice::erase(Choco::SSize index, Choco::SSize blockSize) {
    auto & data = this->impl_->data;
    data.erase(
            data.begin() + blockSize * index,
            data.begin() + blockSize * (index + 1));
}
