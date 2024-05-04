#include "Mat4.h"

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

}
