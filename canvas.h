#ifndef CANVAS_H
#define CANVAS_H

#include <cstdio>
#include <cmath>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>

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
        template <typename xy>
        void DrawPolygon(xy*, unsigned int);
};

template <typename xy>
void Canvas::DrawPolygon(xy* vertices, unsigned int size)
{
    if (NULL != vertices && 0 < size) {
        glBegin(GL_POLYGON);
        for (i = 0; i < size; i++) {
            glVertex2f(vertices[i].x, vertices[i].y);
        }
        glEnd();
    }
}
#endif
