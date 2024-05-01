#pragma once

#include <sstream>
#include <string>

namespace Renderer {

    class Mat4
    {
    public:
        Mat4();
        Mat4(float values[4][4]);

        ~Mat4() = default;

        static Mat4 Identity();

        std::string ToString() const;

    private:
        float m_Vals[4][4];
    };

}
