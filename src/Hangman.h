#pragma once

#include <string>
#include <vector>

class Hangman {
    public:
        Hangman(const std::string& phrase);
        void play();
        void incGuessCount();
        void updatePhraseGuessed(char ch);
        void displayGameProgress();     
        bool checkSolved();  
    private:
        int guessCount;
        char guessedLetter;
        std::string phrase;
        std::vector<char> phraseGuessed;
        std::vector<char> guessedLetters;
};