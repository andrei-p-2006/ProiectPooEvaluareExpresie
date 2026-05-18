#ifndef NOD_OPERATOR_BINAR_H
#define NOD_OPERATOR_BINAR_H

#include "NodExpresie.h"
//
#include <iosfwd>

class NodOperatorBinar : public NodExpresie {
protected:
    NodExpresie* stanga;
    NodExpresie* dreapta;
public:
    explicit NodOperatorBinar(NodExpresie* s = nullptr, NodExpresie* d = nullptr);
    NodOperatorBinar(const NodOperatorBinar& other);
    NodOperatorBinar& operator=(const NodOperatorBinar& other);
    ~NodOperatorBinar() override;

    [[nodiscard]] NodExpresie* getStanga() const { return stanga; }
    [[nodiscard]] NodExpresie* getDreapta() const { return dreapta; }
    void setStanga(NodExpresie* s);
    void setDreapta(NodExpresie* d);

    bool operator==(const NodOperatorBinar& other) const;

    friend std::istream& operator>>(std::istream& is, NodOperatorBinar& nod);
};

#endif