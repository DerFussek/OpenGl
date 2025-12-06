#pragma once


struct Rect {
    float x = 0, y = 0;
    float w = 0, h = 0;

    bool Contains(float px, float py) const {


        return px > x && px <= x + w &&
               py >= y && py <= y + h;
    }

    inline float getArea() {
        return w * h;
    }
};