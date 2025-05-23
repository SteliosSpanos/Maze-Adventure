#include "Grigorakis.h"
#include "Asimenia.h"
#include <ncurses.h>
#include <cstdlib>
#include <vector>

Grigorakis::Grigorakis() : Entity() {}

Grigorakis::Grigorakis(const Maze& maze, const Position& _pos) : Entity(maze, _pos) {}

void Grigorakis::moveToNext(const Position& newPos){
	mvaddch(pos.y, pos.x, ' ');
	pos.x = newPos.x;
	pos.y = newPos.y;
	mvaddch(pos.y, pos.x, 'G');
}

void Grigorakis::move(const Maze& maze){
	const int dx[] = {0, 0, -1, 1};
	const int dy[] = {-1, 1, 0, 0};
	std::vector<Position> neighbors;
	for(int i = 0; i < 4; i++){
		int newx = pos.x + dx[i];
		int newy = pos.y + dy[i];
		if((maze.isEmpty(Position(newx, newy)) || maze.isTrap(Position(newx, newy)) || maze.isKey(Position(newx, newy))) && !visited[newy][newx]){
			neighbors.emplace_back(newx, newy);
		}
	}
	if(!neighbors.empty()){
		Position next = neighbors[rand() % neighbors.size()];
		moveToNext(next);
		visited[pos.y][pos.x] = true;
		path.push({pos.x, pos.y});
	}
	else{
		if(!path.empty()){
			Position back = path.top();
			path.pop();
			moveToNext(back);
		}
		else{
			for(int i = 0; i < visited.size(); i++){
				for(int j = 0; j < visited[i].size(); j++){
					visited[i][j] = false;
				}
			}
			visited[pos.y][pos.x] = true;
		}
	}
}
