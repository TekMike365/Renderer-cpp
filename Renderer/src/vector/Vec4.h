#pragma once

#include <sstream>
#include <string>
#include <cmath>

namespace Renderer
{
    class Vec4
    {
    public:
        float x, y, z, w;

        Vec4();
        Vec4(float x, float y, float z, float w);

        ~Vec4() = default;

        void Normalize();

        std::string ToString();
        Vec4 GetNormalized() const;
        inline float GetScale() const { return std::sqrt(x*x + y*y + z*z + w*w); }

        float Dot(Vec4 const& other) const;
        bool operator==(Vec4 const& other) const;
        bool operator!=(Vec4 const& other) const;
        Vec4 operator+(Vec4 const& other) const;
        Vec4& operator+=(Vec4 const& other);
        Vec4 operator-(Vec4 const& other) const;
        Vec4& operator-=(Vec4 const& other);
        Vec4 operator*(float scalar) const;
        Vec4& operator*=(float scalar);
        Vec4 operator/(float scalar) const;
        Vec4& operator/=(float scalar);
    };
}

