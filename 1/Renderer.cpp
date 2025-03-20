#include <iostream>
#include <fstream>
#include "Renderer.h"

using namespace std;

Renderer::Renderer(char ARGB[4], short SIZE[2]){
    for (int i = 0; i < 18; i++) {
        header[i] = 0;
    }
    header[2] = 0x02;

    header[12] = (SIZE[0] & 0x00FF);
    header[13] = ((SIZE[0] & 0xFF00) / 256);

    header[14] = (SIZE[1] & 0x00FF);
    header[15] = ((SIZE[1] & 0xFF00) / 256);

    header[16] = 0x20;

    sizes[0] = SIZE[0];
    sizes[1] = SIZE[1];

    pixelData = new char[SIZE[0] * SIZE[1] * 4];
    for(int i = 0; i < SIZE[0] * SIZE[1]; i++){
        pixelData[i * 4 + 0] = ARGB[3];
        pixelData[i * 4 + 1] = ARGB[2];
        pixelData[i * 4 + 2] = ARGB[1];
        pixelData[i * 4 + 3] = ARGB[0];
    }
}

void Renderer::Save(){
    ofstream file("output.tga", ios::binary);
    file.write(header, 18);
    file.write(pixelData, sizes[0] * sizes[1] * 4);
    file.close();
}

Renderer::~Renderer() {
    delete[] pixelData;
}

