module CommandInterpreter;

using namespace std;

CommandInterpreter::theParse::theParse(int mult, CommandType cmd, char forced, string file): mult{mult}, cmd{cmd}, forced{forced}, file{file} {}


bool CommandInterpreter::isADigit(char c) const {
    return c >= '0' && c <= '9';
}


// Mike new
CommandInterpreter::theParse CommandInterpreter::parse(const std::string &line) const {
    if (line.empty()) return theParse{1, CommandType::Invalid, 0, ""};

    int i = 0;
    int mult = 0;

    // added static_cast to remove warnings of type comparison, signed vs unsigned
    while (i < static_cast<int>(line.size()) && isADigit(line[i])) {
        mult = mult * 10 + (line[i] - '0');
        i++;
    }

    if (mult == 0) mult = 1;
    string cmd = line.substr(i);

    if (cmd == "EOF") return theParse{1, CommandType::EOFCommand, 0, ""};
    string leftPrefix = "lef";
    string rightPrefix = "ri";
    string downPrefix = "do";
    string dropPrefix = "dr";
    string cwPrefix = "cl";
    string ccwPrefix = "co";
    string levelUpPrefix = "levelu";
    string levelDownPrefix = "leveld";
    string restartPrefix = "re";
    string randomPrefix = "ra";
    string norandomPrefix = "no";
    // string sequencePrefix = "s";


    
    if (cmd.substr(0, leftPrefix.size()) == leftPrefix) return theParse{mult, CommandType::Left, 0, ""};
    if (cmd.substr(0, rightPrefix.size()) == rightPrefix) return theParse{mult, CommandType::Right, 0, ""};
    if (cmd.substr(0, downPrefix.size()) == downPrefix) return theParse{mult, CommandType::Down, 0, ""};
    if (cmd.substr(0, dropPrefix.size()) == dropPrefix) return theParse{mult, CommandType::Drop, 0, ""};
    if (cmd.substr(0, cwPrefix.size()) == cwPrefix) return theParse{mult, CommandType::CW, 0, ""};
    if (cmd.substr(0, ccwPrefix.size()) == ccwPrefix) return theParse{mult, CommandType::CCW, 0, ""};
    if (cmd.substr(0, levelUpPrefix.size()) == levelUpPrefix) return theParse{mult, CommandType::LevelUp, 0, ""};
    if (cmd.substr(0, levelDownPrefix.size()) == levelDownPrefix) return theParse{mult, CommandType::LevelDown, 0, ""};
    if (cmd.substr(0, restartPrefix.size()) == restartPrefix) return theParse{1, CommandType::Restart, 0, ""};
    if (cmd.substr(0, norandomPrefix.size()) == norandomPrefix) {return theParse{1, CommandType::NoRandom, 0, cmd.substr(9)}; }// 8 chars in sequence
    if (cmd.substr(0, randomPrefix.size()) == randomPrefix) return theParse{1, CommandType::Random, 0, ""};


    // testing the single blocks
    if (cmd.size() == 1) {
        if (cmd[0] == 'I' || cmd[0] == 'J' || cmd[0] == 'L' || cmd[0] == 'O' || cmd[0] == 'S' || cmd[0] == 'T' || cmd[0] == 'Z') {
            return theParse{1, CommandType::Invalid, cmd[0], ""};
        }
    }

    return theParse{1, CommandType::Invalid, 0, ""};

}
