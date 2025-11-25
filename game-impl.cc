module Game;

import <iostream>;
import <string>;
import Types;

Game::Game(int startLevel)
    : p1{startLevel}, p2{startLevel}, td{&p1, &p2} {
    p1.getBoard().attach(&td);
    p2.getBoard().attach(&td);
    p1.getBoard().notify();
    p2.getBoard().notify();
}

void Game::run() {
    std::string line;

    while (!gameOver && std::getline(std::cin, line)) {
        auto [mult, cmd, forced] = parser.parse(line);

        Player *active = (turn == 0 ? &p1 : &p2);

        if (cmd == CommandType::EOFCommand) break;

        if (forced != 0) {
            active->forceBlock(charToBlockType(forced));
        } else {
            for (int k = 0; k < mult; ++k) {
                switch (cmd) {
                    case CommandType::Left: active->moveLeft(); break;
                    case CommandType::Right: active->moveRight(); break;
                    case CommandType::Down: active->moveDown(); break;
                    case CommandType::CW: active->rotateCW(); break;
                    case CommandType::CCW: active->rotateCCW(); break;
                    case CommandType::LevelUp: active->levelUp(); break;
                    case CommandType::LevelDown: active->levelDown(); break;
                    case CommandType::Restart:
                        p1.reset(); p2.reset(); turn = 0; break;
                    case CommandType::Drop: {
                        active->drop();
                        turn = 1 - turn; // switch player turn after drop :contentReference[oaicite:8]{index=8}
                        active = (turn == 0 ? &p1 : &p2);
                        if (!active->spawnNext()) {
                            std::cout << "Game Over! Player " << (1-turn) << " wins.\n";
                            gameOver = true;
                        }
                        break;
                    }
                    default: break;
                }
            }
        }

        p1.getBoard().notify();
        p2.getBoard().notify();
        td.render();
    }
}
