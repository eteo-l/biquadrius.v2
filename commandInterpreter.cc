export module CommandInterpreter;

import <string>;
import Types;

export class CommandInterpreter {
public:
    // returns (multiplier, commandType, optional forced block char)
    std::tuple<int, CommandType, char> parse(const std::string &line) const;
};
