#pragma once
#include "Maze.h"
#include "Grigorakis.h"
#include "Asimenia.h"

class Simulation{
private:
	Maze maze;
	Grigorakis g;
	Asimenia a;
	bool met;
public:
	Simulation(const std::string& filename);
	void destroyMaze(Maze& maze);
	void run();
	void displayTime(const Maze& maze, unsigned int time) const;
};
