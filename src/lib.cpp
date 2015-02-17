#include <stdio.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include "vertexbuffer.h"
#include "share/gamestate.h"

static float Test = 0.5f;
static GLuint vertexBuffer;

struct Vertex
{
    float x,y;
};

float aspectRatio = (600.0f/800.0f);
float fsize = 1.0f/20.0f;
float dw = fsize * aspectRatio;
float dh = fsize;
bool immediateMode = false;

extern "C" {

void initialize(gamestate* Gamestate)
{
    printf("initialize\n");
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
          /* Problem: glewInit failed, something is seriously wrong. */
          printf("Error: %s\n", glewGetErrorString(err));
    }

    Gamestate->x = 0.0f;
    Gamestate->y = .30f;


    Gamestate->color[0] = 1.0f;
    Gamestate->color[1] = 0.0f;
    Gamestate->color[2] = 0.0f;
    Gamestate->color[3] = 1.0f;



    std::vector<Vertex> vertices;
    Vertex v = {-dw, -dh};
    vertices.push_back(Vertex{-dw, -dh});
    vertices.push_back(Vertex{+dw, -dh});
    vertices.push_back(Vertex{-dw, +dh});
    vertices.push_back(Vertex{+dw, +dh});
    vertexBuffer = eth::gl::createBufferFromVector(GL_ARRAY_BUFFER, GL_STATIC_DRAW, vertices);
}

void execute(gamestate* Gamestate)
{
    const float GREY = 0.53333f;
    glClearColor(GREY, GREY, GREY, 1.0f);
    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
    glColor4fv(Gamestate->color);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if(immediateMode)
    {
        float& x = Gamestate->x;
        float& y = Gamestate->y;

        x += 0.01f;
        if(x>1.1f)
        {
            x=-1.0f;
        }
        glBegin(GL_TRIANGLE_STRIP);
        {
            glVertex2f(x-dw, y-dh);
            glVertex2f(x+dw, y-dh);
            glVertex2f(x-dw, y+dh);
            glVertex2f(x+dw, y+dh);
        }
        glEnd();
    }
    else
    {
        ///TODO(hati): provide fix for reload of vertexBuffer -> (provide in gamestate)
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glVertexPointer(2, GL_FLOAT, 0, NULL);
        glEnableClientState(GL_VERTEX_ARRAY);
        glDrawArrays(GL_TRIANGLES, 0, 4);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}

}

