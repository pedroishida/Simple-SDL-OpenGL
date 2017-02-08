#include <cstdio>
#include <ctime>

#include "canvas.h"

typedef struct Vertex
{
    double x, y;
}Vertex;

int main(int argc, char** argv)
{
    unsigned int WIDTH = 800;
    unsigned int HEIGHT = 600;
    bool running = true;
    clock_t clockCounter;
    Canvas canvas(WIDTH, HEIGHT);
    Vertex triangle[3];

    if (0 != canvas.GetError()) {
        return 1;
    }

    triangle[0].x = 0.0;
    triangle[0].y = 0.5;
    triangle[1].x = 0.5;
    triangle[1].y = -0.5;
    triangle[2].x = -0.5;
    triangle[2].y = -0.5;

    while (running) {
        clockCounter = clock();
        running = canvas.HandleEvents();

        canvas.Clear();

        canvas.DrawPolygon(triangle, 3);

        canvas.Show();

        while (CLOCKS_PER_SEC / 60.0 > clock() - clockCounter) {}

        fprintf(
            stdout,
            "%.2g \r",
            ((float) CLOCKS_PER_SEC) / (clock() - clockCounter)
        );
        fflush(stdout);
    }

    return 0;
}
