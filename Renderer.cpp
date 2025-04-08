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
    depthData = new float[SIZE[0] * SIZE[1]];
    for(int i = 0; i < SIZE[0] * SIZE[1]; i++) {
        depthData[i] = 1.0f;
        //cout << depthData[i] << ", ";
    }
    //cout << endl << endl;
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

float Renderer::EdgeFunction(float x1, float x2, float y1, float y2, float x, float y) {
    return (x1 - x2) * (y - y1) - (y1 - y2) * (x - x1);
}

void Renderer::RenderTriangle(float x1, float y1,float x2, float y2, float x3, float y3, float z1, float z2, float z3, char ARGB[3][4]) {
    x1 = (x1 + 1) * sizes[0] * 0.5f;
    x2 = (x2 + 1) * sizes[0] * 0.5f;
    x3 = (x3 + 1) * sizes[0] * 0.5f;

    y1 = (y1 + 1) * sizes[1] * 0.5f;
    y2 = (y2 + 1) * sizes[1] * 0.5f;
    y3 = (y3 + 1) * sizes[1] * 0.5f;

    int minx = min(min(x1, x2), x3);
    int maxx = max(max(x1, x2), x3);
    int miny = min(min(y1, y2), y3);
    int maxy = max(max(y1, y2), y3);

    minx = max(minx, 0);
    maxx = min(maxx, sizes[0] - 1);
    miny = max(miny, 0);
    maxy = min(maxy, sizes[1] - 1);

    float dx12 = x1 - x2;
    float dx23 = x2 - x3;
    float dx31 = x3 - x1;
    float dy12 = y1 - y2;
    float dy23 = y2 - y3;
    float dy31 = y3 - y1;

    bool t1 = dy12 < 0 || (dy12 == 0 && dx12 > 0);
    bool t2 = dy23 < 0 || (dy23 == 0 && dx23 > 0);
    bool t3 = dy31 < 0 || (dy31 == 0 && dx31 > 0);

    for(int y = miny; y <= maxy; y++){
        for(int x = minx; x <= maxx; x++){
            float e1 = EdgeFunction(x1,x2,y1,y2,x,y);
            float e2 = EdgeFunction(x2,x3,y2,y3,x,y);
            float e3 = EdgeFunction(x3,x1,y3,y1,x,y);

            //if((e1 > 0) && (e2 > 0) && (e3 > 0)){
            if((e1 > 0 || (e1 == 0 && t1)) && (e2 > 0 || (e2 == 0 && t2)) && (e3 > 0 || (e3 == 0 && t3))){
                float l1 = (((y2-y3) * (x-x3)) + ((x3-x2) * (y-y3))) / (((y2-y3) * (x1-x3)) + ((x3-x2) * (y1-y3)));
                float l2 = (((y3-y1) * (x-x3)) + ((x1-x3) * (y-y3))) / (((y3-y1) * (x2-x3)) + ((x1-x3) * (y2-y3)));
                float l3 = 1.0f - l1 - l2;

                char finalColor[4];
                float c1[4],c2[4],c3[4];

                for(int i = 0; i < 4; i++) {
                    finalColor[i] = (char)(l1 * (unsigned char)ARGB[0][i] +
                                           l2 * (unsigned char)ARGB[1][i] +
                                           l3 * (unsigned char)ARGB[2][i]);
                }
                float depth = (l1 * z1) + (l2 * z2) + (l3 * z3);
                if(depth < depthData[y * sizes[0] + x]) {
                    SetPixel(x, y, finalColor);
                    //SetPixel(x, y, ARGB[0]);
                    SetDepth(x, y, depth);
                }
            }
        }
    }
}

void Renderer::SetPixel(int x, int y, char *ARGB) {
    //if (x < 0 || x >= sizes[0] || y < 0 || y >= sizes[1]) return;
    int index = (y * sizes[0] + x) * 4;
    pixelData[index + 0] = ARGB[3]; // Blue
    pixelData[index + 1] = ARGB[2]; // Green
    pixelData[index + 2] = ARGB[1]; // Red
    pixelData[index + 3] = ARGB[0]; // Alpha
}

void Renderer::SetDepth(int x, int y, float depth) {
    if (x < 0 || x >= sizes[0] || y < 0 || y >= sizes[1]) return;
    int index = (y * sizes[0] + x);
    depthData[index] = depth;
}

