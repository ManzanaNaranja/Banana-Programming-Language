#ifndef LEXER__H
#define LEXER__H

#include <vector>
#include <list>
#include <string>
#include "token.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <regex>
using namespace std;

class Lexer {
    public:
        vector<vector<Token*>> getTokens(string fileName) {
            vector<vector<Token*>> data;
            ifstream ifs(fileName);
            string line;
            while(getline(ifs, line)) {
                vector<Token*> l;
                stringstream ss(line);
                vector<string> strings = getStrings(line);
                string chunk;
                string tokenContents;
                while(ss >> chunk) {
                    tokenContents += chunk;
                    if(tokenContents.at(0) == '\"' && tokenContents.at(tokenContents.size()-1) != '\"') {
                        // cout << tokenContents << endl;
                    } else if(tokenContents.at(0) == '\"' && tokenContents.at(tokenContents.size()-1) == '\"') {
                        tokenContents = tokenContents.substr(1, tokenContents.length()-2);
                        Token *t = new Token(strings.at(0), astring);
                        // strings.erase(strings.begin()); ????????????????????
                        l.push_back(t);
                        tokenContents = "";
                    } else {
                        VarType type;
                        regex pat1("^0$|^[1-9][0-9]*$");
                        regex pat2("^[a-zA-Z0-9_]*$");
                        if(tokenContents == "True" || tokenContents == "False") {
                            type = abool;
                        } else if(regex_match(tokenContents, pat1)) {
                            type = aint;
                        } else if(tokenContents.size() == 3 && tokenContents.at(0) == '\'' && tokenContents.at(2) == '\'') {
                            type = achar;
                            tokenContents = string(1, tokenContents.at(1)); 
                        } else if(regex_match(tokenContents, pat2)) {
                            type = avar;
                        }
                        Token *t = new Token(tokenContents, type);
                        l.push_back(t);
                        tokenContents = "";
                    }

                }
                data.push_back(l);
            }
            return data;
        }

        vector<string> getStrings(string txt) {
            vector<string> list;
            string curr;
            bool inastring = false;
            for(int i = 0; i < txt.length(); i++) {
                if(txt.at(i) == '\"') {
                    inastring = !inastring;
                    if(!inastring) {
                        list.push_back(curr);
                        curr = "";
                    }
                }
                else if(inastring) {
                    curr += string(1, txt.at(i));
                }
            }
            return list;
        }
    
};

#endif