#include "Hangman.h"
#include <algorithm>
#include <cctype>
#include <cstring>
#include <iostream>
#include <ostream>
#include <string>

bool checkPassphraseValid(const std::string& str) {
    for (char c : str) {
        if (!std::isalpha(c) && !std::isspace(c)) return false;
    }
    return true;
}

int main() {
    bool playAgain = true;

    while (playAgain) {
        std::string phrase;
        std::string response;
        bool passphraseIsValid = false;

        while (phrase.length() == 0 || !passphraseIsValid) {
            std::cout << "Please enter your passphrase followed by enter: ";
            std::getline(std::cin, phrase);
            std::cout << "\033[2J\033[H";
            
            passphraseIsValid = checkPassphraseValid(phrase);

            if (!passphraseIsValid) std::cout << "Invalid passphrase. Passphrase must only contain letters and spaces. Please try again." << std::endl;
        }

        Hangman hangman = Hangman(phrase);
        hangman.play();

        std::cout << "Play again? (y/n): ";
        std::cin >> response;
        std::transform(response.begin(), response.end(), response.begin(), ::tolower);

        if (!(tolower(response[0]) == 'y')) playAgain = false;
    }

    return 0;
}