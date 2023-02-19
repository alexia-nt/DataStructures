#ifndef NODE_H
#define NODE_H

#include <iostream>
using namespace std;

class Node
{
private:
    string word;
    int cnt;

    Node *left;
    Node *right;
    Node *parent;
public:
    Node();
    Node(string,int);

    Node *getLeft();
    Node *getRight();
    Node *getParent();

    void setLeft(Node *);
    void setRight(Node *);
    void setParent(Node *);

    string getWord();
    void setWord(string);

    int getCNT(); //θέτει το πλήθος εμφανίσεων της λέξης
    void setCNT(int); //επιστρέφει το πλήθος εμφανίσεων της λέξης
};

#endif //NODE_H