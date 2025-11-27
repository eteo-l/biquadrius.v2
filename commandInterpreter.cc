export module CommandInterpreter;

import <string>;
import Types;

export class CommandInterpreter {
public:
    struct theParse {
        int mult;
        CommandType cmd;
        char forced;
        theParse(int mult, CommandType cmd, char forced);
    };
    // returns (multiplier, commandType, optional forced block char)
    theParse parse(const std::string &line) const;
};
