#include "include/parser.h"

Parser::Parser(char* path):
    root(ASTNode<ASTNodePrimitives>(Root)),
    currentLine(0)
{
    currentScope = &root;
    lexer.loadFile(path);
}

Parser::~Parser(){
}

void Parser::parse(){
    while(!lexer.completed()){
        nextLine();
    }
}

void Parser::print(){
    root.print(0);
}

IASTNode* Parser::evalEquation(vector<Token>* v, int start = 0, int length = -1){
    vector<Token> tokens = *v;

    if(length == 1){
        ASTNode<int>* thing = new ASTNode<int>(stoi(tokens[start].value));
        return thing;
    }

    if(length < 0)
        length = tokens.size() - start;


    string operations[4] = {
        "-", "+", "*", "/"
    };
    
    for(int i = 0; i < 4; i++){
        for(int j = start; j < start + length; j++){
            if(tokens[j].value == operations[i]){
                ASTNode<char>* root = new ASTNode<char>(((char*)operations[i].c_str())[0]);
                root -> push_back(evalEquation(v, start, j-start));
                root -> push_back(evalEquation(v, j+1, length - (j-start)-1));

                return root;
            }
        }
    }

    return nullptr;
}

void Parser::completeAssign(){
    ASTNode<ASTNodePrimitives>* assignNode = new ASTNode<ASTNodePrimitives>(Assign);
    
    Token identifierToken = lexer.nextToken();

    if(identifierToken.type != Identifier)
        throw identifierToken.value + " is not an identifier.";

    ASTNode<string>* identifierNode = new ASTNode<string>(identifierToken.value);
    assignNode -> push_back(identifierNode);

    Token t = lexer.nextToken();

    if(t.value == "="){
        t = lexer.nextToken();
        vector<Token> expression;

        while(t.value != ";"){
            expression.push_back(t);
            t = lexer.nextToken();
        }

        if(expression.size() == 1){
            ASTNode<int>* val = new ASTNode<int>(stoi(expression[0].value));
            assignNode -> push_back(val);
        }else{
            assignNode -> push_back(evalEquation(&expression));
        }
    }
    
    currentScope -> push_back(assignNode);
}

void Parser::completeFunctionCall(string identifier){
    IASTNode* callNode = evalFunctionCall(identifier);
    Token t = lexer.nextToken();
    
    if(t.value == ";")
        currentScope -> push_back(callNode);
}

IASTNode* Parser::evalFunctionCall(string identifier){
    ASTNode<ASTNodePrimitives>* callNode = new ASTNode<ASTNodePrimitives>(Call);
    ASTNode<string>* identifierNode = new ASTNode<string>(identifier);
    ASTNode<ASTNodePrimitives>* parametersNode = new ASTNode<ASTNodePrimitives>(Parameters);

    Token t = lexer.nextToken();

    while(t.value != ")"){
        vector<Token> expression;
        
        expression.push_back(t);
        t = lexer.nextToken();
    }

    callNode -> push_back(identifierNode);
    callNode -> push_back(parametersNode);

    return callNode;
}

void Parser::nextLine(){
    Token t = lexer.nextToken();

    if(t.type == Keyword){
        if(t.value == "let")
            completeAssign();
    }
    else if(t.type == Identifier){
        Token tnext = lexer.nextToken();
        if(tnext.value == "("){
            completeFunctionCall(t.value);
        }
    }
}