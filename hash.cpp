#include "hash.h"

void Hash::rehash()
{
    vector<CampoHash*> hashAux = campos;   // guarda os elementos do hash para reinseri-los

    campos.resize(tamanho*2 + 1);      // aumenta o tamanho do hash para um número ímpar
    tamanho = tamanho*2 + 1;        // garantindo menores chances de j ser divisor do tamanho no duplo hash

    for (int i = 0; i < tamanho; i++)
        campos[i] = new CampoHash();               // marca todos os campos do hash redimensionado como livre

    for (int i = 0; i < hashAux.size(); i++)
    {
        if (hashAux[i]->n != LIVRE && hashAux[i]->n != APAGADO)
            insere(hashAux[i]->c, hashAux[i]->e, hashAux[i]->eAc, hashAux[i]->n);    // reinsere todos os itens (nova função de hash)
    }
}

double Hash::busca(string c, int opcao)
{
    int indice{0}, j{0};

    do
    {
        for (int i = 0; i < c.size(); i++)
            indice += (i+1)*c[i] + j*c[0];  // funcao de hash
        indice %= tamanho;

        j++;
        while (tamanho%j == 0)
            j++;        // escolhe j que não seja divisor do tamanho

    } while (campos[indice]->n != LIVRE && campos[indice]->c != c);
    // procura chave ou um campo livre indicando que a chave não está presente no hash

    if (campos[indice]->c == c)
    {
        if (opcao == ESCORE)
            return campos[indice]->e;
        if (opcao == ESCOREAC)
            return campos[indice]->eAc;
        if (opcao == NTWEETS)
            return campos[indice]->n;
    }
    else
        return 0;
}

void Hash::insere(string c, double v1, int v2, int v3)     // inserção por duplo hash
{
    int indice{0}, j{0};

    do
    {
        for (int i = 0; i < c.size(); i++)
            indice += (i+1)*c[i] + j*c[0];  // funcao de hash
        indice %= tamanho;

        j++;
        while (tamanho%j == 0)
            j++;        // escolhe j que não seja divisor do tamanho

    } while (campos[indice]->n != LIVRE && campos[indice]->n != APAGADO && campos[indice]->c != c);
    // procura posição disponível para inserção

    if (campos[indice]->c == c)    // se o elemento ja estiver no hash, atualiza as informações
    {
        campos[indice]->eAc += v1;
        campos[indice]->n++;
        campos[indice]->e = double(campos[indice]->eAc)/double(campos[indice]->n);
    }
    else
    {
        campos[indice] = new CampoHash(c, v1, v2, v3);  // insere valores no Hash
        ocupacao++;

        if (ocupacao/tamanho > 2/3)
            rehash();
    }
}
