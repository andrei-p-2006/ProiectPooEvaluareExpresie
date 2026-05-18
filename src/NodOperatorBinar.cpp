#include "NodOperatorBinar.h"
#include "NodValoare.h"

#include <istream>
#include <typeinfo>
//
NodOperatorBinar::NodOperatorBinar(NodExpresie* s, NodExpresie* d): stanga(s),dreapta(d) {}

NodOperatorBinar::NodOperatorBinar(const NodOperatorBinar& other):
        NodExpresie(other),
        stanga(other.stanga ? other.stanga->clona() : nullptr),
        dreapta(other.dreapta ? other.dreapta->clona() : nullptr) {}

NodOperatorBinar& NodOperatorBinar::operator=(const NodOperatorBinar& other) {
    if (this==&other)
        return *this;

    NodExpresie* stangaNoua = other.stanga ? other.stanga->clona() : nullptr;
    NodExpresie* dreaptaNoua = other.dreapta ? other.dreapta->clona() : nullptr;

    delete stanga;
    delete dreapta;
    stanga = stangaNoua;
    dreapta = dreaptaNoua;

    return *this;
}

NodOperatorBinar::~NodOperatorBinar()
{
    delete stanga;
    delete dreapta;
}

void NodOperatorBinar::setStanga(NodExpresie* s)
{
    if (s==stanga)
        return;

    delete stanga;
    stanga = s;
}

void NodOperatorBinar::setDreapta(NodExpresie* d)
{
    if (d==dreapta)
        return;

    delete dreapta;
    dreapta = d;
}

bool NodOperatorBinar::operator==(const NodOperatorBinar& other) const
{
    if (typeid(*this)!=typeid(other))
    {
        return false;
    }

    auto egal = [](const NodExpresie* a, const NodExpresie* b) -> bool
    {
        if (!a || !b)
            return (a==b);

        if (typeid(*a)!=typeid(*b))
            return false;

        const auto* va=dynamic_cast<const NodValoare*>(a);
        const auto* vb=dynamic_cast<const NodValoare*>(b);
        if (va && vb) {
            if (va->esteConstanta()!=vb->esteConstanta())
                return false;
            if (va->esteConstanta())
                return (va->getValoare()==vb->getValoare());
            return (va->getNume()==vb->getNume());
        }

        const auto* ba = dynamic_cast<const NodOperatorBinar*>(a);
        const auto* bb = dynamic_cast<const NodOperatorBinar*>(b);
        if (ba && bb)
            return (*ba == *bb);

        return false;
    };

    return egal(stanga, other.stanga) && egal(dreapta, other.dreapta);
}

std::istream& operator>>(std::istream& is, NodOperatorBinar& nod) {
    double stg=0.0;
    double dr=0.0;
    is>>stg>>dr;
    nod.setStanga(new NodValoare(stg));
    nod.setDreapta(new NodValoare(dr));
    return is;
}