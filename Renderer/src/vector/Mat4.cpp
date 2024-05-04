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

    int Mat4::ToIndex(int m, int n)
    {
        return m * 4 + n;
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

}
