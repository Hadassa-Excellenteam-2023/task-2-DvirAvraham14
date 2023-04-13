#include "Board.h"

/**
 * @brief Construct a new Board:: Board object
 *
 * @param board_string
 */
Board::Board(const string &board_string): m_isWhiteTurn(true) {
    // Initialize the board
    for(auto row = 0; row < 8; ++row)
        for(auto col = 0; col < 8; ++col)
            m_board[row][col] = nullptr;
    //set default king positions
    m_kingPos[0] = {-1, -1};
    m_kingPos[1] = {-1, -1};

    // Create the pieces
    ChessPieceFactory factory;
    for(auto i = 0; i < board_string.size(); ++i) {
        auto row = i / 8;
        auto col = i % 8;
        if(board_string[i] == 'K')
            m_kingPos[WHITE] = {row, col};
        else if(board_string[i] == 'k')
            m_kingPos[BLACK] = {row, col};

        m_board[row][col] = factory.createPiece(board_string[i]);
    }
}

/**
 * @brief get the response code of the move
 * response code value : 11 - there is not piece at the source
 *                      12 - the piece in the source is piece of your opponent
 *                      13 - there one of your pieces at the destination
 *                      21 - illegal movement of that piece
 *                      31 - this movement will cause you checkmate
 *                      41 - the last movement was legal and cause check
 *                      42 - the last movement was legal
 *
 * @param move the move to check
 * @return int the response code
 */
int Board::getResponeCode(const std::string &move) {
    Position src = {move[0] - 'a', move[1] - '1'};
    Position dst = {move[2] - 'a', move[3] - '1'};

    if(isEmpty(src)) return 11;
    if(isEnemy(src)) return 12;
    if(isCurPlayerPiece(dst)) return 13;
    if(!m_board[src.row][src.col]->isValidMove(src, dst) ||
        isPathBlocked(src, dst)) return 21;
    if(isMoveCauseYouCheck(src, dst)) return 31;
    updateBoard(src, dst);
    if(isCheckmate()) return 41;
    return 42;
}

/**
 * @brief check if the cell is empty
 *
 * @param src the source position
 * @return true if the cell is empty
 * @return false if the cell is not empty
 */
bool Board::isEmpty(const Position src) const {
    return m_board[src.row][src.col] == nullptr;
}

/**
 * @brief check if the cell is enemy piece
 *
 * @param src the source position
 * @return true if the cell is enemy piece
 * @return false if the cell is not enemy piece
 */
bool Board::isEnemy(const Position src) const {
    return m_board[src.row][src.col]->isWhite() != m_isWhiteTurn;
}

/**
 * @brief check if the cell is current player piece
 *
 * @param src the source position
 * @return true if the cell is current player piece
 * @return false if the cell is not current player piece
 */
bool Board::isCurPlayerPiece(const Position src) const {
    return !isEmpty(src) && m_board[src.row][src.col]->isWhite() == m_isWhiteTurn;
}

/**
 * @brief check if the path between the source and the destination is blocked
 * @param source
 * @param dest
 * @return true if the path is blocked
 * @return false if the path is not blocked
 */
bool Board::isPathBlocked(const Position& source, const Position& dest) const
{
    int dx = dest.row - source.row;
    int dy = dest.col - source.col;

    // Movement is not straight or diagonal
    if (dx != 0 && dy != 0 && dx != dy)
        return false;

    // Check if there is a piece between the source and the destination
    int steps = std::max(std::abs(dx), std::abs(dy));
    int x_step = (dx > 0) ? 1 : ((dx < 0) ? -1 : 0);
    int y_step = (dy > 0) ? 1 : ((dy < 0) ? -1 : 0);
    Position curPos = source;
    for (int i = 1; i < steps; i++) {
        curPos.row += x_step;
        curPos.col += y_step;
        if (!isEmpty(curPos))
            return true;
    }
    return false;
}

/**
 * @brief update the board after the move
 * @param src the source position
 * @param des the destination position
 */
void Board::updateBoard(const Position src, const Position des) {
    if(isKing(src))
        m_kingPos[m_board[src.row][src.col]->isWhite()] = des;
    if(isPawn(src))
        dynamic_cast<Pawn*>(m_board[src.row][src.col].get())->setFirstMove();
    m_board[des.row][des.col] = std::move(m_board[src.row][src.col]);
    m_board[src.row][src.col] = nullptr;
    m_isWhiteTurn = !m_isWhiteTurn;
}

/** check ig the piece in the position is king
 * @param pos the position to check
 * @return true if the piece in the position is king
 * @return false if the piece in the position is not king
 */
bool Board::isKing(const Position &pos) const {
    return m_board[pos.row][pos.col]->getType() == ChessPieceType::KING;
}

/** check ig the piece in the position is pawn
 * @param pos the position to check
 * @return true if the piece in the position is pawn
 * @return false if the piece in the position is not pawn
 */
bool Board::isPawn(const Position &pos) const {
    return m_board[pos.row][pos.col]->getType() == ChessPieceType::PAWN;
}

/**
 * @brief check if the move cause you check
 *
 * @param src the source position
 * @param des the destination position
 * @return true if the move cause you check
 * @return false if the move not cause you check
 */
bool Board::isMoveCauseYouCheck(const Position &src, const Position &des)  {
    //swap the pieces
    auto temp = std::move(m_board[des.row][des.col]);
    m_board[des.row][des.col] = std::move(m_board[src.row][src.col]);
    if(isKing(des)) //update king position
        m_kingPos[m_board[des.row][des.col]->isWhite()] = des;
    bool isCheck = isCheckmate();
    if(isKing(des)) //update king position
        m_kingPos[m_board[des.row][des.col]->isWhite()] = src;
    //swap the pieces back
    m_board[src.row][src.col] = std::move(m_board[des.row][des.col]);
    m_board[des.row][des.col] = std::move(temp);
    return isCheck;
}

/**
 * @brief check if the current player is checkmate
 *
 * @return true if the current player is checkmate
 * @return false if the current player is not checkmate
 */
bool Board::isCheckmate() const {
    auto oppenentMoves = getEnemyMoves();
    for(auto &move : oppenentMoves)
        if(m_board[move.row][move.col]->isValidMove(move, m_kingPos[m_isWhiteTurn]) &&
           !isPathBlocked(move, m_kingPos[m_isWhiteTurn]))
            return true;
    return false;
}

/**
 * @brief get all the enemy locations for the opponent
 *
 * @return vector<Position> the enemy moves
 */
vector<Position> Board::getEnemyMoves() const {
    vector<Position> enemyMoves;
    for (auto row = 0; row < 8; ++row)
        for (auto col = 0; col < 8; ++col) {
            if (isEmpty({row, col}) || isCurPlayerPiece({row, col}))
                continue;
            enemyMoves.push_back(Position{row, col});
        }
    return enemyMoves;
}
