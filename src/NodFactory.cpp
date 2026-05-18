#include "NodFactory.h"
#include "NodValoare.h"
#include "NodOperatoriBinari.h"
#include "NodOperatoriUnari.h"
#include "MathException.h"
//
#include <cctype>
#include <stdexcept>

using namespace std;

namespace {
    bool esteNumar(const string& s)
    {
        if (s.empty())
            return false;

        std::size_t i = 0;
        if (s[0]=='+' || s[0]=='-')
        {
            if (s.size() == 1)
                return false;
            i=1;
        }

        bool punct=false;
        for (; i<s.size(); ++i)
        {
            if (s[i]=='.')
            {
                if (punct)
                    return false;
                punct=true;
            }
            else if (s[i]<'0' || s[i]>'9')
            {
                return false;
            }
        }
        return true;
    }

    bool esteIdentificator(const string& s)
    {
        if (s.empty())
            return false;
        if (!isalpha(static_cast<unsigned char>(s[0])) && s[0] != '_')
            return false;
        for (char c : s)
        {
            if (!isalnum(static_cast<unsigned char>(c)) && c != '_')
                return false;
        }
        return true;
    }
}

bool NodFactory::esteOperatorBinar(const string& token)
{
    return (token == "+" || token == "-" || token == "*" || token == "/");
}

bool NodFactory::esteFunctie(const string& token)
{
    return (token == "sin" || token == "cos" || token == "abs");
}

int NodFactory::precedenta(const string& token)
{
    if (token == "+" || token == "-")
        return 1;
    if (token == "*" || token == "/")
        return 2;
    if (esteFunctie(token))
        return 3;
    return 0;
}

NodExpresie* NodFactory::creeazaNod(const string& token,NodExpresie* stg,NodExpresie* dr)
{
    if (token == "+")
        return new NodAdunare(stg, dr);
    if (token == "-")
        return new NodScadere(stg, dr);
    if (token == "*")
        return new NodInmultire(stg, dr);
    if (token == "/")
        return new NodImpartire(stg, dr);

    if (token == "sin")
        return new NodSin(stg);
    if (token == "cos")
        return new NodCos(stg);
    if (token == "abs")
        return new NodAbs(stg);

    if (esteNumar(token))
    {
        try
        {
            return new NodValoare(std::stod(token));
        }
        catch (const std::exception&)
        {
            throw ParseException("token numeric invalid: '" + token + "'");
        }
    }

    if (esteIdentificator(token))
    {
        return new NodValoare(token);
    }

    throw ParseException("token necunoscut: '" + token + "'");
}