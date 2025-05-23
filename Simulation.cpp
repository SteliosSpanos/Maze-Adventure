#include "Simulation.h"
#include "Grigorakis.h"
#include "Asimenia.h"
#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <cmath>

Simulation::Simulation(const std::string& filename) : maze(filename), met(false) {
	srand(time(nullptr));
	int x1, y1;
	do{
		x1 = rand() % maze.getWidth();
		y1 = rand() % maze.getHeight();
	}while(maze.isWall(Position(x1, y1)));
	g = Grigorakis(maze, Position(x1, y1));
	int x2, y2;
	do{
		x2 = rand() % maze.getWidth();
		y2 = rand() & maze.getHeight();
	}while(maze.isWall(Position(x2, y2)) || (std::abs(x2 - x1) < 7 && std::abs(y2 - y1) < 7));
	a = Asimenia(maze, Position(x2, y2));
}

void Simulation::destroyMaze(Maze& maze){
	for(int y = 1; y < maze.getHeight() - 2; y++){
		for(int x = 1; x < maze.getWidth() - 2; x++){
			if(maze.isWall(Position(x, y)) || maze.isTrap(Position(x, y))){
				maze.setTile(Position(x, y), ' ');
				mvaddch(y, x, ' ');
			}
		}
		refresh();
		usleep(500000);
	}
}

void Simulation::run(){
	initscr();
	noecho();
	curs_set(0);
	unsigned int tries = 1000;
	while(!met){
		if(tries == 0){
			endwin();
			return;
		}
		clear();
		maze.drawMaze();
		displayTime(maze, tries);
		if(!g.isTrapped()){
			g.move(maze);
		}
		if(!a.isTrapped()){
			a.move(maze);
		}
		if(maze.isKey(g.getPosition())){
			g.pickupKey();
			maze.setTile(g.getPosition(), ' ');
		}
		if(maze.isKey(a.getPosition())){
			a.pickupKey();
			maze.setTile(a.getPosition(), ' ');
		}
		if(maze.isTrap(g.getPosition())){
			g.setTrapped(true);
			maze.useTrap();
			if(g.carriesKey()){
				endwin();
				return;
			}
		}
		if(maze.isTrap(a.getPosition())){
			a.setTrapped(true);
			maze.useTrap();
			if(a.carriesKey()){
				endwin();
				return;
			}
		}
		refresh();
		usleep(200000);
		if(maze.areNeighbors(g.getPosition(), a.getPosition())){
			if(g.isTrapped() && a.carriesKey()){
				g.setTrapped(false);
				a.useKey();
				met = true;
			}
			else if(a.isTrapped() && g.carriesKey()){
				a.setTrapped(false);
				g.useKey();
				met = true;
			}
			else if(!g.isTrapped() && !a.isTrapped()){
				met = true;
			}
		}
		tries--;
	}
	destroyMaze(maze);
	while(!maze.areNeighbors(g.getPosition(), maze.getExit()) && !maze.areNeighbors(a.getPosition(), maze.getExit())){
		maze.drawMaze();
		a.moveToExit(maze, maze.getExit());
		g.moveToExit(maze, maze.getExit());
		refresh();
		usleep(200000);
	}
	endwin();
}

void Simulation::displayTime(const Maze& maze, unsigned int time) const{
	mvprintw((maze.getHeight() / 2) - 1, maze.getWidth() + 20, "Time Remaining:");
	mvprintw(maze.getHeight() / 2, maze.getWidth() + 20, "%d", time);
}
