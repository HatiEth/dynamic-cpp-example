#include "plattformlayer.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <cassert>

SDL2 initSDL_GL_Window(int windowWidth, int windowHeight)
{
    SDL2 sdl;

#ifdef _PW_DEBUG_
    std::setbuf(stdout, NULL); // used to always flush std::cout
#endif

    auto sdl_init_status = SDL_Init(SDL_INIT_EVENTS
                                     | SDL_INIT_JOYSTICK
                                     | SDL_INIT_GAMECONTROLLER);
    assert(sdl_init_status==0);
#if __unix__ // For personal debug reasons (otherwise destroys splitting)
    sdl.sdlWindow = SDL_CreateWindow("SampleWindow", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WindowFlags::SDL_WINDOW_SHOWN|SDL_WindowFlags::SDL_WINDOW_OPENGL);
#else
    sdl.sdlWindow = SDL_CreateWindow("SampleWindow", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WindowFlags::SDL_WINDOW_SHOWN|SDL_WindowFlags::SDL_WINDOW_OPENGL|SDL_WindowFlags::SDL_WINDOW_RESIZABLE);
#endif

    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);
    sdl.sdl_glContext = SDL_GL_CreateContext(sdl.sdlWindow);

    return sdl;
}
