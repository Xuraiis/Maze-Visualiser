//============================================================================
// Name        : Main.cpp
// Author      : Nathan
// Version     :
// Copyright   : n/a
// Description : Maze Generation
//============================================================================

#include <thread>
#include <chrono>
#include <stdlib.h>
#include <string.h>
#include <ctime>

#include "sdlwindow.h"
#include "mazegrowingtree.h"

int maze_w = 15;
int maze_h = 15;
long seed;
int wait_ms = 50;
int cell_size = 20;
bool instant = false;
bool color = false;
float color_gradient = 5;


int main(int argc, const char *argv[]) {

	seed = time(0);

	for(int i = 0; i < argc; i++) {
		if( strcmp(argv[i], "-w") == 0 ) {
			maze_w = atoi(argv[++i]);
		} else if ( strcmp(argv[i], "-h") == 0 ) {
			maze_h = atoi(argv[++i]);
		} else if ( strcmp(argv[i], "-seed") == 0 ) {
			seed = atoi(argv[++i]);
		} else if ( strcmp(argv[i], "-ms") == 0 ) {
			wait_ms = atoi(argv[++i]);
		} else if ( strcmp(argv[i], "-s") == 0 ) {
			cell_size = atoi(argv[++i]);
		} else if ( strcmp(argv[i], "-pregen") == 0 ) {
			instant = true;
		} else if ( strcmp(argv[i], "-color") == 0 ) {
			color = true;
		} else if ( strcmp(argv[i], "-cgrad") == 0 ) {
			color_gradient = atoi(argv[++i]);
		} 
	}

	int w = maze_w * (cell_size + 1) + 1;
	int h = maze_h * (cell_size + 1) + 1;

	if(color) {
		w = maze_w;
		h = maze_h;
	}

	SDLWindow *window;
	window = new SDLWindow(w, h);

	MazeGrowingTree *maze;
	maze = new MazeGrowingTree(maze_w, maze_h, seed);
	maze->setup_first_step();

	if(instant) {
		maze->generate();

		if(color) 	maze->sdl_paint_count(window, color_gradient);
		else 		maze->sdl_paint_all(window, cell_size);

		window->render();
	} else {
		while(maze->has_next_step() && !window->closed()) {
			maze->step_maze();

			if(color) 	maze->sdl_paint_count(window, color_gradient);
			else 		maze->sdl_paint_all(window, cell_size);

			window->render();

			if(wait > 0) std::this_thread::sleep_for(std::chrono::milliseconds(wait_ms));
		}
	}
	
	window->waitForClosed();
	window->sdl_close();

	return 0;
}
