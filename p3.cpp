/*
*   Author: Felipe Delclaux
*   Project #2a
*   p3.cpp
*   February 14, 2020
*   COSC160
*/

#include "p3.h"

void cleanUpWord(string &x);

int main(int argc, const char* argv[])
{
    try
    {

        if( argc < 3 )
        {
            throw logic_error("Please enter a dictionaryFile and an inputFile in that order.");
        }

        string dictionaryFile = argv[1];

        string inputFile = argv[2];
        
        ifstream inFile;

        /*******************************************
         * 
         *   Reading in Dictionary to hash tables
         * 
         *******************************************/


        inFile.open(dictionaryFile.c_str());

        if(!inFile)
        {   
            throw logic_error("\t ERROR: Failure to open file");
        }

        string word;

        vector<string> dictionary;

        while(inFile >> word)
        {   
            dictionary.push_back(word);
        }

        ChainHashTable chainDictionary = ChainHashTable(dictionary.size());


        //Calculate size for hash table

        int doubleSize = 2 * dictionary.size();

        bool prime = false;
        
        while(!prime)
        {
            prime = true;
            doubleSize++;
            for(int i = 2; i < doubleSize/2; i++)
            {
                if(doubleSize % i == 0)
                {
                    prime = false;
                    break;
                }
            }
        }

        QuadHashTable quadDictionary = QuadHashTable(doubleSize);

        for(int i = 0; i < dictionary.size();i++)
        {
            chainDictionary.insert(dictionary[i]);
            quadDictionary.insert(dictionary[i]);
        }

        inFile.close();

        /*************************************
         * 
         *     Storing inputFile into vector
         * 
         *************************************/

        inFile.open(inputFile.c_str());

        if(!inFile)
        {   
            throw logic_error("\t ERROR: Failure to open file");
        }

        vector<string> check;

        while(inFile >> word)
        {
            cleanUpWord(word);
            check.push_back(word);
        }

        inFile.close();


        /******************************************************
         * 
         *          Performing spell checks and timing
         * 
         ******************************************************/


        //For chaining collision resolution
        int misspelledChain = 0;

        auto start = chrono::steady_clock::now();
        for(int i = 0; i < check.size(); i++)
        {
            string split;
            istringstream is(check[i]);

            while(is >> split)
            {
                if(!chainDictionary.contains(split))
                {
                    misspelledChain++;
                }
            }
        }
        auto end = chrono::steady_clock::now();

        std::chrono::duration<double> timeCheckChain = end - start;



        //For quad probing collision resolution
        int misspelledQuad = 0;

        auto start1 = chrono::steady_clock::now();
        for(int i = 0;i < check.size(); i++)
        {
            string split;
            istringstream is(check[i]);
    
            while(is >> split)
            {
                if(!quadDictionary.contains(split))
                {
                    misspelledQuad++;
                }
            }

        }
        auto end1 = chrono::steady_clock::now();

        std::chrono::duration<double> timeCheckQuad = end1 - start1;


       /********************************
        * 
        *          Output section
        * 
        ********************************/

        cout << "Here are the following results for the Spell Checks using the two collision handling methods" << endl;

        cout << setw(20) << "Method" << setw(20) << "Misspelt words" << setw(20) << "Time" << endl;
        cout << setw(20) << "Chaining" << setw(20) << misspelledChain << setw(20) << timeCheckChain.count() << endl;
        cout << setw(20) << "Q Probing" << setw(20) << misspelledQuad << setw(20) << timeCheckQuad.count() << endl;



    }
    catch(logic_error &e)
    {
        cout << e.what() << endl;
    }
    catch(...)
    {
        cout << "Unkwon exception caught in main" << endl;
    }

}

void cleanUpWord(string &x)
{
    std::for_each(x.begin(),x.end(), [](char & c) {if(c == '-') c = ' ';});
    x.erase (std::remove_if(x.begin (), x.end (), ::ispunct), x.end ());
    std::for_each(x.begin(),x.end(), [](char & c) {c = ::tolower(c);});
}

