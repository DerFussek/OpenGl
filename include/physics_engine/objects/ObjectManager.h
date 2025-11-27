#pragma once
#include <iostream>
#include <stdexcept>
#include <string>
#include <array>
#include <unordered_map>
#include <memory>
#include <sstream>
#include <iomanip>

#include "physics_engine/objects/shapes/Circle.h"
#include "physics_engine/objects/shapes/Rect.h"

struct IdGenerator {
    private:
        inline static unsigned int s_Counter = 0;
        static const int maxObjs = 9999;
    public:
        static std::string Next() {
            if(s_Counter > maxObjs) {
                s_Counter = 0;
                throw std::runtime_error("Maximum Number of IDs reached");
            }

            std::ostringstream oss;
            oss << std::setw(4) << std::setfill('0') << s_Counter++;
            return oss.str();
        }
};



class ObjectManager {
    private:
        std::unordered_map<std::string, std::unique_ptr<Circle>> m_Circles;
        std::unordered_map<std::string, std::unique_ptr<Rect>> m_Rects;

    public:
        // Circle
        Circle* CreateCircle(std::array<float, 2> position, std::array<float, 4> color, float radius) {
            std::string id = IdGenerator::Next();
            auto circle = std::make_unique<Circle>(id, position, color, radius);
            Circle* ptr = circle.get();
            m_Circles.emplace(id, std::move(circle));
            return ptr;
        }

        Circle* GetCircle(const std::string& id) {
            auto it = m_Circles.find(id);
            if (it == m_Circles.end()) return nullptr;
            return it->second.get();
        }

        bool RemoveCircle(const std::string& id) {
            return m_Circles.erase(id) > 0;
        }

        auto& GetAllCircles() { return m_Circles; }

        // Rect
        Rect* CreateRect(std::array<float, 2> pos, std::array<float, 4> color, std::array<float, 2> size) {
            std::string id = IdGenerator::Next();
            auto rect = std::make_unique<Rect>(id, pos, color, size);
            Rect* ptr = rect.get();
            m_Rects.emplace(id, std::move(rect));
            return ptr;
        }

        Rect* GetRect(const std::string& id) {
            auto it = m_Rects.find(id);
            if (it == m_Rects.end()) return nullptr;
            return it->second.get();
        }

        bool RemoveRect(const std::string& id) {
            return m_Rects.erase(id) > 0;
        }

        auto& GetAllRects() { return m_Rects; }
};

