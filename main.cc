import Game;
import <cstdlib>;
import <iostream>;

int main(int argc, char **argv) {
    int startLevel = 0;
    int seed = 1;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-startlevel" && i+1 < argc) {
            startLevel = std::stoi(argv[++i]);
        } else if (arg == "-seed" && i+1 < argc) {
            seed = std::stoi(argv[++i]);
        }
    }

    std::srand(seed);

    Game g{startLevel};
    g.run();
}
