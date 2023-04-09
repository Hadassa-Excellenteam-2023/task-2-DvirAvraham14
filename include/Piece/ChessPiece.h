#pragma once
#include <string>
#include "macros.h"
using std::string;

class Board;

class ChessPiece {
private:
    bool m_isWhite;

public:
    ChessPiece(bool isWhite) : m_isWhite(isWhite) {};;
    virtual ~ChessPiece() = default;
    bool isWhite() const { return m_isWhite; }
    virtual bool isValidMove(const Position src, const Position des) const = 0;
};