#ifndef BST_H
#define BST_H

#include "Node.h"

#include <iostream>
using namespace std;

//οι συναρτήσεις insert, search, delete, inorder, preorder, postorder
//είναι διπλές έτσι ώστε η διαχείριση της ρίζας να γίνεται μέσα στην κλάση κι όχι στη main

class BST
{
private:
    Node *root;
    bool insert_word(Node *,const string &); //για την εισαγωγή μιας λέξης στο δυαδικό δένδρο
    Node *search_word(const string&); //για την αναζήτηση μιας λέξης στο δυαδικό δένδρο
    bool delete_word(Node *); //για την διαγραφή μιας λέξης από το δυαδικό δένδρο
    Node *min(Node *); //για την εύρεση του ελαχίστου στοιχείου του δένδρου
    Node *max(Node *); //για την εύρεση του μέγιστου στοιχείου του δένδρου
    void inOrder(Node *); //για την εμφάνιση των στοιχείων του δένδρου σε ενδοδιατεταγμένη σειρά
    void preOrder(Node *); //για την εμφάνιση των στοιχείων του δένδρου σε προδιατεταγμένη σειρά
    void postOrder(Node *); //για την εμφάνιση των στοιχείων του δένδρου σε μεταδιατεταγμένη σειρά
    void destroyTree(Node *); //για τη καταστροφή του δέντρου
    int numofwords;
public:
    BST();
    void destroyTree(); //για τη καταστροφή του δέντρου

    bool insert_word(const string &);
    //καλεί την insert_word(Node *,const string &) για την εισαγωγή της λέξης στο δυαδικό δέντρο
    bool search_word(string,int &);
    //καλεί την *search_word(string) για την αναζήτηση μιας λέξης στο δυαδικό δέντρο
    bool delete_word(string);
    //καλεί την delete_word(Node *) για την διαγραφή μιας λέξεις από το δυαδικό δέντρο

    void printInOrder();
    //καλεί την inOrder() για την εμφάνιση των στοιχείων του δένδρου σε ενδοδιατεταγμένη σειρά
    void printPreOrder();
    //καλεί την preOrder() για την εμφάνιση των στοιχείων του δένδρου σε προδιατεταγμένη σειρά
    void printPostOrder();
    //καλεί την postOrder() για την εμφάνιση των στοιχείων του δένδρου σε μεταδιατεταγμένη σειρά

    int getNumofwords();
    //επιστρέφει τον αριθμό των διαφορετικών λέξεων που υπάρχουν στο δυαδικό δέντρο
};

#endif