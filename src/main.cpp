#include<iostream>
#include<fstream>
#include<sstream>
#include<algorithm>
#include"program.h"
#include"type.h"
#include"builtin.h"
using namespace std;

Function *createProgram(string file, vector<Function*> funcTable) {
    //Parses file into functions of instructions
    //Handles and removes ';'
    //Turns function calls into name arg1 arg2 ... argN
    //Turns function declaration into new 
    vector<Instruction> instructions;
    string curr;
    stringstream sin(file);
    while (getline(sin, curr, ';')){ // wont work for function declarations
        string oLine;
        oLine = curr;
        replace(curr.begin(), curr.end(), '(', ' ');
        replace(curr.begin(), curr.end(), ')', ' ');
        replace(curr.begin(), curr.end(), ',', ' ');
        Instruction *inst = new Instruction(curr, oLine);
        instructions.push_back(*inst);
    }
    string name("main");
    Function *func = new Function(name, instructions, funcTable);
    return func;
}

vector<Function*> makeBaseFunctions(){
    vector<Function*> newFuncTable;

    string name("print");
    Function *printFunc = new Function(name, print);
    newFuncTable.push_back(printFunc);

    return newFuncTable;
}

int main(int argc, char **argv){
    if (argc < 2){
        cerr << "Usage: " << argv[0] << " <input file>" << endl;
        return 1;
    }
    vector<Function*> functionTable;

    ifstream fin(argv[1]);
    string file {istreambuf_iterator<char>(fin), istreambuf_iterator<char>()};

    functionTable = makeBaseFunctions();

    Function *program = createProgram(file, functionTable);
    vector<Variable> args;
    RetCode ret;
    ret = program -> exec(args);
    if (ret.err){
        cerr << "Aborted: Program Error" << endl;
    }

    return 0;
}
