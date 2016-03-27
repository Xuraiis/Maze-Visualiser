/*
 * Maze.cpp
 *
 *  Created on: 24 Mar 2016
 *      Author: Nathan
 */

#include "maze.h"

Maze::Maze(int arg_x_size, int arg_y_size, long seed)
	: x_size(arg_x_size)
	, y_size(arg_y_size)
	, size(arg_x_size * arg_y_size)
	, dirShift{-arg_x_size, arg_x_size, -1, 1}
	, xors(seed)
{
	std::cout << x_size << "x" << y_size << "maze created with seed: " << seed << std::endl;
	walls = new int[size]{0};
	dist = new int[size]{0};
	actv = new bool[size]{0};
	// walls = {};
	// dist = {};
	// actv = {};
}

Maze::~Maze() {
	std::cout << x_size << "x" << y_size << "maze being deleted." << std::endl;
	// delete xors;
	delete[] walls;
	delete[] dist;
	delete[] actv;
}

int Maze::to_x(int pos) {
	return pos % x_size;
}

int Maze::to_y(int pos) {
	return pos / x_size;
}

int Maze::to_pos(int x, int y) {
	return y * x_size + x;
}

int Maze::shift_pos(int pos, int dir) {
	return pos + dirShift[dir];
}

int Maze::dir_opp(int dir) {
	switch(dir) {
		case N: return S;
		case S: return N;
		case E: return W;
		case W: return E;
	}
	return dir;
}

void Maze::set_active(int pos, bool active) {
	actv[pos] = active;
}

void Maze::open(int pos, int dir) {
	walls[pos] |= dirEnc[dir];
}

void Maze::open_adj_points(int pos1, int pos2) {
    int diff = pos2 - pos1;
    int dir1, dir2;

    if (diff == dirShift[N]) { dir1 = N; dir2 = S; }
    else if (diff == dirShift[S]) { dir1 = S; dir2 = N; }
    else if (diff == dirShift[W]) { dir1 = W; dir2 = E; }
    else if (diff == dirShift[E]) { dir1 = E; dir2 = W; }
    else { return; }

    open(pos1, dir1);
    open(pos2, dir2);
}

bool Maze::is_dir_open(int pos, int dir) {
	return (walls[pos] & dirEnc[dir]) == dirEnc[dir];
}

bool Maze::is_free(int pos) {
	return walls[pos] == 0;
}

bool Maze::dir_in_bounds(int pos, int dir) {
	switch (dir) {
		case N : return (to_y(pos) > 0);
		case S : return (to_y(pos) < y_size-1);
		case W : return (to_x(pos) > 0);
		case E : return (to_x(pos) < x_size-1);
		default: return false;
	}
}

bool Maze::is_dir_free(int pos, int dir) {
	if( dir_in_bounds(pos, dir) ) {
		return is_free(shift_pos(pos, dir));
	}
	return false;
}

void Maze::sdl_paint_count(SDLWindow *window, float div) {
	if(window -> SCREEN_WIDTH < x_size || window -> SCREEN_HEIGHT < y_size)
		return;

	for (int i = 0; i < size; i++) {
		window -> setColorHSV(dist[i] / div, 0.5, 0.9);
		window -> setPixel(to_x(i), to_y(i));
	}
}

int temp_x0 = 0, temp_y0 = 0, temp_x1 = 0, temp_y1 = 0;

void Maze::sdl_paint_all(SDLWindow *window, int path_width) {
	window->clear();

	for(int pos = 0; pos < size; pos++) {
		temp_x0 = to_x(pos) * (path_width + 1);
		temp_y0 = to_y(pos) * (path_width + 1);
		temp_x1 = temp_x0 + path_width + 1;
		temp_y1 = temp_y0 + path_width + 1;

		if(walls[pos] == 0 && !actv[pos]) {
			window -> setColor(0xCC, 0xCC, 0xCC);
			window -> fillRect(temp_x0+1, temp_y0+1, path_width, path_width);
		} else {
			if (actv[pos]) {
				window -> setColor(0xDE, 0xCA, 0xFF);
				window -> fillRect(temp_x0, temp_y0, path_width+1, path_width+1);
			}
			window -> setColor(0x00, 0x00, 0x00);
			if ( !(walls[pos] & dirEnc[N]) ) window -> drawLine(temp_x0, temp_y0, temp_x1, temp_y0);
			if ( !(walls[pos] & dirEnc[S]) ) window -> drawLine(temp_x0, temp_y1, temp_x1, temp_y1);
			if ( !(walls[pos] & dirEnc[W]) ) window -> drawLine(temp_x0, temp_y0, temp_x0, temp_y1);
			if ( !(walls[pos] & dirEnc[E]) ) window -> drawLine(temp_x1, temp_y0, temp_x1, temp_y1);
		}
	}
}

void Maze::generate() {
	long old_time = time(0);
	while(has_next_step()) {
		step_maze();
	}
	std::cout << "Finished maze generation in: " << time(0) - old_time << "ms" << std::endl;
}

bool Maze::has_next_step() { return 0; };
void Maze::setup_first_step() {};
void Maze::step_maze() {};
