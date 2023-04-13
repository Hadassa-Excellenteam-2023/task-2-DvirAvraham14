#pragma once

const bool WHITE = true;
const bool BLACK = false;

/**
 * @brief A struct that represents a position on the board.
 */
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

/**
 * @brief An enum that represents the type of a chess piece.
 */
enum ChessPieceType {
    KING,
    QUEEN,
    KNIGHT,
    PAWN,
    ROOK,
    BISHOP,
};
