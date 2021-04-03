#pragma once

#include <string>
#include <iostream>
#include <vector>

using namespace std;

enum ASTNodePrimitives {
    Root,
    Assign,
    Call,
    Parameters
};

class IASTNode{
    private:
        vector<IASTNode*> children;

    public:
        ~IASTNode();
        virtual void push_back(IASTNode* node);
        virtual void print(int depth) {};
        int size();
        IASTNode* getChild(int i);
};

template <class T>
class ASTNode: public IASTNode{
    private:
        T val;

    public:
        ASTNode(T _val);
        void print(int depth);
};

template <class T>
ASTNode<T>::ASTNode(T _val):
    val(_val)
{}

template <class T>
void ASTNode<T>::print(int depth){
    for(int i = 0; i < depth ; i++)
        cout << "  ";

    cout << val << '\n';

    for(int i = 0; i < IASTNode::size(); i++)
        IASTNode::getChild(i) -> print(depth+1);
}