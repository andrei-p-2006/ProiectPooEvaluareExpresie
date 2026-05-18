#ifndef NOD_EXPRESIE_H
#define NOD_EXPRESIE_H

#include <map>
#include <string>
//
class NodExpresie {
public:
    virtual ~NodExpresie() = default;

    virtual double evalueaza() const = 0;
    virtual NodExpresie* clona() const = 0;

    static std::map<std::string, double> tabelVariabile;

    static bool valideazaParanteze(const std::string& expr);
};

#endif