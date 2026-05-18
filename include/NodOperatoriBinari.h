#ifndef NOD_OPERATORI_BINARI_H
#define NOD_OPERATORI_BINARI_H

#include "NodOperatorBinar.h"
//
class NodAdunare : public NodOperatorBinar {
public:
    using NodOperatorBinar::NodOperatorBinar;
    double evalueaza() const override;
    NodExpresie* clona() const override;
};

class NodScadere : public NodOperatorBinar {
public:
    using NodOperatorBinar::NodOperatorBinar;
    double evalueaza() const override;
    NodExpresie* clona() const override;
};

class NodInmultire : public NodOperatorBinar {
public:
    using NodOperatorBinar::NodOperatorBinar;
    double evalueaza() const override;
    NodExpresie* clona() const override;
};

class NodImpartire : public NodOperatorBinar {
public:
    using NodOperatorBinar::NodOperatorBinar;
    double evalueaza() const override;
    NodExpresie* clona() const override;
};

#endif