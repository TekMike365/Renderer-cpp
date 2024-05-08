#include "Mat4.h"

#include <cmath>

namespace Renderer {

    Mat4::Mat4()
        : m_Vals { 0.0f }
    {
    }

    Mat4::Mat4(float values[16])
        : m_Vals { 0.0f }
    {
        for (int i = 0; i < 16; i++) {
            m_Vals[i] = values[i];
        }
    }

    Mat4 Mat4::Identity()
    {
        float vals[16] = {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };
        return Mat4(vals);
    }

    Mat4& Mat4::Transform(Vec3 const& xyz)
    {
        m_Vals[ToIndex(0, 3)] += xyz.x;
        m_Vals[ToIndex(1, 3)] += xyz.y;
        m_Vals[ToIndex(2, 3)] += xyz.z;
        return *this;
    }

    Mat4& Mat4::Scale(Vec3 const& xyz)
    {
        m_Vals[ToIndex(0, 0)] *= xyz.x;
        m_Vals[ToIndex(1, 1)] *= xyz.y;
        m_Vals[ToIndex(2, 2)] *= xyz.z;
        return *this;
    }

    Mat4& Mat4::Rotate(Vec3 const& xyz)
    {
        float sinG = std::sin(xyz.x);
        float sinB = std::sin(xyz.y);
        float sinA = std::sin(xyz.z);
        float cosG = std::cos(xyz.x);
        float cosB = std::cos(xyz.y);
        float cosA = std::cos(xyz.z);
        m_Vals[ToIndex(0, 0)] *= cosB * cosG;
        m_Vals[ToIndex(0, 1)] *= sinA * sinB * cosG - cosA * sinG;
        m_Vals[ToIndex(0, 2)] *= cosA * sinB * cosG + sinA * sinG;
        m_Vals[ToIndex(1, 0)] *= cosB * sinG;
        m_Vals[ToIndex(1, 1)] *= sinA * sinB * sinG + cosA * cosG;
        m_Vals[ToIndex(1, 2)] *= cosA * sinB * sinG - sinA * cosG;
        m_Vals[ToIndex(2, 0)] *= -sinB;
        m_Vals[ToIndex(2, 1)] *= sinA * cosB;
        m_Vals[ToIndex(2, 2)] *= cosA * cosB;
        return *this;
    }

    std::string Mat4::ToString() const
    {
        std::stringstream ss;
        ss << "[" << m_Vals[0] << ", " << m_Vals[1] << ", " << m_Vals[2] << ", " << m_Vals[3] << "]\n";
        ss << "[" << m_Vals[4] << ", " << m_Vals[5] << ", " << m_Vals[6] << ", " << m_Vals[7] << "]\n";
        ss << "[" << m_Vals[8] << ", " << m_Vals[9] << ", " << m_Vals[10] << ", " << m_Vals[11] << "]\n";
        ss << "[" << m_Vals[12] << ", " << m_Vals[13] << ", " << m_Vals[14] << ", " << m_Vals[15] << "]\n";
        return ss.str();
    }

    float Mat4::GetValue(int m, int n) const
    {
        return m_Vals[ToIndex(m, n)];
    }

    void Mat4::SetValue(int m, int n, float val)
    {
        m_Vals[ToIndex(m, n)] = val;
    }

    std::array<float, 16> Mat4::GetValuesArray() const
    {
        std::array<float, 16> vals;
        for (int i = 0; i < 16; i++) {
            vals[i] = m_Vals[i];
        }
        return vals;
    }

    Mat4 Mat4::operator*(float scalar) const
    {
        float vals[16];
        for (int i = 0; i < 16; i++) {
            vals[i] = m_Vals[i] * scalar;
        }
        return Mat4(vals);
    }

    Mat4& Mat4::operator*=(float scalar)
    {
        for (int i = 0; i < 16; i++) {
            m_Vals[i] *= scalar;
        }
        return *this;
    }

