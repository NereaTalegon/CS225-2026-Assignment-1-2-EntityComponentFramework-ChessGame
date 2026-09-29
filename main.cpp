#include <iostream>
#include <cmath>
#include <cctype>
#include <string>
#include "chess_base.hh"
#include "chess_pieces.hh"

ChessBoard board;

bool inBounds(int x, int y) {
    return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE;
}

bool isPathClear(int fromX, int fromY, int toX, int toY) {
    int stepX = (toX > fromX) - (toX < fromX);
    int stepY = (toY > fromY) - (toY < fromY);
    int x = fromX + stepX;
    int y = fromY + stepY;
    while (x != toX || y != toY) {
        if (board.getPieceAt(x, y) != nullptr) {
            return false;
        }
        x += stepX;
        y += stepY;
    }
    return true;
}

bool isLegalMove(Piece* piece, int toX, int toY) {
    if (!piece || !inBounds(toX, toY)) {
        return false;
    }
    int fromX = piece->getPosition()->getX();
    int fromY = piece->getPosition()->getY();
    if (fromX == toX && fromY == toY) {
        return false;
    }

    Piece* target = board.getPieceAt(toX, toY);
    if (target && target->isWhite() == piece->isWhite()) {
        return false;
    }

    if (!piece->canMoveTo(toX, toY)) {
        return false;
    }

    if (piece->getType() == PAWN) {
        bool isCapture = (std::abs(toX - fromX) == 1);
        if (isCapture) {
            return target != nullptr;
        }
        if (target != nullptr) {
            return false;
        }
        if (std::abs(toY - fromY) == 2) {
            int midY = (fromY + toY) / 2;
            return board.getPieceAt(fromX, midY) == nullptr;
        }
        return true;
    }

    if (piece->getType() != KNIGHT && !isPathClear(fromX, fromY, toX, toY)) {
        return false;
    }

    return true;
}

bool parseSquare(const std::string& square, int& x, int& y) {
    if (square.size() != 2) {
        return false;
    }
    char file = static_cast<char>(std::tolower(square[0]));
    char rank = square[1];
    if (file < 'a' || file > 'h' || rank < '1' || rank > '8') {
        return false;
    }
    x = file - 'a';
    y = rank - '1';
    return true;
}

bool parseMove(const std::string& input, int& fromX, int& fromY, int& toX, int& toY) {
    std::string from;
    std::string to;
    std::string token;

    for (char ch : input) {
        if (std::isspace(static_cast<unsigned char>(ch))) {
            if (!token.empty()) {
                if (from.empty()) {
                    from = token;
                } else if (to.empty()) {
                    to = token;
                } else {
                    return false;
                }
                token.clear();
            }
            continue;
        }
        token.push_back(ch);
    }
    if (!token.empty()) {
        if (from.empty()) {
            from = token;
        } else if (to.empty()) {
            to = token;
        } else {
            return false;
        }
    }

    if (to.empty() && from.size() == 4) {
        to = from.substr(2, 2);
        from = from.substr(0, 2);
    }

    return parseSquare(from, fromX, fromY) && parseSquare(to, toX, toY);
}

void printBoard() {
    std::cout << "\n    a b c d e f g h\n";
    std::cout << "  +-----------------+\n";
    for (int y = BOARD_SIZE - 1; y >= 0; --y) {
        std::cout << (y + 1) << " | ";
        for (int x = 0; x < BOARD_SIZE; ++x) {
            Piece* piece = board.getPieceAt(x,y);
            if (piece == nullptr) {
                std::cout << ". ";
            } else {
                piece->getVisual()->Draw();
            }
        }
        std::cout << "| " << (y + 1) << '\n';
    }
    std::cout << "  +-----------------+\n";
    std::cout << "    a b c d e f g h\n";
    std::cout << "White = uppercase, Black = lowercase\n";
}


int main() {
    board.initializeBoard();

    bool whiteToMove = true;
    bool gameOver = false;

    std::cout << "Two-player chess\n";
    std::cout << "Enter moves like e2 e4 or e2e4. Type quit to exit.\n";

    while (!gameOver) {
        printBoard();
        std::cout << (whiteToMove ? "White" : "Black") << " to move: ";

        std::string input;
        if (!std::getline(std::cin, input)) {
            break;
        }
        if (input.empty()) {
            continue;
        }
        if (input == "quit" || input == "exit") {
            std::cout << "Game ended.\n";
            break;
        }

        int fromX = 0;
        int fromY = 0;
        int toX = 0;
        int toY = 0;
        if (!parseMove(input, fromX, fromY, toX, toY)) {
            std::cout << "Invalid input. Use squares like e2 e4.\n";
            continue;
        }

        Piece* piece = board.getPieceAt(fromX, fromY);
        if (piece == nullptr) {
            std::cout << "There is no piece on that square.\n";
            continue;
        }
        if (piece->isWhite() != whiteToMove) {
            std::cout << "That is not your piece.\n";
            continue;
        }
        if (!isLegalMove(piece, toX, toY)) {
            std::cout << "Illegal move.\n";
            continue;
        }

        Piece* captured = board.getPieceAt(toX, toY);
        bool capturedKing = captured && captured->getType() == KING;
        delete captured;

        board.setPieceAt(nullptr, fromX, fromY);
        board.setPieceAt(piece, toX, toY);

        Component* component = piece->getComponent("Position");
        PositionComponent* position = dynamic_cast<PositionComponent*>(component);
        position->setPosition(toX, toY);

        if (capturedKing) {
            printBoard();
            std::cout << (whiteToMove ? "White" : "Black") << " wins by capturing the king.\n";
            gameOver = true;
            continue;
        }

        whiteToMove = !whiteToMove;
    }

    return 0;
}