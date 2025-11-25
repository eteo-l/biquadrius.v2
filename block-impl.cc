module Block;

import <algorithm>;

Block::Block(BlockType t, std::vector<Point> off, int lvl)
    : type{t}, offsets{std::move(off)}, levelCreated{lvl} {}

BlockType Block::getType() const { return type; }
char Block::getChar() const { return blockTypeToChar(type); }
int Block::getLevelCreated() const { return levelCreated; }
const std::vector<Point>& Block::getOffsets() const { return offsets; }

// helper: normalize so lower-left of bounding box is at (0,0)
static void normalize(std::vector<Point> &pts) {
    int minR = pts[0].r, minC = pts[0].c;
    for (auto &p : pts) {
        minR = std::min(minR, p.r);
        minC = std::min(minC, p.c);
    }
    for (auto &p : pts) {
        p.r -= minR;
        p.c -= minC;
    }
}

void Block::rotateCW() {
    // CW: (r, c) -> (c, -r)
    for (auto &p : offsets) {
        int nr = p.c;
        int nc = -p.r;
        p.r = nr;
        p.c = nc;
    }
    normalize(offsets); // preserve lower-left of bounding box per spec :contentReference[oaicite:2]{index=2}
}

void Block::rotateCCW() {
    // CCW: (r, c) -> (-c, r)
    for (auto &p : offsets) {
        int nr = -p.c;
        int nc = p.r;
        p.r = nr;
        p.c = nc;
    }
    normalize(offsets);
}

std::unique_ptr<Block> makeBlock(BlockType t, int lvl) {
    // Initial shapes based on spec :contentReference[oaicite:3]{index=3}
    switch (t) {
        case BlockType::I:
            return std::make_unique<Block>(t, std::vector<Point>{{0,0},{1,0},{2,0},{3,0}}, lvl);
        case BlockType::J:
            return std::make_unique<Block>(t, std::vector<Point>{{0,0},{0,1},{1,1},{2,1}}, lvl);
        case BlockType::L:
            return std::make_unique<Block>(t, std::vector<Point>{{2,0},{0,1},{1,1},{2,1}}, lvl);
        case BlockType::O:
            return std::make_unique<Block>(t, std::vector<Point>{{0,0},{1,0},{0,1},{1,1}}, lvl);
        case BlockType::S:
            return std::make_unique<Block>(t, std::vector<Point>{{1,0},{2,0},{0,1},{1,1}}, lvl);
        case BlockType::Z:
            return std::make_unique<Block>(t, std::vector<Point>{{0,0},{1,0},{1,1},{2,1}}, lvl);
        case BlockType::T:
            return std::make_unique<Block>(t, std::vector<Point>{{0,0},{1,0},{2,0},{1,1}}, lvl);
        case BlockType::Star:
            return std::make_unique<Block>(t, std::vector<Point>{{0,0}}, lvl);
    }
    return std::make_unique<Block>(BlockType::I, std::vector<Point>{{0,0},{1,0},{2,0},{3,0}}, lvl);
}
