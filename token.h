#ifndef TOKEN__H
#define TOKEN__H

#include <string>
#include "variable.h"
using namespace std;

class Token {
    public:
        string contents;
        VarType type;
        Token(string c="", VarType t=aundefined) : contents(c), type(t) {}
};

#endif