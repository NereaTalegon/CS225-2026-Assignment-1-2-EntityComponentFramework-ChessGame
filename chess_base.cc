#include "chess_base.hh"
#include "chess_pieces.hh"

Piece::Piece(bool iswhite){
    is_color_white = iswhite;
}

Piece::Piece(bool iswhite, int x, int y, char letter) {
    is_color_white = iswhite;
    attach(new PositionComponent(x,y));
    attach(new VisualComponent(letter));
}

PositionComponent* Piece::getPosition(){
    Component* component = getComponent("Position");
    PositionComponent* position = static_cast<PositionComponent*>(component);
    return position;
}

void ChessBoard::initializeBoard(){
    //init by setting all to null

    //place all poieces in inital places
    Pawn* pawn = new Pawn();
    setPieceAt(pawn, 0, 0);
}