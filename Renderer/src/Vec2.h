#pragma once

#include <sstream>
#include <string>

#include "Vec3.h"

namespace Renderer
{
    class Vec2
    {
    public:
        float x, y;

        Vec2();
        Vec2(float x, float y);

        ~Vec2() = default;

        std::string ToString();
        inline Vec3 ToVec3(float z = 0.0f) const { return Vec3(x, y, z); }

        float Dot(Vec2 const& other) const;

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

