module Player;

import <utility>;
import Types;
import Block;
import Level;
import Board;
import Score; 

// mike new overloaded player ctor
Player::Player(int startLevel, const std::vector<BlockType> *level0Seq)
{
    if (startLevel == 0 && level0Seq) {
        level = makeLevel0(*level0Seq);
    } else {
        level = makeLevel(startLevel);
    }

    current = level->createBlock();
    next = level->createBlock();
    curR = 3 - current->getMaxRelRow();
}

Board& Player::getBoard() { 
    return board;
}

void Player::reset() {
    board.reset();
    score.resetCurrent();
    level = makeLevel(0);
    current = level->createBlock();
    next = level->createBlock();
    curR = 3; curC = 0;
}

const Board& Player::getBoard() const {
    return board;
}
const Block& Player::getCurrentBlock() const {
    return *current;
}
const Block& Player::getNextBlock() const {
    return *next;
}
int Player::getLevelNum() const {
    return level->getLevelNum();
}
const Score& Player::getScore() const {
    return score;
}
int Player::getCurR() const {
    return curR;
}
int Player::getCurC() const {
    return curC;
}
void Player::setCurR(int r) {
    curR = r;
}

bool Player::spawnNext() {
    current = std::move(next);
    next = level->createBlock();
    curR = 3 - current->getMaxRelRow(); curC = 0;
    // check if current block fits if its bottom row is occupying the row below the reserve rows
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
    /*while (board.canMove(*current, curR, curC, +1, 0)) {
        curR++;
    }
    board.place(*current, curR, curC);
    int cleared = board.clearFullRows();
    score.addLinesCleared(level->getLevelNum(), cleared);
    // block-cleared scoring later when you track block IDs
    spawnNext();
    return cleared;*/
    // NEW: (xinyu)
    while (board.canMove(*current, curR, curC, +1, 0)) {
        curR++;
    }

    int id = nextBlockId++;
    bool isExpiring = level->isDisappearingBlock();
    int timeout = isExpiring ? 10 : -1;

    droppedBlocks.push_back(DroppedBlock{
        id,
        current->getLevelCreated(),
        true,
        timeout
    });

    board.place(*current, curR, curC, id);
    int cleared = board.clearFullRows();

    score.addLinesCleared(level->getLevelNum(), cleared);

    // NEW: check which blocks are now fully gone, 
    // and check for Blocks dropped before 10 more blocks dropped
    updateClearedBlocksScoring();
    decrementAndExpireOldBlocks(); 

    spawnNext();
    return cleared;
    
}

// NEW xinyu Helper function
void Player::updateClearedBlocksScoring() {
    const auto &ids = board.getBlockIdGrid();
    // mark which ids are still present
    std::vector<bool> present(nextBlockId, false);

    for (int r = 0; r < Board::Rows; ++r) {
        for (int c = 0; c < Board::Cols; ++c) {
            int id = ids[r][c];
            if (id >= 0 && id < nextBlockId) {
                present[id] = true;
            }
        }
    }

    // any droppedBlock with alive && not present => fully cleared now
    for (auto &db : droppedBlocks) {
        if (db.alive && !present[db.id]) {
            db.alive = false;
            score.addBlockCleared(db.levelCreated);
        }
    }
}

// NEW xinyu Helper function
void Player::decrementAndExpireOldBlocks() {
    for (auto &db : droppedBlocks) {
        if (!db.alive) continue;
        if (db.dropsLeft < 0) continue; // non-expiring

        db.dropsLeft--;
        if (db.dropsLeft == 0) {
            // erase this block from Board, but no score
            board.eraseBlock(db.id);
            db.alive = false;
        }
    }
}

void Player::levelUp() {
    int n = level->getLevelNum();
    n++;
    if (n == 4) n = 3;
    level = makeLevel(n);
}
void Player::levelDown() {
    int n = level->getLevelNum();
    level = makeLevel(n - 1);
    // n--;
    // if (n <= 0) {
    //     n = 0;
    //     // need the sequence here!
    //     level = makeLevel0(const std::vector<BlockType> &sequence);
    //     return;
    // }
    // level = makeLevel(n);
}

void Player::forceBlock(BlockType t) {
    current = makeBlock(t, level->getLevelNum());
    curR = 3; curC = 0;
}
