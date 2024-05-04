#include "Renderer.h"

namespace Renderer {

    Pixel* screen = nullptr;

    int Init(int width, int height)
    {
        screen = new Pixel[width * height];
        if (screen == nullptr)
            return -1;

        return 0;
    }

    int Cleanup()
    {
        delete screen;
        return 0;
    }

}

