#include<string>
#include<iostream>
#include<sstream>
#include"program.h"
#include"parse.h"
#include"type.h"
using namespace std;

Instruction::Instruction(string iLine, string oLine){
    line = iLine;
    originalLine = oLine;
    lineNum = 0;
}

string Instruction::err(){
    string error = "\nError on line ";
    error += to_string(lineNum);
    error += ": ";
    error += originalLine;
    error += "\nParsed as: ";
    error += line;
    return error; 
}

RetCode Instruction::exec(vector<Function*> &functionTable){
    //Parse line
    stringstream sin(line);
    string token;
    sin >> token;
    if (isTypeDeclaration(token) != TError){ // If type declaration

    } else if (isFuncCall(token, functionTable) != NULL) { // If function call
        Function* func = isFuncCall(token, functionTable);
        vector<Variable> args;
        
        while (sin >> token){
            if (token[0] == '\"'){ //Special handle strings becuase they can be multi token
                vector<string> stringList;
                stringList.push_back(token);
                sin >> token;
                do{
                    if (token[token.length()-1] == '\"'){
                        stringList.push_back(token);
                        break;
                    } else {
                        stringList.push_back(token);
                    }
                } while (sin >> token);
                token = stringList[0];
                for (u64 i = 1; i < stringList.size(); ++i){
                    token += " ";
                    token += stringList[i];
                }
            }
            
            Variable var = getVar(token);
            if (var.type != TError){
                args.push_back(var);
            }
        }
        return func -> exec(args);
    }

}


Function::Function(string FName, vector<Instruction> inst, vector<Function*> &FFuncTable){
    instructions = inst;
    name = FName;
    funcTable = FFuncTable;
    builtin = false;
}

Function::Function(string FName, RetCode (*FBuiltin)(vector<Variable>)){
    builtin = true;
    name = FName;
    Builtin = FBuiltin;
}

RetCode Function::exec(vector<Variable> args){
    RetCode res;
    res.err = false;
    res.var = NULL;
    if (builtin){
        res = Builtin(args);
        if (res.err) {
            cerr << "Failed to perform " << name << endl;
            return res;
        }
    }
    for (u64 i = 0; i < instructions.size(); ++i){
        res = instructions[i].exec(funcTable);
        if (res.err){
            cerr << instructions[i].err() << endl;
            return res;
        }
        if (res.var != NULL){
            vars.push_back(res.var);
        }
    }
    return res;
}