module Block;

import <algorithm>;

Block::Block(BlockType t, std::vector<Point> off, int lvl)
    : type{t}, offsets{std::move(off)}, levelCreated{lvl} {}

BlockType Block::getType() const { return type; }
char Block::getChar() const { return blockTypeToChar(type); }
int Block::getLevelCreated() const { return levelCreated; }
const std::vector<Point>& Block::getOffsets() const { return offsets; }

// Mike
// int Block::minimum(int x, int y) {
//     if (x <= y) return x;
//     return y;
// }

// helper: normalize so lower-left of bounding box is at (0,0)
static void normalize(std::vector<Point> &pts) {
    int minR = pts[0].r;
    int minC = pts[0].c;
    for (auto &p : pts) {
        // minR = (minR <= minC ? minR : p.r); DOES NOT WORK
        // minC = (minC <= p.c ? minC : p.c);
        minR = std::min(minR, p.r);
        minC = std::min(minC, p.c);
    }
    for (auto &p : pts) {
        p.r -= minR;
        p.c -= minC;
    }
}

void Block::rotateCW() {
    // CW: (r, c) ==> (c, -r)
    for (auto &p : offsets) {
        int nr = p.c;
        int nc = -p.r;
        p.r = nr;
        p.c = nc;
    }
    normalize(offsets); // preserve the lower-left of bounding box based on :contentReference[oaicite:2]{index=2}
}

void Block::rotateCCW() {
    // CCW: (r, c) ==> (-c, r)
    for (auto &p : offsets) {
        int nr = -p.c;
        int nc = p.r;
        p.r = nr;
        p.c = nc;
    }
    normalize(offsets);
}

// Lorena new
int Block::getMaxRelRow() const {
    int maxR = offsets[0].r;
    for (auto &p : offsets) {
        maxR = std::max(maxR, p.r);
    }
    return maxR;
}

std::unique_ptr<Block> makeBlock(BlockType t, int lvl) {
    // initial blcoks based on :contentReference[oaicite:3]{index=3}
    
    // Mike new
    if (t == BlockType::I) {
        return std::make_unique<Block>(t, std::vector<Point>{{0,0},{0,1},{0,2},{0,3}}, lvl);
    } else if (t == BlockType::J) {
        return std::make_unique<Block>(t, std::vector<Point>{{0,0},{1,0},{1,1},{1,2}}, lvl);
    } else if (t == BlockType::L) {
        return std::make_unique<Block>(t, std::vector<Point>{{0,2},{1,0},{1,1},{1,2}}, lvl);
    } else if (t == BlockType::O) {
        return std::make_unique<Block>(t, std::vector<Point>{{0,0},{0,1},{1,0},{1,1}}, lvl);
    } else if (t == BlockType::S) {
        return std::make_unique<Block>(t, std::vector<Point>{{0,1},{0,2},{1,0},{1,1}}, lvl);
    } else if (t == BlockType::Z) {
        return std::make_unique<Block>(t, std::vector<Point>{{0,0},{0,1},{1,1},{1,2}}, lvl);
    } else if (t == BlockType::T) {
        return std::make_unique<Block>(t, std::vector<Point>{{0,0},{0,1},{0,2},{1,1}}, lvl);
    } else {
        return std::make_unique<Block>(t, std::vector<Point>{{0,0}}, lvl);
    }
}
