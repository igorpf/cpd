#include "TrieTree.h"
#include "Indexador.h"

class Dupla //classe que armazena um autor e um numero de publicações
{
public:
	Dupla(){ Autor = ""; NumArt = 0; }
	void setNome(std::string nome){ Autor = nome; }
	void IncrementaNum(){ NumArt++; }
	void SetNum(int num){ NumArt = num; }
	int GetNum(){ return NumArt; }
	std::string GetAutor(){ return Autor; }

private:
	std::string Autor;
	int NumArt;
};

//Funções

std::string EscolheArq();
void cabecalho(std::string Nome);
void DisplayNome(std::string Nome);
void Menu(Trie* Autor, Trie* Areas, Trie* Anos, Trie* Titulos, std::vector<int> ListaTamanhos, int IndexSaida);
void Para(bool *Continua, bool *NewFile);
void IndexaAutor(std::vector<int> Indices, std::vector<int> ListaTamanhos, int IndexSaida);
void IndexaTitulo(std::vector<int> Indices, std::vector<int> ListaTamanhos, int IndexSaida);
void IndexaArea(std::vector<int> Indices, std::vector<int> ListaTamanhos, int IndexSaida);
void IndexaAno(std::vector<int> Indices, std::vector<int> ListaTamanhos, int IndexSaida);
void ArqDeSaida(std::vector<Article> Artigos, int IndexSaida);
bool IntCompare(Dupla a, Dupla b);
void ArqDeSaidaArea(std::vector<Dupla> Duplas, int IndexSaida);
void NovoArq(bool *NewFile);

bool StringCompare(Article a, Article b);	//Retirado e adaptado da resposta de Antonio em Apr 27 at 22:41 de http://stackoverflow.com/questions/29907135/how-to-sort-vector-of-objects-by-a-private-string-variable-alphabetically
std::string ToUpper(std::string in);		//Retirado e adaptado da resposta de Antonio em Apr 27 at 22:41 de http://stackoverflow.com/questions/29907135/how-to-sort-vector-of-objects-by-a-private-string-variable-alphabetically
