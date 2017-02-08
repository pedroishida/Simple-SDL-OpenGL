CPPFLAGS=-Wall -O3

build: openGL

openGL: openGL.cpp canvas.cpp -lGL -lGLU -lSDL2

.PHONY: clean
clean:
	-rm -f openGL
