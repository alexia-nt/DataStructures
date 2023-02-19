#include "SortedArray.h"

#include <iostream>
using namespace std;

SortedArray::SortedArray()
{
    numofwords=0;
    maxsize=5000;
    sorted_array=new wordcnt[maxsize];
}

bool SortedArray::resize_array()
{
    //cout<<"Not enough space. Requesting more..."<<endl;
    cout<<"resizing sorted array..."<<endl;

    wordcnt *temp;
    temp=new (nothrow) wordcnt[maxsize*2];
    if(temp==nullptr)
    {
        cout<<"Space not found. Stopping."<<endl;
        return false;
    }
    else
    {
        //cout<<"Space found. Moving data..."<<endl;
        for(int i=0;i<numofwords;i++)
        {
            temp[i].word=sorted_array[i].word;
            temp[i].cnt=sorted_array[i].cnt;
        }
        delete[] sorted_array;
        sorted_array=temp;
        maxsize=maxsize*2;

        return true;
    }
}

//αναζήτηση πίνακα με βάση τη λέξη keyword
//επιστρέφει το πλήθος εμφανίσεων της λέξης και τον δείκτη θέσης στον πίνακα μέσω των c και m
bool SortedArray::binarySearch(const string &keyword, int &c, int &m)
{
    bool found=false;
    int low=0, high=numofwords-1; //m;
    while(!found && low<=high)
    {
        m=(low+high)/2;
        if(sorted_array[m].word==keyword)
        {
            found=true;
        }
        else if(sorted_array[m].word<keyword)
        {
            low=m+1;
        }
        else
        {
            high=m-1;
        }
    }
    if(found)
    {
        c=sorted_array[m].cnt;
        return true;
    }
    else
        return false;
}

bool SortedArray::insert_word(const string &word_input)
{
    if(numofwords==0)
    {
        sorted_array[0].word=word_input;
        sorted_array[0].cnt=1;
        numofwords++;
        return true;
    }
    //δυαδική αναζήτηση
    bool found=false;
    int low=0, high=numofwords-1, m, index;
    while(!found && low <= high)
    {
        m=(low+high)/2;
        if(sorted_array[m].word==word_input)
        {
            found=true;
        }
        else if(sorted_array[m].word<word_input)
        {
            low=m+1;
            index=m+1;
        }
        else
        {
            high=m-1;
            index=m;
        }
    }
    //η μεταβλητή index υποδεικνύει την θέση στην οποία πρέπει να μπει η λέξη
    //σε περίπτωση που δεν υπάρχει ήδη στον πίνακα

    if(found) //η λέξη βρέθηκε
    {
        sorted_array[m].cnt++;
        return true;
    }
    else //η λέξη δεν βρέθηκε
    {
        if(numofwords==maxsize)
        {
            //διπλασιασμός μεγέθους πίνακα
            bool resizear=resize_array();
            if(!resizear)
            {
                cout<<"Insertion failed."<<endl;
                return false;
            }
        }
        for(int i=numofwords-1;i>=index;i--)
        {
            sorted_array[i+1].word=sorted_array[i].word;
            sorted_array[i+1].cnt=sorted_array[i].cnt;
        }
        sorted_array[index].word=word_input;
        sorted_array[index].cnt=1;
        numofwords++;
        return true;
    }
}

bool SortedArray::delete_word(const string &word)
{
    if(numofwords==0)
    {
        cout<<"Cannot delete word ("<<word<<"). Unsorted array is empty."<<endl;
        return false;
    }
    else
    {
        int counter, index_pos;
        bool found=binarySearch(word, counter, index_pos);
        if(!found)
        {
            cout<<"Cannot delete word ("<<word<<"). Word not found."<<endl;
            return false;
        }
        else
        {
            for(int i=index_pos;i<numofwords;i++)
            {
                sorted_array[i].word=sorted_array[i+1].word;
                sorted_array[i].cnt=sorted_array[i+1].cnt;
            }
            numofwords--;
            return true;
        }
    }
}

int SortedArray::getNumofwords()
{
    return numofwords;
}

void SortedArray::show()
{
    for(int i=0;i<numofwords;i++)
    {
        cout<<sorted_array[i].word<<" "<<sorted_array[i].cnt<<endl;
    }
    cout<<"numofwords="<<numofwords<<"    maxsize="<<maxsize<<endl;
}
