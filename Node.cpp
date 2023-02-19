#include "Node.h"

#include <iostream>
using namespace std;

Node::Node()
{
    word=" ";
    cnt=0;
    left=nullptr;
    right=nullptr;
    parent=nullptr;
}

Node::Node(string wo, int counter)
{
    word=wo;
    cnt=counter;
    left=nullptr;
    right=nullptr;
    parent=nullptr;
}

void Node::setLeft(Node *l)
{
    left=l;
}

void Node::setRight(Node *r)
{
    right=r;
}

void Node::setParent(Node *p)
{
    parent=p;
}

void Node::setWord(string wo)
{
    word=wo;
}

void Node::setCNT(int counter)
{
    cnt=counter;
}

Node *Node::getLeft()
{
    return left;
}

Node* Node::getRight()
{
    return right;
}

Node* Node::getParent()
{
    return parent;
}

string Node::getWord()
{
    return word;
}

int Node::getCNT()
{
    return cnt;
}
