#include "ParserShuntingYard.h"
#include "NodExpresie.h"
#include "NodValoare.h"
#include "NodOperatorBinar.h"
#include "NodOperatorUnar.h"
#include "NodOperatoriUnari.h"
#include "NodFactory.h"
#include "MathException.h"

#include <cctype>
#include <stack>
#include <string>
#include <vector>
//
NodExpresie* ParserShuntingYard::parseaza(const std::string& expresie)
{
    if (!NodExpresie::valideazaParanteze(expresie))
    {
        throw ParseException("parantezele nu sunt echilibrate.");
    }
    const auto tokens = tokenizeaza(expresie);
    if (tokens.empty())
    {
        throw ParseException("expresie vidă.");
    }
    const auto postfixat = laPostfixat(tokens);
    return construiesteArbore(postfixat);
}

std::vector<std::string> ParserShuntingYard::tokenizeaza(const std::string& expresie)
{
    std::vector<std::string> tokens;
    const std::size_t n = expresie.size();
    std::size_t i = 0;
    while (i < n)
    {
        const char c = expresie[i];
        if (std::isspace(static_cast<unsigned char>(c)))
        {
            ++i;
            continue;
        }
        if (std::isdigit(static_cast<unsigned char>(c)) || c == '.')
        {
            std::size_t j = i;
            bool punct = (c == '.');
            ++j;
            while (j < n) {
                const char d = expresie[j];
                if (std::isdigit(static_cast<unsigned char>(d)))
                {
                    ++j;
                }
                else if (d == '.' && !punct)
                {
                    punct = true;
                    ++j;
                } else
                {
                    break;
                }
            }
            tokens.emplace_back(expresie.substr(i, j - i));
            i = j;
            continue;
        }
        if (std::isalpha(static_cast<unsigned char>(c)) || c == '_')
        {
            std::size_t j = i + 1;
            while (j < n)
            {
                const char d = expresie[j];
                if (std::isalnum(static_cast<unsigned char>(d)) || d == '_')
                {
                    ++j;
                } else
                {
                    break;
                }
            }
            tokens.emplace_back(expresie.substr(i, j - i));
            i = j;
            continue;
        }
        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == ',')
        {
            tokens.emplace_back(1, c);
            ++i;
            continue;
        }
        throw ParseException(std::string("caracter neașteptat: '") + c + "'");
    }
    return tokens;
}

std::vector<std::string> ParserShuntingYard::laPostfixat(const std::vector<std::string>& tokens)
{
    std::vector<std::string> iesire;
    std::stack<std::string> stivaOp;
    //std::string prev;
    for (const auto& tok : tokens)
    {
        if (tok == "(")
        {
            stivaOp.push(tok);
        }
        else if (tok == ")")
        {
            while (!stivaOp.empty() && stivaOp.top() != "(")
            {
                iesire.push_back(stivaOp.top());
                stivaOp.pop();
            }
            if (stivaOp.empty())
            {
                throw ParseException("paranteză închisă fără pereche.");
            }
            stivaOp.pop();
            if (!stivaOp.empty() && NodFactory::esteFunctie(stivaOp.top()))
            {
                iesire.push_back(stivaOp.top());
                stivaOp.pop();
            }
        }
        else if (tok == ",")
        {
            while (!stivaOp.empty() && stivaOp.top() != "(")
            {
                iesire.push_back(stivaOp.top());
                stivaOp.pop();
            }
        }
        else if (NodFactory::esteFunctie(tok))
        {
            stivaOp.push(tok);
        }
        else if (NodFactory::esteOperatorBinar(tok))
        {
            const int pTok = NodFactory::precedenta(tok);
            while (!stivaOp.empty() && stivaOp.top() != "(" && NodFactory::precedenta(stivaOp.top()) >= pTok)
            {
                iesire.push_back(stivaOp.top());
                stivaOp.pop();
            }
            stivaOp.push(tok);
        }
        else
        {
            iesire.push_back(tok);
        }
        //prev = tok;
    }
    while (!stivaOp.empty())
    {
        if (stivaOp.top() == "(")
        {
            throw ParseException("paranteză deschisă fără pereche.");
        }
        iesire.push_back(stivaOp.top());
        stivaOp.pop();
    }
    return iesire;
}

