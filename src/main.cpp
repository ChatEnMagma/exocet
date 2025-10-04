#include "engine.hpp"

int main(int argc, char** argv) {
    exocet::Engine engin;

    if(!engin.init(WIN_MIN_WIDTH, WIN_MIN_HEIGHT, "Exocet")) {
        engin.clean();
        return EXIT_FAILURE;
    }

    engin.run();

    engin.clean();

    return EXIT_SUCCESS;
}