#include<iostream>
#include<vector>
#include"type.h"
#include"program.h"
#include"builtin.h"

using namespace std;


RetCode print(vector<Variable> args){
    RetCode ret;
    ret.err = true;
    ret.var = NULL;
    if (args.size() == 1){
        if (args[0].type == TString){
            cout << args[0].String << endl;
            ret.err = false;
        }
    }
    return ret;
}