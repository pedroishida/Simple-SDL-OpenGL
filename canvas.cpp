#include "canvas.h"

Canvas::Canvas()
{
    xScale = 1;
    yScale = 1;
    xTrans = 0;
    yTrans = 0;
    width = 640;
    height = 480;
    error_code = Init();
}

Canvas::Canvas(unsigned int w, unsigned int h)
{
    xScale = 1;
    yScale = 1;
    xTrans = 0;
    yTrans = 0;
    width = w;
    height = h;
    error_code = Init();
}

Canvas::~Canvas()
{
    Quit();
}

int Canvas::Init()
{
    if (0 > SDL_Init(SDL_INIT_VIDEO)) {
        std::fprintf(stderr,"SDL_Init failed:\n%s\n", SDL_GetError());
        return 1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    display = SDL_CreateWindow(
        "SDL OpenGL",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        width,
        height,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
    );
    if (NULL == display) {
        std::fprintf(stderr, "SDL_CreateWindow failed:\n%s\n", SDL_GetError());
        return 2;
    }

    context = SDL_GL_CreateContext(display);
    if (NULL == context) {
        std::fprintf(stderr, "SDL_GL_CreateContext failed:\n%s\n", SDL_GetError());
        return 3;
    }

    if (0 > SDL_GL_SetSwapInterval(1)) {
        std::fprintf(stderr, "SDL_GL_SetSwapInterval failed:\n%s\n", SDL_GetError());
    }

    if (!InitGL()) {
        return 4;
    }
    return 0;
}

bool Canvas::InitGL()
{
    GLenum error = GL_NO_ERROR;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    error = glGetError();
    if (GL_NO_ERROR != error) {
        std::fprintf(stderr, "GL_PROJECTION failed:\n%s\n", gluErrorString(error));
        return false;
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    error = glGetError();
    if (GL_NO_ERROR != error) {
        std::fprintf(stderr, "GL_MODELVIEW failed:\n%s\n", gluErrorString(error));
        return false;
    }

    glClearColor(0.0, 0.0, 0.0, 1.0);

    error = glGetError();
    if (GL_NO_ERROR != error) {
        std::fprintf(stderr, "glClearColor failed:\n%s\n", gluErrorString(error));
        return false;
    }

    return true;
}

unsigned short int Canvas::HandleEvents()
{
    while (SDL_PollEvent(&event)) {
        if (SDL_QUIT == event.type) {
            return 0;
        } else if (SDL_KEYUP == event.type) {
            if (SDLK_ESCAPE == event.key.keysym.sym) {
                return 0;
            } else if (SDLK_SPACE == event.key.keysym.sym) {
                return CANVAS_KEY_SPACE;
            }
        }
    }
    return CANVAS_KEY_EMPTY;
}

void Canvas::Clear(unsigned short r, unsigned short g, unsigned short b)
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void Canvas::Show()
{
    SDL_GL_SwapWindow(display);
}

void Canvas::Quit()
{
    SDL_DestroyWindow(display);
    SDL_Quit();
}

int Canvas::GetError()
{
    return error_code;
}

void Canvas::DrawPolygon(double (*vertices)[2], unsigned int size)
{
    if (NULL != vertices && 0 < size) {
        glBegin(GL_POLYGON);
        for (i = 0; i < size; i++) {
            glVertex2f(vertices[i][0], vertices[i][1]);
        }
        glEnd();
    }
}
