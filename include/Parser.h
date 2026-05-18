#ifndef PARSER_H
#define PARSER_H

#include <string>
//
class NodExpresie;

class Parser {
public:
    virtual ~Parser() = default;
    virtual NodExpresie* parseaza(const std::string& expresie) = 0;
};

#endif