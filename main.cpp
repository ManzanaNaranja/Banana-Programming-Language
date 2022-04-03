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

using namespace std;

void Test_Evaluate();
void Test_Variable();
void Test_Lexer();
void Test_Parser();
void Test_Regex(string, string);

int main() {
   // Test_Evaluate();
    // Test_Variable();
   // Test_Lexer();
 //   Test_Regex("145681", "^0$|^[1-9][0-9]*$");
 //   Test_Regex("a", "[A-Za-z]");
  //  Test_Parser();
  //  Test_Regex("asf234", "^[a-zA-Z0-9_]*$");
 
 Test_Evaluate();
    return 0;
}

void Test_Regex(string input, string thing) {
    regex pattern(thing);
    if(regex_match(input, pattern)) {
        cout << input << " matches " << thing << endl;
    } else {
        cout << input << " doesn't match " << thing << endl;
    }

}


void Test_Parser() {
    Lexer l;
    Parser p;

    vector<vector<Token*>> tokenList = l.getTokens("input.txt");
    unordered_map<int, LineInfo*> progData = p.parse(tokenList);
    cout << progData.at(2)->goto_line << endl;
}



void Test_Lexer() {
    Lexer l;
    vector<vector<Token*>> tl = l.getTokens("input.txt");
    cout << tl.size();
    for(int i = 0; i < tl.size(); i++) {
        vector<Token*> e = tl.at(i);
        for(int j = 0; j < e.size(); j++) {
            cout << "[" << e.at(j)->contents << " " << e.at(j)->type << "] ";
        }
        cout << endl;
    }

}

void Test_Variable() {
    // IntVariable v(2);
    // cout << v.data << endl;

    // Evaluator e;
    // e.createVariable("apple", new IntVariable(10));
    // auto data = e.getVariable("apple");
    // if(data->getType() == aint) {
    //     IntVariable *nnn = dynamic_cast<IntVariable*>(data);
    //     cout << nnn->data << endl;
    // }
}

void Test_Evaluate() {
    Lexer l;
    Parser p;
    Evaluator e;
    vector<vector<Token*>> tokenList = l.getTokens("input.txt");
    unordered_map<int, LineInfo*> programInfo = p.parse(tokenList);
   
    e.evaluate(tokenList, programInfo);
}

