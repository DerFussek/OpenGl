#pragma once

#include <vector>
#include <memory>
#include "physics_engine/objects/Drawable.h"
#include "physics_engine/objects/Updateable.h"

namespace PhyEn {

    class Renderer2D;

    // ObjectManager.h
    class ObjectManager {
        public:
            template<typename T, typename... Args>
            T* createDrawable(Args&&... args)
            {
                auto obj = std::make_unique<T>(std::forward<Args>(args)...);
                T* ptr = obj.get();
                m_drawables.push_back(std::move(obj));
                return ptr;
            }

            Drawable* addDrawable(std::unique_ptr<Drawable> obj)
            {
                Drawable* ptr = obj.get();
                m_drawables.push_back(std::move(obj));
                return ptr;
            }

            void updateAll(float dt)
            {
                for (auto& u : m_updateables)
                    u->update(dt);
            }

            void drawAll(Renderer2D& renderer)
            {
                for (auto& d : m_drawables)
                    d->draw(renderer);
            }

        private:
            std::vector<std::unique_ptr<Drawable>>   m_drawables;
            std::vector<std::unique_ptr<Updateable>> m_updateables;
    };


} // namespace pe
