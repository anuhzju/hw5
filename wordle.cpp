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
    const std::string& floating,
    const std::set<std::string>& dict,
    string current,
    size_t ind,
    set<string>& results)
{
    if (ind == in.size()){
      if (floating.empty() && dict.find(current) != dict.end()){
        results.insert(current);
      }
      return;

      /*
      map<char, int> floatCounts;
      for (char c : floating){
        floatCounts[c]++;
      }
      map<char, int> currentCounts;
      for (char c : current){
        currentCounts[c]++;
      }
      bool allFloatsUsed = true;
      for (map<char, int>::iterator it = floatCounts.begin(); it != floatCounts.end(); ++it){
        if (currentCounts[it->first] < it->second){
        allFloatsUsed = false;
        break;
        }
      }
      if (allFloatsUsed && dict.find(current) != dict.end()){
        results.insert(current);
      }
      return;
      */
    }

    if (in[ind] != '-'){
      wordleHelper(in, floating, dict, current + in[ind], ind + 1, results);
    }
    else {
      std::set<char> lettersToTry;

      if ((in.size() - ind) == floating.size()){
        for (char c : floating){
          lettersToTry.insert(c);
        }
      }
      else {
        for (char c = 'a'; c <= 'z'; ++c){
          lettersToTry.insert(c);
        }
      }
      for (char c : lettersToTry){
        std::string newFloating = floating;
        size_t pos = newFloating.find(c);
        if (pos != std::string::npos){
          newFloating.erase(pos, 1);
        }
        wordleHelper(in, newFloating, dict, current + c, ind + 1, results);
      }
      /*
      map<char, int> floatCounts;
      for (string::const_iterator it = floating.begin(); it != floating.end(); ++it){
        floatCounts[*it]++;
      }
      map<char, int> currentCounts;
      for (string::const_iterator it = current.begin(); it != current.end(); ++it){
        currentCounts[*it]++;
      }
      map<char, int> remainingFloats;
      for (map<char, int>::const_iterator it = floatCounts.begin(); it != floatCounts.end(); ++it){
        int need = it->second - currentCounts[it->first];
        if (need > 0){
          remainingFloats[it->first] = need;
        }
      }
      int totalRemainingFloats = 0;
      for (map<char, int>::const_iterator it = remainingFloats.begin(); it != remainingFloats.end(); ++it){
        totalRemainingFloats += it->second;
      }
      
      int remainingDashes = in.size() - ind;

      if (totalRemainingFloats > remainingDashes){ 
        return;
      }

      //std::set<char> tried;
      for (char c = 'a'; c <= 'z'; ++c){

        bool open = true;
        map<char, int> newRemainingFloats = remainingFloats;
        int newTotalRemainingFloats = totalRemainingFloats;
        map<char, int>::iterator floatIt = newRemainingFloats.find(c);
        if (floatIt != newRemainingFloats.end()){
          floatIt->second--;
          if (floatIt->second == 0){
            newRemainingFloats.erase(floatIt);
          }
          newTotalRemainingFloats--;
        }

        if (newTotalRemainingFloats > (int)(in.size() - ind - 1)){
          open = false;
        }

        if (open){
          wordleHelper(in, floating, dict, current + c, ind + 1, results);
        }
        /*
        if (totalRemainingFloats == remainingDashes && floatCounts[c] == 0){
          continue;
        }
        if (tried.count(c)){
          continue;
        }
        tried.insert(c);
        wordleHelper(in, floating, dict, current + c, ind + 1, results);
      }
      }
       */
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
    wordleHelper(in, floating, dict, "", 0, results);
    return results;
}

// Define any helper functions here
