#pragma once
#include "utils/forms/Rect.h"
#include "physics_engine/core/Engine.h"

struct ButtonState {
    bool hovered = false;
    bool pressed = false;
};

bool DoButton(const char* id, const Rect &r, InputState& in, ButtonState& state) {
    state.hovered = r.Contains((float)in.mouseX, (float)in.mouseY);

    bool clicked = false;
    if(state.hovered && in.mousePressedLeft) {
        clicked = true;
        state.pressed = true;
    } else {
        state.pressed = false;
    }

    return clicked;
}