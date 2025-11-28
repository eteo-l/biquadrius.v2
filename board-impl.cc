module Board;

/*Board::Board() : grid(Rows, std::vector<char>(Cols, ' ')) {}*/

Board::Board()
    : grid(Rows, std::vector<char>(Cols, ' ')),
      blockIds(Rows, std::vector<int>(Cols, -1)) {}

void Board::reset() {
    for (auto &row : grid) {
        for (auto &cell : row) {
            cell = ' ';
        }
    }
    // render
    notify();
}

const std::vector<std::vector<char>>& Board::getGrid() const { return grid; }

bool Board::canPlace(const Block &b, int baseR, int baseC) const {
    for (auto &off : b.getOffsets()) {
        int r = baseR + off.r;
        int c = baseC + off.c;

        if (r < 0 || r >= Rows || c < 0 || c >= Cols) return false; // Lorena edited, changed r < 3 to r < 0
        if (grid[r][c] != ' ') return false;
    }
    // blocks.push_back(b);
    return true;
}

void Board::place(const Block &b, int baseR, int baseC, int blockId) {
    for (auto &off : b.getOffsets()) {
        int r = baseR + off.r;
        int c = baseC + off.c;
        grid[r][c] = b.getChar();
        blockIds[r][c] = blockId; // NEW xinyu
    }
    // re-render the board
    notify();
}

 
bool Board::canMove(const Block &b, int baseR, int baseC, int dr, int dc) const {
    return canPlace(b, baseR + dr, baseC + dc);
}

int Board::clearFullRows() {
    int cleared = 0;
    for (int r = 0; r < Rows; ++r) {
        bool full = true;
        for (int c = 0; c < Cols; ++c) {
            if (grid[r][c] == ' ') { full = false; break; }
        }
        if (full) {
            cleared++;
            // drop everything above down by 1
            for (int rr = r; rr > 0; --rr) {
                grid[rr] = grid[rr-1];
                blockIds[rr] = blockIds[rr-1]; // NEW xinyu
            }
            grid[0] = std::vector<char>(Cols, ' ');
            blockIds[0] = std::vector<int>(Cols, -1); // NEW xinyu
        }
    }
    
    /* i think this part is unnecessary since game already calls notify() after each command
    if (cleared > 0) {
        notify();
    } 
    */
    return cleared;
}
std::vector<std::vector<char>> Board::renderWithCurrent(const Block &b, int baseR, int baseC) const {
    auto tmp = grid;
    if (baseR == -1) return tmp; // if game over, just return the grid
    for (auto &off : b.getOffsets()) {
        int r = baseR + off.r;
        int c = baseC + off.c;
        if (r >= 0 && r < Rows && c >= 0 && c < Cols)
            tmp[r][c] = b.getChar();
    }
    return tmp;
}

// NEW xinyu
const std::vector<std::vector<int>>& Board::getBlockIdGrid() const {
    return blockIds;
}

void Board::eraseBlock(int blockId) {
    for (int r = 0; r < Rows; ++r) {
        for (int c = 0; c < Cols; ++c) {
            if (blockIds[r][c] == blockId) {
                blockIds[r][c] = -1;
                grid[r][c] = ' ';
            }
        }
    }
    notify();
}
