#include "MeniuInteractiv.h"
#include "NodExpresie.h"
#include "ParserShuntingYard.h"

#include <iostream>

using namespace std;

int main() {
    cout<<"Proiect POO - Evaluator de expresii matematice (AST)\n";

    ParserShuntingYard parser;
    MeniuInteractiv meniu(parser);
    meniu.ruleaza();

    return 0;
}