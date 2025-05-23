#pragma once

#include <stack>
#include <vector>
#include "Maze.h"
#include "Position.h"

class Entity{
protected:
	std::vector<std::vector<bool>> visited;
	std::stack<Position> path;
	bool hasKey;
	bool trapped;
	Position pos;
public:
	Entity();
	Entity(const Maze& maze, const Position& _pos);
	virtual void move(const Maze& maze) = 0;
	virtual void moveToNext(const Position& newPos) = 0;
	void moveToExit(const Maze& maze, const Position& exit);
	bool carriesKey() const;
	void pickupKey();
	void useKey();
	bool isTrapped() const;
	void setTrapped(bool t);
	Position getPosition() const;
};
