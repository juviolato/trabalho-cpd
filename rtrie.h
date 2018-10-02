#ifndef _RTRIE_H
#define _RTRIE_H
#include <iostream>
#include <vector>
using namespace std;

struct Nodo
{
	char conteudo;
	Nodo *caminhos[26];
	int chave;

	Nodo()		// cria um nodo completamente nulo
	{
		this->conteudo = '\0';
		for (int i = 0; i < 26; i++)
			this->caminhos[i] = nullptr;
		this->chave = 0;
	}

	Nodo(char s)	// cria um nodo com caminhos nulos
	{
		this->conteudo = s;
		for (int i = 0; i < 26; i++)
			this->caminhos[i] = nullptr;
		this->chave = 0;
	}

	Nodo(char s, Nodo* c[26])		// cria um nodo com caminhos
	{
		this->conteudo = s;
		for (int i = 0; i < 26; i++)
			this->caminhos[i] = c[i];
		this->chave = 0;
	}
};

class rTrie
{
private:
	Nodo *raiz;

	void insereAux(Nodo* n, string s);
	int buscaAux(Nodo* n, string s);
	void listaAux(Nodo* n, string temp, vector<string>& s);

public:
	void insere(string s);
	int busca(string s);
	void listaPrefixo(vector<string>& v, string s);
	void listaPalavras(vector<string>& s);

	rTrie()		// cria uma raiz nula e define a primeira chave como 1
	{
		raiz = new Nodo();
	}
};

#endif
