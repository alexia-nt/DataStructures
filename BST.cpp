#include "BST.h"

#include <iostream>
using namespace std;

BST::BST()
{
    root=nullptr;
    numofwords=0;
}

void BST::destroyTree()
{
    destroyTree(root);
}

void BST::destroyTree(Node *r)
{
    if(r!=nullptr) //αν το δένδρο δεν είναι άδειο καταστρέφονται αναδρομικά το δεξί και το αριστερό υποδένδρο
    {
        destroyTree(r->getLeft());
        destroyTree(r->getRight());
        delete(r);
    }
}
bool BST::insert_word(const string &word)
{
    if(root==nullptr)
    {
        root=new Node(word,1); //δημιουργείται ο πρώτος κόμβος
        numofwords=1; //προστέθηκε η πρώτη λέξη στο δένδρο
        return true;
    }
    return insert_word(root,word);
}

bool BST::insert_word(Node *r, const string &word)
{
    if(word==(*r).getWord()) //αν η λέξη υπάρχει ήδη
    {
        int counter=(*r).getCNT()+1; //αυξάνεται το πλήθος εμφανίσεων της λέξης
        (*r).setCNT(counter);
        return true;
    }
    if(word>(*r).getWord()) //αν η λέξη είναι μεγαλύτερη από την λέξη του κόμβου
    {
        if((*r).getRight()==nullptr) //αν δεν υπάρχει δεξί παιδί
        {
            (*r).setRight(new Node(word,1)); //δημιουργία δεξιού παιδιού
            (*r).getRight()->setParent(r);
            numofwords++; //αυξάνεται το πλήθος των διαφορετικών λέξεων που υπάρχουν στο δένδρο
            return true;
        }
        return insert_word((*r).getRight(),word);
    }
    else //αν η λέξη είναι μικρότερη από την λέξη του κόμβου
    {
        if((*r).getLeft()==nullptr) //αν δεν υπάρχει αριστερό παιδί
        {
            (*r).setLeft(new Node(word,1)); //δημιουργία αριστερού παιδιού
            (*r).getLeft()->setParent(r);
            numofwords++; //αυξάνεται το πλήθος των διαφορετικών λέξεων που υπάρχουν στο δένδρο
            return true;
        }
        return insert_word((*r).getLeft(),word);
    }
}

bool BST::search_word(string keyword,int &counter)
{
    Node *s=search_word(keyword);
    if(s==nullptr)
        return false;
    counter=(*s).getCNT(); //το πλήθος εμφανίσεων της λέξης αποθηκεύεται στη μεταβλητή counter
    return true;
}

Node *BST::search_word(const string &keyword)
{
    Node *s;
    s=root;
    while(s!=nullptr && keyword!=(*s).getWord())
        //όσο υπάρχουν παιδιά και δεν έχει βρεθεί η λέξη
    {
        if(keyword>(*s).getWord()) //αν η λέξη κλειδί είναι μεγαλύτερη της λέξη του κόμβου
            s=(*s).getRight(); //αναζήτηση στο δεξί υποδένδρο
        else
            s=(*s).getLeft(); //αναζήτηση στο αριστερό υποδένδρο
    }
    return s;
}

bool BST::delete_word(string keyword)
{
    Node *child;
    child=search_word(keyword);
    if(child!=nullptr) //αν βρέθει ο κόμβος με τη λέξη κλειδί
        return delete_word(child); //διαγραφή του κόμβου
    return false;
}

