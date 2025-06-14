#include "Entity.h"
#include "Maze.h"
#include <cstdlib>
#include <ctime>
#include <ncurses.h>
#include <algorithm>

Entity::Entity() {}

Entity::Entity(const Maze& maze, const Position& p) : hasKey(false), trapped(false), pos(p) {
	visited.resize(maze.getHeight(), std::vector<bool>(maze.getWidth(), false));
	visited[pos.y][pos.x] = true;
}

void Entity::moveTo(const Maze& maze, const Position& p) {
	const int dx[] = {0, 0, -1, 1};
	const int dy[] = {1, -1, 0, 0};
	Position current = pos;
	Position optimalMove = current;
	int minDistance = std::abs(p.x - current.x) + std::abs(p.y - current.y);
	for(int i = 0; i < 4; i++){
		int newx = pos.x + dx[i];
		int newy = pos.y + dy[i];
		Position neighbor(newx, newy);
		if(!maze.isWall(neighbor)){
			int distance = std::abs(p.x - newx) + std::abs(p.y - newy);
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

void Entity::pushPath(const Position& p) {
	path.push(p);
}

void Entity::popPath() {
	if(!path.empty()){
		path.pop();
	}
}

bool Entity::isPathEmpty() const {
	return path.empty();
}

Position Entity::getPathTop() const {
	return path.top();
}

void Entity::setVisited(const Position& p, bool value) {
	visited[p.y][p.x] = value;
}

bool Entity::isVisited(const Position& p) const {
	return visited[p.y][p.x];
}

void Entity::resetVisited() {
	for(int i = 0; i < visited.size(); i++){
		for(int j = 0; j < visited[i].size(); j++){
			visited[i][j] = false;
		}
	}
	visited[pos.y][pos.x] = true;
}

Position Entity::getPosition() const {
	return pos;
}

void Entity::setPosition(const Position& p) {
	pos = p;
}

bool Entity::carriesKey() const {
	return hasKey;
}

void Entity::pickupKey() {
	hasKey = true;
}

void Entity::useKey() {
	hasKey = false;
}

bool Entity::isTrapped() const {
	return trapped;
}

void Entity::setTrapped(bool t) {
	trapped = t;
}
