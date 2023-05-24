#include <SDL2/SDL.h>
#include <GL/glew.h>
#include "Utils.h"
#define FPS 60
int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;
    check(SDL_Init(SDL_INIT_VIDEO));
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
    SDL_Window* window = check(SDL_CreateWindow("gnout",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                SCREEN_WIDTH, SCREEN_HEIGHT,
                                SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI));
    int gl_ver_major, gl_ver_minor;
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &gl_ver_major);
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &gl_ver_minor);
    printf("OpenGL %d.%d\n", gl_ver_major, gl_ver_minor);
    SDL_GLContext context = check(SDL_GL_CreateContext(window));
    SDL_GL_MakeCurrent(window, context);
    if (GLEW_OK != glewInit()) {
        fprintf(stderr, "Can't init glew\n");
        exit(EXIT_FAILURE);
    }
    if (glDebugMessageCallback != NULL) {
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(MessageCallback, 0);
    }
    bool quit = false;
    SDL_Event event;
    while (!quit) {
        uint32_t start_tick = SDL_GetTicks(); // start tick for fps handle
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT: {
                quit = true;
            } break;
            }
        }
        SDL_GL_SwapWindow(window);
        uint32_t interval = SDL_GetTicks() - start_tick;
        if (interval < 1000 / FPS) {
            SDL_Delay(1000 / FPS - interval);
        }
    }
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    return 0;
}
