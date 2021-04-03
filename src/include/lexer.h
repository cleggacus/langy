#pragma once

#include "token.h" 

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Lexer{
    private:
        ifstream fs;
        string completeString();
        string completeInt(char c);
        Token completeToken(char c);
        string completeTokenVal(char c);
        char nextChar();

    public:
        ~Lexer();
        void loadFile(char* path);
        bool completed();
        Token nextToken();
};