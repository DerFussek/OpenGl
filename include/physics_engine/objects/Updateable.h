#pragma once

namespace PhyEn
{
    class Renderer2D;

    class Updateable {
        public:
            virtual ~Updateable() = default;
            virtual void update(float dt) = 0;
    };
} // namespace PhyEn
