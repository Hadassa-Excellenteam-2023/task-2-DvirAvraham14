#pragma once
#include "ChessPiece.h"

class Pawn : public ChessPiece {
private:
    bool isFirstMove = true;
public:
    using ChessPiece::ChessPiece;
    bool isValidMove(const Position src, const Position des) const override;
    ChessPieceType getType() const override;
    void setFirstMove();
};