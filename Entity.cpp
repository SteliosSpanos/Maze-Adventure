#include "Entity.h"
#include "Maze.h"
#include <cstdlib>
#include <ctime>
#include <ncurses.h>
#include <algorithm>

Entity::Entity() {}

Entity::Entity(const Maze& maze, const Position& _pos) : hasKey(false), trapped(false), pos(_pos) {
	visited.resize(maze.getHeight(), std::vector<bool>(maze.getWidth(), false));
	visited[pos.y][pos.x] = true;
}

void Entity::moveToExit(const Maze& maze, const Position& exit){
	const int dx[] = {0, 0, -1, 1};
	const int dy[] = {1, -1, 0, 0};
	Position current = getPosition();
	Position optimalMove = current;
	int minDistance = std::abs(exit.x - current.x) + std::abs(exit.y - current.y);
	for(int i = 0; i < 4; i++){
		int newx = pos.x + dx[i];
		int newy = pos.y + dy[i];
		Position neighbor(newx, newy);
		if(!maze.isWall(neighbor)){
			int distance = std::abs(exit.x - newx) + std::abs(exit.y - newy);
			if(distance < minDistance){
				minDistance = distance;
				optimalMove = neighbor;
			}
		}
	}
	if(optimalMove != current){
		moveToNext(optimalMove);
	}
}

void Entity::resetVisited(){
	for(int i = 0; i < visited.size(); i++){
		for(int j = 0; j < visited[i].size(); j++){
			visited[i][j] = false;
		}
	}
	visited[pos.y][pos.x] = true;
}

Position Entity::getPosition() const{
	return pos;
}

bool Entity::carriesKey() const{
	return hasKey;
}

void Entity::pickupKey(){
	hasKey = true;
}

void Entity::useKey(){
	hasKey = false;
}

bool Entity::isTrapped() const{
	return trapped;
}

void Entity::setTrapped(bool t){
	trapped = t;
}
