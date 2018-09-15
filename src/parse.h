#include"type.h"
#include"program.h"
#include<string>

using namespace std;

Type isTypeDeclaration(string token){
    if (token == "int"){
        return TInt;
    } else if (token == "uint") {
        return TUInt;
    } else if (token == "char") {
        return TChar;
    } else if (token == "string") {
        return TString;
    } else if (token == "float") {
        return TFloat;
    }
    return TError;
}

Function* isFuncCall(string token, const vector<Function*> &funcTable){
    for (u64 i = 0; i < funcTable.size(); ++i){
        if (funcTable[i] -> getName() == token){
            return funcTable[i];
        }
    }
    return NULL;
}

Variable getVar(string token){
    Variable var;
    if (token[0] == '\"'){ // String
        if (token[token.length()-1] == '\"'){
            var.type = TString;
            var.String = token.substr(1,token.length()-2);
            return var;
        } else {
            var.type = TError;
            return var;
        }
    } else if (token[0] == '\'') { //Char
        if (token[token.length()-1] == '\''){
            var.type = TChar;
            var.Char = token[2];
            return var;
        } else {
            var.type = TError;
            return var;
        }
    }
}