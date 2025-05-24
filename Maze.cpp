#include "Maze.h"
#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>
#include <algorithm>

Maze::Maze(const std::string& filename) : trapUsed(false) {
	std::ifstream file(filename);
        std::string line;
	srand(time(nullptr));

        while(std::getline(file, line)){    //Read maze from file
        	maze.push_back(line);
        }
	file.close();

        rows = maze.size();
        cols = maze.empty() ? 0 : maze[0].size();

	std::vector<Position> availablePos;
	for(int y = 0; y < rows; y++){
		for(int x = 0; x < cols; x++){
			if(!isWall(Position(x, y))){
				availablePos.emplace_back(x, y);
			}
		}
	}

	int keyIdx = rand() % availablePos.size();   //Initialize key
	setTile(availablePos[keyIdx], 'K');
	key = availablePos[keyIdx];
	availablePos.erase(availablePos.begin() + keyIdx);

	int trapIdx = rand() % availablePos.size();   //Initialize trap
	setTile(availablePos[trapIdx], 'T');
	trap = availablePos[trapIdx];
	availablePos.erase(availablePos.begin() + trapIdx);

	int exitIdx = rand() % availablePos.size();   //Initialize exit
	setTile(availablePos[exitIdx], 'L');
	exit = availablePos[exitIdx];
}

void Maze::drawMaze() const{
	for(size_t y = 0; y < maze.size(); y++){
		mvprintw(y, 0, "%s", maze[y].c_str());
	}
	refresh();
}

bool Maze::isValid(const Position& _pos) const{     //Function for checking the position
	return _pos.y >= 0 && _pos.y < maze.size() && _pos.x >= 0 && _pos.x < maze[_pos.y].size();
}

void Maze::setTile(const Position& _pos, char ch){
	if(isValid(_pos)){
		maze[_pos.y][_pos.x] = ch;
	}
}

bool Maze::areNeighbors(const Position& pos1, const Position& pos2) const{
	return std::abs(pos1.x - pos2.x) <= 1 && std::abs(pos1.y - pos2.y) <= 1;
}

bool Maze::isWall(const Position& _pos) const{
	if(!isValid(_pos)){
		return true;
	}
	return maze[_pos.y][_pos.x] == '#';
}

bool Maze::isEmpty(const Position& _pos) const{
	if(!isValid(_pos)){
                return false;
        }
	return maze[_pos.y][_pos.x] == ' ';
}

bool Maze::isExit(const Position& _pos) const{
	if(!isValid(_pos)){
		return false;
	}
	return maze[_pos.y][_pos.x] == 'L';
}

bool Maze::isKey(const Position& _pos) const{
	if(!isValid(_pos)){
		return false;
	}
	return maze[_pos.y][_pos.x] == 'K';
}

bool Maze::isTrap(const Position& _pos) const{
	if(!isValid(_pos)){
		return false;
	}
	return maze[_pos.y][_pos.x] == 'T' && !trapUsed;
}

void Maze::useTrap(){
	trapUsed = true;
}

int Maze::getHeight() const{
	return rows;
}

int Maze::getWidth() const{
	return cols;
}

Position Maze::getExit() const{
	return exit;
}

Position Maze::getKey() const{
	return key;
}

Position Maze::getTrap() const{
	return trap;
}


