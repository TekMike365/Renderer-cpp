#pragma once

#include <sstream>
#include <string>
#include <array>

#include "Vec4.h"
#include "Vec3.h"

namespace Renderer {

    class Mat4
    {
    public:
        Mat4();
        Mat4(float values[16]);

        ~Mat4() = default;

        static Mat4 Identity();
        inline static int ToIndex(int m, int n) { return m * 4 + n; }

        Mat4& Transform(Vec3 const& xyz);
        Mat4& Scale(Vec3 const& xyz);
        Mat4& Rotate(Vec3 const& xyz);

        std::string ToString() const;
        float GetValue(int m, int n) const;
        void SetValue(int m, int n, float val);
        std::array<float, 16> GetValuesArray() const;

        bool operator==(Mat4 const& other) const;
        bool operator!=(Mat4 const& other) const;
        Mat4 operator+(Mat4 const& other) const;
        Mat4 operator+=(Mat4 const& other);
        Mat4 operator-(Mat4 const& other) const;
        Mat4 operator-=(Mat4 const& other);
        Mat4 operator*(float scalar) const;
        Mat4& operator*=(float scalar);
        Mat4 operator/(float scalar) const;
        Mat4& operator/=(float scalar);
        Mat4 operator*(Mat4 const& other) const;
        Mat4& operator*=(Mat4 const& other);
        Vec4 operator*(Vec4 const& vec) const;

    private:
        float m_Vals[16];
    };

}
