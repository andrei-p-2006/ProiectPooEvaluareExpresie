#include "MeniuInteractiv.h"
//
#include "MathException.h"
#include "NodExpresie.h"
#include "Parser.h"

#include <iostream>
#include <string>

using namespace std;

MeniuInteractiv::MeniuInteractiv(Parser& p): parser(p),arboreCurent(nullptr) {}

MeniuInteractiv::~MeniuInteractiv()
{
    delete arboreCurent;
}

void MeniuInteractiv::afiseazaMeniu() const
{
    cout<<" Evaluator de expresii matematice (AST)\n";
    cout<<" 1) Citeste o expresie\n";
    cout<<" 2) Citeste necunoscutele\n";
    cout<<" 3) Afiseaza rezultatul\n";
    cout<<" 0) Iesire\n";

    if (arboreCurent)
    {
        cout<<" Expresie curenta: "<<expresieCurenta<<'\n';
    }
    else
    {
        cout<<" Nicio expresie incarcata.\n";
    }

    cout<<" Alegere: ";
}

void MeniuInteractiv::citesteExpresie()
{
    cout<<" Introduceti expresia: ";
    string linie;
    getline(std::cin,linie);
    if (linie.empty())
    {
        cout<<" Expresie vida, anulat.\n";
        return;
    }
    if (!NodExpresie::valideazaParanteze(linie))
    {
        cout<<" ! Paranteze neechilibrate, expresia a fost respinsa.\n";
        return;
    }
    try
    {
        NodExpresie* nou=parser.parseaza(linie);
        delete arboreCurent;
        arboreCurent=nou;
        expresieCurenta=linie;
        cout<<" Expresie acceptata.\n";
    }
    catch (const MathException& e)
    {
        cout<<" ! "<<e.what()<<'\n';
    }
}

void MeniuInteractiv::citesteNecunoscute()
{
    cout<<" Cate necunoscute doriti sa setati? ";
    string linie;
    getline(cin, linie);
    int n=0;
    try
    {
        n=stoi(linie);
    }
    catch (const std::exception&)
    {
        cout<<" ! Numar invalid.\n";
        return;
    }
    for (int i=0; i<n; i++)
    {
        cout<<" Numele necunoscutei #"<<(i + 1)<<": ";
        string nume;
        getline(std::cin, nume);
        if (nume.empty())
        {
            cout<<" ! Nume vid, sar peste.\n";
            continue;
        }
        cout<<" Valoarea pentru "<<nume<<": ";
        string val;
        getline(std::cin, val);
        try
        {
            NodExpresie::tabelVariabile[nume]=stod(val);
            cout<<" Setat "<<nume<<" = "<<NodExpresie::tabelVariabile[nume]<<'\n';
        }
        catch (const std::exception&)
        {
            cout<<" ! Valoare numerica invalida.\n";
        }
    }
}

void MeniuInteractiv::afiseazaRezultat()
{
    if (!arboreCurent)
    {
        cout<<" ! Nu exista o expresie. Cititi mai intai una.\n";
        return;
    }
    try
    {
        const double rezultat=arboreCurent->evalueaza();
        cout<<" Rezultat: " <<rezultat<<'\n';
    }
    catch (const MathException& e)
    {
        cout<< " ! " <<e.what()<<'\n';
    }
}

void MeniuInteractiv::ruleaza()
{
    while (true)
    {
        afiseazaMeniu();
        string linie;
        if (!getline(cin, linie))
        {
            cout<<"\n Sfarsit de intrare, ies.\n";
            return;
        }
        if (linie.empty())
            continue;
        const char optiune=linie[0];
        switch (optiune) {
            case '1': citesteExpresie(); break;
            case '2': citesteNecunoscute(); break;
            case '3': afiseazaRezultat(); break;
            case '0':
                cout<<" La revedere!\n";
                return;
            default:
                cout<<" ! Optiune necunoscuta.\n";
                break;
        }
    }
}