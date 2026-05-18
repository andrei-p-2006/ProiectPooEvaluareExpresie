#include "NodOperatoriBinari.h"
#include "MathException.h"

#include <cmath>
//
double NodAdunare::evalueaza() const
{
    return stanga->evalueaza()+dreapta->evalueaza();
}

NodExpresie* NodAdunare::clona() const
{
    return new NodAdunare(stanga ? stanga->clona() : nullptr,dreapta ? dreapta->clona() : nullptr);
}

double NodScadere::evalueaza() const
{
    return stanga->evalueaza() - dreapta->evalueaza();
}

NodExpresie* NodScadere::clona() const
{
    return new NodScadere(stanga ? stanga->clona() : nullptr,dreapta ? dreapta->clona() : nullptr);
}

double NodInmultire::evalueaza() const
{
    return stanga->evalueaza() * dreapta->evalueaza();
}

NodExpresie* NodInmultire::clona() const
{
    return new NodInmultire(stanga ? stanga->clona() : nullptr,dreapta ? dreapta->clona() : nullptr);
}

double NodImpartire::evalueaza() const
{
    const double dr=dreapta->evalueaza();
    if (std::fabs(dr) < 1e-12) {
        throw DivisionByZeroException("numitor evaluat la 0");
    }
    return stanga->evalueaza() / dr;
}

NodExpresie* NodImpartire::clona() const
{
    return new NodImpartire(stanga ? stanga->clona() : nullptr,dreapta ? dreapta->clona() : nullptr);
}