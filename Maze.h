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
	bool trapUsed;
	Position key;
public:
	Maze(const std::string& filename);

	void drawMaze() const;
	void setTile(const Position& _pos, char ch);

	bool areNeighbors(const Position& pos1, const Position& pos2) const;
	bool isWall(const Position& _pos) const;
	bool isEmpty(const Position& _pos) const;
	bool isExit(const Position& _pos) const;
	bool isKey(const Position& _pos) const;
	bool isTrap(const Position& _pos) const;
	bool isValid(const Position& _pos) const;

	void useTrap();

	int getHeight() const;
	int getWidth() const;
	Position getExit() const;
	Position getKey() const;
	Position getTrap() const;
};
