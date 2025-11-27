#pragma once

#include <string>
#include <utility>
#include "physics_engine/render/Drawable.h"

class ObjectBase : public Drawable {
    protected:
        std::string m_Id;
    
    public:
        explicit ObjectBase(std::string id) : m_Id(std::move(id)) {}
        virtual ~ObjectBase() = default;

        virtual void draw(Renderer& r) const = 0;

        const std::string& GetId() const { return m_Id; }  
};