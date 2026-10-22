

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

opengl_app: m.o glad.o
	$(CXX) m.o glad.o -o opengl_app $(LDFLAGS)

m.o: m.cpp
	$(CXX) $(CXXFLAGS) -c m.cpp -o m.o

glad.o: ./src/glad.c
	$(CC) $(CFLAGS) -c ./src/glad.c -o glad.o

clean:
	rm -f *.o opengl_app
