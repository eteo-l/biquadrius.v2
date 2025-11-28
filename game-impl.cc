module Game;

import <iostream>;
import <string>;
import Types;

using namespace std;

Game::Game(int startLevel, const std::vector<BlockType> *seq1, const std::vector<BlockType> *seq2): 
p1{startLevel, seq1}, p2{startLevel, seq2}, td{&p1, &p2} 
{
    p1.getBoard().attach(&td);
    p2.getBoard().attach(&td);
    p1.getBoard().notify();
    p2.getBoard().notify();
}

void Game::run() {
    string line;

    cout << "           ˗ˋˏ ♡ ˎˊ˗" << endl;
    cout << "Welcome to Biquadris!*⸜( •ᴗ• )⸝*" << endl;
    td.render();

    bool blindPrint = false; //new lorena

    while (!gameOver && getline(cin, line)) {
        auto temp = parser.parse(line);
        auto mult = temp.mult;
        auto cmd = temp.cmd;
        auto forced = temp.forced;

        Player *active = (turn == 0 ? &p1 : &p2);

        if (cmd == CommandType::EOFCommand) break;

        if (forced != 0) {
            active->forceBlock(charToBlockType(forced));
        } else {
            for (int k = 0; k < mult; ++k) {
                if (cmd == CommandType::Left) {
                    active->moveLeft();
                }
                else if (cmd == CommandType::Right) {
                    active->moveRight();
                }
                else if (cmd == CommandType::Down) {
                    active->moveDown();
                }
                else if (cmd == CommandType::CW) {
                    active->rotateCW();
                }
                else if (cmd == CommandType::CCW) {
                    active->rotateCCW();
                }
                else if (cmd == CommandType::LevelUp) {
                    active->levelUp();
                }
                else if (cmd == CommandType::LevelDown) {
                    active->levelDown();
                }
                else if (cmd == CommandType::Restart) {
                    p1.reset();
                    p2.reset();
                    turn = 0;
                }
                else if (cmd == CommandType::Drop) {
                    //new lorena
                    // remove blind effect after drop
                    for (size_t i = 0; i < effects.size(); ++i) {
                        if (dynamic_cast<BlindEffect*>(effects[i].get())) {
                            effects.erase(effects.begin() + i);  
                            blindPrint = false;   
                            break;
                        }
                    } 

                    // active->drop();
                    // new for player effect
                    if (active->drop() >= 2) {
                        applyEffects(1 - turn);
                    }

                    // dont call spawnNext() for the player whose turn starting
                    // only the player who dropped should get a new block (alrady in player:;drop())
                    // check if next players current block can be placed at their spawn
                    // position; if not, the game is over.
                    if (!active->getBoard().canPlace(active->getCurrentBlock(), active->getCurR(), active->getCurC())) {
                        active->setCurR(-1); // cant place (by MY definition)
                        gameOver = true;
                    }

                    // switch player turn after drop
                    turn = 1 - turn;
                    active = (turn == 0 ? &p1 : &p2);
                }
                else {
                    // nothing i guess
                }

            }
        }

        p1.getBoard().notify();
        p2.getBoard().notify();
        
        //new
        // print blind version of board if blind effect active
        for (auto &eff : effects) {
            if (auto *blind = dynamic_cast<BlindEffect*>(eff.get())) {
                blindPrint = true;
                blind->apply(p1, p2);
            }
        }

        if (!blindPrint) {
            td.render();
        }
        //new end

        if (gameOver) {
            cout << "Game Over! Player " << (1-turn) << " wins" << endl;
        }
    }
}

// new lorena
void Game::applyEffects(int opponent) {
    std::string action;

    // Prompt for effect until valid
    while (true) {
        std::cout << "Enter effect to apply to opponent (blind, heavy, force): ";
        if (!std::getline(std::cin, action)) continue; // bad input → retry
        if (action.empty()) continue;

        if (action == "blind" || action == "heavy" || action.starts_with("force")) break;

        std::cout << "Invalid effect.\n";
    }

    // Apply the chosen effect
    if (action == "blind") {
        effects.push_back(std::make_unique<BlindEffect>(opponent));
        std::cout << "Blind effect applied!\n";
    }
    else if (action == "heavy") {
        effects.push_back(std::make_unique<HeavyEffect>(opponent));
        std::cout << "Heavy effect applied!\n";
    }
    else if (action.starts_with("force")) {
        // Prompt for block type until valid
        char blockType;
        std::string block;
        while (true) {
            if (action.length() < 7) {
                std::cout << "Enter block type (I, J, L, O, S, T, Z): ";
                if (!std::getline(std::cin, block)) continue; // bad input → retry
                if (block.size() != 1) {
                    std::cout << "Please enter exactly one character.\n";
                    continue;
                }
            } else {
                std::string block = action.substr(6); // extract after "force "
            }
            blockType = std::toupper(block[0]);
            if (blockType=='I' || blockType=='J' || blockType=='L' ||
                blockType=='O' || blockType=='S' || blockType=='T' ||
                blockType=='Z') break;

            std::cout << "Invalid block type. Try again.\n";
        }

        // Apply ForceEffect to the opponent
        effects.push_back(std::make_unique<ForceEffect>(opponent, blockType));
        std::cout << "Force effect applied! Next block will be: " << blockType << "\n";
    }
}
