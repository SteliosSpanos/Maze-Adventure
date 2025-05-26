#include "Grigorakis.h"
#include "Asimenia.h"
#include <ncurses.h>
#include <cstdlib>
#include <vector>

Grigorakis::Grigorakis() : Entity() {}

Grigorakis::Grigorakis(const Maze& maze, const Position& _pos) : Entity(maze, _pos) {}

void Grigorakis::moveToNext(const Position& newPos){
	mvaddch(getPosition().y, getPosition().x, ' ');
	setPosition(newPos);     //No '=' overloading needed
	mvaddch(getPosition().y, getPosition().x, 'G');
}

void Grigorakis::move(const Maze& maze){
	const int dx[] = {0, 0, -1, 1};
	const int dy[] = {-1, 1, 0, 0};
	std::vector<Position> neighbors;
	for(int i = 0; i < 4; i++){
		int newx = getPosition().x + dx[i];
		int newy = getPosition().y + dy[i];
		Position newPos(newx, newy);
		if((maze.isEmpty(newPos) || maze.isTrap(newPos) || maze.isKey(newPos)) && !isVisited(newPos)){
			neighbors.emplace_back(newPos);
		}
	}
	if(!neighbors.empty()){
		Position next = neighbors[rand() % neighbors.size()];
		moveToNext(next);
		setVisited(getPosition(), true);
		pushPath(getPosition());
	}
	else{
		if(!isPathEmpty()){
			Position back = getPathTop();
			popPath();
			moveToNext(back);
		}
		else{
			resetVisited();
		}
	}
}
