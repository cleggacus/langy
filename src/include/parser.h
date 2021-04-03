#pragma once

#include "lexer.h"
#include "astnode.h"

class Parser{
    private:
        ASTNode<ASTNodePrimitives> root;
        ASTNode<ASTNodePrimitives>* currentScope;
        unsigned int currentLine;
        Lexer lexer;
        
    public:
        Parser(char* path);
        ~Parser();
        void nextLine();
        void parse();
        void completeAssign();
        void completeFunctionCall(string identifier);
        IASTNode* evalFunctionCall(string identifier);
        void print();
        IASTNode* evalEquation(vector<Token>* v, int start, int length);
        ASTNode<ASTNodePrimitives> getRootNode();
};