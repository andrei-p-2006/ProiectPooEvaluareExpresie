#include "NodOperatorUnar.h"
//
NodOperatorUnar::NodOperatorUnar(NodExpresie* c) : copil(c) {}

NodOperatorUnar::NodOperatorUnar(const NodOperatorUnar& other): NodExpresie(other),
copil(other.copil ? other.copil->clona() : nullptr) {}

NodOperatorUnar& NodOperatorUnar::operator=(const NodOperatorUnar& other)
{
    if (this==&other)
        return *this;

    NodExpresie* nou = other.copil ? other.copil->clona() : nullptr;

    delete copil;
    copil = nou;

    return *this;
}

NodOperatorUnar::~NodOperatorUnar()
{
    delete copil;
}

void NodOperatorUnar::setCopil(NodExpresie* c)
{
    if (c == copil)
        return;

    delete copil;
    copil = c;
}