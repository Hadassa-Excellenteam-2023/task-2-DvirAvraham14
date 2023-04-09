#pragma once

#include <memory>
#include "macros.h"
#include "Piece/ChessPiece.h"
#include "ChessPieceFactory.h"


using std::unique_ptr;
using std::string;



class Board {
private:
   bool m_isWhiteTurn = true;
   unique_ptr<ChessPiece> m_board[8][8];
   bool isEmpty(const Position src) const;
   bool isEnemy(const Position src) const;
   bool isCurPlayerPiece(const Position src) const;
   bool isCheckCurrentPlayer(const Position src, const Position des) const;
   void updateBoard(const Position src, const Position des);
public:
    Board(const string &board_string);
    int getResponeCode(const string &move);
};
