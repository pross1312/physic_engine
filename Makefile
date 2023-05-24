CC=g++
CFLAGS=-Wall -Wextra -pedantic -std=c++20 `pkgconf --cflags sdl2 glew opengl` -ggdb
LIBS=`pkgconf --libs sdl2 glew opengl`
SRC=main.cpp Utils.cpp
default:
	$(CC) -o engine $(SRC) $(CFLAGS) $(LIBS)
