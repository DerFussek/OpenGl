#pragma once
#include "utils/forms/Rect.h"
#include "physics_engine/core/Engine.h"

struct ButtonState {
    bool hovered = false;
    bool pressed = false;
};

bool DoButton(const char* id, const Rect& r, const InputState& in, ButtonState& state) {
    state.hovered = (in.mouseX >= r.x && in.mouseX <= r.x + r.w &&
                     in.mouseY >= r.y && in.mouseY <= r.y + r.h);

    bool clicked = false;
    if (state.hovered && in.mousePressedLeft) {
        state.pressed = true;
        clicked = true;
    } else {
        state.pressed = false;
    }
    return clicked;
}
