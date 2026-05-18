#ifndef MENIU_INTERACTIV_H
#define MENIU_INTERACTIV_H

#include <string>
//
class NodExpresie;
class Parser;

class MeniuInteractiv {
    Parser& parser;
    NodExpresie* arboreCurent;
    std::string expresieCurenta;

    void afiseazaMeniu() const;
    void citesteExpresie();
    void citesteNecunoscute();
    void afiseazaRezultat();

public:
    explicit MeniuInteractiv(Parser& p);
    ~MeniuInteractiv();

    MeniuInteractiv(const MeniuInteractiv&) = delete;
    MeniuInteractiv& operator=(const MeniuInteractiv&) = delete;

    void ruleaza();
};

#endif