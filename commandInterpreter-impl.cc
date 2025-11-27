module CommandInterpreter;


CommandInterpreter::theParse::theParse(int mult, CommandType cmd, char forced): mult{mult}, cmd{cmd}, forced{forced} {}

bool CommandInterpreter::startsWith(const std::string &s, const std::string &p) const {
    return s.size() >= p.size() && s.substr(0, p.size()) == p;
}

bool CommandInterpreter::isADigit(char c) const {
    return c >= '0' && c <= '9';
}


// Mike new
CommandInterpreter::theParse CommandInterpreter::parse(const std::string &line) const {
    if (line.empty()) return theParse{1, CommandType::Invalid, 0};

    int i = 0;
    int mult = 0;

    while (i < static_cast<int>(line.size()) && isADigit(line[i])) {
        mult = mult * 10 + (line[i] - '0');
        i++;
    }

    if (mult == 0) mult = 1;
    std::string cmd = line.substr(i);

    if (cmd == "EOF") return theParse{1, CommandType::EOFCommand, 0};
    if (cmd == "exit") return theParse{1, CommandType::EOFCommand, 0};

    if (startsWith(cmd, "left")) return theParse{mult, CommandType::Left, 0};
    if (startsWith(cmd, "right")) return theParse{mult, CommandType::Right, 0};
    if (startsWith(cmd, "down")) return theParse{mult, CommandType::Down, 0};
    if (startsWith(cmd, "drop")) return theParse{mult, CommandType::Drop, 0};
    if (startsWith(cmd, "clockwise")) return theParse{mult, CommandType::CW, 0};
    if (startsWith(cmd, "counterclockwise")) return theParse{mult, CommandType::CCW, 0};
    if (startsWith(cmd, "levelup")) return theParse{mult, CommandType::LevelUp, 0};
    if (startsWith(cmd, "leveldown")) return theParse{mult, CommandType::LevelDown, 0};
    if (startsWith(cmd, "restart")) return theParse{1, CommandType::Restart, 0};

    // testing commands I/J/L/O/S/Z/T
    if (cmd.size() == 1 && std::string("IJLOSTZ").find(cmd[0]) != std::string::npos) {
        return theParse{1, CommandType::Invalid, cmd[0]};
    }

    return theParse{1, CommandType::Invalid, 0};

}
