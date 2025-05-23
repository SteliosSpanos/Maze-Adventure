#pragma once
#include "Entity.h"
#include "Maze.h"

class Asimenia : public Entity{
public:
	Asimenia();
	Asimenia(const Maze& maze, const Position& _pos);
	void move(const Maze& maze) override;
	void moveToNext(const Position& newPos) override;
};
