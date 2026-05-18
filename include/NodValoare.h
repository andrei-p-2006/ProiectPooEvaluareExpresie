#ifndef NOD_VALOARE_H
#define NOD_VALOARE_H

#include "NodExpresie.h"

#include <string>
//
class NodValoare : public NodExpresie {
    double valoare;
    std::string numeVariabila;
public:
    explicit NodValoare(double v);
    explicit NodValoare(std::string nume);

    [[nodiscard]] bool esteConstanta() const { return numeVariabila.empty(); }
    [[nodiscard]] double getValoare() const { return valoare; }
    [[nodiscard]] const std::string& getNume() const { return numeVariabila; }

    double evalueaza() const override;
    NodExpresie* clona() const override;
};

#endif