#include "files.h"

void inicializacao(vector<string>& swords)
{
    string sw;
    ifstream arquivo;

    arquivo.open("stopwords.txt");  // le uma lista pre definida de stop words que sera usada
                                    // durante a execucao do programa
    if (arquivo.is_open())
    {
        while(!arquivo.fail())
        {
            if (getline(arquivo, sw, '\n'))
                swords.push_back(sw);
        }
    }
    else
        cout << "Nao foi possivel inicializar a lista de stop words!";
}

void ajeitaChar(char& buffer)
{
    ///testes para transformar caracteres acentuados para versoes minusculas sem acento
    if ((buffer >= 131 && buffer <= 134) || buffer == 142 || buffer == 143 || buffer == 160 || buffer == 199 || (buffer >= 181 && buffer <= 183))
        buffer = 'a';
    else if (buffer == 128 || buffer == 135)
        buffer = 'c';
    else if (buffer == 130 || (buffer >= 136 && buffer <= 138) || buffer == 144 || (buffer >= 210 && buffer <= 212))
        buffer = 'e';
    else if ((buffer >= 139 && buffer <= 141) || buffer == 161 || (buffer >= 213 && buffer <= 216))
        buffer = 'i';
    else if (buffer == 164 || buffer == 165)
        buffer = 'n';
    else if ((buffer >= 147 && buffer <= 149) || buffer == 153 || buffer == 162 || buffer == 224 || (buffer >= 226 && buffer <= 229))
        buffer = 'o';
    else if (buffer == 129 || buffer == 150 || buffer == 151 || buffer == 154 || buffer == 163 || (buffer >= 233 && buffer <= 235))
        buffer = 'u';
    else if (buffer == 152 || buffer == 236 || buffer == 237)
        buffer = 'y';

    if (buffer >= 65 && buffer <= 90)    //passa para minusculo, caso necessario
        buffer += 32;
}

void leCSV(string nome_arquivo, rTrie* a, Hash* h, vector<string>& swords)
{
	string tweet;
	ifstream arquivo;
	ofstream saida;

	arquivo.open(nome_arquivo);
	saida.open("Tweets.csv");

	if (arquivo.is_open() && saida.is_open())
	{
		while (!arquivo.fail())
		{
			if (getline(arquivo, tweet, ','))
			{
                double polaridade;
                arquivo >> polaridade;

                string temp;
                for (int i = 0; i < tweet.size(); i++)
                {
                    char c = tolower(tweet[i]);
                    ajeitaChar(c);

                    if (c == ' ' && !temp.empty())
                    {
                        if (count(swords.begin(), swords.end(), temp) == 0) // ignora stop words
                        {
                            h->insere(temp, polaridade, polaridade, 1); // guarda a palavra lida na rtrie
                            a->insere(temp);            // e no hash com seus escores e frequencia
                        }
                        temp.clear();
                    }
                    else if (c >= 'a' && c <= 'z')
                        temp += c;
                }
				saida << tweet << '\n';
            }
		}
		arquivo.close();
	}
	else
		cout << "\nErro ao abrir um dos arquivos!\n";
}

void avaliaTweets(string nome_arquivo, Hash* h)
{
	string tweet;
	ifstream entrada;
	ofstream saida;

	entrada.open(nome_arquivo);
	saida.open("TweetsPolarizados.csv");

	if (entrada.is_open() && saida.is_open())
	{
		while (!entrada.fail())
		{
			if (getline(entrada, tweet))   // comeca a avaliacao do tweet
			{
				double polaridade{0};

                string temp;
                for (int i = 0; i < tweet.size(); i++)
                {
                    char c = tolower(tweet[i]);
                    ajeitaChar(c);

                    if (c == ' ' && !temp.empty())     // atualiza a polaridade do tweet com a polaridade
                        polaridade += h->busca(temp, 1);   // da palavra atual
                    else if (c >= 'a' && c <= 'z')
                        temp += c;
                }

				saida << tweet.substr(0, tweet.size()-1) << "; " << polaridade << '\n';
				tweet.clear();      // escreve o tweet com sua polaridade no arquivo de saida
            }
		}
		entrada.close();
		saida.close();
	}
	else
		cout << "\nErro ao abrir um dos arquivos!\n";
}
