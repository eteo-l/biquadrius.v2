module Score;

void Score::resetCurrent() { current = 0; }

void Score::addLinesCleared(int level, int lines) {
    if (lines <= 0) return;
    int pts = (level + lines) * (level + lines);  // spec formula :contentReference[oaicite:5]{index=5}
    current += pts;
    if (current > hi) hi = current;
}

void Score::addBlockCleared(int levelCreated) {
    int pts = (levelCreated + 1) * (levelCreated + 1); // spec :contentReference[oaicite:6]{index=6}
    current += pts;
    if (current > hi) hi = current;
}

int Score::getCurrent() const { return current; }
int Score::getHi() const { return hi; }
