module Game;

import <iostream>;
import <string>;
import <fstream>;
import Types;

using namespace std;

static Player *active = nullptr; // currently active player
static bool blindPrint = false; // variable to know if blind version of board should be printed

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

    while (getline(cin, line)) {
        auto temp = parser.parse(line);
        auto mult = temp.mult;
        auto cmd = temp.cmd;
        auto forced = temp.forced;
        auto file = temp.file;

        active = (turn == 0 ? &p1 : &p2);

        if (cmd == CommandType::EOFCommand) break;

        // find if heavy effect is active for active player
        HeavyEffect *heavyEffect = nullptr;
        for (auto &eff : effects) {
            if (auto *heavy = dynamic_cast<HeavyEffect*>(eff.get())) {
                if (heavy->getOwner() == turn) {
                    heavyEffect = heavy;
                    break;
                } 
            }
        }

        if (forced != 0) {
            active->forceBlock(charToBlockType(forced));
        } else {
            for (int k = 0; k < mult; ++k) {
                if (cmd == CommandType::Drop) {
                    drop();
                } 
                else if (cmd == CommandType::Left) {
                    active->moveLeft();
                    checkHeavy(heavyEffect);
                }
                else if (cmd == CommandType::Right) {
                    // if heavy moveDown()
                    active->moveRight();
                    checkHeavy(heavyEffect);
                }
                else if (cmd == CommandType::Down) {
                    // if heavy moveDown()
                    active->moveDown();
                }
                else if (cmd == CommandType::CW) {
                    // if heavy moveDown()
                    active->rotateCW();
                }
                else if (cmd == CommandType::CCW) {
                    active->rotateCCW();
                    // if heavy moveDown()
                }
                else if (cmd == CommandType::LevelUp) {
                    active->levelUp();
                }
                else if (cmd == CommandType::LevelDown) {
                    active->levelDown();
                }
                else if (cmd == CommandType::Restart) {
                    resetGame();
                }
                else if (cmd == CommandType::NoRandom) {
                    ifstream in{file};
                    vector<BlockType> seq;
                    char c;
                    while (in >> c) {
                        seq.push_back(charToBlockType(c));
                    }
                    active->setOverride(seq);
                }
                else if (cmd == CommandType::Random) {
                    active->clearOverride();
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

        if (gameOver) {
            cout << "Game Over! Player " << (1-turn) << " wins" << endl;

            resetGame();
        }
    }
}

void Game::drop() {
    // remove blind effect after drop
    for (size_t i = 0; i < effects.size(); ++i) {
        if (dynamic_cast<BlindEffect*>(effects[i].get())) {
            effects.erase(effects.begin() + i);  
            blindPrint = false;   
            break;
        }
    } 

    // new for player effect
    if (active->drop() >= 2) {
        int opponent = 1 - turn;
        applyEffects(opponent);
    }

    // apply forceeffect if exists and then deletes it
    for (size_t i = 0; i < effects.size(); ++i) {
        if (dynamic_cast<ForceEffect*>(effects[i].get())) {
            effects[i]->apply(p1, p2);
            effects.erase(effects.begin() + i);  
            break;
        }
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

void Game::applyEffects(int opponent) {
    std::string action;

    // Prompt for effect until valid
    while (true) {
        std::cout << "Enter effect to apply to opponent (blind, heavy, force): ";
        if (!std::getline(std::cin, action)) continue; // bad input → retry
        if (action.empty()) continue;

        if (action == "blind" || action == "heavy" || action.starts_with("force")) break;

        std::cout << "Invalid effect." << endl;
    }

    // Apply the chosen effect
    if (action == "blind") {
        effects.push_back(std::make_unique<BlindEffect>(opponent));
        std::cout << "Blind effect applied!" << endl;
    }
    else if (action == "heavy") {
        effects.push_back(std::make_unique<HeavyEffect>(opponent));
        std::cout << "Heavy effect applied!" << endl;
    }
    else if (action.starts_with("force")) {
        // Prompt for block type until valid
        char blockType;
        char block = '\0';
        if (action.length() == 7) {
            block = action[6]; // extract after "force "
        }
        while (true) {
            blockType = std::toupper(block);
            if (blockType=='I' || blockType=='J' || blockType=='L' ||
                blockType=='O' || blockType=='S' || blockType=='T' ||
                blockType=='Z') break;

            std::cout << "Invalid block type. Enter block type (I, J, L, O, S, T, Z): " << endl;
            while (!(std::cin >> block)) {
                std::cin.clear(); 
                std::cin.ignore(10000,'\n');
            }
        }

        // Apply ForceEffect to the opponent
        effects.push_back(std::make_unique<ForceEffect>(opponent, blockType));
        std::cout << "Force effect applied! Next block will be: " << blockType << endl;
    }
}

void Game::checkHeavy(HeavyEffect *heavyEffect) {
    if (heavyEffect) {
        heavyEffect->apply(p1, p2);
        if (heavyEffect->getDropped()) {
            heavyEffect->setDropped(false); // reset for next turn
            drop();
        }
    }
}

void Game::resetGame() {
    p1.reset(true);
    p2.reset(false);
    turn = 0;
    gameOver = false;
    td.render();
    effects.clear();
}
