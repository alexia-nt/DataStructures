//Εργασία Εξαμήνου Δομές Δεδομένων
//Εαρινό Εξάμηνο 2020-2021
//Αλεξία Νταντουρή ΑΕΜ:3871
//Καλλιόπη Πλιόγκα ΑΕΜ:3961

#include <iostream>
#include <fstream> //file handling
#include <string> //string handling
#include <sstream> //read lines
#include <cstdlib> //srand, rand
#include <chrono> //count time
#include <ctime>

using namespace std;

const int size_rand=1000; //καθορίζει το μέγεθος που θα έχει ο πίνακας των τυχαίων λέξεων

#include "UnsortedArray.h"
#include "SortedArray.h"
#include "BST.h"
#include "AVL.h"
#include "HashTable.h"

string edit_word(string word_input);
//δέχεται μια λέξη και την επιστρέφει σε πεζά και χωρίς σημεία στίξης

string *create_random(const string &fn);
//δημιουργεί έναν πίνακα με size_rand τυχαίες λέξεις από το αρχείο με όνομα fn

void insertHashTable(const string &fn, HashTable &ht);
//ανοίγει ένα αρχείο με όνομα fn και κάνει insert κάθε λέξη του αρχείου στο Hash Table
void countHashTable(HashTable &ht, string *random);
//αναζητά 1000 λέξεις από τον πίνακα random κι εμφανίζει τον συνολικό χρόνο αναζήτησης με τη χρήση του Hash Table

NodeAVL *insertAVL(const string &fn, AVL &avltr, NodeAVL *root);
//ανοίγει ένα αρχείο με όνομα fn, κάνει insert κάθε λέξη του αρχείου στο δένδρο AVL κι επιστρέφει τη νέα ρίζα
void countAVL(AVL &avltr, NodeAVL *root, string *random);
//αναζητά 1000 λέξεις από τον πίνακα random κι εμφανίζει τον συνολικό χρόνο αναζήτησης με τη χρήση του δένδρου AVL

void insertBST(const string &fn, BST &bintr);
//ανοίγει ένα αρχείο με όνομα fn και κάνει insert κάθε λέξη του αρχείου στο δυαδικό δένδρο αναζήτησης
void countBST(BST &bintr, string *random);
//αναζητά 1000 λέξεις από τον πίνακα random κι εμφανίζει τον συνολικό χρόνο αναζήτησης με τη χρήση του δυαδικού δένδρου αναζήτησης

void insertSortedArray(const string &fn, SortedArray &sortar);
//ανοίγει ένα αρχείο με όνομα fn και κάνει insert κάθε λέξη του αρχείου στον ταξινομημένο πίνακα
void countSortedArray(SortedArray &sortar, string *random);
//αναζητά 1000 λέξεις από τον πίνακα random κι εμφανίζει τον συνολικό χρόνο αναζήτησης με τη χρήση του ταξινομημένου πίνακα

void insertUnsortedArray(const string &fn, UnsortedArray &unsortar);
//ανοίγει ένα αρχείο με όνομα fn και κάνει insert κάθε λέξη του αρχείου στον αταξινόμητο πίνακα
void countUnsortedArray(UnsortedArray &unsortar, string *random);
//αναζητά 1000 λέξεις από τον πίνακα random κι εμφανίζει τον συνολικό χρόνο αναζήτησης με τη χρήση του αταξινόμητου πίνακα

//οι παραπάνω συναρτήσεις είναι υλοποιημένες κάτω από τη main

void showTime(chrono::steady_clock::time_point t1, chrono::steady_clock::time_point t2)
//εμφανίζει το διάστημα χρόνου μεταξύ των χρονικών σημείων t1 και t2 σε milliseconds
{
    //cout<<(float)(chrono::duration_cast<chrono::microseconds>(t2 - t1).count())/1000000<<"[seconds]";
    cout<<(float)(chrono::duration_cast<chrono::microseconds>(t2 - t1).count())/1000<<" ms"<<endl;
    //cout<<"   "<<chrono::duration_cast<chrono::microseconds>(t2 - t1).count() << "[microseconds]"<<endl;
}

