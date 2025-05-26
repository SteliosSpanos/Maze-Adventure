#pragma once

#include <stack>
#include <vector>
#include "Maze.h"
#include "Position.h"

class Entity{
private:
	std::vector<std::vector<bool>> visited;
	std::stack<Position> path;
	bool hasKey;
	bool trapped;
	Position pos;
public:
	Entity();
	Entity(const Maze& maze, const Position& p);

	virtual void move(const Maze& maze) = 0;
	virtual void moveToNext(const Position& newPos) = 0;
	void moveToExit(const Maze& maze, const Position& exit);

	void pushPath(const Position& p);
	void popPath();
	bool isPathEmpty() const;
	Position getPathTop() const;

	void setVisited(const Position& p, bool value);
	bool isVisited(const Position& p) const;

	bool carriesKey() const;
	void pickupKey();
	void useKey();
	bool isTrapped() const;
	void setTrapped(bool t);
	void setPosition(const Position& p);
	Position getPosition() const;

	void resetVisited();
};
