#pragma once
#include "ChessPiece.h"

class Queen : public ChessPiece {
public:
    using ChessPiece::ChessPiece;
    bool isValidMove(const Position src, const Position des) const override;
    ChessPieceType getType() const override;
};