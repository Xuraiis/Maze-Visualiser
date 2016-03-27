/*
 * MazeGrowingTree.h
 *
 *  Created on: 24 Mar 2016
 *      Author: Nathan
 */

#ifndef MAZEGROWINGTREE_H_
#define MAZEGROWINGTREE_H_

#include "maze.h"
#include "intlist.h"

class MazeGrowingTree : public Maze {

protected:
	int current;

	IntList *tempPos;
	IntList *tempDir;
	IntList *active;

public:
	MazeGrowingTree(int arg_x_size, int arg_y_size, long arg_seed);
	virtual ~MazeGrowingTree();

	//override
	virtual bool has_next_step() override;
	virtual void setup_first_step() override;
	virtual void step_maze() override;
};

#endif /* MAZEGROWINGTREE_H_ */
