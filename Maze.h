#pragma once

#include "Position.h"
#include <vector>
#include <string>

class Maze{
private:
	std::vector<std::string> maze;
	int rows;
	int cols;
	Position exit;
	Position trap;
	Position trap2;
	bool trapUsed;
	bool trap2Used;
	Position key;
public:
	Maze(const std::string& filename);

	void drawMaze() const;
	void setTile(const Position& p, char ch);

	bool areNeighbors(const Position& p1, const Position& p2) const;
	bool isWall(const Position& p) const;
	bool isEmpty(const Position& p) const;
	bool isExit(const Position& p) const;
	bool isKey(const Position& p) const;
	bool isTrap(const Position& p) const;
	bool isValid(const Position& p) const;

	void useTrap(const Position& p);

	int getHeight() const;
	int getWidth() const;
	Position getExit() const;
	Position getKey() const;
	Position getTrap() const;
	Position getTrap2() const;
};
