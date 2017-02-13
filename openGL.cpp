#include <cstdio>
#include <cstdlib>
#include <ctime>

#include "canvas.h"

using namespace std;

double unit_rand()
{
    return rand() * (2.0 / RAND_MAX) - 1;
}

int main(int argc, char** argv)
{
    unsigned int WIDTH = 800;
    unsigned int HEIGHT = 600;
    unsigned int polygon_size = 4;
    unsigned int i = 0;
    int running = CANVAS_KEY_EMPTY;
    clock_t clockCounter;
    Canvas canvas(WIDTH, HEIGHT);
    double polygon[polygon_size][2] = {
        {0.5, 0.5},
        {0.5, -0.5},
        {-0.5, -0.5},
        {-0.5, 0.5}
    };

    if (0 != canvas.GetError()) {
        return 1;
    }

    srand(time(NULL));

    while (running) {
        clockCounter = clock();
        running = canvas.HandleEvents();

        if (CANVAS_KEY_SPACE == running) {
            for (i = 0; i < polygon_size; i++) {
                polygon[i][0] = unit_rand();
                polygon[i][1] = unit_rand();
            }
        }

        canvas.Clear();

        canvas.DrawPolygon(polygon, polygon_size);

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
