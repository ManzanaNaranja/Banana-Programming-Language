#ifndef PARSER__H
#define PARSER__H

#include<vector>
#include "token.h"
#include <string>
#include <stack>
#include <unordered_map>
#include "LineInfo.h"
using namespace std;

class Parser {
    public:
        unordered_map<int, LineInfo*> parse(vector<vector<Token*>> data) {
            stack<int> FORstack;
            unordered_map<int, LineInfo*> programInfo;
            for(int i = 0; i < data.size(); i++) {
                string cmd = data.at(i).at(0)->contents;
                if(cmd == "FOR") {
                    FORstack.push(i);
                } else if(cmd == "NEXT") {
                    int topInt = FORstack.top();
               //     gotoList.at(topInt) = i+1;
                    programInfo.insert(make_pair(topInt, new LineInfo(i+1)));
                    programInfo.insert(make_pair(i, new LineInfo(topInt)));
                   // gotoList.at(i) = topInt;
                    FORstack.pop();
                }
            }
            return programInfo;
        }
};

#endif