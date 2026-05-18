#ifndef PARSER_SHUNTING_YARD_H
#define PARSER_SHUNTING_YARD_H

#include "Parser.h"

#include <string>
#include <vector>
//
class NodExpresie;

class ParserShuntingYard : public Parser {
public:
    NodExpresie* parseaza(const std::string& expresie) override;

    static void simplificaArbore(NodExpresie*& radacina);
    static int numaraFunctiiTrigonometrice(NodExpresie* radacina);

private:
    static std::vector<std::string> tokenizeaza(const std::string& expresie);
    static std::vector<std::string> laPostfixat(const std::vector<std::string>& tokens);
    static NodExpresie* construiesteArbore(const std::vector<std::string>& postfixat);
};

#endif