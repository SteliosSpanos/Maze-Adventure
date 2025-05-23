#pragma once

struct Position{
        int x;
        int y;

	Position(int _x, int _y) : x(_x), y(_y) {}
	Position() {}

        bool operator==(const Position& pos) const{
                return x == pos.x && y == pos.y;
        }
        bool operator!=(const Position& pos) const{
                if(*this == pos){
			return false;
		}
		return true;
	}
};
