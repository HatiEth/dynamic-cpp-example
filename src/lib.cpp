#include <stdio.h>
#include <GL/glew.h>

#include "share/gamestate.h"

extern "C" {
void initialize(gamestate* Gamestate)
{
    printf("initialize\n");
    Gamestate->x = 0.0f;
    Gamestate->y = .30f;
    Gamestate->color[0] = 1.0f;
    Gamestate->color[1] = 1.0f;
    Gamestate->color[2] = 0.0f;
    Gamestate->color[3] = 1.0f;
}

void execute(gamestate* Gamestate)
{
    float aspectRatio = (600.0f/800.0f);
    float fsize = 1.0f/30.0f;
    float dw = fsize * aspectRatio;
    float dh = fsize;
    const float GREY = 0.53333f;
    glClearColor(GREY, GREY, GREY, 1.0f);
    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
    float& x = Gamestate->x;
    float& y = Gamestate->y;

    x += 0.01f;
    if(x>1.1f)
    {
        x=-1.0f;
    }
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor4fv(Gamestate->color);
    glBegin(GL_TRIANGLE_STRIP);
    {
        glVertex2f(x-2*dw, y-dh);
        glVertex2f(x+2*dw, y-dh);
        glVertex2f(x-3*dw, y+dh);
        glVertex2f(x+dw, y+dh);
    }
    glEnd();
}

}

