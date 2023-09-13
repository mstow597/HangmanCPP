#include "Hangman.h"
#include <vector>
#include <cctype>
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>

using namespace std;

Hangman::Hangman(const std::string& phrase) {
    std::string phraseLower = phrase;
    std::transform(phraseLower.begin(), phraseLower.end(), phraseLower.begin(), ::tolower);
    this->phrase = phraseLower;
    this->guessCount = 0;
    this->guessedLetters = std::vector<char> {};
    this->phraseGuessed = std::vector<char> {};
    this->phraseGuessed.resize(phrase.size());

    for (int i = 0; i < phrase.size(); i++) {
        if (std::isspace(phrase[i])) this->phraseGuessed[i] = ' ';
        else this->phraseGuessed[i] = '_';
    }
    
}

void Hangman::play() {
    bool solved = false;

    displayGameProgress();
    
    std::cout << "Please guess a letter: ";
    
    while (this->guessCount < 6 && !solved) {
        char guessedLetter;
        bool guessValid = false;

        while (!guessValid) {
            std::string input;
            std::cin >> input;
            guessedLetter = tolower(input[0]);

            // Check if guessed character is a letter. If not: display error, skip remainder of loop, and start again.
            if (!(std::isalpha(guessedLetter))) {
                std::cout << "Letter is not a character [a-zA-Z]. Please try again.";
                continue;
            }

            // Check if guessed character has already been tried. If yes: display error, skip remainder of loop, and start again.
            if (std::find(this->guessedLetters.begin(), this->guessedLetters.end(), guessedLetter) != this->guessedLetters.end()){
                std::cout << "Duplicate entry. Please try again with another letter.";
                continue;
            }

            this->guessedLetters.push_back(guessedLetter);
            guessValid = true;
        }

        if ((this->phrase.find(guessedLetter)) != std::string::npos) {
            this->updatePhraseGuessed(guessedLetter);

            displayGameProgress();
            
            cout << "Character found!" << endl << endl;
            
            solved = checkSolved();
            
            if (!solved) cout << "Please guess another letter: ";
        } else {
            this->incGuessCount();
            
            displayGameProgress();
            
            std::cout << "Sorry! The character " + std::string(1, guessedLetter) + " does not exist in the passphrase." << endl << endl;
            
            if (this->guessCount < 6) std::cout << "Please guess another letter: ";
        }
    };

    if (solved) {
        cout << "Congratulations, you WIN! You guess the passphrase: " + this->phrase << endl << endl;
    } else {
        // Final strike, game over.
        cout << "Sorry you lose! :(\n\n";
        cout << "The correct passphrase: " + this->phrase << endl << endl;
    }


}

void Hangman::incGuessCount() {
    this->guessCount++;
}

bool Hangman::checkSolved() {
    for (int i = 0; i < phrase.size(); i++) {
        if (!(phrase[i] == phraseGuessed[i])) return false;
    }
    return true;
}

void Hangman::updatePhraseGuessed(char ch) {
    for (int i = 0; i < this->phrase.size(); i++) {
        if (this->phrase[i] == ch) phraseGuessed[i] = ch;
    }
}

void Hangman::displayGameProgress() {
    switch (this->guessCount) {
        case 0: {
            std::string hangmanArt = 
            "    _______\n"
            "   |       |\n"
            "   |       \n"
            "   |      \n"
            "   |       \n"
            "   |       \n"
            " __|__    \n"
            "|_____| \n\n";
            std::cout << hangmanArt << std::endl;
        } break;
        case 1: {
                        std::string hangmanArt = 
            "    _______\n"
            "   |       |\n"
            "   |       0\n"
            "   |      \n"
            "   |       \n"
            "   |       \n"
            " __|__    \n"
            "|_____| \n\n";
            std::cout << hangmanArt;
        } break;
        case 2: {
            std::string hangmanArt = 
            "    _______\n"
            "   |       |\n"
            "   |       0\n"
            "   |       |\n"
            "   |       |\n"
            "   |       |\n"
            " __|__    \n"
            "|_____| \n\n";
            std::cout << hangmanArt;
        } break;
        case 3: {
            std::string hangmanArt = 
            "    _______\n"
            "   |       |\n"
            "   |       0\n"
            "   |       |\n"
            "   |       |\n"
            "   |       |\n"
            " __|__    /\n"
            "|_____| \n\n";
            std::cout << hangmanArt;
        } break;
        case 4: {
            std::string hangmanArt = 
            "    _______\n"
            "   |       |\n"
            "   |       0\n"
            "   |       |\n"
            "   |       |\n"
            "   |       |\n"
            " __|__    / \\\n"
            "|_____| \n\n";
            std::cout << hangmanArt;
        } break;
        case 5: {
            std::string hangmanArt = 
            "    _______\n"
            "   |       |\n"
            "   |       0\n"
            "   |      _|\n"
            "   |       |\n"
            "   |       |\n"
            " __|__    / \\\n"
            "|_____| \n\n";
            std::cout << hangmanArt;
        } break;
        case 6: {
            std::string hangmanArt = 
            "    _______\n"
            "   |       |\n"
            "   |       0\n"
            "   |      _|_\n"
            "   |       |\n"
            "   |       |\n"
            " __|__    / \\\n"
            "|_____| \n\n";
            std::cout << hangmanArt;
        } break;
    }

    for (int i = 0; i < this->phraseGuessed.size(); i++) std::cout << std::string(1, this->phraseGuessed[i]) + ' ';

    std::cout << endl << endl;

    std::cout << "Guessed letters: ";
    for (int i = 0; i < this->guessedLetters.size(); i++) std::cout << std::string(1, this->guessedLetters[i]) + ", ";

    std::cout << endl << endl;
}