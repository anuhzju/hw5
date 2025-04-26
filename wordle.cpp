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


// Add prototypes of helper functions here
void wordleHelper(const std::string& in,
    //const std::set<char> floating,
    string& current,
    int index,
    int floatCounts[26],
    int floatLeft,
    const std::set<std::string>& dict,
    set<string>& results)
{
  /*
    int remainingPos = in.size() - ind;
    if (floating.size() > remainingPos) {
        return;
    }
  */
    if (index == in.size()){
      if (floatLeft == 0 && dict.find(current) != dict.end()) {
            results.insert(current);
        }
        return;
    }

    /*
    size_t remaining = in.size() - ind;
    if (floating.size() > remaining){
      return;
    }
    */

    if (in[index] != '-'){
      current[index] = in[index];
      //current.push_back(in[ind]);
      wordleHelper(in, current, index + 1, floatCounts, floatLeft, dict, results);
      //current.pop_back();
      return;
    }

    for (int i = 0; i < 26; ++i){
      if (floatCounts[i] > 0){
        current[index] = 'a' + i;
        floatCounts[i]--;
        wordleHelper(in, current, index + 1, floatCounts, floatLeft - 1, dict, results);
        floatCounts[i]++;
      }
    }
    int remainingSlots = in.size() - index - 1;
    if (remainingSlots >= floatLeft){
      for (int i = 0; i < 26; ++i){
        if (floatCounts[i] == 0){
          current[index] = 'a' + i;
          wordleHelper(in, current, index + 1, floatCounts, floatLeft, dict, results);
        }
      }
    }
    /*
    std::set<char> tried; 
    for (auto it = floating.begin(); it != floating.end(); ++it) {
        if (tried.count(*it)) continue;
        tried.insert(*it);

        char c = *it;
        current.push_back(c);

        std::multiset<char> newFloating = floating;
        newFloating.erase(newFloating.find(c));         
        wordleHelper(in, newFloating, dict, current, ind + 1, results);

        current.pop_back();
    }
    if (floating.size() < remaining) {
        for (char c = 'a'; c <= 'z'; ++c) {
            if (floating.count(c)) continue; // already tried above

            current.push_back(c);
            wordleHelper(in, floating, dict, current, ind + 1, results);
            current.pop_back();
        }
    }

    //bool used[26] = {false};
    for (size_t i = 0; i < floating.size(); ++i) {
        char c = floating[i];
        string newFloating = floating.substr(0, i) + floating.substr(i + 1);
        //current.push_back(c);
        wordleHelper(in, newFloating, dict, current + c, ind + 1, results);
        //current.pop_back();
    }
  
    //int remainingPos = in.size() - ind - 1;
    if (in.size() - ind > floating.size()){
      for (char c = 'a'; c <= 'z'; ++c){
        if (floating.find(c) != string::npos) {
          continue;
        }
        //current.push_back(c);
        wordleHelper(in, floating, dict, current + c, ind + 1, results);
        //current.pop_back();
      }
    }
    */
}

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    set<string> results;
    string current = in;
    int floatCounts[26] = {0};
    for (char c : floating){
      floatCounts[c - 'a']++;
    }
    //multiset<char> inFloat(floating.begin(), floating.end());
    //current.reserve(in.size());
    wordleHelper(in, current, 0, floatCounts, floating.size(), dict, results);
    return results;
}

// Define any helper functions here
