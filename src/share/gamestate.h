#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <GL/gl.h>

struct Viewport
{
    int windowWidth, windowHeight;
};

struct gamestate
{
    Viewport PhysicalResolution;

    float x, y;
    float color[4];

    GLuint meshVertices;
};

#endif //GAMESTATE_H


