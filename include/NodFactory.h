#ifndef NOD_FACTORY_H
#define NOD_FACTORY_H

#include <string>
//
class NodExpresie;

class NodFactory {
public:
    static NodExpresie* creeazaNod(const std::string& token,
                                   NodExpresie* stg = nullptr,
                                   NodExpresie* dr = nullptr);

    static bool esteOperatorBinar(const std::string& token);
    static bool esteFunctie(const std::string& token);
    static int precedenta(const std::string& token);
};

#endif