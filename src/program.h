#pragma once
#include<vector>
#include<string>
#include"type.h"
using namespace std;

class Function;

struct Variable { //Inefficient
    Type type;
    string name;
    i64 Int;
    u64 UInt;
    char Char;
    string String;
    double Float;
};

struct RetCode {
    bool err;
    Variable *var;
};

class Instruction {
public:
    Instruction(string iLine, string oLine);
    RetCode exec(vector<Function*> &functionTable);
    string err();
private:
    string line;
    string originalLine;
    u64 lineNum;
};

class Function {
public:
    Function(string FName, vector<Instruction> inst, vector<Function*> &FFuncTable); //Normal Lang func
    Function(string FName, RetCode (*FBuiltin)(vector<Variable>));
    RetCode exec(vector<Variable> args);
    string getName(){return name;}
private:
    string name;
    bool builtin;
    RetCode (*Builtin)(vector<Variable>);
    vector<Function*> funcTable;
    vector<Instruction> instructions;
    vector<Variable*> vars;
};
