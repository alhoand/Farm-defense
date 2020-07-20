#pragma once

//Helper class for coordinates on game field
#include <utility>

class Position {
    public:
        //getter function for coordinates
        std::pair<int, int> GetPosition() {
            return std::make_pair(x_, y_);
        }

    private:
        int x_;
        int y_;
};