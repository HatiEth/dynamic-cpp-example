#ifndef PLATTFORMLAYER_H
#define PLATTFORMLAYER_H

#include <SDL2/SDL.h>

#define BYTES(x) (x)
#define KILOBYTES(x) (BYTES(x)<<10)
#define MEGABYTES(x) (KILOBYTES(x)<<10)
#define GIGABYTES(x) (MEGABYTES(x)<<10)

#define BYTES_TO_KILOBYTES(x) (x/1024.0f)
#define BYTES_TO_MEGABYTES(x) (BYTES_TO_KILOBYTES(x)/1024.0f)
#define BYTES_TO_GIGABYTES(x) (BYTES_TO_MEGABYTES(x)/1024.0f);

struct SDL2
{
    SDL_Window* sdlWindow{nullptr};
    SDL_GLContext sdl_glContext;
};


SDL2 initSDL_GL_Window(int windowWidth, int windowHeight);

#endif // PLATTFORMLAYER_H