void clear_file(const string &fn) //διαγράφει τα περιεχόμενα του αρχείου με όνομα fn
{
    ofstream ofs;
    ofs.open(fn, ofstream::out | ofstream::trunc);
    ofs.close();
}

int main()
{
    UnsortedArray unsortar;
    SortedArray sortar;
    BST bintr;
    AVL avltr;
    HashTable ht;

    NodeAVL *root=nullptr;

    //string filename="gutenberg.txt";
    string filename="small-file.txt";

    clear_file("output.txt");
    clear_file("HashTable.txt");
    clear_file("AVL.txt");
    clear_file("BST.txt");
    clear_file("SortedArray.txt");
    clear_file("UnsortedArray.txt");

    string *random;
    //random=new string[size_rand];
    random=create_random(filename);

    //μέτρηση χρόνου εισαγωγής όλων των λέξεων του αρχείου στο HashTable
    chrono::steady_clock::time_point t1=chrono::steady_clock::now();
    insertHashTable(filename,ht);
    chrono::steady_clock::time_point t2=chrono::steady_clock::now();
    cout<<"hash table insertion time: ";
    showTime(t1,t2);
    countHashTable(ht, random);
    ht.clearHashTable();

    //μέτρηση χρόνου εισαγωγής όλων των λέξεων του αρχείου στο δένδρο AVL
    t1=chrono::steady_clock::now();
    root=insertAVL(filename,avltr,root);
    t2=chrono::steady_clock::now();
    cout<<"avl insertion time: ";
    showTime(t1,t2);
    countAVL(avltr,root,random);
    avltr.destroyTree(root);

    //μέτρηση χρόνου εισαγωγής όλων των λέξεων του αρχείου στο δυαδικό δένδρο αναζήτησης
    t1=chrono::steady_clock::now();
    insertBST(filename,bintr);
    t2=chrono::steady_clock::now();
    cout<<"bst insertion time: ";
    showTime(t1,t2);
    countBST(bintr,random);
    bintr.destroyTree();

    //μέτρηση χρόνου εισαγωγής όλων των λέξεων του αρχείου στον ταξινομημένο πίνακα
    t1=chrono::steady_clock::now();
    insertSortedArray(filename,sortar);
    t2=chrono::steady_clock::now();
    cout<<"sorted array insertion time: ";
    showTime(t1,t2);
    countSortedArray(sortar,random);

    //μέτρηση χρόνου εισαγωγής όλων των λέξεων του αρχείου στον αταξινόμητο πίνακα
    t1=chrono::steady_clock::now();
    insertUnsortedArray(filename,unsortar);
    t2=chrono::steady_clock::now();
    cout<<"unsorted array insertion time: ";
    showTime(t1,t2);
    countUnsortedArray(unsortar,random);

    return 0;
}

string edit_word(string word_input)
{
    //αφαίρεση σημείων στίξης
    int len=word_input.size();
    for(int i=0;i<len;i++)
    {
        //έλεγχος αν η λέξη έχει σημεία στίξης
        if(ispunct(word_input[i]))
        {
            word_input.erase(i--,1);
            len=word_input.size();
        }
    }

    //μετατροπή κεφαλαίων γραμμάτων σε πεζά
    //transform(word_input.begin(), word_input.end(), word_input.begin(), ::tolower);
    for(int i=0;i<len;i++)
    {
        if(word_input[i]>='A' && word_input[i]<='Z')
        {
            word_input[i]=word_input[i]+32;
        }
    }
    return word_input;
}

