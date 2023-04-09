//
// Created by coral on 09/04/2023.
//

#include "Board.h"

Board::Board(const string &board_string) {
    // Initialize the board
    for(auto row = 0; row < 8; ++row)
        for(auto col = 0; col < 8; ++col)
            m_board[row][col] = nullptr;

    ChessPieceFactory factory;
    for(auto i = 0; i < board_string.size(); ++i) {
        auto row = i / 8;
        auto col = i % 8;
        m_board[row][col] = factory.createPiece(board_string[i]);
    }
}

int Board::getResponeCode(const std::string &move) {
    Position src = {move[0] - 'a', move[1] - '1'};
    Position dst = {move[2] - 'a', move[3] - '1'};

    if(isEmpty(src)) return 11;
    else if(isEnemy(src)) return 12;
    else if(isCurPlayerPiece(dst)) return 13;
    else if(!m_board[src.row][src.col]->isValidMove(src, dst)) return 21;
    updateBoard(src, dst);
    return 42;
}

bool Board::isEmpty(const Position src) const {
    return m_board[src.row][src.col] == nullptr;
}

bool Board::isEnemy(const Position src) const {
    return m_board[src.row][src.col]->isWhite() != m_isWhiteTurn;
}

bool Board::isCurPlayerPiece(const Position src) const {
    return !isEmpty(src) && m_board[src.row][src.col]->isWhite() == m_isWhiteTurn;
}


void Board::updateBoard(const Position src, const Position des) {
    m_board[des.row][des.col] = std::move(m_board[src.row][src.col]);
    m_board[src.row][src.col] = nullptr;
    m_isWhiteTurn = !m_isWhiteTurn;
}