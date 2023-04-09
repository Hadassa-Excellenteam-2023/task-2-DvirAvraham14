#pragma once

const bool WHITE = true;
const bool BLACK = false;



struct Position {
    int row;
    int col;
    bool operator==(const Position &other) const {
        return row == other.row && col == other.col;
    }

    bool operator!=(const Position &other) const {
        return !(*this == other);
    }

    Position operator+(const Position &other) const {
        return {row + other.row, col + other.col};
    }

    Position operator+=(const Position &other) {
        row += other.row;
        col += other.col;
        return *this;
    }
};
