#pragma once

namespace PhyEn {
    class Renderer2D;

    class Drawable {
        public:
            virtual ~Drawable() = default;
            virtual void draw(Renderer2D& renderer) = 0;
    };
}