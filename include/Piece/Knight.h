#pragma once
#include "ChessPiece.h"

#include <vector>
using std::vector;

class Knight : public ChessPiece {
public:
    using ChessPiece::ChessPiece;
    bool isValidMove(const Position src, const Position des) const override;
    ChessPieceType getType() const override;
};