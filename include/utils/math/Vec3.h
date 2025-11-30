#pragma once
#include <iostream>
#include <cmath>


template <typename T>
struct Vec2 {
    T x, y, z;

    Vec2 normalized() const {
        float norm = std::sqrt( x*x + y*y + z*z);
        float rNorm = 1 / norm;

        return Vec2 { x * rNorm, y * rNorm, z * rNorm };
    }

    void normalize() {
        float norm = std::sqrt( x*x + y*y + z*z );
        float rNorm = 1 / norm;

        x = x * rNorm;
        y = y * rNorm;
        z = z * rNorm;
    }

    inline T X() const {
        return x;
    }

    inline T Y() const {
        return y;
    }

    inline T Z() const {
        return z;
    }
};

