#include "Simulation.h"
#include "Grigorakis.h"
#include "Asimenia.h"
#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <cmath>

Simulation::Simulation(const std::string& filename) : maze(filename), met(false), rounds(1000) {
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
		for(int x = 1; x < maze.getWidth() - 1; x++){
			Position toDestroy(x, y);
			if(maze.isWall(toDestroy) || maze.isTrap(toDestroy) || maze.isKey(toDestroy)){
				maze.setTile(toDestroy, ' ');
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

	while(!met){
		if(rounds == 0){
			gameOver(maze);
			getch();
			endwin();
			return;
		}
		clear();
		maze.drawMaze();
		displayTime(maze, rounds);

		if(!g.isTrapped()){    //If the charctecter is trapped it doesnt move
			g.move(maze);
		}
		if(!a.isTrapped()){
			a.move(maze);
		}

		if(maze.isKey(g.getPosition())){   //The character picks up the key
			g.pickupKey();
			maze.setTile(g.getPosition(), ' ');
		}
		if(maze.isKey(a.getPosition())){
			a.pickupKey();
			maze.setTile(a.getPosition(), ' ');
		}

		if(maze.isTrap(g.getPosition())){
			g.setTrapped(true);
			maze.useTrap(g.getPosition());
			if(g.carriesKey()){
				gameOver(maze);
				getch();
				endwin();
				return;
			}
		}
		if(maze.isTrap(a.getPosition())){
			a.setTrapped(true);
			maze.useTrap(a.getPosition());
			if(a.carriesKey()){
				gameOver(maze);
				getch();
				endwin();
				return;
			}
		}

		if(a.isTrapped() && g.isTrapped()){
			gameOver(maze);
			getch();
			endwin();
			return;
		}

		refresh();
		usleep(200000);

		if(maze.areNeighbors(g.getPosition(), a.getPosition())){   //If the character are neighbors they can
			if(g.isTrapped() && a.carriesKey()){               //only meet under these conditions
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
		rounds--;
	}

	destroyMaze(maze);   //Destroy the maze cinematically

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

void Simulation::gameOver(const Maze& maze) const{
	mvprintw(maze.getHeight() + 5, maze.getWidth(), "GAME OVER");
}
