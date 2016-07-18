#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <algorithm>
#include "TrieTree.h"

// Retirado e adapatado do post de SorceTricks, Friday, June 17, 2011. Link http://www.sourcetricks.com/2011/06/c-tries.html#.VWsf6M9VhBc
// Funções próprias - addString, SizeChildren, findWildChild, addString, FindWild, AddIndex, GetIndex, AcessaLista, GetIndexPeriodo, SearchString.

Node* Node::findChild(char c)
{
    for (int i = 0; i < mChildren.size(); i++)
    {
        Node* tmp = mChildren.at(i);
        if (tmp->content() == c || tmp->content() + 32 == c || tmp->content() - 32 == c)		//Modificado da original para ignorar lower ou upper case na distinção de uma palavra
        {
            return tmp;
        }
    }

    return NULL;
}

Trie::Trie()
{
    root = new Node();
}

Trie::~Trie()
{
    // Free memory
}

void Trie::addWord(std::string s, int indice)
{
    Node* current = root;

    if (s.length() == 0)
    {
        current->setWordMarker(); // an empty word
        return;
    }

    for (int i = 0; i < s.length(); i++)
    {
        Node* child = current->findChild(s[i]);
        if (child != NULL)
        {
            current = child;
        }
        else
        {
            Node* tmp = new Node();
            tmp->setContent(s[i]);
            current->appendChild(tmp);
            current = tmp;
        }

        if (current->wordMarker() && i == s.length() - 1)			//FUNÇÃO ORIGINAL EDITADA
        {
            //
            current->AddIndex(indice);							// Se ja existir essa palavra, somente adiciona seu indice
        }														//
        else
        {
            if (i == s.length() - 1)
            {
                current->setWordMarker();		//FUNÇÃO ORIGINAL EDITADA
                current->AddIndex(indice);		//Insere o indice no vetor
            }
        }
    }
}


bool Trie::searchWord(std::string s)
{
    Node* current = root;

    while (current != NULL)
    {
        for (int i = 0; i < s.length(); i++)
        {
            Node* tmp = current->findChild(s[i]);
            if (tmp == NULL)
                return false;
            current = tmp;
        }

        if (current->wordMarker())
            return true;
        else
            return false;
    }

    return false;
}

std::string Trie::FindWild(std::string WildString)		// Função Própria, implementação para tornar possivel a utilização de wildcards
{
    std::vector<std::string> Wilds;
    std::string Base = "";
    std::string aux = "";
    Node NodoBase;
    Node* current = root;
    Node* tmp;
    int i = 0;

    while (WildString[i] != '*')		//vai até o nodo anterior ao asterisco
    {
        tmp = current->findChild(WildString[i]);
        if (tmp == NULL)						//caso de vazio, é pq nenhum nodo com essa informação existe
            return "";							//devolve Vazio
        current = tmp;
        Base += current->content();			//Salva char atual na string base

        i++;
    }

    i = 0;
    NodoBase = *current;

    while (i < NodoBase.SizeChildren(NodoBase))
    {
        current = &NodoBase;	//reseta o nodo e a string para a base obtida antes
        aux = Base;

        Wilds = current->findWildChild(aux, current->GetISon(i), &Wilds);	//depois de achada a base, basta seguir para todas as folhas
        i++;
    }
    aux = "";

    aux = VectorToString(Wilds);		//Transforma o vector em string
    //std::cout << aux;		// Verificação da consistencia da função

    return aux;
}

std::vector<std::string> Node::findWildChild(std::string aux, Node* atual, std::vector<std::string> *Wilds)		// Função Própria, retorna um vetor com todas palavras abaixo do nodo atual
{
    int k = 0;

    aux += atual->content();		//Concatena o conteudo atual a string base + seu caminho percorrido

    while(k < atual->mChildren.size())		//verifica todos os filhos do nodo
    {
        if (atual->wordMarker())			//caso seja uma palavra "dentro" de outra
            Wilds->push_back(aux);		// e salva no vetor

        findWildChild(aux, atual->GetISon(k), Wilds);	//vai para o k-esimo filho para completar a string

        k++;
    }

    if (atual->mChildren.size() == 0)		//caso esteja no nodo folha, adiciona ao vetor
        Wilds->push_back(aux);

    return *Wilds;		//retorna o ponteiro do vetor
}

void Trie::addString(std::string Words, int indice)		// Função Própria, separa uma string por ' '
{
    std::string aux;
    std::stringstream StreamString(Words); // Cria Uma stream com a string de entrada, para podermos tratar essa string como stream


    while (StreamString >> aux)				//Copia o stream para a string auxiliar até os espaços
        addWord(aux, indice);						//adiciona a arvore a palavra separada
}

std::vector<int> Trie::GetIndex(std::string palavra)        //Função Própria, devolve os indices de uma palavra
{
    Node* current = root;
    std::vector<int> empty;					//vetor vazio, caso a palavra n exista na arvore

    while (current != NULL)
    {
        for (int i = 0; i < palavra.length(); i++)			//busca identica a searchword()
        {
            Node* tmp = current->findChild(palavra[i]);
            if (tmp == NULL)
                return empty;
            current = tmp;
        }

        if (current->wordMarker())			//se a palavra existe, devolve a lista de indices do nodo, caso contrario devolve a lista vazia
            return current->AcessaLista();
        else
            return empty;
    }

    return empty;
}

