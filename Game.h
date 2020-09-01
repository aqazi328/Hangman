#ifndef Game_h
#define Game_h
#include "Difficulty.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

class Game : public Difficulty{
    private:
        int random_num;
    public:
        string filecontent;
        string selected_num;
        ifstream fileinput;
        ofstream fileoutput;
        string word;
        int numwords;
        string chain;
        int bodypart;
    
        Game():Difficulty(){  //diff will be easy
            srand(time(NULL));
            random_num = rand() % 9 + 10;// 10 to 18
        }
        void setRandom(){
            srand(time(NULL));
            if (getDifficulty()== "Easy"){
                random_num = rand() % 9 + 10;
            }
            if (getDifficulty()== "Medium"){    //19 to 32
                random_num = rand() % 14 + 19;
            }
            if (getDifficulty()== "Hard"){    //33 to 38
                random_num = rand() % 6 + 33;
            }
        }
        int getRandom(){
            return random_num;
        }
        string locateWord(int x){
            fileinput.open("dictionary.txt");
            x = random_num;
            while (getline(fileinput, filecontent)){
                selected_num = filecontent.substr(0,2);
                if (stod(selected_num)==x){
                    word = filecontent.substr(4,filecontent.length());
                }
            }
            fileinput.close();
            return word;
        }
        int numOfLetters(){
            numwords = word.size();
            return numwords;
        }
        string emptychain(int x){
            for (int i = 0; i < x; i++){
                chain.push_back('_');
            }
            return chain;
        }
        string fillchain(char x){
            bool found = false;
            for (int i = 0; i < word.length(); i++){
                if (word[i] == x){
                    chain[i] = x;
                    found = true;
                }
            }
            if(!found){
                cout << endl;
            }
            return chain;
        }
        string getChain(){
            return chain;
        }
        void changeChain(string x){
            chain = x;
        }
    
};


#endif /* Game_h */
