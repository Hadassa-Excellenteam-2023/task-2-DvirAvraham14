#pragma once
#include "Piece/Bishop.h"

bool Bishop::isValidMove(const Position src, const Position des) const {
    int row_diff = abs(src.row - des.row);
    int col_diff = abs(src.col - des.col);
    return row_diff == col_diff;
}

ChessPieceType Bishop::getType() const {
    return ChessPieceType::BISHOP;
}