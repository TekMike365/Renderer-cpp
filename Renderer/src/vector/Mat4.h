#pragma once

#include <sstream>
#include <string>
#include <array>

namespace Renderer {

    class Mat4
    {
    public:
        Mat4();
        Mat4(float values[16]);

        ~Mat4() = default;

        static Mat4 Identity();
        static int ToIndex(int m, int n);

        std::string ToString() const;
        float GetValue(int m, int n) const;
        void SetValue(int m, int n, float val);
        std::array<float, 16> GetValuesArray() const;

    private:
        float m_Vals[16];
    };

}
