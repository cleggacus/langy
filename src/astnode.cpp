#include "include/astnode.h"

void IASTNode::push_back(IASTNode* node){
    children.push_back(node);
}

int IASTNode::size(){
    return children.size();
}

IASTNode* IASTNode::getChild(int i){
    return children[i];
}


string ASTNodePrimitivesString[3] = {
    "Root",
    "Assign",
    "Call"
};

IASTNode::~IASTNode(){
    for(int i = 0 ; i < children.size(); i++){
        delete children[i];
    }
}

template <>
void ASTNode<ASTNodePrimitives>::print(int depth){
    for(int i = 0; i < depth ; i++)
        cout << "  ";

    cout << ASTNodePrimitivesString[(int)val] << '\n';

    for(int i = 0; i < IASTNode::size(); i++)
        IASTNode::getChild(i) -> print(depth+1);
}