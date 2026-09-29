#pragma once
#include "framework.hh"

// We will use enumerated types to represent the different types of pieces.
enum PieceType {
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
};

// Abstract class Piece, all chess pieces must inherit from this base class 
class Piece : public Entity
{
    protected:
        // defines the color of the piece
        bool is_color_white;
    public:
        //Default constructor, set the color 
        Piece(bool iswhite);
        
        //Overload constructor, set the color and attach a new Position and Visual component with the coordinates (x,y) and letter
        Piece(bool iswhite, int x, int y, char letter);

        // Returns if the piece color is white
        bool isWhite();

        // Get the posicion component attached to the entity
        PositionComponent* getPosition();
        
        // Get the visual component attached to the entity
        VisualComponent* getVisual();

        // Pure virtual function, determines if the Piece can move to the coordinates (x,y)
        virtual bool canMoveTo(int x, int y) = 0;

        // Pure virtual function, returns the type of the Piece based on the Enum PieceType
        virtual PieceType getType() = 0;

        // Must release al the memory allocated to the components attached to the entity
        ~Piece();
};


const int BOARD_SIZE = 8;

class ChessBoard
{
    // We will use a two-dimensional array to represent the chess board.
    // Each element of the array will be a pointer to a Piece object.
    // We will use nullptr to represent an empty square.
    Piece* board[BOARD_SIZE][BOARD_SIZE];

    public:
        // Initialize the board with the starting positions of the pieces.     
        void initializeBoard();

        // Get the piece located at the coordinates x, y, be carefull! you may need to swap the coordinates
        Piece* getPieceAt(int x, int y);

        // Set the submited piece at the coordinates x, y, be carefull! you may need to swap the coordinates
        void setPieceAt(Piece* piece, int x, int y);
        
        // destructor, must release all memory allocated for pieces in the board
        ~ChessBoard();    
};
