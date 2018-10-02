#ifndef _FILES_H
#define _FILES_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "rtrie.h"
#include "hash.h"
using namespace std;

void inicializacao(vector<string>& swords);

void ajeitaChar(char& c);

void leCSV(string nome_arquivo, rTrie* a, Hash* h, vector<string>& swords);

void avaliaTweets(string nome_arquivo, Hash* h);

#endif
