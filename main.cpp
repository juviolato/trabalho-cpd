#include <iostream>
#include <string>
#include <vector>
#include "hash.h"
#include "rtrie.h"
#include "files.h"
#include "rlutil.h"

int main()
{
    vector<string> stopWords;
    inicializacao(stopWords);

    string arquivo;
    char opcao;
    rTrie *a = new rTrie();
    Hash *h = new Hash();

    cout << endl <<  "\t> Nome do arquivo .CSV para construcao do dicionario: ";
    cin >> arquivo;
    if (arquivo.find(".csv") == arquivo.npos)
        arquivo += ".csv";

    leCSV(arquivo, a, h, stopWords);

   	do
	{
		cout << endl << "\tPressione qualquer tecla para continuar" << endl;
        cin.ignore();
		getch();
		for (int i = 0; i < 50; i++)
		    cout << endl;

		cout << "\tSelecione uma opcao:" << endl;
		cout << "\t\t1. Atualizar dicionario" << endl;
		cout << "\t\t2. Avaliar tweets" << endl;
		cout << "\t\t3. Procurar radical" << endl;
		cout << "\t\t4. Sair" << endl;
		opcao = getch();

		switch (opcao)
		{
		    case '1':
		        cout << endl << endl << "\tQual arquivo deve ser utilizado?" << endl << '\t';
		        cin >> arquivo;
                if (arquivo.find(".csv") == arquivo.npos)
                    arquivo += ".csv";
		        leCSV(arquivo, a, h, stopWords);
				break;
			case '2':
				cout << endl << endl << "\tQual arquivo deve ser utilizado?" << endl << '\t';
				cin >> arquivo;
                if (arquivo.find(".csv") == arquivo.npos)
                    arquivo += ".csv";
				avaliaTweets(arquivo, h);
				break;
			case '3':
			{
				string rad;
				vector<string> variacoes;

				cout << endl << endl << "\tQual radical voce quer procurar?" << endl << '\t';
				cin >> rad;
				a->listaPrefixo(variacoes, rad);
				cout << "\tPalavras encontradas:" << endl;
				for (int i = 0; i < variacoes.size(); i++)
					cout << '\t' << i+1 << ". " << variacoes[i].substr(0, variacoes[i].size()-2) << endl;
				cout << endl << endl;
				break;
			}
			case '4':
				cout << "\tAdeus!" << endl << endl;
				break;
			default:
				cout << "\tOpcao invalida" << endl;
    	}
	} while (opcao != '4');

    return 0;
}
