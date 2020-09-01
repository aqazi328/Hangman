#ifndef Difficulty_h
#define Difficulty_h
#include <iostream>
using namespace std;

class Difficulty{
    private:
        string difficulty;
    public:
        Difficulty(){
            difficulty = "Easy";
        }
        Difficulty(string x){
            difficulty = x;
        }
        virtual string getDifficulty(){
            return difficulty;
        }
        void setDifficulty(string x){
            difficulty = x;
        }
    
};

#endif /* Difficulty_h */
