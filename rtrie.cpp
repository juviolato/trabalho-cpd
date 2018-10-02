#include "rtrie.h"
using namespace std;

void rTrie::insere(string s)
{
	insereAux(raiz, s);
}

void rTrie::insereAux(Nodo* n, string s)
{
	char temp{s[0]};

	if (n->caminhos[temp-97] == nullptr)
	{
		n->caminhos[temp-97] = new Nodo(temp);		// cria nodo para o caractere atual, caso ele nao exista ainda
		if (s.size() == 1)
			n->caminhos[temp-97]->chave = 1;// marca o final da palavra (no nodo seguinte) com sua chave
		else
			insereAux(n->caminhos[temp-97], s.substr(1, s.size()-1));	// insere proximos caracteres
	}
	else
	{
		if (s.size() == 1)
			n->caminhos[temp-97]->chave++;	// se a palavra ja existir, apenas incrementa a chave
		else
			insereAux(n->caminhos[temp-97], s.substr(1, s.size()-1));	// insere proximos caracteres
	}
}

void rTrie::listaPalavras(vector<string>& s)
{
	string temp;
	listaAux(raiz, temp, s);
}

void rTrie::listaPrefixo(vector<string>& v, string s)
{
	Nodo *n{raiz};

	for (int i = 0; i < s.size(); i++)
	{
		if (n->caminhos[s[i]-97] != nullptr)
			n = n->caminhos[s[i]-97];	// percorre a arvore ate encontrar o nodo da ultima letra do prefixo
		else
		{
			cout << "Nao ha nenhuma palavra com esse prefixo." << endl;
			return;
		}
	}

	listaAux(n, s.substr(0, s.size()-1), v);	// lista todas as palavras a partir desse nodo
}

void rTrie::listaAux(Nodo* n, string temp, vector<string>& s)
{
	temp += n->conteudo;	// inclui o caractere desse nodo
	for(int i = 0; i < 26; i++)
	{
		if(n->caminhos[i] != nullptr)
			listaAux(n->caminhos[i], temp, s);	// repete para todos os caminhos onde ha mais caracteres
	}
	if (n->chave != 0)
	{
		temp += ' ' + to_string(n->chave);	// inclui a chave da palavra no final
		s.push_back(temp);
	}
}

int rTrie::busca(string s)
{
	return buscaAux(raiz, s);
}

int rTrie::buscaAux(Nodo* n, string s)
{
	char c{s[0]};

	if (n->caminhos[c-97] != nullptr)
	{
		if (s.size() == 1)
			return n->caminhos[c-97]->chave;	// retorna a chave da palavra se todos os nodos das letras existirem
		else
			return buscaAux(n->caminhos[c-97], s.substr(1, s.size()-1));
	}
	else
		return 0;
}
