#pragma once

namespace Renderer {

    class Mat4
    {
    public:
        Mat4();
        Mat4(float values[4][4]);

        ~Mat4() = default;

    private:
        float m_Vals[4][4];
    };

}
