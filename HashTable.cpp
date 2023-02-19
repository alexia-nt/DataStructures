#include "HashTable.h"

#include <iostream>
using namespace std;

HashTable::HashTable()
{
    size=10000;
    elements=0;

    deleted=this; //new int();

    A=new WordCNT *[size];
    for(int i=0;i<size;i++)
        A[i]=nullptr;
}

void HashTable::clearHashTable()
{
    cout<<"destroy table called"<<endl;
    delete[] A;
    A=nullptr;
    elements=0;
    size=0;
}
/*
unsigned int HashTable::hash(const string &d)
{
    unsigned int sum = 0;
    for(int i=0; i<d.size(); i++)
    {
      sum = (i+1)*d[i];
    }
    return sum%size;
}
*/
unsigned int HashTable::hash(string d) //http://www.cse.yorku.ca/~oz/hash.html
{
    unsigned long int hash=5381;

    for(char c: d) //για κάθε χαρακτήρα του string (range-based for loop)
    {
        hash=((hash<<5)+hash)+c; /* hash * 33 + c */
    }
    return (hash%size);
}

unsigned int HashTable::hash2(unsigned int d)
{
    return (d+1)%size;
}

bool HashTable::insert(const string &key)
{
    WordCNT *k=search(key);
    if(search(key)!=nullptr)
    {
        k->cnt++;
        return true;
    }
    if(elements>=size/2)
    {
        cout<<"resizing table..."<<endl;
        WordCNT **temp;
        size*=2;
        temp=new WordCNT *[size];
        for(int i=0;i<size;i++)
            temp[i]=nullptr;

        for(int i=0;i<size/2;i++)
        {
            if(A[i]!=nullptr && A[i]!=deleted)
            {
                unsigned int p=hash(A[i]->word);
                while(temp[p]!=nullptr)
                    p=hash2(p);
                temp[p]=A[i];
                A[i]=nullptr;
            }
        }
        delete[]A;
        A=temp;
    }
    unsigned int p=hash(key);
    while(A[p]!=nullptr && A[p]!=deleted)
        p=hash2(p);

    A[p]=new WordCNT(1,key); //?
    elements++;
    return true;
}

WordCNT *&HashTable::search(const string &word)
{
    unsigned int p=hash(word);

    while((A[p]!=nullptr && A[p]->word!=word))
        p=hash2(p);
    return A[p];
}

bool HashTable::search(const string &w, int &c)
{
    WordCNT *p=search(w);

    if(p==nullptr) //αν η λέξη δεν βρεθεί
        return false;

    c=p->cnt; //η μεταβλητή c αποθηκεύει το πλήθος εμφανίσεων της λέξης

    return true;
}

int HashTable::getElements()
{
    return elements;
}

void HashTable::show()
{
    for(int i=0; i<size; i++)
    {
        if(A[i]!=nullptr)
        {
            cout<<A[i]->word<<" "<<A[i]->cnt<<endl;
        }
    }
}
