/*
 * MazeGrowingTree.cpp
 *
 *  Created on: 24 Mar 2016
 *      Author: Nathan
 */

#include "mazegrowingtree.h"

MazeGrowingTree::MazeGrowingTree(int arg_x_size, int arg_y_size, long arg_seed)
	: Maze(arg_x_size, arg_y_size, arg_seed)
	, current(0)
{
	active = new IntList(size);
	tempPos = new IntList(4);
	tempDir = new IntList(4);
}

MazeGrowingTree::~MazeGrowingTree() {
	Maze::~Maze();
	delete active;
	delete tempDir;
	delete tempPos;
}


bool MazeGrowingTree::has_next_step() {
	return !active->is_empty();
}

void MazeGrowingTree::setup_first_step() {
	current = 0;
	int s_pos = xors.rand_to(x_size*y_size);
	current = s_pos;
	active->add( s_pos );
}

void MazeGrowingTree::step_maze() {
	current = active->last();

	tempPos->clear();
	tempDir->clear();

    if (is_dir_free(current, N)) {
        tempPos->add(shift_pos(current, N));
        tempDir->add(N);
    }
    if (is_dir_free(current, S)) {
        tempPos->add(shift_pos(current, S));
        tempDir->add(S);
    }
    if (is_dir_free(current, W)) {
        tempPos->add(shift_pos(current, W));
        tempDir->add(W);
    }
    if (is_dir_free(current, E)) {
        tempPos->add(shift_pos(current, E));
        tempDir->add(E);
    }

	if(!tempPos->is_empty()) {
		int index = xors.rand_to(tempDir->size());

		int dir = tempDir->get(index);
		int adj = tempPos->get(index);
		int dirAdj = dir_opp(dir);

		dist[adj] = dist[current] + 1;
		open_adj_points(current, adj);
		set_active(current, true);
		set_active(adj, true);

		active->add(adj);
	} else {
		active->pop();
		set_active(current, false);
	}
}
