#include <iostream>
#include <SDL2/SDL.h>
#include <cassert>
#include <memory>
#include <GL/gl.h>
#include <math.h>
#include <dlfcn.h>
#include "plattformlayer.h"

#include "../share/gamestate.h"
typedef void(*executionFunc_t)(gamestate* Gamestate);
typedef void(*initializeFunc_t)(gamestate* Gamestate);

// loads an .so file (since linux dlopen)
void* loadlib(const char* libpath)
{
    void* dll_handle = dlopen(libpath, RTLD_LAZY);
    if(dll_handle == NULL)
    {
        printf("%s not found %s!\n", libpath, dlerror());
    }
    return(dll_handle); 
}

// loads an exported initialize() function from an dynamic lib
initializeFunc_t loadInit(void*& dll_handle, const char* libpath)
{
    initializeFunc_t Result = nullptr;
    dlclose(dll_handle);
    dll_handle = loadlib(libpath);
    if(dll_handle)
    {
        Result = (initializeFunc_t) dlsym(dll_handle, "initialize");
        const char* dlsym_error = dlerror();
        if(dlsym_error)
        {
            printf("%s\n", dlsym_error);
        }
    }
    return(Result);
}

// loads an exported execute() function from an dynamic lib
executionFunc_t loadExecute(void*& dll_handle, const char* libpath)
{
    executionFunc_t execute = nullptr;
    dlclose(dll_handle);
    dll_handle = loadlib(libpath);
    if(dll_handle)
    {
        execute = (executionFunc_t) dlsym(dll_handle, "execute");
        const char* dlsym_error = dlerror();
        if(dlsym_error)
        {
            printf("%s\n", dlsym_error);
        }
    }
    return(execute);
}

int main(int argc, char** argv)
{
    // Convienance for initSDL_GL_Window
    int windowWidth     = 800;
    int windowHeight    = 600;


    SDL2 sdl = initSDL_GL_Window(windowWidth, windowHeight);
    SDL_Event event;
    
    float accumulator = 0.0f;
    float currentTime = SDL_GetTicks();
    bool quitFlag = false; 
   
    void* appLib = loadlib("./libApp.so");
    executionFunc_t execute = nullptr;
    initializeFunc_t initialize = nullptr;
    // Persistent "memory" << Host has to provide any memory, as libs are reallocated if reloaded
    // Actual game needs more data, plus viewport sizes and stuff (since window is probally resizeable later)
    gamestate Gamestate;

    // loading libs and initializing
    initialize = loadInit(appLib, "./libApp.so");
    execute = loadExecute(appLib, "./libApp.so");
    initialize(&Gamestate);

    // [BEG] Gameloop 
    while(!quitFlag)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_QUIT:
                quitFlag = true;
                break;
            case SDL_WINDOWEVENT_RESIZED:
                break;
            case SDL_KEYDOWN:
                {
                    // This code should be replaced by a filewatcher,
                    // -> watching for compilation of your app-lib so you don't have to rerun loadInit/loadExecute manually
                    // Though you probally want to execute initialize(..) manually - for reasons
                    if(event.key.state == SDL_PRESSED && event.key.repeat == 0)
                    {
                        if(event.key.keysym.scancode == SDL_SCANCODE_1)
                        {
                            initialize = loadInit(appLib, "./libApp.so");
                            initialize(&Gamestate);
                            execute = loadExecute(appLib, "./libApp.so");
                        }
                        if(event.key.keysym.scancode == SDL_SCANCODE_5)
                        {
                            execute = loadExecute(appLib, "./libApp.so");
                        }
                    }
                }
                break;
            }
        }

        int windowWidth, windowHeight;
        SDL_GetWindowSize(sdl.sdlWindow, &windowWidth, &windowHeight);

        // Advanced tick
        float lastTime = currentTime;
        currentTime = SDL_GetTicks();
        accumulator += (currentTime - lastTime);

        const float TIMER = 16.0f;
        while(accumulator >= TIMER)
        {
            accumulator -= TIMER;
            if(execute)
            {
                execute(&Gamestate);
            }
            SDL_GL_SwapWindow(sdl.sdlWindow);
        }

    }
    // [END] Gameloop
    SDL_GL_DeleteContext(sdl.sdl_glContext);
    SDL_DestroyWindow(sdl.sdlWindow);

    return(0);
}


