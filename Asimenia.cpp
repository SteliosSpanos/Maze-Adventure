#include "Grigorakis.h"
#include "Asimenia.h"
#include <ncurses.h>
#include <cstdlib>
#include <vector>

Asimenia::Asimenia() : Entity() {}

Asimenia::Asimenia(const Maze& maze, const Position& _pos) : Entity(maze, _pos) {}

void Asimenia::moveToNext(const Position& newPos){
	mvaddch(pos.y, pos.x, ' ');
	pos = newPos;
	mvaddch(pos.y, pos.x, 'A');
}

void Asimenia::move(const Maze& maze){
	const int dx[] = {0, 0, 1, -1};
	const int dy[] = {1, -1, 0, 0};
	std::vector<Position> neighbors;
	for(int i = 0; i < 4; i++){
		int newx = pos.x + dx[i];
		int newy = pos.y + dy[i];
		Position newPos(newx, newy);
		if((maze.isEmpty(newPos) || maze.isTrap(newPos) || maze.isKey(newPos)) && !visited[newy][newx]){
			neighbors.emplace_back(newPos);
		}
	}
	if(!neighbors.empty()){
		Position next = neighbors[0];
		moveToNext(next);
		visited[pos.y][pos.x] = true;
		path.push(pos);
	}
	else{
		if(!path.empty()){
			Position back = path.top();
			path.pop();
			moveToNext(back);
		}
		else{
			resetVisited();
		}
	}
}
