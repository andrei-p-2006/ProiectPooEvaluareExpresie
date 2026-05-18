#ifndef NOD_OPERATORI_UNARI_H
#define NOD_OPERATORI_UNARI_H

#include "NodOperatorUnar.h"
//
class NodSin : public NodOperatorUnar {
public:
    using NodOperatorUnar::NodOperatorUnar;
    double evalueaza() const override;
    NodExpresie* clona() const override;
};

class NodCos : public NodOperatorUnar {
public:
    using NodOperatorUnar::NodOperatorUnar;
    double evalueaza() const override;
    NodExpresie* clona() const override;
};

class NodAbs : public NodOperatorUnar {
public:
    using NodOperatorUnar::NodOperatorUnar;
    double evalueaza() const override;
    NodExpresie* clona() const override;
};

#endif