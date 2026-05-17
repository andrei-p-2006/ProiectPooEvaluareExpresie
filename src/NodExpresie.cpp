#include "NodExpresie.h"

#include <stack>

using namespace std;

map<string,double> NodExpresie::tabelVariabile;

bool NodExpresie::valideazaParanteze(const std::string& expr)
{
    stack<char> stiva;
    for (char c:expr)
    {
        if (c=='(')
        {
            stiva.push(c);
        }
        else if (c==')')
        {
            if (stiva.empty())
                return false;
            stiva.pop();
        }
    }

    return stiva.empty();
}