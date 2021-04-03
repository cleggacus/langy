#include "include/lexer.h"

Lexer::~Lexer(){
    fs.close();
}

void Lexer::loadFile(char* path){
    fs = ifstream(path);
}

char Lexer::nextChar(){
    char x;
    fs.get(x);
    return x;
}

bool Lexer::completed(){
    return fs.peek() == -1;
}

string Lexer::completeString(){
    string buffer = "";

    while(true){
        char c = nextChar();
        if(c == '"') return buffer;
        buffer += c;
    }
}

string Lexer::completeInt(char c){
    string buffer = {c};

    while(true){
        c = nextChar();
        if(isdigit(c))
            buffer += c;
        else{
            fs.unget();
            break;
        }
    }

    return buffer;
}

string Lexer::completeTokenVal(char c){
    string tokenVal = {c};
    
    while(true){
        char nc = nextChar();

        if(!(isalnum(nc) || nc == '_')){
            fs.unget();
            return tokenVal;
        }

        tokenVal.push_back(nc);
    }
}

Token Lexer::completeToken(char c){
    string s = completeTokenVal(c);

    if(s == "true" || s == "false"){
        return Token(Boolean,s);
    }

    for(int i = 0; i < KEYWORD_SIZE; i++){
        if(s == keywords[i])
            return Token(Keyword, keywords[i]);
    }

    for(int i = 0; i < OPERATOR_SIZE; i++){
        if(s == operators[i])
            return Token(Operator, operators[i]);
    }

    return Token(Identifier, s);;
}

Token Lexer::nextToken(){
    char nc = nextChar();

    while(nc == ' ' || nc == '\n' || nc == '\t'){
        nc = nextChar();
    }

    if(isdigit(nc)){
        string s = completeInt(nc);
        return Token(Int, s);
    }else if(nc == ';'){
        string s = completeInt(nc);
        return Token(Int, s);
    }else{
        Token t = completeToken(nc);
        return t;
    }
}