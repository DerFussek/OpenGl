#pragma once
#include <iostream>
#include <cmath>


template <typename T>
struct Vec2 {
    T x, y;

    Vec2 normalized() const {
        float norm = std::sqrt( x*x + y*y);
        float rNorm = 1 / norm;

        return Vec2 { x * rNorm, y * rNorm };
    }

    void normalize() {
        float norm = std::sqrt( x*x + y*y);
        float rNorm = 1 / norm;

        x = x * rNorm;
        y = y * rNorm;
    }

    inline T X() const {
        return x;
    }

    inline T Y() const {
        return y;
    }
};

