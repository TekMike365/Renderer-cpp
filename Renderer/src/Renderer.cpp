#include "Renderer.h"

#include <iostream>
#include <fstream>

namespace Renderer {

    Pixel* screen = nullptr;
    int screenWidth = 0;
    int screenHeight = 0;

    int Init(int width, int height)
    {
        screenWidth = width;
        screenHeight = height;
        screen = new Pixel[width * height];
        if (screen == nullptr)
            return 1;

        return 0;
    }

    int Cleanup()
    {
        delete screen;
        return 0;
    }

    void ToBinary(char* arr, uint32_t val)
    {
        for (int i = 0; i < 4; i++) {
            arr[i] = (val & 0xff << i * 8) >> i * 8;
        }
    }

    int SaveBMP(const char* filepath)
    {
        if (screen == nullptr)
            return 1;

        uint32_t r = (screenWidth * 3) % 4;
        uint32_t pad = r == 0 ? 0 : 4 - r;
        uint32_t row = screenWidth * 3 + pad;
        uint32_t dataSize = row * screenHeight;
        uint32_t fileSize = dataSize + 54;

        char data[fileSize];
        // BMP header
        data[0] = 'B';
        data[1] = 'M';                      // 2    ID field
        ToBinary(data + 2, fileSize);       // 4    Size of BMP file
        ToBinary(data + 6, 0);              // 2+2  Unused
        ToBinary(data + 10, 54);            // 4    Offset to pixel array
        // DIB header
        ToBinary(data + 14, 40);            // 4    DIB header size
        ToBinary(data + 18, screenWidth);   // 4    BMP width in pixels
        ToBinary(data + 22, screenHeight);  // 4    BMP height in pixels
        data[26] = 0x01;
        data[27] = 0x00;                    // 2    Number of color planes
        data[28] = 0x18;
        data[29] = 0x00;                    // 2    Number of bits pre pixel (BPP)
        ToBinary(data + 30, 0);             // 4    BI_RGB, pixel array compression (none)
        ToBinary(data + 34, dataSize);      // 4    Size of raw BMP data
        ToBinary(data + 38, 2835);          // 4    Horizontal resolution of the image (pixel prem meter)
        ToBinary(data + 42, 2835);          // 4    Vertical resolution of the image (pixel prem meter)
        ToBinary(data + 46, 0);             // 4    number of colors in palette
        ToBinary(data + 50, 0);             // 4    number of important colors (all)

        // Pixel Array
        char* pArr = data + 54;
        for (int i = 0; i < screenHeight; i++) {
            for (int j = 0; j < screenWidth; j++) {
                int si = screenWidth * i + j;
                Pixel p = screen[si];
                pArr[0] = p.b;
                pArr[1] = p.g;
                pArr[2] = p.r;
                pArr += 3;
            }
            
            for (int n = 0; n < pad; n++) {
                *pArr = 0;
                pArr++;
            }
        }

        std::ofstream file(filepath, std::ios::out | std::ios::binary | std::ios::trunc);
        if (!file)
            return 2;

        file.write(data, sizeof(data));
        if (file.bad())
            return 3;

        file.close();
        return 0;
    }
}

