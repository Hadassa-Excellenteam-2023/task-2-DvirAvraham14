#pragma once
#include <memory>
#include <map>
#include <functional>
#include "macros.h"
#include "Piece/Queen.h"
#include "Piece/King.h"
#include "Piece/Pawn.h"
#include "Piece/Bishop.h"
#include "Piece/Knight.h"
#include "Piece/Rook.h"

using std::map;


class ChessPieceFactory {

private:
    using PieceCreator = std::function<std::unique_ptr<ChessPiece> (bool)>;
    std::map<char, PieceCreator> m_pieceCreators;
public:
    ChessPieceFactory() {
        m_pieceCreators['Q'] = [](bool isWhite) { return std::make_unique<Queen>(isWhite); };
        m_pieceCreators['K'] = [](bool isWhite) { return std::make_unique<King>(isWhite); };
        m_pieceCreators['R'] = [](bool isWhite) { return std::make_unique<Rook>(isWhite); };
        m_pieceCreators['N'] = [](bool isWhite) { return std::make_unique<Knight>(isWhite); };
        m_pieceCreators['B'] = [](bool isWhite) { return std::make_unique<Bishop>(isWhite); };
        m_pieceCreators['P'] = [](bool isWhite) { return std::make_unique<Pawn>(isWhite); };
    }


    std::unique_ptr<ChessPiece> createPiece(char pieceSymbol) {
        bool is_upper = std::isupper(pieceSymbol); // true if White, false if Black
        auto it = m_pieceCreators.find(std::toupper(pieceSymbol));
        if(it != m_pieceCreators.end())
            return it->second(is_upper);
        else
            return nullptr;
    }
};