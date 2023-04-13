#pragma once
#include "Piece/Queen.h"

bool Queen::isValidMove(const Position src, const Position des) const {
    // Check if the move is along a straight line (horizontally, vertically, or diagonally)
    if (src.row == des.row || src.col == des.col || abs(src.row - des.row) == abs(src.col - des.col)) {
        // The move is along a straight line
        return true;
    }

    // The move is not along a straight line
    return false;
}


ChessPieceType Queen::getType() const {
    return ChessPieceType::QUEEN;
}