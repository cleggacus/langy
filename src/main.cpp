#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>
#include "include/parser.h"

using namespace std;

void outputLexer(char* arg){
    Lexer lexer;

    lexer.loadFile(arg);

    string sa[] = {
        "Keyword     ",
        "Identifier  ",
        "Operator    ",
        "String      ",
        "Int         ",
        "Boolean     "
    };
    
    while(!lexer.completed()){
        Token t = lexer.nextToken();
        cout << sa[t.type] << "    " << t.value << "\n";
    }
}

void outputParser(char* arg){
    Parser p(arg);
    p.parse();
    p.print();
}

int main(int argc, char** argv){
    outputParser(argv[1]);
    return 0;
}