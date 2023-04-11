#pragma once

#include <memory>
#include <iostream>
#include "macros.h"
#include "Piece/ChessPiece.h"
#include "ChessPieceFactory.h"


using std::unique_ptr;
using std::vector;
using std::string;
using std::cout;

class Board {
private:
   // Private members
   bool m_isWhiteTurn;
   unique_ptr<ChessPiece> m_board[8][8];
   Position m_kingPos[2]; // 1 - white, 0 - black

   // Private methods
   bool isEmpty(const Position src) const;
   bool isEnemy(const Position src) const;
   bool isCurPlayerPiece(const Position src) const;
   bool isCheckCurrentPlayer(const Position src, const Position des) const;
   void updateBoard(const Position src, const Position des);
   bool isPathBlocked(const Position& source, const Position& dest) const;
   bool isKing(const Position &pos) const;
   bool isPawn(const Position &pos) const;
   bool isMoveCauseYouCheck(const Position &src, const Position &des);
   bool isCheckmate() const;
   vector<Position> getEnemyMoves() const;
public:
    Board(const string &board_string);
    int getResponeCode(const string &move);
};
