export module Level;

import <memory>;
import Block;

export class Level {
protected:
    int levelNum;
public:
    Level(int n);
    virtual ~Level() = default;

    int getLevelNum() const;

    // Factory Method pattern:
    virtual std::unique_ptr<Block> createBlock() = 0;

    virtual bool isHeavy() const { return false; }
};

export std::unique_ptr<Level> makeLevel(int n);
