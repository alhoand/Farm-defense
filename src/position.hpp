#pragma once
#include<iostream>

//Helper class for coordinates on game field
#include <utility>

class Position {
    public:

		Position(int x, int y): x_(x), y_(y) {};
		
		
        //getter function for coordinates
        std::pair<int, int> GetPosition() {
            return std::make_pair(x_, y_);
        }
		
		friend std::ostream& operator<<(std::ostream& os, const Position p){
			os << "[" << p.x_ << " , " << p.y_ << "]" << std::endl;
			return os;
		}
		

    private:
        int x_;
        int y_;
};