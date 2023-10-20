

/* ---------------------------------------------
Program 3: Wordle Reload *

Course: CS 141, Fall 2021. Tues 3pm lab
System: MacOS and iPadOS
Author: Steve Corral, Isaac Rosales
---------------------------------------------*/

#include <algorithm>
#include <cassert>
#include <cctype>
#include <ctime>
#include <ctype.h>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

// Function to read the dictionary txt into a vector
void readWordsIntoDictionary(vector<string> &wordleWords) {
  ifstream inStream;
  inStream.open("wordlewords.txt");
  assert(inStream.fail() == false);
  wordleWords.clear();
  string newWord;
  while (inStream >> newWord) {
    wordleWords.push_back(newWord);
  }
  inStream.close();
}

// Function to display the objective to the user
void gameObjective() {
  cout << "Program 3: Wordle Reload \n"
       << "CS 141, Spring 2022, UIC \n"
       << "\n"
       << "The objective of this game is to guess the randomly selected \n"
       << "word within a given number of attempts. You can select either \n"
       << "a three or five word board. \n"
       << "At the conclusion of the game, stats will be displayed. \n"
       << "Indicators will be given if characters of the user entered \n"
       << "word are reflected in the guessed word. \n"
       << "  - If the character is in the correct position, the character \n"
       << "    will display as an uppercase value. \n"
       << "  - If the character is within the random word, the character \n"
       << "    will display as a lowercase value. \n"
       << "  - If you enter a character that is not in the word,"
       << " an asterisk '*' \n"
       << "    will display. \n";
  cout << endl;
}

// Function to check if the randomly generated word is the same for the inputted
// word.
void wordCheck(string randWord, string &userGuess, string &outputResult) {
  transform(userGuess.begin(), userGuess.end(), userGuess.begin(), ::tolower);
  if (userGuess == randWord) {
    for (int letter = 0; letter < randWord.size(); letter++) {
      outputResult.push_back('[');
      if (userGuess.at(letter) == randWord.at(letter)) {
        outputResult.push_back(char(toupper(userGuess.at(letter))));
      } 
      outputResult.push_back(']');
      outputResult.push_back(' ');
    }
    outputResult.push_back('\n');
  } 
  else {
    for (int letter = 0; letter < randWord.size(); letter++) {
      outputResult.push_back('[');
      if (userGuess.at(letter) == randWord.at(letter)) {
        outputResult.push_back(char(toupper(userGuess.at(letter))));
      } 
      else if (randWord.find(userGuess.at(letter)) != string::npos) {
        outputResult.push_back(userGuess.at(letter));
      } 
      else {
        outputResult.push_back('*');
      }
      outputResult.push_back(']');
      outputResult.push_back(' ');
    }
    outputResult.push_back('\n');
  }
}

// Binary Search Function


int binarySearch (vector<string> wordleWords, string userGuess) {
    int firstWord;
    int midWord;
    int lastWord;

    if (userGuess.size() == 3) {
        firstWord = 0;
        lastWord = 1065 - 1;
        while (lastWord >= firstWord) {
            midWord = (lastWord + firstWord) / 2;
            if (wordleWords.at(midWord) < userGuess) {
                firstWord = midWord + 1;
            }
            else if (wordleWords.at(midWord) > userGuess) {
                lastWord = midWord - 1;
            }
            else {
              return 1;
            }
        }
    }
    return -1;
}

void userInput(string &userGuess, int &binaryCheck, vector<string> wordleWords) {
  cin >> userGuess;
      transform(userGuess.begin(), userGuess.end(), userGuess.begin(), ::tolower);
      binaryCheck = binarySearch(wordleWords, userGuess);
}

