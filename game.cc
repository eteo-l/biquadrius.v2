export module Game;

import Player;
import TextDisplay;
import CommandInterpreter;

export class Game {
    Player p1;
    Player p2;
    TextDisplay td;
    CommandInterpreter parser;

    int turn = 0; // 0 => p1, 1 => p2
    bool gameOver = false;

public:
    Game(int startLevel = 0);
    void run();
};
