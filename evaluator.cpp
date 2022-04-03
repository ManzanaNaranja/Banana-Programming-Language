#include "evaluator.h"
#include <unordered_map>
#include <string> 
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

Evaluator::Evaluator() {

}

void Evaluator::deleteVariable(string name) {
    auto obj = vars.find(name);
    if(obj != vars.end() ) { 
        delete obj->second;
        vars.erase(name); 
    }
}
void Evaluator::createVariable(string name, Token* data) {
    auto obj = vars.find(name);
    if(obj != vars.end() ) { // exists already
        delete obj->second;
        vars.erase(name); 
    }
    Variable* var;
    if(data->type == astring) {
        var = new StringVariable(data->contents);
    } else if(data->type == aint) {
        var = new IntVariable(stoi(data->contents));
    } else if(data->type == abool) {
        var = new BoolVariable((data->contents == "True") ? true : false);
    } else if(data->type == achar) {
        var = new CharVariable(data->contents.at(0));
    }
    vars.insert(make_pair(name, var));
}

void Evaluator::createVariable(string name, Variable* v) {
    vars.insert(make_pair(name, v));
}

Variable* Evaluator::getVariable(string name) {
    auto obj = vars.find(name);
    if(obj == vars.end()) {
        return nullptr;
    } else {
        return obj->second;
    }
}

void Evaluator::evaluate(vector<vector<Token*>> data, unordered_map<int, LineInfo*> programInfo) {

    unsigned line = 0;
    while(line < data.size()) {
        vector<Token*> curr = data.at(line);
        string cmd = curr.at(0)->contents;
        if(cmd == "LET") {
            createVariable(curr.at(1)->contents, curr.at(3));
        } else if(curr.size() == 3 && curr.at(1)->contents == "=") {
            // need to check if rhs is an expression to evaluate
            createVariable(curr.at(0)->contents, curr.at(2));
        } else if(cmd == "PRINT") {
          // need to add check if rhs is expression to evaluate
          Token* t = curr.at(1);
          if(t->type != aundefined && t->type != avar) {
              cout << t->contents;
          } else if(t->contents == "LINE") {
              cout << endl;
          } else if(t->type == avar) {
              Variable* v = getVariable(t->contents);
              cout << v->toString();
          }
        } else if(cmd == "FOR") {
            auto obj = vars.find(curr.at(1)->contents);
            int lhs, rhs;
            if(obj == vars.end()) { // if var doesn't exist
                if(curr.at(3)->type == aint) {
                    createVariable(curr.at(1)->contents, curr.at(3));
                    lhs = stoi(curr.at(3)->contents);
                } else if(curr.at(3)->type == avar) {
                    Variable *v = getVariable(curr.at(3)->contents);
                    IntVariable *n = dynamic_cast<IntVariable*>(v);
                    createVariable(curr.at(1)->contents, n);
                    lhs = n->data;
                } else {
                    cout << "ERR LINE 77 EVAL.cpp" <<endl;
                }
             
            } else {
                IntVariable *n = dynamic_cast<IntVariable*>(obj->second);
                n->data++;
                lhs = n->data;
            }
            if(curr.at(5)->type == avar) {
                Variable *v = getVariable(curr.at(5)->contents);
                IntVariable *n = dynamic_cast<IntVariable*>(v);
                rhs = n->data;
            } else {
                rhs = stoi(curr.at(5)->contents);
            }
            
            if(lhs < rhs) {
                line++;
                continue;
            } else {
                deleteVariable(curr.at(1)->contents);
                line = programInfo.at(line)->goto_line;
                continue;
            }
        } else if(cmd == "NEXT") {
            line = programInfo.at(line)->goto_line;
            continue;
        }
        line++;
    }
//     unsigned line = 0;
//     while(line < data.size()) {
//   //      cout << "LINE: " << line;
//         vector<Token*> curr = data.at(line);
//         string cmd = curr.at(0)->contents;
//         if(cmd == "LET") {
//        //     createVariable(curr.at(1)->contents, ); NEED KNOW DATATYPE
//         //    vars.insert(make_pair(curr.at(1)->contents, curr.at(3)->contents));
//         }   else if(cmd == "FOR") {
//             auto obj = vars.find(curr.at(1)->contents);
//             string lhs, rhs;
//             if(obj == vars.end()) {
//            //     cout << "VAR " << curr.at(1)->contents << "is undefined\n";
//                 return;
//             } else {
//                 lhs = obj->second;
//             }
//             rhs = curr.at(3)->contents; // CHECK TOKEN'S TYPE IN FUTURE (ex: expression, var, or const)
//             if(stoi(lhs) < stoi(rhs)) {
//                 line++;
//                 continue;
//             } else {
//                 line = programInfo.at(line)->goto_line;
//                 continue;
//             }

//         } else if(cmd == "PRINT") {
//            cout << curr.at(1)->contents; // replace with token type check
//         } else if(cmd == "NEXT") {
//             line = programInfo.at(line)->goto_line;
//             auto obj = vars.find(data.at(line).at(1)->contents);
//         //    cout << "SEC: [" << obj->second << "]"<<endl;
//             string sSsSs = obj->second;
//             int n = stoi(sSsSs);
//             stringstream ss;
//             ss << (n+1);
//             string str = ss.str();
//             obj->second = str;
//             continue;
//         }
//         line++;
//     }
}