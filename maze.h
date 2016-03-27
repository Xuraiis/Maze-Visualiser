/*
 * Maze.h
 *
 *  Created on: 24 Mar 2016
 *      Author: Nathan
 */

#ifndef MAZE_H_
#define MAZE_H_

#include <chrono>
#include <cmath>
#include <iostream>
 
#include "sdlwindow.h"
#include "xorshift.h"

static const int DIR_N = 1;
static const int DIR_S = 2;
static const int DIR_W = 4;
static const int DIR_E = 8;

static const int N = 0;
static const int S = 1;
static const int W = 2;
static const int E = 3;

const int dirEnc[4]{DIR_N, DIR_S, DIR_W, DIR_E};

class Maze {

// private:
	// int x0 = 0, y0 = 0, x1 = 0, y1 = 0;
	// bool n = 0, s = 0, w = 0, e = 0;

protected:
	// int x0, y0, x1, y1;
	// bool n, s, w, e;

	XOrShift xors;
	int *walls;
	int *dist;
	bool *actv;

public:
	const int dirShift[4];
	const int x_size;
	const int y_size;
	const int size;

	Maze(int arg_x_size, int arg_y_size, long seed);
	virtual ~Maze();

	int to_x(int pos);
	int to_y(int pos);
	int to_pos(int x, int y);
	int shift_pos(int pos, int dir);
	int dir_opp(int dir);
	// bool pos_in_range(int pos);

	void set_active(int pos, bool active);

	void open(int pos, int dir);
	void open_adj_points(int pos1, int pos2);

	bool is_dir_open(int pos, int dir);
	bool is_free(int pos);
	bool dir_in_bounds(int pos, int dir);
	bool is_dir_free(int pos, int dir);

	// void sdl_paint_cell(SDLWindow *window, int pos, int pathWidth);
	void sdl_paint_all(SDLWindow *window, int path_width);
	void sdl_paint_count(SDLWindow *window, float div);

	void generate();

	//override
	virtual bool has_next_step();
	virtual void setup_first_step();
	virtual void step_maze();
};


// void sdl_paint_cell(SDLWindow *window, int x, int y, int encode_dir, int pathWidth, int r, int g, int b);

#endif /* MAZE_H_ */
