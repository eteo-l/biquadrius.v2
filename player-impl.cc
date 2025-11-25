module Player;

import <utility>;
import Types;
import Block;
import Level;
import Board;
import Score; 

Player::Player(int startLevel)
    : level{makeLevel(startLevel)} {
    current = level->createBlock();
    next = level->createBlock();
}

Board& Player::getBoard() { return board; }

void Player::reset() {
    board.reset();
    score.resetCurrent();
    level = makeLevel(0);
    current = level->createBlock();
    next = level->createBlock();
    curR = 3; curC = 0;
}

const Board& Player::getBoard() const { return board; }
const Block& Player::getCurrentBlock() const { return *current; }
const Block& Player::getNextBlock() const { return *next; }
int Player::getLevelNum() const { return level->getLevelNum(); }
const Score& Player::getScore() const { return score; }
int Player::getCurR() const { return curR; }
int Player::getCurC() const { return curC; }

bool Player::spawnNext() {
    current = std::move(next);
    next = level->createBlock();
    curR = 3; curC = 0;
    return board.canPlace(*current, curR, curC);
}

void Player::moveLeft() {
    if (board.canMove(*current, curR, curC, 0, -1)) curC--;
}
void Player::moveRight() {
    if (board.canMove(*current, curR, curC, 0, +1)) curC++;
}
void Player::moveDown() {
    if (board.canMove(*current, curR, curC, +1, 0)) curR++;
}
void Player::moveUp() {
    if (board.canMove(*current, curR, curC, -1, 0)) curR--;
}



void Player::rotateCW() {
    auto backup = current->getOffsets();
    current->rotateCW();
    if (!board.canPlace(*current, curR, curC)) {
        // undo rotation if illegal
        *current = Block(current->getType(), backup, current->getLevelCreated());
    }
}

void Player::rotateCCW() {
    auto backup = current->getOffsets();
    current->rotateCCW();
    if (!board.canPlace(*current, curR, curC)) {
        *current = Block(current->getType(), backup, current->getLevelCreated());
    }
}

int Player::drop() {
    while (board.canMove(*current, curR, curC, +1, 0)) {
        curR++;
    }
    board.place(*current, curR, curC);
    int cleared = board.clearFullRows();
    score.addLinesCleared(level->getLevelNum(), cleared);
    // block-cleared scoring later when you track block IDs
    spawnNext();
    return cleared;
}

void Player::levelUp() {
    int n = level->getLevelNum();
    level = makeLevel(n + 1);
}
void Player::levelDown() {
    int n = level->getLevelNum();
    level = makeLevel(n - 1);
}

void Player::forceBlock(BlockType t) {
    current = makeBlock(t, level->getLevelNum());
    curR = 3; curC = 0;
}
