#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;

// Helper function to do the recursion
void solve(
    const std::string& origin,
    std::string& currWord_,
    std::string floating_,
    const std::set<std::string>& dict_,
    std::set<std::string>& words_,
    int pos
    );

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    // Initialize variables so that we can modify them
    std::string currWord = in;
    std::set<std::string> words;
    // Call our helper function to basically do all the work
    solve(in, currWord, floating, dict, words, 0);
    return words;
}

// Define any helper functions here
// Function that does all the recursion
void solve(
    const std::string& origin,
    std::string& currWord_,
    std::string floating_,
    const std::set<std::string>& dict_,
    std::set<std::string>& words_,
    int pos
    )
{
    int blanksLeft = 0;
    for (int i = pos; i < origin.size(); ++i)
    {
        if (origin[i] == '-')
        {
            ++blanksLeft;
        }
    }
    // impossible case
    if (floating_.size() > blanksLeft)
    {
        return;
    }
    // base case
    if (pos == origin.size())
    {
        if (floating_.size() == 0 && dict_.find(currWord_) != dict_.end())
        {
        words_.insert(currWord_);
        }
        return;
    }
    // Check if the letter we are on is a green letter
    if (origin[pos] != '-')
    {
        solve (origin, currWord_, floating_, dict_, words_, pos+1);
    }
    // if it is a dash, then loop through each letter in the alphabet to add
    // and recurse
    else
    {
        // looping through all floating characters
        for (int i = floating_.size() - 1; i >= 0 ; --i)
        {
            char c = floating_[i];
            currWord_[pos] = c;
            std::string newFloat = floating_;
            newFloat.erase(i, 1);
            solve(origin, currWord_, newFloat, dict_, words_, pos+1);
        }
        // looping through all other alphabetical options
        if (floating_.size() < blanksLeft)
        {
            for (int i = 97; i < 123; ++i)
            {
                if (floating_.find(i) == std::string::npos)
                {
                    currWord_[pos] = i;
                    solve(origin, currWord_, floating_, dict_, words_, pos+1);
                }
            }
        }

    }
}