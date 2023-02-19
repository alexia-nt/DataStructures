#ifndef SORTEDARRAY_H
#define SORTEDARRAY_H

#include <iostream>
using namespace std;

class SortedArray
{
private:
    struct wordcnt
    {
        string word;
        int cnt;
    };

    wordcnt *sorted_array;
    int numofwords;
    int maxsize;
public:
    SortedArray();
    bool resize_array(); //για τον διπλασιασμό του μεγέθους του δυαδικού πίνακα
    bool binarySearch(const string&, int&, int&); //για την δυαδική αναζήτηση μιας λέξης στον πίνακα
    bool insert_word(const string&); //για την εισαγωγή μιας λέξης στον πίνακα
    bool delete_word(const string&); // για τη διαγραφή μιας λέξης από τον πίνακα
    int getNumofwords(); //επιστρέφει τον αριθμό των διαφορετικών λέξεων του πίνακα
    void show(); //εμφανίζει όλες τις λέξεις του πίνακα και το πλήθος εμφανίσεων τους
};

#endif // SORTEDARRAY_H
