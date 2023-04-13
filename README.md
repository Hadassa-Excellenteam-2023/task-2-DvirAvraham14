# task-2-dvir avraham
# <h2> Chess Game </h2>
This is a command-line chess game written in C++. The game is played by entering commands to move pieces on the board. The game follows standard chess rules and 

# Classes

<h3>ChessPiece</h3>
This is an abstract class for chess pieces. It has a boolean member variable m_isWhite to indicate whether the piece is white or black. It also has two pure virtual member functions:

isValidMove(const Position src, const Position des): This function returns true if the move from source to destination is valid for the piece, false otherwise.
getType(): This function returns the type of the chess piece.
<h3>Bishop, King, Queen, Knight, Rook, Pawn</h3>
These are classes that inherit from ChessPiece and implement their respective piece's behavior.


<h3>ChessPieceFactory</h3>
This class is responsible for creating instances of chess pieces. It uses a map to store functions that create instances of the various chess pieces.

<h3>Board</h3>
This class represents the chess board. It has a 2D array of unique_ptr<ChessPiece> to store the pieces. It also has member variables to keep track of the current player's turn and the position of the kings. It has various member functions to perform actions on the board like moving a piece, checking if a square is empty, checking if a square is occupied by an enemy piece, etc. It also has a member function to get the response code for a move.
  
  
  TO DO:
  Pawn behavior need to be fix, he can only move forward.
