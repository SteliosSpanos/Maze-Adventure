#include "Asimenia.h"
#include <ncurses.h>
#include <cstdlib>
#include <vector>

Asimenia::Asimenia() : Entity() {}

Asimenia::Asimenia(const Maze& maze, const Position& p) : Entity(maze, p) {}

void Asimenia::moveToNext(const Position& newPos) {
	mvaddch(getPosition().y, getPosition().x, ' ');
	setPosition(newPos);
	attron(COLOR_PAIR(2));
	mvaddch(getPosition().y, getPosition().x, 'A');
	attroff(COLOR_PAIR(2));
}

void Asimenia::move(const Maze& maze) {
	const int dx[] = {0, 0, 1, -1};
	const int dy[] = {1, -1, 0, 0};
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
		Position next = neighbors[0];
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
