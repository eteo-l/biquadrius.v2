module CommandInterpreter;

import <cctype>;
import <tuple>;

static bool startsWith(const std::string &s, const std::string &p) {
    return s.size() >= p.size() && s.substr(0, p.size()) == p;
}


// REMOVE TUPLE!!!
// return a struct instead


// theParse CommandInterpreter::parse(const std::string) {
//     if (line.empty()) return theParse{1, CommandType::Invalid, 0};

//     int i = 0;
//     int mult = 0;

//     while

// }

std::tuple<int, CommandType, char> CommandInterpreter::parse(const std::string &line) const {
    if (line.empty()) return {1, CommandType::Invalid, 0};

    int i = 0, mult = 0;
    while (i < static_cast<int>(line.size()) && std::isdigit(line[i])) {
        mult = mult * 10 + (line[i] - '0');
        i++;
    }
    if (mult == 0) mult = 1;

    std::string cmd = line.substr(i);

    if (cmd == "EOF") return {1, CommandType::EOFCommand, 0};

    if (startsWith(cmd, "left")) return {mult, CommandType::Left, 0};
    if (startsWith(cmd, "right")) return {mult, CommandType::Right, 0};
    if (startsWith(cmd, "down")) return {mult, CommandType::Down, 0};
    if (startsWith(cmd, "drop")) return {mult, CommandType::Drop, 0};
    if (startsWith(cmd, "clockwise")) return {mult, CommandType::CW, 0};
    if (startsWith(cmd, "counterclockwise")) return {mult, CommandType::CCW, 0};
    if (startsWith(cmd, "levelup")) return {mult, CommandType::LevelUp, 0};
    if (startsWith(cmd, "leveldown")) return {mult, CommandType::LevelDown, 0};
    if (startsWith(cmd, "restart")) return {1, CommandType::Restart, 0};

    // testing commands I/J/L/O/S/Z/T
    if (cmd.size() == 1 && std::string("IJLOSTZ").find(cmd[0]) != std::string::npos) {
        return {1, CommandType::Invalid, cmd[0]};
    }

    return {1, CommandType::Invalid, 0};
}
