

# Dynamically get Homebrew prefix
BREW_PREFIX := $(shell brew --prefix)

CXX = clang++
CXXFLAGS = -std=c++17 -Wall -I./include -I$(BREW_PREFIX)/include

CC = clang
CFLAGS = -Wall -I./include

LDFLAGS = -L$(BREW_PREFIX)/lib -lglfw \
          -framework OpenGL \
          -framework Cocoa \
          -framework IOKit \
          -framework CoreVideo

all: opengl_app

opengl_app: Callbacks.o m.o glad.o PVMat.o InitShaders.o vertex_shader.glsl fragment_shader.glsl Tux.hpp PVmat.hpp
	$(CXX) Callbacks.o InitShaders.o PVMat.o m.o glad.o -o opengl_app $(LDFLAGS)

Callbacks.o: Callbacks.cpp
	$(CXX) $(CXXFLAGS) -c Callbacks.cpp -o Callbacks.o

m.o: m.cpp
	$(CXX) $(CXXFLAGS) -c m.cpp -o m.o

glad.o: ./src/glad.c
	$(CC) $(CXXFLAGS) -c ./src/glad.c -o glad.o

PVMat.o: PVMat.cpp
	$(CC) $(CXXFLAGS) -c ./PVMat.cpp -o PVMat.o

InitShaders.o: InitShaders.cpp
	$(CC) $(CXXFLAGS) -c ./InitShaders.cpp -o InitShaders.o


tux: Tux.cpp
	$(CC) $(CXXFLAGS) $(LDFLAGS) ./Tux.cpp -o test


clean:
	rm -f *.o opengl_app