string *create_random(const string &fn)
{
    //δημιουργία πίνακα που περιέχει size_rand τυχαίες λέξεις από το αρχείο
    int k=0, cnt=0;
    //η μεταβλητή k μετράει το πλήθος των λέξεων που έχουν προστεθεί στον πίνακα
    //η μεταβλητή cnt μετράει το πλήθος των λέξεων που έχουν διαβαστεί από το αρχείο
    string *random;

    random=new string[size_rand];

    srand(time(nullptr));

    //ifs.clear();
    //ifs.seekg(0,ifs.beg);

    ifstream ifs;
    ifs.open(fn);
    if(ifs.is_open())
    {
        //cout<<"file open"<<endl;

        bool stop=false;

        //read file line by line
        string line;
        while(getline(ifs, line) && !stop)
        {
            //stringstream ss(line);
            istringstream iss(line);
            string word_input;
            while(iss>>word_input && !stop)
            {
                //cout<<word_input<<"-->";
                word_input=edit_word(word_input);
                //cout<<word_input<<endl;

                cnt++;

                //παραγωγή τυχαίου αριθμού από το 1 έως και το 100
                int rand_num=rand()%100+1;
                //cout<<"random num="<<rand_num<<endl;

                if(k<size_rand) //what if file ends?
                    //όσο δεν έχουν προστεθεί size_rand λέξεις στον πίνακα
                {
                    int len=(int)word_input.size();
                    if(len%2==rand_num%2) //συνθήκη τυχαιότητας
                        //το μήκος της λέξης που έχει διαβαστεί από το κείμενο και ο τυχαίος αριθμός
                        //πρέπει να είναι ταυτόχρονα είτε άρτιοι είτε περιττοί αριθμοί
                    {
                        random[k]=word_input;
                        k++;
                        //cout<<"word #"<<cnt<<" added to random"<<"  k="<<k<<"   len="<<len<<"   rand_num="<<rand_num<<endl;
                    }
                }
                else
                    stop=true;
            }
        }
        ifs.close();
    }
    else
    {
        cout<<"file error random"<<endl;
    }

    return random;
}

void insertHashTable(const string &fn, HashTable &ht)
{
    ifstream ifs;
    ifs.open(fn);
    if(ifs.is_open())
    {
        //διάβασμα αρχείου ανά γραμμή
        string line;
        while(getline(ifs, line))
        {
            //stringstream ss(line);
            istringstream iss(line);
            string word_input;
            while(iss>>word_input)
            {
                //cout<<word_input<<"-->";
                word_input=edit_word(word_input);
                //cout<<word_input<<endl;

                bool ins=ht.insert(word_input);
                if(!ins)
                    cout<<"could not insert word (ht)"<<endl;
            }
        }
        ifs.close();
    }
    else
    {
        cout<<"file error (ht)"<<endl;
    }
}

void countHashTable(HashTable &ht, string *random)
{
    string word[size_rand];
    int cnt[size_rand];

    auto t1=chrono::steady_clock::now();
    for(int i=0;i<size_rand;i++)
    {
        int counter;

        bool found=ht.search(random[i],counter);

        if(found)
        {
            word[i]=random[i];
            cnt[i]=counter;
        }
        else
        {
            cout<<"word not found (ht)"<<endl;
        }
    }
    auto t2=chrono::steady_clock::now();

    cout<<"hash table total search time: ";
    showTime(t1,t2);

    ofstream ofs1;
    ofs1.open("HashTable.txt", ofstream::out | ofstream::trunc);
    ofs1<<"Output αναζήτησης τυχαίου δείγματος 1000 λέξεων με χρήση της δομής Hash Table"<<endl<<endl;
    ofs1<<"A/A  Λέξη  ΠΛήθος Εμφανίσεων"<<endl;
    for(int i=0;i<size_rand;i++)
    {
        ofs1<<i+1<<".   "<<word[i]<<" -> "<<cnt[i]<<endl;
    }
    ofs1.close();

    ofstream ofs;
    ofs.open("output.txt", ofstream::out | ofstream::app);
    ofs<<"hash table total search time: ";
    ofs<<(float)(chrono::duration_cast<chrono::microseconds>(t2 - t1).count())/1000<<" ms"<<endl;
    ofs.close();
}

NodeAVL *insertAVL(const string &fn, AVL &avltr, NodeAVL *root) //root?
{
    ifstream ifs;
    ifs.open(fn);
    if(ifs.is_open())
    {
        //διάβασμα αρχείου ανά γραμμή
        string line;
        while(getline(ifs, line))
        {
            //stringstream ss(line);
            istringstream iss(line);
            string word_input;
            while(iss>>word_input)
            {
                //cout<<word_input<<"-->";
                word_input=edit_word(word_input);
                //cout<<word_input<<endl;

                root=avltr.insert_word(root,word_input);
            }
        }
        ifs.close();
    }
    else
    {
        cout<<"file error (avl)"<<endl;
    }
    return root;
}

