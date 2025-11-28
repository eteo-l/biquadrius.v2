export module Player;

import <memory>;
import <vector>;
import Board;
import Block;
import Level;
import Score;
import Types;

// NEW xinyu
struct DroppedBlock {
    int id;
    int levelCreated;
    bool alive = true;
    int dropsLeft = -1;
};

export class Player {
    Board board;
    std::unique_ptr<Level> level;
    Score score;

    std::unique_ptr<Block> current;
    std::unique_ptr<Block> next;

    int curR = 3; // if curR == -1 then indicates game over
    int curC = 0;

public:
    // NEW xinyu
    std::vector<DroppedBlock> droppedBlocks;
    int nextBlockId = 0;
    int blocksDropped = 0;
    // new fin
    Player(int startLevel = 0, const std::vector<BlockType> *level0Seq = nullptr);
    // Player(int startLevel = 0);


    void reset();

    // getters for display
    Board& getBoard();
    const Board& getBoard() const;
    const Block& getCurrentBlock() const;
    const Block& getNextBlock() const;
    int getLevelNum() const;
    const Score& getScore() const;
    int getCurR() const;
    int getCurC() const;

    // setter to indicate block does not fit when game over
    void setCurR(int r);

    // returns false if cannot spawn => lose
    bool spawnNext(); 

    // move rotate drop leves
    void moveLeft();
    void moveRight();
    void moveDown();
    void rotateCW();
    void rotateCCW();
    int drop();         // returns num of lines cleared
    void updateClearedBlocksScoring();    // Helper function for drop()
    void decrementAndExpireOldBlocks(); // Helper function for erasing blocks
    void levelUp();
    void levelDown();


    // REMOVE???
    // for testing replacement later (I/J/L commands)
    void forceBlock(BlockType t);
};
