/*
*   Author: Felipe Delclaux
*   Project #2a
*   hash.h
*   February 14, 2020
*   COSC160
*/

#include <iostream>
#include <string>
#include <fstream>
#include <exception>
#include <vector>
#include <list>
#include <cctype>
#include <algorithm>
#include <sstream>


using std::string;
using std::list;
using std::iterator;
using std::vector;

/**********************************************
 *                                            *
 *              Hash Function                 *
 *                                            *
 **********************************************/

class hash
{
    public:
        unsigned long operator()(const string &key);

};

/**********************************************
 *                                            *
 *             Chaining Hash Table            *
 *                                            *
 **********************************************/


class ChainHashTable
{

private:
    int size;
    vector<list<string>> lists;

    unsigned long myHash(const string &x) const;

public:
    ChainHashTable( int size = 100 );
    ~ChainHashTable();
    
    bool contains(const string &key) const;
    void insert(const string &key);

    void makeEmpty();

};

/**********************************************
 *                                            *
 *       Quadratic Probing Hash Table         *
 *                                            *
 **********************************************/

class QuadHashTable
{

private:
    int size;
    vector<string> array;

    unsigned long myHash(const string &x) const;
    unsigned long findPos(const string &key) const;

public:
    QuadHashTable(int size = 101);
    ~QuadHashTable();

    bool contains(const string &key);
    bool insert(const string &key);
   
    void makeEmpty();

};