#include <iostream>
#include "lexer.h"
#include "variable.h"
#include "evaluator.h"
#include "parser.h"
#include <vector>
#include <list>
#include "token.h"
#include <unordered_map>
#include <regex>
#include <fstream>
#include "bananafinder.h"

using namespace std;

void Evaluate();

int main() {
    
    ofstream ofs("userFile.txt");

    string line;
    while(line != "RUN BANANA") {
        cout << "] ";
        getline(cin, line);
        if(line != "RUN BANANA")  ofs << line << endl;
    }

    BananaFinder b;
    int a= b.findBananas("userFile.txt");
    if(a <= 0) {
        cout << "err: NO BANANAS IN YOUR CODE? BADDDD" << endl;
        return 1;
    }
 
    Evaluate();
    return 0;
}


void Evaluate() {
    Lexer l;
    Parser p;
    Evaluator e;
    vector<vector<Token*>> tokenList = l.getTokens("userFile.txt");
    unordered_map<int, LineInfo*> programInfo = p.parse(tokenList);
   
    e.evaluate(tokenList, programInfo);
}

