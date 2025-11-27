export module Player;

import <memory>;
import Board;
import Block;
import Level;
import Score;
import Types;

export class Player {
    Board board;
    std::unique_ptr<Level> level;
    Score score;

    std::unique_ptr<Block> current;
    std::unique_ptr<Block> next;

    int curR = 3; // if curR == -1 then indicates game over
    int curC = 0;

public:
    Player(int startLevel = 0);

    void reset();

    // Accessors for display
    Board& getBoard();
    const Board& getBoard() const;
    const Block& getCurrentBlock() const;
    const Block& getNextBlock() const;
    int getLevelNum() const;
    const Score& getScore() const;
    int getCurR() const;
    int getCurC() const;

    // Mutator to indicate block doesn't fit when game over
    void setCurR(int r);

    bool spawnNext(); // returns false if cannot spawn => lose

    // actions
    void moveLeft();
    void moveRight();
    void moveDown();
    // void moveUp();
    void rotateCW();
    void rotateCCW();
    int drop(); // returns lines cleared

    void levelUp();
    void levelDown();

    // for testing replacement later (I/J/L commands)
    void forceBlock(BlockType t);
};
