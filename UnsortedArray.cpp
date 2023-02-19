#include "UnsortedArray.h"

#include <iostream>
using namespace std;

UnsortedArray::UnsortedArray()
{
    numofwords=0;
    maxsize=5000;
    unsorted_array=new wordcnt[maxsize];
}

bool UnsortedArray::resize_array()
{
    //cout<<"Not enough space. Requesting more..."<<endl;
    cout<<"resizing unsorted array..."<<endl;

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
            temp[i].word=unsorted_array[i].word;
            temp[i].cnt=unsorted_array[i].cnt;
        }
        delete[] unsorted_array;
        unsorted_array=temp;
        maxsize=maxsize*2;
        cout<<"unsorted array resized"<<endl;
        return true;
    }
}

//αναζήτηση πίνακα με βάση τη λέξη keyword
//επιστρέφει το πλήθος εμφανίσεων της λέξης και τον δείκτη θέσης στον πίνακα μέσω των counter και index_pos
bool UnsortedArray::linearSearch(const string &keyword, int &counter, int &index_pos)
{
    bool found=false;
    //int index_pos;
    for(int i=0;(i<numofwords && found==false);i++)
    {
        if(unsorted_array[i].word==keyword)
        {
            index_pos=i;
            found=true;
        }
    }
    if(found)
    {
        counter=unsorted_array[index_pos].cnt;
        return true;
    }
    else
    {
        return false;
    }
}

bool UnsortedArray::insert_word(const string &word)
{
    int counter, index_pos;
    bool found=linearSearch(word, counter, index_pos);

    if(found) //αν η λέξη βρέθηκε
    {
        unsorted_array[index_pos].cnt++;
    }
    else //αν η λέξη δεν βρέθηκε
    {
        if(numofwords==maxsize) //αν ο πίνακας είναι γεμάτος
        {
            //διπλασιασμός μεγέθους πίνακα
            bool resizear=resize_array();
            if(!resizear)
            {
                cout<<"Insertion failed."<<endl;
                return false;
            }
        }
        unsorted_array[numofwords].word=word;
        unsorted_array[numofwords].cnt=1;
        numofwords++;
    }
    return true;
}

bool UnsortedArray::delete_word(const string &word)
{
    if(numofwords==0) //ο πίνακας είναι άδειος
    {
        cout<<"Cannot delete word ("<<word<<"). Unsorted array is empty."<<endl;
        return false;
    }
    else //ο πίνακας δεν είναι άδειος
    {
        int counter, index_pos;
        bool found=linearSearch(word, counter, index_pos);
        if(!found)
        {
            cout<<"Cannot delete word ("<<word<<"). Word not found."<<endl;
            return false;
        }
        else
        {
            //μετακίνηση των στοιχείων του πίνακα
            for(int i=index_pos;i<numofwords;i++)
            {
                unsorted_array[i].word=unsorted_array[i+1].word;
                unsorted_array[i].cnt=unsorted_array[i+1].cnt;
            }
            numofwords--;
            return true;
        }
    }
}

int UnsortedArray::getNumofwords()
{
    return numofwords;
}

void UnsortedArray::show()
{
    for(int i=0;i<numofwords;i++)
    {
        cout<<unsorted_array[i].word<<" -> "<<unsorted_array[i].cnt<<endl;
    }
    //cout<<"numofwords="<<numofwords<<"    maxsize="<<maxsize<<endl;
}
