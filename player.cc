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

    // new 
    std::unique_ptr<Level> overrideLevel;
    bool overrideOn = false;
    std::vector<BlockType> level0Sequence;
    bool hasLevel0Seq = false;


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

    // new mike
    void setOverride(const std::vector<BlockType> &seq);
    void clearOverride();
    bool hasOverride() const;

    std::unique_ptr<Level>& getLevel();

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


    // for forcing a replacement later (I/J/L cmds)
    void forceBlock(BlockType t);
};