NodExpresie* ParserShuntingYard::construiesteArbore(const std::vector<std::string>& postfixat)
{
    std::stack<NodExpresie*> stiva;
    try
    {
        for (const auto& tok : postfixat)
        {
            if (NodFactory::esteOperatorBinar(tok))
            {
                if (stiva.size() < 2)
                {
                    throw ParseException("operator binar '" + tok + "' fără operanzi suficienți.");
                }
                NodExpresie* dr = stiva.top(); stiva.pop();
                NodExpresie* st = stiva.top(); stiva.pop();
                stiva.push(NodFactory::creeazaNod(tok, st, dr));
            }
            else if (NodFactory::esteFunctie(tok))
            {
                if (stiva.empty())
                {
                    throw ParseException("funcție '" + tok + "' fără operand.");
                }
                NodExpresie* arg = stiva.top(); stiva.pop();
                stiva.push(NodFactory::creeazaNod(tok, arg));
            } else
            {
                stiva.push(NodFactory::creeazaNod(tok));
            }
        }
        if (stiva.size() != 1)
        {
            throw ParseException("expresie malformată (operanzi rămași pe stivă).");
        }
        return stiva.top();
    }
    catch (...)
    {
        while (!stiva.empty())
        {
            delete stiva.top();
            stiva.pop();
        }
        throw;
    }
}

void ParserShuntingYard::simplificaArbore(NodExpresie*& radacina)
{
    if (!radacina)
        return;

    if (auto* binar = dynamic_cast<NodOperatorBinar*>(radacina))
    {
        NodExpresie* st = binar->getStanga();
        NodExpresie* dr = binar->getDreapta();
        simplificaArbore(st);
        simplificaArbore(dr);
        if (st != binar->getStanga()) binar->setStanga(st);
        if (dr != binar->getDreapta()) binar->setDreapta(dr);

        const auto* vStg = dynamic_cast<NodValoare*>(binar->getStanga());
        const auto* vDr  = dynamic_cast<NodValoare*>(binar->getDreapta());
        if (vStg && vDr && vStg->esteConstanta() && vDr->esteConstanta())
        {
            const double rezultat = binar->evalueaza();
            delete binar;
            radacina = new NodValoare(rezultat);
        }
        return;
    }

    auto* unar=dynamic_cast<NodOperatorUnar*>(radacina);
    if (unar)
    {
        NodExpresie* c = unar->getCopil();
        simplificaArbore(c);
        if (c != unar->getCopil()) unar->setCopil(c);

        const auto* val = dynamic_cast<NodValoare*>(unar->getCopil());
        if (val && val->esteConstanta())
        {
            const double rezultat = unar->evalueaza();
            delete unar;
            radacina = new NodValoare(rezultat);
        }
    }
}

int ParserShuntingYard::numaraFunctiiTrigonometrice(NodExpresie* radacina)
{
    if (!radacina)
        return 0;
    int total = 0;
    if (dynamic_cast<NodSin*>(radacina) || dynamic_cast<NodCos*>(radacina))
    {
        ++total;
    }
    const auto* binar = dynamic_cast<NodOperatorBinar*>(radacina);
    if (binar)
    {
        total += numaraFunctiiTrigonometrice(binar->getStanga());
        total += numaraFunctiiTrigonometrice(binar->getDreapta());
    } else if (const auto* unar = dynamic_cast<NodOperatorUnar*>(radacina))
    {
        total += numaraFunctiiTrigonometrice(unar->getCopil());
    }
    return total;
}