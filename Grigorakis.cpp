#include "Grigorakis.h"
#include <ncurses.h>
#include <cstdlib>
#include <vector>

Grigorakis::Grigorakis() : Entity() {}

Grigorakis::Grigorakis(const Maze& maze, const Position& _pos) : Entity(maze, _pos) {}

void Grigorakis::moveToNext(const Position& newPos) {
	mvaddch(getPosition().y, getPosition().x, ' ');
	setPosition(newPos);
	attron(COLOR_PAIR(2));
	mvaddch(getPosition().y, getPosition().x, 'G');
	attroff(COLOR_PAIR(2));
}

void Grigorakis::move(const Maze& maze) {
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
		for(size_t i = 0; i < neighbors.size(); i++){
			if(maze.isKey(neighbors[i])){
				Position next = neighbors[i];
				moveToNext(next);
			}
			else{
				Position next = neighbors[rand() % neighbors.size()];
				moveToNext(next);
			}
		}
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

void Grigorakis::displayHasKey(const Maze& maze) const {
	attron(COLOR_PAIR(1));
	mvprintw((maze.getHeight() / 3) + 1, maze.getWidth() + 10, "|| GRIGORAKIS HAS KEY ||");
	attroff(COLOR_PAIR(1));
}

void Grigorakis::displayIsTrapped(const Maze& maze) const {
	attron(COLOR_PAIR(1));
	mvprintw((maze.getHeight() / 3) + 2, maze.getWidth() + 10, "|| GRIGORAKIS IS TRAPPED ||");
	attroff(COLOR_PAIR(1));
}
