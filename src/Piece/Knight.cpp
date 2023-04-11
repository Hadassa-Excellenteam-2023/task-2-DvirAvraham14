#pragma once
#include "Piece/Knight.h"

bool Knight::isValidMove(const Position src, const Position des) const {
    vector<Position> moves = {
            {src.row + 2, src.col + 1},
            {src.row + 2, src.col - 1},
            {src.row - 2, src.col + 1},
            {src.row - 2, src.col - 1},
            {src.row + 1, src.col + 2},
            {src.row + 1, src.col - 2},
            {src.row - 1, src.col + 2},
            {src.row - 1, src.col - 2}
    };

    for (auto move : moves)
        if (move == des)
            return true;
    return false;
}

ChessPieceType Knight::getType() const {
    return ChessPieceType::KNIGHT;
}