#pragma once
#include "Piece/Pawn.h"

bool Pawn::isValidMove(const Position src, const Position des) const {
    if(isFirstMove)
        if(this->isWhite())
            return (des.row == src.row + 2 || des.row == src.row + 1) && des.col == src.col;
        else
            return (des.row == src.row - 2 || des.row == src.row - 1) && des.col == src.col;
    else
        if(this->isWhite())
            return des.row == src.row + 1 && des.col == src.col;
        else
            return des.row == src.row - 1 && des.col == src.col;

}

ChessPieceType Pawn::getType() const {
    return ChessPieceType::PAWN;
}

void Pawn::setFirstMove() {
    isFirstMove = false;
}