#include "Simulation.h"
#include <unistd.h>
#include <ctime>
#include <cstdlib>
#include <ncurses.h>
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

void Simulation::destroyMaze(Maze& maze) {
	for(int y = 1; y < maze.getHeight() - 1; y++){
		for(int x = 1; x < maze.getWidth() - 1; x++){
			Position toDestroy(x, y);
			if(maze.isWall(toDestroy) || maze.isTrap(toDestroy) || maze.isKey(toDestroy)){
				maze.setTile(toDestroy, ' ');
				mvaddch(y, x, ' ');
			}
		}
		refresh();
		usleep(400000);
	}
}

void Simulation::headToExit() {
	 while(!maze.areNeighbors(g.getPosition(), maze.getExit()) && !maze.areNeighbors(a.getPosition(), maze.getExit())){
                maze.drawMaze();
                a.moveTo(maze, maze.getExit());
                g.moveTo(maze, maze.getExit());
                refresh();
                usleep(200000);
        }
}

void Simulation::run() {
	initscr();
	start_color();
	noecho();
	curs_set(0);

	init_pair(1, COLOR_BLUE, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);

	while(!met){
		if(rounds == 0){
			gameOver(maze);
			getch();
			endwin();
			return;
		}
		clear();
		maze.drawMaze();

		if(!g.isTrapped()){
                	g.move(maze);
        	}
        	if(!a.isTrapped()){
                	a.move(maze);
        	}

        	if(g.getPosition() == maze.getKey()){
			g.pickupKey();
			maze.setTile(g.getPosition(), ' ');
        	}
        	if(a.getPosition() ==  maze.getKey()){
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

		if(maze.areNeighbors(g.getPosition(), a.getPosition())){
			if(!g.isTrapped() && !a.isTrapped()){
				met = true;
			}
			else if(g.isTrapped() && !a.isTrapped()){
				if(a.carriesKey()){
					a.useKey();
					g.setTrapped(false);
					met = true;
				}
			}
			else if(a.isTrapped() && !g.isTrapped()){
				if(g.carriesKey()){
					g.useKey();
					a.setTrapped(false);
					met = true;
				}
			}
		}
		displayTime(maze, rounds);
		if(a.carriesKey()){
			a.displayHasKey(maze);
		}
		if(g.carriesKey()){
			g.displayHasKey(maze);
		}
		if(g.isTrapped()){
			g.displayIsTrapped(maze);
		}
		if(a.isTrapped()){
			a.displayIsTrapped(maze);
		}

		refresh();
		usleep(200000);
		rounds--;
	}

	destroyMaze(maze);

	headToExit();
	endwin();
}

void Simulation::displayTime(const Maze& maze, unsigned int time) const {
	attron(COLOR_PAIR(1));
	mvprintw(maze.getHeight() / 3, maze.getWidth() + 10, "|| TIME REMAINING ||: %d", time);
	attroff(COLOR_PAIR(1));
}

void Simulation::gameOver(const Maze& maze) const {
	attron(COLOR_PAIR(1));
   	mvprintw(maze.getHeight() / 2 - 2, maze.getWidth() + 5, " _________________________________________");
    	mvprintw(maze.getHeight() / 2 - 1, maze.getWidth() + 5, "|  _               __     _        __  _  |");
    	mvprintw(maze.getHeight() / 2, maze.getWidth() + 5, "| | _  /\\   /\\/\\  |_     / \\ \\  / |_  |_| |");
    	mvprintw(maze.getHeight() / 2 + 1, maze.getWidth() + 5, "| |_| /--\\ /    \\ |__    \\_/  \\/  |__ | \\ |");
    	mvprintw(maze.getHeight() / 2 + 2, maze.getWidth() + 5, "|_________________________________________|");
	attroff(COLOR_PAIR(1));
}
