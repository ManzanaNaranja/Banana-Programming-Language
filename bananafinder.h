#ifndef BANANAFINDER__H
#define BANANAFINDER__H

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class BananaFinder {
    public:
        int findBananas(string fname) {
            int c = 0;
            ifstream ifs(fname);

            string str;
            while(getline(ifs, str)) {
                if(str.find("banana") != string::npos || str.find("BANANA") != string::npos) {
                    c++;
                }
            }
            return c;
           

        }
};

#endif