//
// Created by jakit on 2023/11/22.
//

#include "choco/graphics/graphics.h"
#include "choco/graphics/window.h"
#include "choco/graphics/renderer.h"
#include "choco/graphics/context.h"
#include <iostream>
#include <vector>

const Choco::Graphics::Driver & Choco::Graphics::GetCurrentDriver() {
    return *GetContext().currentDriver;
}

Choco::Graphics::Color &Choco::Graphics::GetColor() {
    return GetContext().getColor();
}

void Choco::Graphics::SetColor(Choco::Byte r, Choco::Byte g, Choco::Byte b, Choco::Byte a) {
    GetContext().setColor(r, g, b, a);
}

void Choco::Graphics::Push() {
    GetContext().push();
}

void Choco::Graphics::Pop() {
    GetContext().pop();
}

bool Choco::Graphics::Open(const char *title, Choco::Size width, Choco::Size height, Choco::UInt32 renderMode) {
    return GetContext().open(title, width, height, renderMode);
}

bool Choco::Graphics::Open(Choco::UInt32 width, Choco::UInt32 height) {
    return GetContext().open(nullptr, width, height, CHOCO_GRAPHICS_MODE_HEADLESS);
}

void Choco::Graphics::Close() {
    return GetContext().close();
}

void *Choco::Graphics::Attach(Choco::Graphics::RunLoop run) {
    return GetContext().attach(run);
}

void Choco::Graphics::Line(Choco::Int32 x1, Choco::Int32 y1, Choco::Int32 x2, Choco::Int32 y2) {
    GetContext().renderer->line(x1, y1, x2, y2);
}
