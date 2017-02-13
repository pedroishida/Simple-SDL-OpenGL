#ifndef CANVAS_H
#define CANVAS_H

#include <cstdio>
#include <cmath>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>

#define CANVAS_KEY_EMPTY -1
#define CANVAS_KEY_SPACE 1

class Canvas
{
    unsigned int i, j;
    unsigned int width;
    unsigned int height;
    double xScale, yScale;
    double xTrans, yTrans;
    int error_code;
    SDL_Window* display;
    SDL_Event event;
    SDL_GLContext context;
    protected:
        int Init();
        bool InitGL();
        void Quit();
    public:
        Canvas();
        Canvas(unsigned int, unsigned int);
        ~Canvas();
        unsigned short int HandleEvents();
        void Clear(
            unsigned short int = 255,
            unsigned short int = 255,
            unsigned short int = 255
        );
        void Show();
        int GetError();
        void DrawPolygon(double (*)[2], unsigned int);
};
#endif
