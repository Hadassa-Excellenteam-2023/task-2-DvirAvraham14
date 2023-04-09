#pragma once
#include "Piece/Rook.h"

bool Rook::isValidMove(const Position src, const Position des) const {
    return src.row == des.row || src.col == des.col;
}