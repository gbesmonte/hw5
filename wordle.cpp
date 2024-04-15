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

#include <vector>
#include <queue>
#include <deque>
using namespace std;


// Add prototypes of helper functions here
void solve(const std::string& in, const std::string& floating, std::string currStr, std::string pool, std::set<std::string>& s);
void solve2(const std::string& in, const std::string& floating, std::string currStr, std::string pool, std::set<std::string>& s);
// Definition of primary wordle function
std::set<std::string> wordle(
        const std::string& in,
        const std::string& floating,
        const std::set<std::string>& dict)
{
    // Add your code here
    std::string currStr = in;
    std::set<std::string> s;
    std::set<string>::iterator it;
    std::set<string>::iterator it2;
    std::set<std::string> s2;
    std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
    std::set<std::string> s3;
    solve(in, floating, currStr, floating, s);
    for (it = s.begin(); it != s.end(); ++it){
        //cout << *it << endl;
        currStr = *it;
        solve(*it, alphabet, currStr, alphabet, s2);
    }
    //cout << "DIVIDER" << endl;
    for (it2 = s2.begin(); it2 != s2.end(); ++it2){
        //cout << *it2 << endl;
        if (dict.find(*it2) != dict.end()) {
            s3.insert(*it2);
        }
    }
    return s3;
}

// Define any helper functions here
void solve(const std::string& in, const std::string& floating, std::string currStr, std::string pool, std::set<std::string>& s){
    //Check if word is full
    int a = 0;
    for (int i = 0; i < currStr.length(); i++){
        if (currStr[i] == '-'){
            break;
        }
        else{
            a++;
        }
    }
    if (a == currStr.length()){
        s.insert(currStr);
        return;
    }
    //Check if pool is empty
    if (pool.length() == 0){
        s.insert(currStr);
        return;
    }
    int count = 0;
    while (pool.length() != 0){
        if (count == floating.length()){
            break;
        }
        for (int j = 0; j < currStr.length(); j++){
            if (currStr[j] == '-'){
                currStr[j] = pool[pool.length()-1];
                std::string newPool = pool.substr(0, pool.length()-1);
                solve(in, floating, currStr, newPool, s);
                currStr[j] = '-';
            }
        }
        count++;
        char letter = pool[pool.length()-1];
        pool = pool.substr(0, pool.length()-1);
        pool = letter + pool;
    }
}

