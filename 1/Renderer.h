//
// Created by mbola on 3/20/2025.
//

#ifndef INC_1_RENDERER_H
#define INC_1_RENDERER_H

#include <iostream>

using namespace std;

class Renderer
{
public:
    Renderer(char ARGB[4], short SIZE[2]);
    ~Renderer();

    void Save();

    char header[18];
    short sizes[2];
    char* pixelData;
private:
};


#endif //INC_1_RENDERER_H