std::vector<int> Trie::GetIndexPeriodo(std::string start, std::string end)      //Função Própria, retorna todos os indices de um periodo entre os dois anos que foram informados
{
    std::vector<int> indices;
    std::vector<int> aux;
    int i;
    int j = 0;
    int anoinicio = std::stoi(start);
    int anofim = std::stoi(end);
    int anoaux;

    if(anofim < anoinicio)  //garante que o inicio seja menor que o fim
    {
        anoaux = anoinicio;
        anoinicio = anofim;
        anofim = anoaux;
    }

    i = anoinicio;

    while (i <= anofim)				//Busca de todos os anos presentes na arvore dentro do periodo de "start" e "end"
    {
        if (searchWord(std::to_string(i)))		//se o ano existe na arvore
        {
            aux = GetIndex(std::to_string(i));		//salva o vetor dos indices do ano em aux

            while (j < aux.size())
            {
                indices.push_back(aux[j]);		//tranfere o vetor aux para indices

                j++;
            }

            j = 0;
        }

        i++;
    }

    return indices;			//retorna o vetor de todos os indices
}

std::vector<int> Trie::SearchString(std::string strComposta)      //Função Própria, faz a intersecção de todas as palavras de uma string separadas por espaços
{
    std::string aux = "";
    std::set<int> indices;
    std::vector<int> vetaux;
    std::vector<int> intersec;
    std::vector<int> saida;
    int i = 0;

    while (i < strComposta.size())
    {
        if (strComposta[i] != ' ' && strComposta[i] != ',' && strComposta[i] != ';' && strComposta[i] != '.')	// Varre a string de entrada buscando tokens ' ' ',' '.' ';'
            aux += strComposta[i];
        else							//quando encontra, separa a string e faz a busca por ela na arvore e pega os indices do nodo
        {
            if(saida.empty())
            {
                saida = GetIndex(aux);  //primeira palavra, salva no vetor saida
                aux = "";               //limpa a variavel auxiliar
            }
            else
            {
                if (searchWord(aux))    //faz a intersecção entre o vetor de saida e o novo vetor
                {
                    vetaux = GetIndex(aux);

                    std::set_intersection(saida.begin(), saida.end(), vetaux.begin(), vetaux.end(), inserter(intersec, intersec.begin()));

                    saida = intersec;   //atualiza a saida

                    intersec.clear();
                }
                aux = "";               //limpa a variavel auxiliar
            }
        }
        i++;
    }

    if (searchWord(aux))		// Pesquisa a ultima palavra que escapou do while
    {
        vetaux = GetIndex(aux);

        if(saida.empty())       //caso só exista uma unica palavra
            return vetaux;

        std::set_intersection(saida.begin(), saida.end(), vetaux.begin(), vetaux.end(), inserter(intersec, intersec.begin()));      // faz a intersecção

        saida = intersec;
        intersec.clear();
    }

    return saida;           //retorna a intersecção de todas as palavras pesquisadas
}

std::vector<int> Trie::SetToVector(std::set<int> SET)       //Função Própria, tranforma um set em vector
{
    std::vector<int> VECTOR;

    while (!SET.empty())
    {
        VECTOR.push_back(*SET.begin());	//Passa do set para o vector
        SET.erase(SET.begin());
    }

    return VECTOR;
}

std::string Trie::VectorToString(std::vector<std::string> Vector)       //Função Própria, transforma um vetor de strings em uma grande string separada por espaços
{
    int i = 0;
    std::string All;

    while (i < Vector.size())		//Transforma um vetor de strings em uma grande string;
    {
        All = All + " " + Vector[i];
        i++;
    }

    return All;
}

std::vector<int> Trie::SearchStringWild(std::string strComposta)    //Função Própria, retorna todos os resultados de todas as palavras que começarem com o prefixo + '*'
{
	std::string aux = "";
	std::set<int> indices;
	std::vector<int> temp;
	std::vector<int> out;
	int i = 0;
	int j = 0;

	while (i < strComposta.size())
	{
		if (strComposta[i] != ' ' && strComposta[i] != ',' && strComposta[i] != ';' && strComposta[i] != '.')	// Varre a string de entrada buscando tokens ' ' ',' '.' ';'
			aux += strComposta[i];
		else							//quando encontra, separa a string e faz a busca por ela na arvore e pega os indices do nodo
		{
			if (searchWord(aux))
			{
				temp = GetIndex(aux);

				while (j < temp.size())		//adiciona os indices do vetor ao set, este é implementado em forma de arvore rubro negra, portanto evitando repetições
				{
					indices.insert(temp[j]);

					j++;
				}
			}

			j = 0;			//limpa as variaveis e segue o tratamento da string de entrada
			aux = "";
		}

		i++;
	}

	if (searchWord(aux))		// Pesquisa a ultima palavra
	{
		temp = GetIndex(aux);

		while (j < temp.size())
		{
			indices.insert(temp[j]);

			j++;
		}
	}

	out = SetToVector(indices);

	return out;
}
