#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <fstream>
#include <cstdlib>
using namespace std;
// Check if player has won the game
bool isCorrectGuess(const string &secretWord, const vector<bool> &guessedLetters) {
    for (size_t i = 0; i < secretWord.size(); ++i) {
        if (!guessedLetters[i]) { // If the number of guessed letters != the number of letters in the secret word,
            return false; // Return false. The player has not won the game
        }
    }
    return true; // Otherwise, return true. The player has won the game 
}

// Draw the Hangman figure based on the number of incorrect guesses
void drawHangman(int incorrectGuesses) {
    if (incorrectGuesses == 0){
        cout << "  ________" << endl;
        cout << " |        |" << endl;
        cout << " |" << endl;
        cout << " |" << endl;
        cout << " |" << endl;
        cout << " |" << endl;
        cout << "_|________" << endl;
    }
    else if (incorrectGuesses == 1) {
        cout << "  ________" << endl;
        cout << " |        |" << endl;
        cout << " |        O" << endl;
        cout << " |" << endl;
        cout << " |" << endl;
        cout << " |" << endl;
        cout << "_|________" << endl;
    }
    else if (incorrectGuesses == 2) {
        cout << "  ________" << endl;
        cout << " |        |" << endl;
        cout << " |        O" << endl;
        cout << " |        |" << endl;
        cout << " |" << endl;
        cout << " |" << endl;
        cout << "_|________" << endl;
    }
    else if (incorrectGuesses == 3) {
        cout << "  ________" << endl;
        cout << " |        |" << endl;
        cout << " |        O" << endl;
        cout << " |       /|" << endl;
        cout << " |" << endl;
        cout << " |" << endl;
        cout << "_|________" << endl;
    }
    else if (incorrectGuesses == 4) {
        cout << "  ________" << endl;
        cout << " |        |" << endl;
        cout << " |        O" << endl;
        cout << " |       /|\\" << endl;
        cout << " |" << endl;
        cout << " |" << endl;
        cout << "_|________" << endl;
    }
    else if (incorrectGuesses == 5) {
        cout << "  ________" << endl;
        cout << " |        |" << endl;
        cout << " |        O" << endl;
        cout << " |       /|\\" << endl;
        cout << " |       / " << endl;
        cout << " |" << endl;
        cout << "_|________" << endl;
    }
    else {
        cout << "  ________" << endl;
        cout << " |        |" << endl;
        cout << " |        O" << endl;
        cout << " |       /|\\" << endl;
        cout << " |       / \\" << endl;
        cout << " |" << endl;
        cout << "_|________" << endl;
    }
}

int main() {
    vector<string> words; // Initialize vector of words we will use in our hangman game
    string word;
    ifstream inputFile("words.txt"); // Read from input word file 
    while (getline(inputFile, word)) {
        if (!word.empty() && word[word.size() - 1] == '\r') { // Remove endline "\n" of each word
            word = word.substr(0, word.size() - 1);
        }
        words.push_back(word); // Then, insert each word into our vector of words
    }

    inputFile.close(); // Close input file 
    srand(static_cast<unsigned int>(time(nullptr))); // Seed the random number generator with the current time,
    string secretWord = words[rand() % words.size()]; // Then use that number to pick a word at random
    vector<bool> guessedLetters(secretWord.size(), false);
    int attemptsLeft = 6; // Initialize the number of attempts given to a user
    cout << "Hangman Game" << endl;

    while (attemptsLeft > 0) { // While, the user has remaining attempts
        // Display the word with underscores for unguessed letters
        cout << "Secret Word: ";
        for (size_t i = 0; i < secretWord.size(); ++i) {
            if (guessedLetters[i]) {
                cout << secretWord[i] << " "; // If letter is guessed correctly, display the letter
            } else {
                cout << "_ "; // Otherwise, display letters as a series of underscores
            }
        }
        cout << endl;
        char inputChar;
        cout << "Guess a letter: "; // User provides a letter as input
        cin >> inputChar;
        bool letterFound = false;
        for (size_t i = 0; i < secretWord.size(); ++i) { // Check if the letter is part of the word
            if (secretWord[i] == inputChar) {
                guessedLetters[i] = true;
                letterFound = true;
            }
        }

        if (!letterFound) {
            --attemptsLeft; // If guess is incorrect, decrease the number of attempts by 1
            cout << "Incorrect guess. Attempts left: " << attemptsLeft << endl;
        }
        drawHangman(6 - attemptsLeft);
        if (isCorrectGuess(secretWord, guessedLetters)) { // If user has correctly guessed the entire word, they have won the game
            cout << "Congratulations! You have won the game. The word was:" << secretWord << endl;
            break;
        }
    }

    if (attemptsLeft <= 0) { // If the user has no attempts remaining,
        cout << "Game Over! The word was: " << secretWord << endl; // Game over. The user has lost the game
    }

    return 0;
}
