#pragma once
#include "ChessPiece.h"

class King : public ChessPiece {
public:
    using ChessPiece::ChessPiece;
    bool isValidMove(const Position src, const Position des) const override {
        return true;
    }
};