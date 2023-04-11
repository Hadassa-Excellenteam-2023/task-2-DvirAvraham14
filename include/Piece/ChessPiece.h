#pragma once
#include <string>
#include "macros.h"
using std::string;

class Board;

/**
 * @brief Abstract class for chess pieces
    *
    */
class ChessPiece {
private:
    bool m_isWhite; // true - white, false - black

public:
    ChessPiece(bool isWhite) : m_isWhite(isWhite) {}; // Ctor
    virtual ~ChessPiece() = default; // Dtor
    bool isWhite() const { return m_isWhite; }  // Return true if the piece is white, false otherwise
    virtual bool isValidMove(const Position src, const Position des) const = 0; // Return true if the move is valid, false otherwise
    virtual ChessPieceType getType() const = 0; // Return the type of the piece
};