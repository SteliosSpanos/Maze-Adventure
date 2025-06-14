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
	virtual ~Entity() = default;

	virtual void move(const Maze& maze) = 0;
	virtual void moveToNext(const Position& newPos) = 0;
	virtual void displayHasKey(const Maze& maze) const = 0;
	virtual void displayIsTrapped(const Maze& maze) const = 0;
	void moveTo(const Maze& maze, const Position& p);

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
