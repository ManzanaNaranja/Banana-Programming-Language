#ifndef VARIABLE__H
#define VARIABLE__H
#include <string>

using namespace std;

enum VarType {aundefined, astring, aint, abool, achar, avar};

class Variable {
    public:
        virtual VarType getType() = 0;
        virtual string toString() = 0;
}; 

class StringVariable : public Variable{
    public:
        string data;
        StringVariable(string d) : data(d) {}
        VarType getType() { return VarType::astring; }
        string toString() { return data; }
};

class IntVariable : public Variable{
    public:
        int data;
        IntVariable(int d) : data(d) {}
        VarType getType() { return VarType::aint; }
        string toString() {
            return to_string(data);
        }
};

class BoolVariable : public Variable{
    public:
        bool data;
        BoolVariable(bool d) : data(d) {}
        VarType getType() { return VarType::abool; }
        string toString() {
            return (data) ? "True" : "False";
        }
};

class CharVariable : public Variable{
    public:
        char data;
        CharVariable(char d) : data(d) {}
        VarType getType() { return VarType::achar; }
        string toString() {
            return string(1, data);
        }
};


#endif