#include <iostream>
#include <cstdlib>
#include "StanfordCPPlib/strlib.h"
#include "Boggle.h"

int main() {
    std::string answer;
    while (true) {
        Boggle boggle;
        boggle.play();

        std::cout << "Would you like to play again? ";
        getline(std::cin, answer);

        if (toLowerCase(answer) == "yes") {
            system("clear");
            continue;
        }

        if (toLowerCase(answer) == "no") {
            string dummy;
            std::cout << std::endl << "[Program finished -- hit RETURN to exit] ";
            getline(std::cin, dummy);
            break;
        }
    }
    return 0;
}