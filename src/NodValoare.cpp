#include "NodValoare.h"
#include "MathException.h"

#include <utility>
//
NodValoare::NodValoare(double v) : valoare(v), numeVariabila() {}

NodValoare::NodValoare(std::string nume) : valoare(0.0), numeVariabila(std::move(nume)) {}

double NodValoare::evalueaza() const
{
    if (esteConstanta())
        {
        return valoare;
    }

    auto it = tabelVariabile.find(numeVariabila);
    if (it == tabelVariabile.end())
    {
        throw MathException("Variabila '" + numeVariabila + "' nu are valoare asociată.");
    }

    return it->second;
}

NodExpresie* NodValoare::clona() const
{
    if (esteConstanta()) {
        return new NodValoare(valoare);
    }
    return new NodValoare(numeVariabila);
}