    Mat4 Mat4::operator/(float scalar) const
    {
        float vals[16];
        for (int i = 0; i < 16; i++) {
            vals[i] = m_Vals[i] / scalar;
        }
        return Mat4(vals);
    }

    Mat4& Mat4::operator/=(float scalar)
    {
        for (int i = 0; i < 16; i++) {
            m_Vals[i] /= scalar;
        }
        return *this;
    }

    Mat4 Mat4::operator+(Mat4 const& other) const
    {
        float vals[16];
        for (int i = 0; i < 16; i++) {
            vals[i] = m_Vals[i] + other.m_Vals[i];
        }
        return Mat4(vals);
    }

    Mat4 Mat4::operator+=(Mat4 const& other)
    {
        for (int i = 0; i < 16; i++) {
            m_Vals[i] += other.m_Vals[i];
        }
        return *this;
    }

    Mat4 Mat4::operator-(Mat4 const& other) const
    {
        float vals[16];
        for (int i = 0; i < 16; i++) {
            vals[i] = m_Vals[i] - other.m_Vals[i];
        }
        return Mat4(vals);
    }

    Mat4 Mat4::operator-=(Mat4 const& other)
    {
        for (int i = 0; i < 16; i++) {
            m_Vals[i] -= other.m_Vals[i];
        }
        return *this;
    }


    bool Mat4::operator==(Mat4 const& other) const
    {
        for (int i = 0; i < 16; i++) {
            if (m_Vals[i] != other.m_Vals[i]) {
                return false;
            }
        }
        return true;
    }

    bool Mat4::operator!=(Mat4 const& other) const
    {
        for (int i = 0; i < 16; i++) {
            if (m_Vals[i] == other.m_Vals[i]) {
                return false;
            }
        }
        return true;
    }

    Mat4 Mat4::operator*(Mat4 const& other) const
    {
        float vals[16];
        for (int m = 0; m < 4; m++) {
            for (int n = 0; n < 4; n++) {
                int i = ToIndex(m, n);
                int i1 = ToIndex(m, 0);
                int i2 = ToIndex(0, n);
                vals[i] = m_Vals[i1 + 0] * other.m_Vals[i2 + 0 * 4] +
                          m_Vals[i1 + 1] * other.m_Vals[i2 + 1 * 4] +
                          m_Vals[i1 + 2] * other.m_Vals[i2 + 2 * 4] +
                          m_Vals[i1 + 3] * other.m_Vals[i2 + 3 * 4];
            }
        }
        return Mat4(vals);
    }

    Mat4& Mat4::operator*=(Mat4 const& other)
    {
        float vals[16];
        for (int m = 0; m < 4; m++) {
            for (int n = 0; n < 4; n++) {
                int i = ToIndex(m, n);
                int i1 = ToIndex(m, 0);
                int i2 = ToIndex(0, n);
                vals[i] = m_Vals[i1 + 0] * other.m_Vals[i2 + 0 * 4] +
                          m_Vals[i1 + 1] * other.m_Vals[i2 + 1 * 4] +
                          m_Vals[i1 + 2] * other.m_Vals[i2 + 2 * 4] +
                          m_Vals[i1 + 3] * other.m_Vals[i2 + 3 * 4];
            }
        }

        for (int i = 0; i < 16; i++) {
            m_Vals[i] = vals[i];
        }

        return *this;
    }

    Vec4 Mat4::operator*(Vec4 const& vec) const
    {
        return Vec4(
            m_Vals[0]  * vec.x + m_Vals[1]  * vec.y + m_Vals[2]  * vec.z + m_Vals[3]  * vec.w,
            m_Vals[4]  * vec.x + m_Vals[5]  * vec.y + m_Vals[6]  * vec.z + m_Vals[7]  * vec.w,
            m_Vals[8]  * vec.x + m_Vals[9]  * vec.y + m_Vals[10] * vec.z + m_Vals[11] * vec.w,
            m_Vals[12] * vec.x + m_Vals[13] * vec.y + m_Vals[14] * vec.z + m_Vals[15] * vec.w
        );
    }

}
