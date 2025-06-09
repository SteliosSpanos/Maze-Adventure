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
	unsigned int rounds;
public:
	Simulation(const std::string& filename);
	void destroyMaze(Maze& maze);
	void headToExit();
	void run();
	void displayTime(const Maze& maze, unsigned int time) const;
	void gameOver(const Maze& maze) const;
};
