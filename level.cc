export module Level;

import <memory>;
import <vector>;
import Block;
import Types;

export class Level {
protected:
    int levelNum;
public:
    Level(int n);
    virtual ~Level() = default;

    int getLevelNum() const;

    // block factory
    virtual std::unique_ptr<Block> createBlock() = 0;

    // use later?
    // virtual bool isHeavy() const;

    // NEW xinyu
    virtual bool isDisappearingBlock() const { return false; }
};

export std::unique_ptr<Level> makeLevelOverride(const std::vector<BlockType> &s);

export std::unique_ptr<Level> makeLevel0(const std::vector<BlockType> &sequence);

export std::unique_ptr<Level> makeLevel(int n);
