/*
*   Author: Felipe Delclaux
*   Project #2a
*   hash.cpp
*   February 14, 2020
*   COSC160
*/

#include "hash.h"




/**************************************
 *                                    *
 *     Hash function implementaion    *
 *                                    *
 **************************************/

unsigned long hash::operator()(const string &key)
{
    unsigned long hashVal = 0;

    for(char ch : key)
        hashVal = 37 * hashVal + ch;

    return hashVal;
}

/******************************************
 *                                        *
 *     Chain Hash table implementaion     *
 *                                        *
 ******************************************/

ChainHashTable::ChainHashTable(int size)
{
    lists.resize(size);
}

unsigned long ChainHashTable::myHash( const string &x) const
{
    static hash hf;
    return hf(x) % lists.capacity();

}

ChainHashTable::~ChainHashTable()
{
    makeEmpty();
}

void ChainHashTable::makeEmpty()
{
    for(auto & thisList : lists)
        thisList.clear();
}

bool ChainHashTable::contains( const string &x) const
{
    bool present = false;

    int pos = myHash(x);

    list<string>::const_iterator it;
    for( it = lists[pos].begin(); it != lists[pos].end();++it)
    {
        if(*it == x)
        {
            present = true;
            break;
        }
    }

    return present;

}

void ChainHashTable::insert(const string &x)
{

    int pos = myHash(x);

    lists[pos].push_back(x);

}

/***************************************************
 *                                                 *
 *  Quadratic Probing Hash table implementaion     *
 *                                                 *
 ***************************************************/

QuadHashTable::QuadHashTable(int size)
{
    
    array.resize(size);
}

QuadHashTable::~QuadHashTable()
{
    array.clear();
}

unsigned long QuadHashTable::myHash(const string &x) const
{
    static hash hf;
    return hf(x) % array.capacity();
}

unsigned long QuadHashTable::findPos( const string &x) const
{

    unsigned long offset = 1;
    unsigned long currentPos = myHash(x);


    while(array[currentPos] != "" && array[currentPos] != x)
    {
        currentPos += offset;
        offset += 2;
        
        if(currentPos >= size)
        {
            currentPos -= size;
        }
    }

    return currentPos;

}

bool QuadHashTable::contains(const string &x)
{
    unsigned long currentPos = findPos(x);

    if(array[currentPos] == x)
    {
        return true;
    }

    return false;
}

bool QuadHashTable::insert(const string &x)
{

    unsigned long currentPos = findPos(x);

    if(!array[currentPos].empty())
    {
        return false;
    }

    array[currentPos] = x;

    return true;
}


