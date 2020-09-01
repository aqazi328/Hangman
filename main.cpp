// Hangman Game Program by Ahson Qazi and Jerin Thomas
// COSC 1430 - 12582 Dr. Chen
#include <iostream>
#include <string>
#include <fstream>
#include "Game.h"
#include "Difficulty.h"

using namespace std;

class DiffError{};
class SaveFile{};

void drawing(int position)
{
    
    switch(position)
    {
        case 1:
            cout << " ___________"<<endl;
            cout << " |         }"<<endl;
            cout << " |       \\  " <<endl;
            cout << "_|______________"<<endl;
            break;
        case 2:       cout << " ___________"<<endl;
            cout << " |         }"<<endl;
            cout << " |       \\ 0 " <<endl;
            cout << "_|______________"<<endl;
            break;
        case 3:
            cout << " ___________"<<endl;
            cout << " |         }"<<endl;
            cout << " |       \\ 0 /" <<endl;
            cout << "_|______________"<<endl;
            break;
        case 4:
            cout << " ___________"<<endl;
            cout << " |         }"<<endl;
            cout << " |       \\ 0 /" <<endl;
            cout << " |         |"<<endl;
            cout << "_|______________"<<endl;
            break;
        case 5:
            cout << " ___________"<<endl;
            cout << " |         }"<<endl;
            cout << " |       \\ 0 /" <<endl;
            cout << " |         |"<<endl;
            cout << " |        /  "<<endl;
            cout << "_|______________"<<endl;
            break;
        case 6:
            cout << " ___________"<<endl;
            cout << " |         }"<<endl;
            cout << " |       \\ 0 /" <<endl;
            cout << " |         |"<<endl;
            cout << " |        / \\ "<<endl;
            cout << "_|______________"<<endl;
    }
}

int main(){
    cout << "                           *************** Let's Play Hangman! ***************" << endl;
    cout << "Rules: A random word will be chosen depending on the difficulty you select. You will be given the number of letters of the word and have multiple opportunities to either guess a letter in the word or the complete word. You also have the option to save your game and come back to it later. Win by completely guessing the word before the hangman is completely hung! " << endl;
    cout << "        *****************************************************************************************************" << endl;
    cout << "\nTo get started, select a difficulty: Easy, Medium, or Hard?" << endl;
    
    string difficulty;
    cin >> difficulty;
    try{
        if (difficulty == "easy"){
            difficulty = "Easy";
        }
        if (difficulty == "medium"){
            difficulty = "Medium";
        }
        if (difficulty == "hard"){
            difficulty = "Hard";
        }
        if ((difficulty == "Easy") || (difficulty == "Medium") || (difficulty == "Hard")){
            cout << endl;
            cout << difficulty << " difficulty selected." << endl;
        }
        else{throw DiffError();}
        
        Game game1;
        game1.setDifficulty(difficulty);
        game1.setRandom();
        game1.locateWord(game1.getRandom());
//        cout << game1.locateWord(game1.getRandom()) << endl;            //test to see word
        int word_size = game1.numOfLetters();
        cout << "Your selected word is " << word_size << " letters long." << endl;
        cout << endl;
        cout << game1.emptychain(word_size) << endl;
        cout << endl;
        
        char letter;
        int wrongGuess = 0;
        string str;
        string tempstr;
        string savegame;
        string wordguess;
        char option;
        bool correct = false;
        str = game1.locateWord(game1.getRandom());

        while (wrongGuess < 6){
            correct = false;
            cout << "Guess a letter! You can also enter in 'x' to try guessing the word or 'q' to quit and save your game at any time. Enter a letter: ";
            cin >> letter;
            if (letter == 'x' || letter == 'X'){
                cout << "Guess a word: ";
                cin >> wordguess;
                if (wordguess==str){
                    cout << endl;
                    cout << "Congrats! You won!" << endl;
                    break;
                }
                else{
                    wrongGuess++;
                    cout << "Incorrect! " << 6 - wrongGuess << " guess(es) remaining."<< endl;
                    continue;
                }
            }
            if (letter == 'q' || letter == 'Q') {
                savegame = game1.getChain();
                ofstream fileout;
                fileout.open("saved.txt");
                fileout << savegame << wrongGuess << endl;
                fileout.close();
                cout << endl;
                cout << "Your data has been saved in file. Would you like to resume the same game or quit?" << endl;
                cout << "Enter Y/N: ";
                cin >> option;
                if ((option == 'N')||(option == 'n')){
                    throw SaveFile();
                }
                if ((option == 'Y')||(option == 'y')){
                    ifstream newinput;
                    newinput.open("savefile");
                    newinput >> tempstr >> wrongGuess;
                    newinput.close();
                    cout << tempstr << " " << wrongGuess << endl;
                    
                }
            }
            else if(isupper(letter)) {
                cout << "Invalid input! Input only lowercase letters." << endl;
                continue;
            }
            else {
                for (int i = 0; i < word_size; i++){
                    if ((str[i] == letter)&&(!correct)) {
                        cout << "You got a letter!" << endl;
                        cout << game1.fillchain(letter) << endl;
                        correct = true;
                        tempstr = game1.getChain();
                    }
                }
                if (!correct) {
                    cout << game1.fillchain(letter) << endl;
                    cout << endl;
                    wrongGuess++;
                    drawing(wrongGuess);
                    cout << endl;
                    cout << "Incorrect! " << 6 - wrongGuess << " guess(es) remaining."<< endl;
                }
                if (tempstr == str){
                    cout << endl;
                    cout << "Congrats! You won! Run program to play again!" << endl;
                    break;
                }
            }
            cout << endl;
        }
        if (wrongGuess == 6) {
            cout << endl;
            cout << "Game Over. You Lost" << endl;
            drawing(6);
            cout << endl;
            cout << "Your word was: " << str << endl;
            cout << "Run the program to play again!\n" << endl;
        }
    }
    catch(DiffError)
    {
        cout << "Invalid input! Run the program again and select one of the three difficulties.\n";
    }
    catch(SaveFile)
    {
        cout << "You have quit the game. Run program to play again! \n";
    }
    return 0;
}