int main() {
  vector<string> wordleWords;
  readWordsIntoDictionary(wordleWords);
  srand(1);

  bool gameStatus = true;
  int averageTime = 0, elapsedTime = 0, maxStreak = 0, menuOption = 0, numGuesses = 0, numWins = 0, totalTime = 0, currentStreak = 0, binaryCheck = 0;
  string outputResult, userGuess;
  
  gameObjective();

  while (gameStatus == true) {
    cout << endl << "Select a menu option: \n" << "   1. To play Wordle Reload 3 letter play \n" << "   2. To play Wordle Reload 5 letter play \n" << "   3. Exit the program \n" << "Your choice --> ";
    cin >> menuOption;
    cout << endl;

    if (menuOption == 1){ // To play 3 letters
      elapsedTime = 0;
      numGuesses = 0;
      string randWord = wordleWords.at(rand() % 1065);

      cout << "To get started, enter your first 3 letter word. \n" << "You have 4 attempts to guess the random word. \n" << "The timer will start after your first word entry. \n" << "Try to guess the word within 20 seconds. \n" << endl << endl << "Please enter word -->  ";

      userInput(userGuess, binaryCheck, wordleWords);    
      while ((userGuess.size() < 3) || (userGuess.size() > 3)) {
        if ((userGuess.size() < 3) || (userGuess.size() > 3)) {
          cout << "Invalid word entry " << "- please enter a word that is 3 characters \n" << "long. \n" << endl << "Please enter word -->  ";
          userInput(userGuess, binaryCheck, wordleWords);
        }
      }
      while (binaryCheck == -1) {
        cout << endl << "Not a playable word, please select another word. \n" << endl << "Please enter word -->  ";
        userInput(userGuess, binaryCheck, wordleWords);
      }
      if (userGuess == randWord) {
        numGuesses = numGuesses + 1;
        totalTime = totalTime + 0;
        cout << "\n" << "\n" << "[" << char(toupper(randWord.at(0))) << "] " << "[" << char(toupper(randWord.at(1))) << "] " << "[" << char(toupper(randWord.at(2))) << "] \n" << endl;
      } 
      else {
        numGuesses = numGuesses + 1;
        wordCheck(randWord, userGuess, outputResult);
        cout << endl << endl << outputResult << endl;
      }

      time_t startTime = time(NULL);

      while (numGuesses < 4) {
        if (randWord != userGuess) {
          cout << "Please enter word -->  ";
          userInput(userGuess, binaryCheck, wordleWords);
          elapsedTime = difftime(time(NULL), startTime);
          if ((userGuess.size() < 3) || (userGuess.size() > 3)) {
            cout << "Invalid word entry " << "- please enter a word that is 3 characters \n" << "long. \n" << endl;       
          } 
          else if (binaryCheck == -1) {
            cout << "\n" << "Not a playable word, please select another word. \n" << endl;
          }
          else if (elapsedTime > 20) {
            wordCheck(randWord, userGuess, outputResult);
            cout << endl << endl << outputResult << endl << "Your time has expired.  Try again." << "  - You are " << (elapsedTime - 20) << " seconds over the 20 second time limit." << endl;
            break;
          } 
          else {
            numGuesses = numGuesses + 1;
            wordCheck(randWord, userGuess, outputResult);
            cout << endl << endl << outputResult << endl;
          }
        } 
        else {
          if (elapsedTime > 20) {
            cout << "Your time has expired.  Try again. \n" << "  - You are " << (elapsedTime - 20) << " seconds over the 20 second time limit." << endl;
            break;
          } 
          else {
            break;
          }
        }
      }

      if ((numGuesses >= 4) && (userGuess != randWord)) {
        cout << "Maximum amount of attempts have been reached. Try again." << endl;
      }
      if (userGuess == randWord && elapsedTime < 20) {
        elapsedTime = difftime(time(NULL), startTime);
        numWins = numWins + 1;
        currentStreak = currentStreak + 1;
        if(maxStreak < currentStreak) {
          maxStreak = currentStreak;
        }
        totalTime = totalTime + elapsedTime;
        cout << "Nice Work!  You guessed the correct word \n" << "- You completed the board in: " << elapsedTime << " seconds. \n" << "- It took you " << numGuesses << "/4 attempts.\n"<< endl;
      }
      else {
        currentStreak = 0;
      }
      outputResult = "";
    }

    // To play 5 letters
    if (menuOption == 2) {
      elapsedTime = 0;
      numGuesses = 0;
      string randWord = wordleWords.at((rand() % 2498) + (1065));

      cout << "To get started, enter your first 5 letter word. \n"
           << "You have 6 attempts to guess the random word. \n"
           << "The timer will start after your first word entry. \n"
           << "Try to guess the word within 40 seconds. \n";

      cout << endl << randWord << endl;

      cout << "Please enter word -->  ";
      cin >> userGuess;
      while ((userGuess.size() < 5) || (userGuess.size() > 5)) {
        if ((userGuess.size() < 5) || (userGuess.size() > 5)) {
          cout << "Invalid word entry "
               << "- please enter a word that is 5 characters \n"
               << "long. \n"
               << endl;
          cout << "Please enter word -->  ";
          cin >> userGuess;
        }
      }

      if (userGuess == randWord) {
        numGuesses = numGuesses + 1;
        totalTime = totalTime + 0;
        cout << "\n"
             << "\n"
             << "[" << char(toupper(randWord.at(0))) << "] "
             << "[" << char(toupper(randWord.at(1))) << "] "
             << "[" << char(toupper(randWord.at(2))) << "] "
             << "[" << char(toupper(randWord.at(3))) << "] "
             << "[" << char(toupper(randWord.at(4))) << "] \n"
             << endl;
      } 
      else {
        numGuesses = numGuesses + 1;
        wordCheck(randWord, userGuess, outputResult);
        cout << endl << endl << outputResult << endl;
      }

      time_t startTime = time(NULL);
      while (numGuesses < 6) {
        if (randWord != userGuess) {
          cout << "Please enter word -->  ";
          cin >> userGuess;
          elapsedTime = difftime(time(NULL), startTime);
          if ((userGuess.size() < 5) || (userGuess.size() > 5)) {
            cout << "Invalid word entry "
                 << "- please enter a word that is 5 characters \n"
                 << "long. \n"
                 << endl;
          } else if (elapsedTime > 40) {
            wordCheck(randWord, userGuess, outputResult);
            cout << endl << endl << outputResult << endl;
            cout << "Your time has expired.  Try again."
                 << "  - You are " << (elapsedTime - 40)
                 << " seconds over the 40 second time limit." << endl;
            break;
          } 
          else {
            numGuesses = numGuesses + 1;
            wordCheck(randWord, userGuess, outputResult);
            cout << endl << endl << outputResult << endl;
          }
        } 
        else {
          elapsedTime = difftime(time(NULL), startTime);
          if (elapsedTime > 40) {
            cout << "Your time has expired.  Try again. \n"
                 << "  - You are " << (elapsedTime - 40)
                 << " seconds over the 40 second time limit." << endl;
            break;
          } 
          else {
            break;
          }
        }
      }
      if ((numGuesses >= 6) && (userGuess != randWord)) {
         cout << "Maximum amount of attempts have been reached. Try again."
              << endl;
        }
      if(userGuess == randWord && elapsedTime < 40) {
         elapsedTime = difftime (time (NULL), startTime);
         numWins = numWins + 1;
         currentStreak = currentStreak + 1;
         if(maxStreak < currentStreak) {
           maxStreak = currentStreak;
         }
         totalTime = totalTime + elapsedTime;
         cout << "Nice Work!  You guessed the correct word \n"
              << "- You completed the board in: " << elapsedTime
              << " seconds. \n"
              << "- It took you " << numGuesses << "/6 attempts.\n"
              << endl;
        }
       else {
         currentStreak = 0;
       } 
      outputResult = "";
      }
    // To exit program
    if(menuOption == 3) {
      gameStatus = false;
      break;
    }
  }

  // Display Overall Stat

  cout << "Overall Stats:\n"
       << "  - You guessed: " << numWins << endl
       << "  - Your longest streak is: " << maxStreak << endl
       << "  - Average word completion time: ";

  if(numWins == 0) {
    cout << "N/A" << endl;
  }
  else {
    cout << (totalTime / numWins) << endl;
  }

  cout << "Exiting program" << endl;

   return 0;
}
