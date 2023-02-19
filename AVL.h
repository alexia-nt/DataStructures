#ifndef AVL_H
#define AVL_H

//#include "NodeAVL.h"

#include <iostream>
using namespace std;

class NodeAVL
{
public:
    string word;
    int cnt;
    NodeAVL *left;
    NodeAVL *right;
    int height;
};

class AVL
{
private:
    int numofwords; //αποθηκεύει το πλήθος των διαφορετικών λέξεων που υπάρχουν στο δένδρο
    NodeAVL *min(NodeAVL *); //για την εύρεση του ελαχίστου στοιχείου του δένδρου
public:
    AVL();
    void destroyTree(NodeAVL *r); //για την καταστροφή του δένδρου

    int max(int,int); //επιστρέφει το μέγιστο μεταξύ των 2 ακεραίων που εισάγονται ως παράμετροι
    int height(NodeAVL *); //επιστρέφει το ύψος του υπόδεντρου
    int getBalance(NodeAVL *); //επιστρέφει τη διαφορά του ύψους ανάμεσα στο αριστερό και το δεξί υπόδεντρο
    NodeAVL* newNode(string, int); //για τη δημιουργία ενός κόμβου

    NodeAVL *rightRotate(NodeAVL *); //απλή δεξιά περιστροφή
    NodeAVL *leftRotate(NodeAVL *); //απλή αριστερά περιστροφή

    NodeAVL* insert_word(NodeAVL*, const string&); //για την εισαγωγή μιας λέξης στο δυαδικό δένδρο
    NodeAVL* deleteNodeAVL(NodeAVL *, const string&); //για τη διαγραφή μιας λέξης από το δυαδικό δένδρο
    bool search_word(NodeAVL *, const string&, int &); //για την αναζήτηση μιας λέξης στο δυαδικό δέντρο

    void inOrder(NodeAVL *);
    //για την εμφάνιση των στοιχείων του δένδρου σε ενδοδιατεταγμένη σειρά
    void preOrder(NodeAVL *);
    //για την εμφάνιση των στοιχείων του δένδρου σε προδιατεταγμένη σειρά
    void postOrder(NodeAVL *);
    //για την εμφάνιση των στοιχείων του δένδρου σε μετάδιατεταγμένη σειρά

    int getNumofwords();
    //επιστρέφει το πλήθος των διαφορετικών λέξεων που υπάρχουν στο δυαδικό δένδρο
};

#endif // AVL_H
