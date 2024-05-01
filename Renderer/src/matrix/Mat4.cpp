#include "Mat4.h"

Renderer::Mat4::Mat4()
    : m_Vals({ 0.0f })
{
}

Renderer::Mat4::Mat4(float values[4][4])
    : m_Vals({ 0.0f })
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            m_Vals[i][j] = values[i][j];
        }
    }
}
