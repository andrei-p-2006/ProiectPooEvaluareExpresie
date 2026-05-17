#include "NodOperatoriUnari.h"

#include <cmath>

double NodSin::evalueaza() const
{
    return std::sin(copil->evalueaza());
}

NodExpresie* NodSin::clona() const
{
    return new NodSin(copil ? copil->clona() : nullptr);
}

double NodCos::evalueaza() const
{
    return std::cos(copil->evalueaza());
}

NodExpresie* NodCos::clona() const
{
    return new NodCos(copil ? copil->clona() : nullptr);
}

double NodAbs::evalueaza() const
{
    return std::fabs(copil->evalueaza());
}

NodExpresie* NodAbs::clona() const
{
    return new NodAbs(copil ? copil->clona() : nullptr);
}