bool BST::delete_word(Node *child)
{
    Node *parent;

    if(child==nullptr)
        return false;

    parent=(*child).getParent();

    if((*child).getLeft()==nullptr && (*child).getRight()==nullptr) //αν ο κόμβος δεν έχει παιδιά
    {
        if(parent==nullptr) //αν ο κόμβος είναι η ρίζα
        {
            delete(child); //διαγράφεται ο κόμβος
            numofwords--; //μειώνεται ο αριθμός των διαφορετικών λέξεων που υπάρχουν στο δένδρο
            root=nullptr;
        }
        else if((*parent).getLeft()==child) //αν ο κόμβος είναι αριστερό παιδί
        {
            delete((*parent).getLeft()); //διαγράφεται ο κόμβος
            numofwords--; //μειώνεται ο αριθμός των διαφορετικών λέξεων που υπάρχουν στο δένδρο
            (*parent).setLeft(nullptr);
        }
        else //αν ο κόμβος είναι δεξί παιδί
        {
            delete((*parent).getRight()); //διαγράφεται ο κόμβος
            numofwords--; //μειώνεται ο αριθμός των διαφορετικών λέξεων που υπάρχουν στο δένδρο
            (*parent).setRight(nullptr);
        }
    }
    else if((*child).getLeft()==nullptr || (*child).getRight()==nullptr) //αν ο κόμβος έχει 1 παιδί
    {
        if(parent==nullptr) //αν ο κόμβος είναι η ρίζα
        {
            if((*child).getLeft()==nullptr)
                //αν δεν υπάρχει αριστερό παιδί τότε ρίζα γίνεται το δεξί παιδί
                root=(*child).getRight();
            else
                //αν δεν υπάρχει δεξί παιδί τότε ρίζα γίνεται το αριστερό παιδί
                root=(*child).getLeft();
            delete(child); //διαγράφεται ο κόμβος
            numofwords--; //μειώνεται ο αριθμός των διαφορετικών λέξεων που υπάρχουν στο δένδρο
        }
        else if((*parent).getLeft()==child) //αν ο κόμβος είναι αριστερό παιδί
        {
            if((*child).getLeft()==nullptr) //αν ο κόμβος έχει δεξί παιδί
                (*parent).setLeft((*child).getRight()); //το δεξί παιδί του κόμβου αντικαθιστά τον κόμβο
            else //αν ο κόμβος έχει αριστερό παιδί
                (*parent).setLeft((*child).getLeft()); //το αριστερό παιδί του κόμβου αντικαθιστά τον κόμβο
            delete(child); //διαγράφεται ο κόμβος
            numofwords--; //μειώνεται ο αριθμός των διαφορετικών λέξεων που υπάρχουν στο δένδρο
        }
        else //αν ο κόμβος είναι δεξί παιδί
        {
            if((*child).getLeft()==nullptr) //αν ο κόμβος έχει δεξί παιδί
                (*parent).setRight((*child).getRight()); //το δεξί παιδί του κόμβου αντικαθιστά τον κόμβο
            else //αν ο κόμβος έχει αριστερό παιδί
                (*parent).setRight((*child).getLeft()); //το αριστερό παιδί του κόμβου αντικαθιστά τον κόμβο
            delete(child); //διαγράφεται ο κόμβος
            numofwords--; //μειώνεται ο αριθμός των διαφορετικών λέξεων που υπάρχουν στο δένδρο
        }
    }
    else //αν ο κόμβος έχει 2 παιδιά
    {
        //ο κόμβος αντικαθιστάται από τον ελάχιστο κόμβο του δεξιού υποδένδρου
        Node *mn=min((*child).getRight());
        (*child).setWord((*mn).getWord());
        (*child).setCNT((*mn).getCNT());
        delete_word(mn);
    }
    return true;
}

Node *BST::min(Node *start)
{
    if(start==nullptr) //αν το δένδρο είναι άδειο
        return nullptr;
    Node *p=start;
    while((*p).getLeft()!=nullptr)
        p=(*p).getLeft();
    return p; //επιστροφή του αριστερότερου (ελάχιστου) κόμβου
}

Node *BST::max(Node *start)
{
    if(start==nullptr) //αν το δένδρο είναι άδειο
        return nullptr;
    Node *p=start;
    while((*p).getRight()!=nullptr)
        p=(*p).getRight();
    return p; //επιστροφή του δεξιότερου (μέγιστου) κόμβου
}

void BST::printInOrder()
{
    inOrder(root);
}

void BST::inOrder(Node *p) //Left, Root, Right
{
    if(p==nullptr)
        return;
    inOrder((*p).getLeft());
    cout<<(*p).getWord()<<" "<<(*p).getCNT()<<endl;
    inOrder((*p).getRight());
}

void BST::printPreOrder()
{
    preOrder(root);
}

void BST::preOrder(Node *p) //Root, Left, Right
{
    if(p==nullptr)
        return;
    cout<<(*p).getWord()<<" "<<(*p).getCNT()<<endl;
    preOrder((*p).getLeft());
    preOrder((*p).getRight());
}

void BST::printPostOrder()
{
    postOrder(root);
}

void BST::postOrder(Node *p) //Left, Right, Root
{
    if(p==nullptr)
        return;
    postOrder((*p).getLeft());
    postOrder((*p).getRight());
    cout<<(*p).getWord()<<" "<<(*p).getCNT()<<endl;
}

int BST::getNumofwords()
{
    return numofwords;
}