void countAVL(AVL &avltr, NodeAVL *root, string *random)
{
    string word[size_rand];
    int cnt[size_rand];

    auto t1=chrono::steady_clock::now();
    for(int i=0;i<size_rand;i++)
    {
        int counter;

        bool found=avltr.search_word(root,random[i],counter);

        if(found)
        {
            word[i]=random[i];
            cnt[i]=counter;
        }
        else
        {
            cout<<"word not found (avl)"<<endl;
        }
    }
    auto t2=chrono::steady_clock::now();

    cout<<"avl total search time: ";
    showTime(t1,t2);

    ofstream ofs1;
    ofs1.open("AVL.txt", ofstream::out | ofstream::trunc);
    ofs1<<"Output αναζήτησης τυχαίου δείγματος 1000 λέξεων με χρήση της δομής AVL"<<endl<<endl;
    ofs1<<"A/A  Λέξη  ΠΛήθος Εμφανίσεων"<<endl;
    for(int i=0;i<size_rand;i++)
    {
        ofs1<<i+1<<".   "<<word[i]<<" -> "<<cnt[i]<<endl;
    }
    ofs1.close();

    ofstream ofs;
    ofs.open("output.txt", ofstream::out | ofstream::app);
    ofs<<"avl total search time: ";
    ofs<<(float)(chrono::duration_cast<chrono::microseconds>(t2 - t1).count())/1000<<" ms"<<endl;
    ofs.close();
}

void insertBST(const string &fn, BST &bintr)
{
    ifstream ifs;
    ifs.open(fn);
    if(ifs.is_open())
    {
        //διάβασμα αρχείου ανά γραμμή
        string line;
        while(getline(ifs, line))
        {
            //stringstream ss(line);
            istringstream iss(line);
            string word_input;
            while(iss>>word_input)
            {
                //cout<<word_input<<"-->";
                word_input=edit_word(word_input);
                //cout<<word_input<<endl;

                bool ins=bintr.insert_word(word_input);
                if(!ins)
                    cout<<"could not insert word (bst)"<<endl;
            }
        }
        ifs.close();
    }
    else
    {
        cout<<"file error (bst)"<<endl;
    }
}

void countBST(BST &bintr, string *random)
{
    string word[size_rand];
    int cnt[size_rand];

    auto t1=chrono::steady_clock::now();
    for(int i=0;i<size_rand;i++)
    {
        int counter;

        bool found=bintr.search_word(random[i],counter);

        if(found)
        {
            word[i]=random[i];
            cnt[i]=counter;
        }
        else
        {
            cout<<"word not found (bst)"<<endl;
        }
    }
    auto t2=chrono::steady_clock::now();

    cout<<"bst total search time: ";
    showTime(t1,t2);

    ofstream ofs1;
    ofs1.open("BST.txt", ofstream::out | ofstream::trunc);
    ofs1<<"Output αναζήτησης τυχαίου δείγματος 1000 λέξεων με χρήση της δομής BST"<<endl<<endl;
    ofs1<<"A/A  Λέξη  ΠΛήθος Εμφανίσεων"<<endl;
    for(int i=0;i<size_rand;i++)
    {
        ofs1<<i+1<<".   "<<word[i]<<" -> "<<cnt[i]<<endl;
    }
    ofs1.close();

    ofstream ofs;
    ofs.open("output.txt", ofstream::out | ofstream::app);
    ofs<<"bst total search time: ";
    ofs<<(float)(chrono::duration_cast<chrono::microseconds>(t2 - t1).count())/1000<<" ms"<<endl;
    ofs.close();
}

