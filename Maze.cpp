#include "Maze.h"
#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>
#include <algorithm>

Maze::Maze(const std::string& filename) : trapUsed(false), trap2Used(false) {
	std::ifstream file(filename);
        std::string line;
	srand(time(nullptr));

        while(std::getline(file, line)){
        	maze.push_back(line);
        }
	file.close();

        rows = (int)maze.size();
        cols = maze.empty() ? 0 : (int)maze[0].size();

	std::vector<Position> availablePos;
	for(int y = 0; y < rows; y++){
		for(int x = 0; x < cols; x++){
			if(!isWall(Position(x, y))){
				availablePos.emplace_back(x, y);
			}
		}
	}

	int keyIdx = rand() % availablePos.size();
	setTile(availablePos[keyIdx], 'K');
	key = availablePos[keyIdx];
	availablePos.erase(availablePos.begin() + keyIdx);

	int trapIdx = rand() % availablePos.size();
	setTile(availablePos[trapIdx], 'T');
	trap = availablePos[trapIdx];
	availablePos.erase(availablePos.begin() + trapIdx);

	int trap2Idx = rand() % availablePos.size();
	setTile(availablePos[trap2Idx], 'T');
	trap2 = availablePos[trap2Idx];
	availablePos.erase(availablePos.begin() + trap2Idx);

	int exitIdx = rand() % availablePos.size();
	setTile(availablePos[exitIdx], 'L');
	exit = availablePos[exitIdx];
}

void Maze::drawMaze() const {
	for(int y = 0; y < rows; y++){
		attron(COLOR_PAIR(1));
		mvprintw(y, 0, "%s", maze[y].c_str());
		attroff(COLOR_PAIR(1));
	}
	refresh();
}

bool Maze::isValid(const Position& p) const {
	return p.y >= 0 && p.y < maze.size() && p.x >= 0 && p.x < maze[p.y].size();
}

void Maze::setTile(const Position& p, char ch) {
	if(isValid(p)){
		maze[p.y][p.x] = ch;
	}
}

bool Maze::areNeighbors(const Position& p1, const Position& p2) const {
	return std::abs(p1.x - p2.x) <= 1 && std::abs(p1.y - p2.y) <= 1;
}

bool Maze::isWall(const Position& p) const {
	if(!isValid(p)){
		return true;
	}
	return maze[p.y][p.x] == '*';
}

bool Maze::isEmpty(const Position& p) const {
	if(!isValid(p)){
                return false;
        }
	return maze[p.y][p.x] == ' ';
}

bool Maze::isExit(const Position& p) const {
	if(!isValid(p)){
		return false;
	}
	return p == exit;
}

bool Maze::isKey(const Position& p) const {
	if(!isValid(p)){
		return false;
	}
	return p == key;
}

bool Maze::isTrap(const Position& p) const {
	if(!isValid(p)){
		return false;
	}
	return (p == trap && !trapUsed) || (p == trap2 && !trap2Used);
}

void Maze::useTrap(const Position& p) {
	if(p == trap){
		trapUsed = true;
		setTile(p, 'C');
	}
	else if(p == trap2){
		trap2Used = true;
		setTile(p, 'C');
	}
}

int Maze::getHeight() const {
	return rows;
}

int Maze::getWidth() const {
	return cols;
}

Position Maze::getExit() const {
	return exit;
}

Position Maze::getKey() const {
	return key;
}

Position Maze::getTrap() const {
	return trap;
}

Position Maze::getTrap2() const {
	return trap2;
}


