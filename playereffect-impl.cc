module PlayerEffect;

import Types;
import Block;
import Player;
import <iostream>;
import <vector>;
using namespace std;

// space for next block display
const int rowsForNext = 2;
const int colsForNext = 4;

PlayerEffect::PlayerEffect(int p) : owner{p} {}

BlindEffect::BlindEffect(int p) : PlayerEffect(p) {}

void BlindEffect::apply(Player &p1, Player &p2) {
    // Print board with ? in rows 3-12 and columns 3-9
    cout << "Level: "  << p1.getLevelNum() << "        Level: " << p2.getLevelNum() << endl;
    cout << "Score: " << p1.getScore().getCurrent() << "        Score: " << p2.getScore().getCurrent() << endl;
    if (p1.getScore().getHi() >= p2.getScore().getHi()) {
        cout << "     High Score: " << p1.getScore().getHi() << endl;
    }
    else {
        cout << "     High Score: " << p2.getScore().getHi() << endl;
    }
    cout << "----------- -----------" << endl;

    auto g1 = p1.getBoard().renderWithCurrent(p1.getCurrentBlock(), p1.getCurR(), p1.getCurC());
    auto g2 = p2.getBoard().renderWithCurrent(p2.getCurrentBlock(), p2.getCurR(), p2.getCurC());

    //print p1
    for (int r = 0; r < 18; ++r) {
        for (int c = 0; c < 11; ++c) {
            char ch1 = g1[r][c];
            if (owner == 0) {
                // p1 is blinded
                if ((r >= 2 && r <= 11) && (c >= 2 && c <= 8)) {
                    cout << "?";
                    continue;
                }
            }
            cout << (ch1 == ' ' ? '.' : ch1); // if it is not a blinded square
        }

        // spacing between two players
        cout << " ";

        //print p2
        for (int c = 0; c < 11; ++c) {
            char ch2 = g2[r][c];
            if (owner == 1) {
                // p2 is blinded
                if ((r >= 2 && r <= 11) && (c >= 2 && c <= 8)) {
                    cout << "?";
                    continue;
                }
            }
            cout << (ch2 == ' ' ? '.' : ch2); // if it is not a blinded square
        }
        cout << endl;
    }

    cout << "----------- -----------" << endl;
    cout << "Next:       Next:" << endl;

    // ***
    // display the actual block not just the type
    
    // should be of type vector<Point> (where origin is 0,0 so need to offset p2's grid by a bit)
    auto p1nextBlockPoints = p1.getNextBlock().getOffsets();
    auto p2nextBlockPoints = p2.getNextBlock().getOffsets();
    char p1Char = p1.getNextBlock().getChar();
    char p2Char = p2.getNextBlock().getChar();

    // need to put it in a grid (2 rows x 4 cols)
    vector<std::vector<char>> p1Next(rowsForNext, std::vector<char>(colsForNext, ' '));
    vector<std::vector<char>> p2Next(rowsForNext, std::vector<char>(colsForNext, ' '));

    for (auto &p : p1nextBlockPoints) {
        p1Next[p.r][p.c] = p1Char;
    }

    for (auto &p : p2nextBlockPoints) {
        p2Next[p.r][p.c] = p2Char;
    }

    // display grid
    for (int r = 0; r < rowsForNext; ++r) {
        string line1;
        string line2;
        for (int c = 0; c < colsForNext; ++c) {
            cout << (p1Next[r][c] == ' ' ? ' ' : p1Next[r][c]);
        }
        cout << "        ";
        for (int c = 0; c < colsForNext; ++c) {
            cout << (p2Next[r][c] == ' ' ? ' ' : p2Next[r][c]);
        }
        cout << endl;
    }
}

HeavyEffect::HeavyEffect(int p) : PlayerEffect(p) {}

void HeavyEffect::apply(Player &p1, Player &p2) {
}

ForceEffect::ForceEffect(int p, char f) : PlayerEffect(p), forcedType{f} {}

void ForceEffect::apply(Player &p1, Player &p2) {
    if (owner == 0) {
        p1.setCurrent(makeBlock(charToBlockType(forcedType), p1.getLevelNum()));
    } else {
        p2.setCurrent(makeBlock(charToBlockType(forcedType), p2.getLevelNum()));
    }
}
