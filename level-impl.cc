module Level;

import <cstdlib>;
import Types;
import Block;

Level::Level(int n) : levelNum{n} {}
int Level::getLevelNum() const { return levelNum; }

class LevelBasic : public Level {
public:
    LevelBasic(int n) : Level{n} {}
    std::unique_ptr<Block> createBlock() override {
        // Basic random like Level2 (equal probability) for now
        int r = std::rand() % 7;
        BlockType t = static_cast<BlockType>(r);
        return makeBlock(t, levelNum);
    }
};

std::unique_ptr<Level> makeLevel(int n) {
    if (n < 0) n = 0;
    if (n > 4) n = 4;
    return std::make_unique<LevelBasic>(n);
}
