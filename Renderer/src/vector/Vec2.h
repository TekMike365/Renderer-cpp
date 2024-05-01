#pragma once

#include <sstream>
#include <string>
#include <cmath>

namespace Renderer
{
    class Vec2
    {
    public:
        float x, y;

        Vec2();
        Vec2(float x, float y);

        ~Vec2() = default;

        void Normalize();

        std::string ToString();
        Vec2 GetNormalized() const;
        inline float GetScale() const { return std::sqrt(x*x + y*y); }

        float Dot(Vec2 const& other) const;
        bool operator==(Vec2 const& other) const;
        Vec2 operator+(Vec2 const& other) const;
        Vec2& operator+=(Vec2 const& other);
        Vec2 operator-(Vec2 const& other) const;
        Vec2& operator-=(Vec2 const& other);
        Vec2 operator*(float scalar) const;
        Vec2& operator*=(float scalar);
        Vec2 operator/(float scalar) const;
        Vec2& operator/=(float scalar);
    };
}

