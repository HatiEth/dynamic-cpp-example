#include <stdio.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "vertexbuffer.h"
#include "share/gamestate.h"

typedef glm::vec3 vec3;
typedef glm::vec2 vec2;

typedef glm::mat3 mat3;
typedef glm::mat4 mat4;


struct Vertex
{
    float x,y;
};


const float GREY = 0.53333f;
static float Test = 0.5f;
bool immediateMode = true;

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
    Gamestate->y = 0.0f;


    Gamestate->color[0] = 1.0f;
    Gamestate->color[1] = 0.0f;
    Gamestate->color[2] = 0.0f;
    Gamestate->color[3] = 1.0f;

    float dw = 20.f;
    float dh = 20.f;

    std::vector<Vertex> vertices;
    Vertex v = {-dw, -dh};
    vertices.push_back(Vertex{-dw, -dh});
    vertices.push_back(Vertex{+dw, -dh});
    vertices.push_back(Vertex{-dw, +dh});
    vertices.push_back(Vertex{+dw, +dh});
    Gamestate->meshVertices = eth::gl::createBufferFromVector(GL_ARRAY_BUFFER, GL_STATIC_DRAW, vertices);
}

void execute(gamestate* Gamestate)
{
    float aspectRatio = (float(Gamestate->PhysicalResolution.windowHeight)/Gamestate->PhysicalResolution.windowWidth);
    float fsize = 1.0f/20.0f;
    float dw = fsize * aspectRatio;
    float dh = fsize;
    glViewport(0, 0, Gamestate->PhysicalResolution.windowWidth, Gamestate->PhysicalResolution.windowHeight);
    glClearColor(GREY, GREY, GREY, 1.0f);
    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
    glColor4fv(Gamestate->color);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
#if 0
    float& x = Gamestate->x;
    float& y = Gamestate->y;

    x += 0.03f;
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
#else
    float& x = Gamestate->x;
    x += 5.f;
    if(x>Gamestate->PhysicalResolution.windowWidth*0.5f)
    {
        x=-Gamestate->PhysicalResolution.windowWidth*0.5f;
    }

    mat4 ProjectionMatrix = glm::ortho<float>(0.0f, float(Gamestate->PhysicalResolution.windowWidth), 0.0f, float(Gamestate->PhysicalResolution.windowHeight), -1000.f, +1000.f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMultMatrixf(glm::value_ptr(ProjectionMatrix));
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    mat4 TranslateMatrix = glm::translate(mat4(1.f), vec3(Gamestate->PhysicalResolution.windowWidth, Gamestate->PhysicalResolution.windowHeight, 0)*0.5f);
    glLoadIdentity();
    glMultMatrixf(glm::value_ptr(TranslateMatrix));
    glPushMatrix();
    glMultMatrixf(glm::value_ptr(glm::translate(mat4(1.f), vec3(Gamestate->x, Gamestate->y, 0))));

    ///TODO(hati): provide fix for reload of vertexBuffer -> (provide in gamestate)
    glBindBuffer(GL_ARRAY_BUFFER, Gamestate->meshVertices);
    glVertexPointer(2, GL_FLOAT, 0, NULL);
    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glColor4f(1,1,1,1);
    glPointSize(5.f);
    glDrawArrays(GL_POINTS, 0, 4);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
#endif
}

}

