# Maze Adventure

## Story

Once upon a time, a beloved couple, `Gregorakis (G)` and `Asimenia (S)`, radiated a love so strong it fueled the entire realm. But their happiness was shattered when the evil wizard trapped them in a dark labyrinth. Separated and confused, the couple must reunite before 1000 turns pass, or the kingdom will fall into ruin.

Two hidden traps (T) are set in the maze. Once stepped on, they turn into cages (C), trapping the hero. Only a magical key (K), lost somewhere in the maze, can unlock them from the outside. If the heroes find each other in time, the walls crumble, a staircase (L) appears, and love prevails.

Will they make it?

## Game Features
- Randomized placement of heroes, traps, key and escape ladder.
- Maze is loaded from a .txt file using `'*'` for walls, `' '` for paths and `'L'` for the ladder.
- Heroes have limited visibility but remember where they have been.
- `Key Logic:` heroes can pick up the key and use it to unlock cages, if they reach them from the outside.
- If heroes meet, the maze gets destroyed and the game ends.
- If the game becomes unwinnable, it ends immediately with a "Game Over".

## What I Learned
- `Object-Oriented Programming` in C++ with focus on inheritance, polymorphism and abstraction.
- `Algorithm Design` for autonomous movement and pathfinding.
- `Game Loop & Design` including win/loss logic and early termination conditions.
- Practice with `ncurses` library. 
