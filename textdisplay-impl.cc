module TextDisplay;

import <iostream>;
import <string>;
import Abstract;
import Board;
import Player;

TextDisplay::TextDisplay(Player *a, Player *b) : p1{a}, p2{b} {}

void TextDisplay::update(Subject &) {
    buffer.clear();

    buffer.push_back("Level: " + std::to_string(p1->getLevelNum()) +
                     "        Level: " + std::to_string(p2->getLevelNum()));
    buffer.push_back("Score: " + std::to_string(p1->getScore().getCurrent()) +
                     "        Score: " + std::to_string(p2->getScore().getCurrent()));
    buffer.push_back("Hi Score: " + std::to_string(p1->getScore().getHi()));
    buffer.push_back("----------- -----------");

    auto g1 = p1->getBoard().renderWithCurrent(p1->getCurrentBlock(), p1->getCurR(), p1->getCurC());
    auto g2 = p2->getBoard().renderWithCurrent(p2->getCurrentBlock(), p2->getCurR(), p2->getCurC());

    for (int r = 3; r < Board::Rows; ++r) {
        std::string line1, line2;
        for (int c = 0; c < Board::Cols; ++c) line1 += (g1[r][c] == ' ' ? '.' : g1[r][c]);
        for (int c = 0; c < Board::Cols; ++c) line2 += (g2[r][c] == ' ' ? '.' : g2[r][c]);

        buffer.push_back(line1 + " " + line2);
    }

    buffer.push_back("----------- -----------");
    buffer.push_back("Next:       Next:");
    buffer.push_back(std::string(1, p1->getNextBlock().getChar()) +
                     "           " +
                     std::string(1, p2->getNextBlock().getChar()));
}

void TextDisplay::render() const {
    for (auto &line : buffer) std::cout << line << "\n";
}
