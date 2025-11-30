#pragma once


struct Rect {
    float x, y;
    float w, h;

    bool Contains(float px, float py) const {


        return px > x && px <= x + w &&
               py >= y && py <= y + h;
    }

    inline float getArea() {
        return w * h;
    }
};