void insertSortedArray(const string &fn, SortedArray &sortar)
{
    ifstream ifs;
    ifs.open(fn);
    if(ifs.is_open())
    {
        //διάβασμα αρχείου ανά γραμμή
        string line;
        while(getline(ifs, line))
        {
            //stringstream ss(line);
            istringstream iss(line);
            string word_input;
            while(iss>>word_input)
            {
                //cout<<word_input<<"-->";
                word_input=edit_word(word_input);
                //cout<<word_input<<endl;

                bool ins=sortar.insert_word(word_input);
                if(!ins)
                    cout<<"could not insert word (sortar)"<<endl;

            }
        }
        ifs.close();
    }
    else
    {
        cout<<"file error (sortar)"<<endl;
    }
}

void countSortedArray(SortedArray &sortar, string *random)
{
    string word[size_rand];
    int cnt[size_rand];

    auto t1=chrono::steady_clock::now();
    for(int i=0;i<size_rand;i++)
    {
        int counter, ind;

        bool found=sortar.binarySearch(random[i],counter,ind);

        if(found)
        {
            word[i]=random[i];
            cnt[i]=counter;
        }
        else
        {
            cout<<"word not found (sortar)"<<endl;
        }
    }
    auto t2=chrono::steady_clock::now();

    cout<<"Sorted Array total search time: ";
    showTime(t1,t2);

    ofstream ofs1;
    ofs1.open("SortedArray.txt", ofstream::out | ofstream::trunc);
    ofs1<<"Output αναζήτησης τυχαίου δείγματος 1000 λέξεων με χρήση της δομής Sorted Array"<<endl<<endl;
    ofs1<<"A/A  Λέξη  ΠΛήθος Εμφανίσεων"<<endl;
    for(int i=0;i<size_rand;i++)
    {
        ofs1<<i+1<<".   "<<word[i]<<" -> "<<cnt[i]<<endl;
    }
    ofs1.close();

    ofstream ofs;
    ofs.open("output.txt", ofstream::out | ofstream::app);
    ofs<<"sorted array total search time: ";
    ofs<<(float)(chrono::duration_cast<chrono::microseconds>(t2 - t1).count())/1000<<" ms"<<endl;
    ofs.close();
}

void insertUnsortedArray(const string &fn, UnsortedArray &unsortar)
{
    ifstream ifs;
    ifs.open(fn);
    if(ifs.is_open())
    {
        //διάβασμα αρχείου ανά γραμμή
        string line;
        while(getline(ifs, line))
        {
            //stringstream ss(line);
            istringstream iss(line);
            string word_input;
            while(iss>>word_input)
            {
                //cout<<word_input<<"-->";
                word_input=edit_word(word_input);
                //cout<<word_input<<endl;

                bool ins=unsortar.insert_word(word_input);
                if(!ins)
                    cout<<"could not insert word (unsortar)"<<endl;
            }
        }
        ifs.close();
    }
    else
    {
        cout<<"file error (unsortar)"<<endl;
    }
}

void countUnsortedArray(UnsortedArray &unsortar, string *random)
{
    string word[size_rand];
    int cnt[size_rand];

    auto t1=chrono::steady_clock::now();
    for(int i=0;i<size_rand;i++)
    {
        int counter, ind;

        bool found=unsortar.linearSearch(random[i],counter,ind);

        if(found)
        {
            word[i]=random[i];
            cnt[i]=counter;
        }
        else
        {
            cout<<"word not found (unsortar)"<<endl;
        }
    }
    auto t2=chrono::steady_clock::now();

    cout<<"Unsorted Array total search time: ";
    showTime(t1,t2);

    ofstream ofs1;
    ofs1.open("UnsortedArray.txt", ofstream::out | ofstream::trunc);
    ofs1<<"Output αναζήτησης τυχαίου δείγματος 1000 λέξεων με χρήση της δομής Unsorted Array"<<endl<<endl;
    ofs1<<"A/A  Λέξη  ΠΛήθος Εμφανίσεων"<<endl;
    for(int i=0;i<size_rand;i++)
    {
        ofs1<<i+1<<".   "<<word[i]<<" -> "<<cnt[i]<<endl;
    }
    ofs1.close();

    ofstream ofs;
    ofs.open("output.txt", ofstream::out | ofstream::app);
    ofs<<"unsorted array total search time: ";
    ofs<<(float)(chrono::duration_cast<chrono::microseconds>(t2 - t1).count())/1000<<" ms"<<endl;
    ofs.close();
}