#ifndef NOD_OPERATOR_UNAR_H
#define NOD_OPERATOR_UNAR_H

#include "NodExpresie.h"

class NodOperatorUnar : public NodExpresie {
protected:
    NodExpresie* copil;
public:
    explicit NodOperatorUnar(NodExpresie* c = nullptr);
    NodOperatorUnar(const NodOperatorUnar& other);
    NodOperatorUnar& operator=(const NodOperatorUnar& other);
    ~NodOperatorUnar() override;

    [[nodiscard]] NodExpresie* getCopil() const { return copil; }
    void setCopil(NodExpresie* c);

    [[nodiscard]] virtual const char* numeFunctie() const = 0;
};

#endif