#ifndef _HASH_H
#define _HASH_H
#include <iostream>
#include <vector>
using namespace std;

const int TAMINICIAL = 151;
const int APAGADO = -1;
const int LIVRE = 0;
const int ESCORE = 1;
const int ESCOREAC = 2;
const int NTWEETS = 3;

struct CampoHash
{
    string c;
    double e;
    int eAc;
    int n;

    CampoHash()
    {
        this->c.clear();
        this->e = 0;
        this->eAc = 0;
        this->n = LIVRE;
    }

    CampoHash(string c, double v1, int v2, int v3)
    {
        this->c = c;
        this->e = v1;
        this->eAc = v2;
        this->n = v3;
    }
};

class Hash
{
    vector<CampoHash*> campos;
    int ocupacao;
    int tamanho;

    void rehash();

public:
    void insere(string c, double v1, int v2, int v3);
    double busca(string c, int opcao);

    Hash()
    {
        campos.resize(TAMINICIAL);                  // define tamanho inicial do hash
        for (int i = 0; i < TAMINICIAL; i++)  // e marca os seus campos como livres (nunca ocupados)
            campos[i] = new CampoHash();

        ocupacao = 0;
        tamanho = TAMINICIAL;
    }
};

#endif
