//
// Created by jakit on 2023/6/18.
//

#ifndef CHOCO_MEMORY_H
#define CHOCO_MEMORY_H

#include "choco/foundation/macros.h"

namespace Choco {
    void Fill(Byte * src, Size size, Byte value);
    void Copy(const Byte * src, Size size, Byte * dst);
    void BlockCopy(const Byte * src, Integer srcOffset, Byte * dst, Integer dstOffset, Integer count);

    struct ComponentImpl {
        ComponentImpl(Size T, Size N);
    };

    template <typename T, unsigned long N = sizeof(T)>
    struct Component : ComponentImpl {
        Choco::Byte data_[N];

        Component() : ComponentImpl(sizeof(T), N) {
            Fill(this->data_, N, 0);
        }

        T * operator->() {
            return reinterpret_cast<T *>(data_);
        }

        T & operator*() {
            return *reinterpret_cast<T *>(data_);
        }
    };

    template<typename T>
    struct ISlice {
        Size sizeOfElement() {
            return sizeof(T);
        }

        virtual void append(const T & element) = 0;
        virtual void append(const T * element) = 0;
        virtual T & at(SSize position) = 0;
        virtual void clear() = 0;
        virtual Size count() = 0;
        virtual void erase(SSize index) = 0;

        virtual T & operator[](SSize index) {
            return this->at(index);
        }
    };

    struct SliceImpl;
    struct ByteSlice : ISlice<Byte> {
        Component<SliceImpl, 256> impl_;
        ByteSlice();
        ~ByteSlice();
//        Size sizeOfElement();
        void append(const Byte & element) override;
        void append(const Byte * element) override;
        void append(const Byte * element, SSize blockSize);
        Byte & at(SSize position) override;
        Byte & at(SSize position, SSize blockSize);
        void clear() override;
        Size count() override;
        Size count(SSize blockSize);
        void erase(SSize index) override;
        void erase(SSize index, SSize blockSize);
    };

    template<typename T>
    struct Slice : ISlice<T> {
        ByteSlice byte_;

        Slice() : byte_() {}

        void append(const T &another) override {
            byte_.append(reinterpret_cast<const Byte *>(&another), sizeof(T));
        }

        void append(const T * another) override {
            byte_.append(reinterpret_cast<const Byte *>(another), sizeof(T));
        }

        T & at(SSize index) override {
            return *reinterpret_cast<T *>(&byte_.at(index, sizeof(T)));
        }

        void clear() override {
            byte_.clear();
        }

        Size count() override {
//            return ByteSlice::count() / this->sizeOfElement();
            return byte_.count(sizeof(T));
        }

        void erase(SSize index) override {
//            auto t = reinterpret_cast<T *>(this->at(index));
//            t->~T();
//            ByteSlice::erase(index);
            byte_.erase(index, sizeof(T));
        }
    };
}

#define CHOCO_ZERO(src, size, value) Choco::Fill(reinterpret_cast<Byte *>(src), size, value)

#endif //CHOCO_MEMORY_H
