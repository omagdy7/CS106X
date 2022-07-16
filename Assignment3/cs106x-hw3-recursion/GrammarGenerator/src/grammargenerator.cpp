/*
 * File: grammargenerator.cpp
 * --------------------------
 * Name:
 * Section leader:
 * This file contains grammar generating code for CS106X HW3.
 */

#include "grammargenerator.h"
#include "map.h"
#include "filelib.h"
#include "random.h"

using namespace std;

/**
 * Generates grammar for a given symbol a certain number of times given
 * a BNF input file.
 *
 * This will be called by grammarmain.cpp.
 *
 * @param input - Input stream of BNF file.
 * @param symbol - Symbol to generate
 * @param times - Number of times grammar is generated
 * @return Vector of strings of size times with random generations of symbol
 */

Map<string, Vector<string>> handleInput(istream& input) {
    Map<string, Vector<string>> mp;
    string line;
    while(getline(input, line)) {
        int ind = 0;
        for(int i = 0; i < int(line.size()); i++) {
            if(line[i] == '=' ) {
                ind = i - 3;
                break;
            }
        }
        mp[line.substr(0, ind + 1)] = stringSplit(line.substr(ind + 4, line.size() - 1), "|");
    }
    return mp;
}


bool isTerminal(const string& st) {
    for(auto ch : st) {
        if(ch == '<' || ch == '>' || isupper(ch)) {
            return false;
        }
    }
    return true;
}



void generateGrammarHelper(const string& symbol, int times, Vector<string> &chosen, Map<string, Vector<string>> &mp) {
    if(times == 0) {
        return;
    } else {
            if(!mp[symbol].isEmpty()) {
                string newSymbol = mp[symbol][randomInteger(0, mp[symbol].size() - 1)];
                Vector<string> tmp = stringSplit(newSymbol, " ");
                for(int i = 0; i < tmp.size(); i++) {
                if(isTerminal(tmp[i])) {
                    chosen.add(tmp[i]);
                } else {
                    generateGrammarHelper(tmp[i], times - 1, chosen, mp);
                    }
                }
            } else {
                chosen.add(symbol);
            }
    }
}




Vector<Vector<string>> generateGrammar(istream& input, const string& symbol, int times) {
    auto mp = handleInput(input);
    Vector<Vector<std::string>> vec;
    for(int i = 0; i < times; i++) {
        Vector<string> chosen;
        generateGrammarHelper(symbol, times, chosen, mp);
        vec.add(chosen);
    }
    return vec;
}
