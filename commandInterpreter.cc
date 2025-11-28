export module CommandInterpreter;

import <string>;
import <iostream>;
import <string>;
import Types;

export class CommandInterpreter {
public:
    struct theParse {
        int mult;
        CommandType cmd;
        char forced;
        std::string file;
        theParse(int mult, CommandType cmd, char forced, std::string file);
    };
    // some helpers
    // bool startsWith(const std::string &s, const std::string &p) const;
    bool isADigit(char c) const;

    // returns (multiplier, commandType, optional forced block char)
    theParse parse(const std::string &line) const;
};
