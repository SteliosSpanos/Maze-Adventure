#pragma once
#include "Entity.h"
#include "Maze.h"

class Grigorakis : public Entity{
public:
	Grigorakis();
	Grigorakis(const Maze& maze, const Position& _pos);
	void move(const Maze& maze) override;
	void moveToNext(const Position& newPos) override;
	void displayHasKey(const Maze& maze) const override;
	void displayIsTrapped(const Maze& maze) const override;
};
