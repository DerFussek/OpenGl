#pragma once

#include "utils/forms/Rect.h"
#include "physics_engine/objects/shapes/GlRect.h"

struct Panel {
    Rect screenRect{};
    GlRect* rect = nullptr;
};