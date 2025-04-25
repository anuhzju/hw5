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
map<char, int> countChars(const string& s){
  map<char, int> counts;
  for (char c : s){
    counts[c]++;
  }
  return counts;
}

void wordleHelper(const std::string& in,
    const std::map<char, int>& floatCounts,
    const std::set<std::string>& dict,
    string current,
    size_t ind,
    set<string>& results,
    const set<string>& dictPrefixes)
{
    int remainingPositions = in.size() - ind;
    int requiredFloats = 0;

    for (const auto& pair : floatCounts){
      requiredFloats += pair.second;
    }
    if (requiredFloats > remainingPositions){
      return;
    }

    if (ind == in.size()){
      if (requiredFloats == 0 && dict.find(current) != dict.end()){
        results.insert(current);
      }
      return;
    }

    if (in[ind] != '-'){
      wordleHelper(in, floatCounts, dict, current + in[ind], ind + 1, results, dictPrefixes);
      return;
    }
    for (const auto& pair : floatCounts){
      if (pair.second > 0){
        char c = pair.first;
        map<char, int> newFloatCounts = floatCounts;
        newFloatCounts[c]--;
        if (newFloatCounts[c] == 0){
          newFloatCounts.erase(c);
        }
        string newPrefix = current + c;
        if (dictPrefixes.find(newPrefix) != dictPrefixes.end()){
          wordleHelper(in, newFloatCounts, dict, newPrefix, ind + 1, results, dictPrefixes);
        }
      }
    }
    
    if (remainingPositions > requiredFloats){
      for (char c = 'a'; c <= 'z'; ++c){
        if (floatCounts.find(c) != floatCounts.end()){
          continue;
        }
        string newPrefix = current + c;
        if (dictPrefixes.find(newPrefix) != dictPrefixes.end()){
          wordleHelper(in, floatCounts, dict, newPrefix, ind + 1, results, dictPrefixes);
        }
      }
    }
}

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    set<string> results;
    map<char, int> floatCounts = countChars(floating);
    set<string> dictPrefixes;
    for (const string& word :dict){
      for (size_t len = 1; len <= word.size(); ++len){
        dictPrefixes.insert(word.substr(0, len));
      }
    }
    wordleHelper(in, floatCounts, dict, "", 0, results, dictPrefixes);
    return results;
}

// Define any helper functions here
