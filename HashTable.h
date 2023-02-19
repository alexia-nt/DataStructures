#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
using namespace std;

class WordCNT
{
public:
    WordCNT(int c, string w)
    {
        cnt=c;
        word=w;
    }
    int cnt;
    string word;
};

class HashTable
{
private:
    int size; //μέγεθος πίνακα
    int elements; //πλήθος στοιχείων στον πίνακα
    WordCNT * *A;
    void *deleted;

    unsigned int hash(string); //συνάρτηση κατακερματισμού
    unsigned int hash2(unsigned int); //δεύτερη συνάρτηση κατακερματισμού
    WordCNT *&search(const string &);
public:
    HashTable();
    void clearHashTable(); //για την καταστροφή του πίνακα
    bool insert(const string &); //για την εισαγωγή μιας λέξης στον πίνακα
    bool search(const string &, int &data); //για την αναζήτηση μιας λέξης στον πίνακα
    int getElements(); //επιστρέφει το πλήθος των στοιχείων του πίνακα
    void show(); //για την εμφάνιση των στοιχείων του πίνακα
};

#endif // HASHTABLE_H
