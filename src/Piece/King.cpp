#pragma once
#include "Piece/King.h"

bool King::isValidMove(const Position src, const Position des) const {
    int row_diff = abs(src.row - des.row);
    int col_diff = abs(src.col - des.col);
    return (row_diff <= 1) && (col_diff <= 1);
}

ChessPieceType King::getType() const {
    return ChessPieceType::KING;
}