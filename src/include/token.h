#pragma once

#include <string>

using namespace std;

#define KEYWORD_SIZE 7
#define OPERATOR_SIZE 19

static const char keywords[KEYWORD_SIZE][7] = {
    "let",
    "const",
    "if",
    "while",
    "for",
    "return"
};

static const char operators[OPERATOR_SIZE][3] = {
    "=>",
    "==",
    "=",
    "<=",
    ">=",
    ">",
    "<",
    "[",
    "]",
    "(",
    ")",
    "{",
    "}",
    ",",
    ";",
    "+",
    "-",
    "/",
    "*"
};

enum TokenType {
    Keyword,
    Identifier,
    Operator,
    String,
    Int,
    Boolean
};

struct Token{
    TokenType type;
    string value;

    Token(TokenType _type, string _value):
        type(_type),
        value(_value)
    {}
};