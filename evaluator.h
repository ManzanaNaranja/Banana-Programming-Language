#include <vector>
#include <list>
#include "token.h"
#include <string>
#include <unordered_map>
#include "variable.h"
#include "LineInfo.h"
using namespace std;

class Evaluator {
    public:
        Evaluator();
        void evaluate(vector<vector<Token*>>, unordered_map<int, LineInfo*>);
        unordered_map<string, Variable*> vars;
    public: 
        void createVariable(string name, Token* data);
        Variable* getVariable(string name);
};