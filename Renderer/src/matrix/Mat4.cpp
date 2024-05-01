#include "Mat4.h"

namespace Renderer {

    Mat4::Mat4()
        : m_Vals { 0.0f }
    {
    }

    Mat4::Mat4(float values[4][4])
        : m_Vals { 0.0f }
    {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                m_Vals[i][j] = values[i][j];
            }
        }
    }

    Mat4 Mat4::Identity()
    {
        float vals[4][4] = {
            {1.0f, 0.0f, 0.0f, 0.0f},
            {0.0f, 1.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 1.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}
        };
        return Mat4(vals);
    }

    std::string Mat4::ToString() const
    {
        std::stringstream ss;
        ss << "[" << m_Vals[0][0] << ", " << m_Vals[0][1] << ", " << m_Vals[0][2] << ", " << m_Vals[0][3] << "]\n";
        ss << "[" << m_Vals[1][0] << ", " << m_Vals[1][1] << ", " << m_Vals[1][2] << ", " << m_Vals[1][3] << "]\n";
        ss << "[" << m_Vals[2][0] << ", " << m_Vals[2][1] << ", " << m_Vals[2][2] << ", " << m_Vals[2][3] << "]\n";
        ss << "[" << m_Vals[3][0] << ", " << m_Vals[3][1] << ", " << m_Vals[3][2] << ", " << m_Vals[3][3] << "]";
        return ss.str();
    }

}
