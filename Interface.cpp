#include <iostream>
#include <string>
#include <set>
#include <algorithm>
#include <fstream>
#include "Interface.h"

std::string EscolheArq()    //Função para escolher o arquivo
{
	std::string Nome;
	std::size_t txt;



	std::cout << "Digite o nome do arquivo: ";
	std::cin >> Nome;
    std::cout << Nome;

	txt = Nome.find(".txt");		//Caso não ache .txt no nome adiciona ".txt" ao final do nome
	if (txt == std::string::npos)
		Nome += ".txt";

	return Nome;
}

void cabecalho(std::string Nome)    //limpa a tela e exibe o cabeçalho junto ao nome do arquivo
{
	std::system("clear");

	std::cout << "Indexador de Publicacoes" << std::endl << std::endl;

	if (Nome.length() > 0)
		DisplayNome(Nome);
}

void DisplayNome(std::string Nome)  //printa o nome do arquivo
{
	std::cout << "Nome do arquivo: " << Nome << std::endl << std::endl;
}

void Para(bool *Continua, bool *NewFile)    //verifica se o usuario deseja continuar a escolher novos metodos de indexação e se deseja escolher um novo arquivo
{
	char tecla;

	do
	{
		std::cout << std::endl << "------------------------------- Fim da Indexacao ------------------------------";
		std::cout << std::endl << std::endl << "\t\tDeseja indexar por outro metodo ou parametros?";
		std::cout << std::endl << std::endl << "\t\t Pressione uma das teclas e depois pressione enter." << std::endl << "\t\t\t s - Continua / n - Fechar" << std::endl << "\t\t\t\t      ";
		std::cin >> tecla;

		if (tecla != 'n' && tecla != 'N' && tecla != 's' && tecla != 'S')
			std::cout << std::endl << std::endl << "\t\t\t\tOpcao Invalida!" << std::endl;

	} while (tecla != 'n' && tecla != 'N' && tecla != 's' && tecla != 'S');

	if (tecla == 'n' || tecla == 'N')
	{
		*Continua = false;

		NovoArq(NewFile);
	}
}

void NovoArq(bool *NewFile)     //verifica se o usuario deseja escolher um novo arquivo
{
	char tecla;

	do
	{
		std::cout << std::endl << "\t\t--------------------------------------------------";
		std::cout << std::endl << std::endl << "\t\t\tDeseja escolher um novo arquivo?";
		std::cout << std::endl << std::endl << "\t\t Pressione uma das teclas e depois pressione enter." << std::endl << "\t\t\t s - Continua / n - Fechar" << std::endl << "\t\t\t\t      ";
		std::cin >> tecla;

		if (tecla == 'n' || tecla == 'N')
				*NewFile = false;

		if (tecla != 'n' && tecla != 'N' && tecla != 's' && tecla != 'S')
			std::cout << std::endl << std::endl << "\t\t\t\tOpcao Invalida!" << std::endl;

	} while (tecla != 'n' && tecla != 'N' && tecla != 's' && tecla != 'S');

}

void Menu(Trie* Autor, Trie* Areas, Trie* Anos, Trie* Titulos, std::vector<int> ListaTamanhos, int IndexSaida)      //menu de iterações
{
	int escolha = 0;
	int i = 0;
	int j = 0;
	char tecla;
	std::size_t find;
	std::string PrimeiroAno;
	std::string SegundoAno;
	std::string Parametros;
	std::string aux;
	std::vector<int> Indices;
	std::vector<int> VecAux;
	std::vector<std::string> ConjAutores;
	std::set<int> SetAutor;

	std::cout << std::endl << std::endl << "Menu:";                                                                          //explicação dos metodos e exemplos de entrada
	std::cout << std::endl << "1 - Indexar por Autor." << std::endl << "(Ex. entrada: Jose da Silva || j*)" << std::endl;
	std::cout << std::endl << "2 - Indexar por Conjuto de Autores." << std::endl << "(Ex. entrada: Jose da Silva; Rafaela Santos)" << std::endl;
	std::cout << std::endl << "3 - Indexar por Palavra presente no Titulo." << std::endl << "(Ex. entrada: Learning || lea*)" << std::endl;
	std::cout << std::endl << "4 - Numero de artigos, por autor de uma area." << std::endl << "(Ex. entrada: Computacao grafica || Comp*)" << std::endl;
	std::cout << std::endl << "5 - Indexar por periodo de anos" << std::endl << "(Ex. entrada: 1998; 2005)" << std::endl;

	do              //seleciona o metodo de indexação, caso a tecla escolhida não seja valida, repete o processo
	{
		std::cout << std::endl << "Modo de Indexacao: ";
		std::cin >> tecla;

		if (tecla < 49 || tecla > 53)
		{
			std::cout << std::endl << "Modo Invalido!" << std::endl;
		}
	} while (tecla < 49 || tecla > 53);

	escolha = tecla - 48;       //passa o char para int

	std::cin.ignore(1000, '\n');										//ignora o CR do buffer
	std::cout << std::endl << std::endl << "Parametros de pesquisa: ";
	std::getline(std::cin, Parametros);									//aceita entrada com espaços

	std::cout << std::endl << std::endl << "Buscando Informacoes...";   //mensagem de espera

	switch (escolha)
	{
	case 1:                             //Autor
		find = Parametros.find("*");    //caso o nome informado possua um '*' faz o processamento de wild cards
		if (find != std::string::npos)
        {
			Parametros = Autor->FindWild(Parametros);
			Indices = Autor->SearchStringWild(Parametros);
        }
        else
            Indices = Autor->SearchString(Parametros);

		IndexaAutor(Indices, ListaTamanhos, IndexSaida);
		break;

	case 2:                             //Conj de autores
	    while(i < Parametros.size())
        {
            if(Parametros[i] != ';')    //separa os autores por ';'
                aux += Parametros[i];
            else
            {
                ConjAutores.push_back(aux);
                aux = "";
            }
            i++;
        }
        ConjAutores.push_back(aux);         //Salva a ultima palavra

        i = 0;

        while(i < ConjAutores.size())       //verifica cada autor
        {
            VecAux = Autor->SearchString(ConjAutores[i]);

            while(j < VecAux.size())        //une os resultados de cada autor
            {
                Indices.push_back(VecAux[j]);
                j++;
            }
            j = 0;

            i++;
        }

        i = 0;

        while(i < Indices.size())       //passa o vetor para um set para eliminar as repetições
        {
            SetAutor.insert(Indices[i]);
            i++;
        }
        Indices.clear();

        Indices = Autor->SetToVector(SetAutor); // passa o set devolta para o vector

		IndexaAutor(Indices, ListaTamanhos, IndexSaida);
		break;

	case 3:                                 //Palavra no titulo
		find = Parametros.find("*");        //caso o nome informado possua um '*' faz o processamento de wild cards
		if (find != std::string::npos)
        {
			Parametros = Titulos->FindWild(Parametros);
			Indices = Titulos->SearchStringWild(Parametros);
        }
        else
            Indices = Titulos->SearchString(Parametros);

		IndexaTitulo(Indices, ListaTamanhos, IndexSaida);
		break;

	case 4:                                 //Listagem do num de artigos de cada autor por uma determinada area
		find = Parametros.find("*");        //caso o nome informado possua um '*' faz o processamento de wild cards
		if (find != std::string::npos)
        {
			Parametros = Areas->FindWild(Parametros);
            Indices = Areas->SearchStringWild(Parametros);
        }
        else
            Indices = Areas->SearchString(Parametros);

		IndexaArea(Indices, ListaTamanhos, IndexSaida);
		break;

	case 5:                                 //Periodo entre anos
		while (i < Parametros.size() && Parametros[i] != ' ' && Parametros[i] != ',' && Parametros[i] != ';' && Parametros[i] != '.')   //separa o primeiro ano
		{
			PrimeiroAno += Parametros[i];

			i++;
		}
		i++;

		while (i < Parametros.size())       //separa o segundo ano
		{
			SegundoAno += Parametros[i];

			i++;
		}

		Indices = Anos->GetIndexPeriodo(PrimeiroAno, SegundoAno);
		IndexaAno(Indices, ListaTamanhos, IndexSaida);
		break;

	default:
		break;
	}
}

void IndexaAutor(std::vector<int> Indices, std::vector<int> ListaTamanhos, int IndexSaida)  //executa a parte da remoção do arquivo
{
	Article IndexadorObj;
	std::vector<Article> Artigos;

	Artigos = IndexadorObj.fetchArticlesBin(Indices, ListaTamanhos);    //busca artigos

    std::sort(Artigos.begin(), Artigos.end(), StringCompare);           //ordena pelo titulo
	ArqDeSaida(Artigos, IndexSaida);                                    //printa no arquivo de saida .txt
}

void IndexaTitulo(std::vector<int> Indices, std::vector<int> ListaTamanhos, int IndexSaida)  //executa a parte da remoção do arquivo
{
	Article IndexadorObj;
	std::vector<Article> Artigos;

	Artigos = IndexadorObj.fetchArticlesBin(Indices, ListaTamanhos);    //busca artigos

	std::sort(Artigos.begin(), Artigos.end(), StringCompare);           //ordena pelo titulo
	ArqDeSaida(Artigos, IndexSaida);                                    //printa no arquivo de saida .txt
}

void IndexaArea(std::vector<int> Indices, std::vector<int> ListaTamanhos, int IndexSaida)  //executa a parte da remoção do arquivo
{
	Article IndexadorObj;
	std::vector<Article> Artigos;
	int i = 0;
	int j = 0;
	int k = 0;
	Dupla Novo;
	std::vector<Dupla> Duplas;
	std::vector<Author> Autores;

	Artigos = IndexadorObj.fetchArticlesBin(Indices, ListaTamanhos);    //busca artigos

	while (i < Artigos.size())
	{
		Autores = Artigos[i].getAuthors();

		while (j < Autores.size())
		{
			while (k < Duplas.size() && Autores[j].getName() != Duplas[k].GetAutor()) //compara nome por nome até o final das duplas
			{
				k++;
			}

			if (k < Duplas.size())  //se o while parou por encontrar um nome igual
			{
				Duplas[k].IncrementaNum();  //incrementa o numero de publicações na area
			}
			else        //saiu porque não encontrou o nome
			{
				Novo.setNome(Autores[j].getName()); //adiciona o nome e incrementa para 1 o numero de publicações
				Novo.IncrementaNum();

				Duplas.push_back(Novo);     //adiciona para as duplas

				Novo.SetNum(0);         //reseta o numero da dupla
			}

			k = 0;
			j++;
		}

		j = 0;
		i++;
	}


	std::sort(Duplas.begin(), Duplas.end(), IntCompare);           //ordena por ordem decrescente de num de artigos
	ArqDeSaidaArea(Duplas, IndexSaida);                            //printa no arquivo de saida .txt
}

void IndexaAno(std::vector<int> Indices, std::vector<int> ListaTamanhos, int IndexSaida)  //executa a parte da remoção do arquivo
{
	Article IndexadorObj;
	std::vector<Article> Artigos;

	Artigos = IndexadorObj.fetchArticlesBin(Indices, ListaTamanhos);    //busca artigos

	std::sort(Artigos.begin(), Artigos.end(), StringCompare);           //ordena pelo titulo
	ArqDeSaida(Artigos, IndexSaida);                                    //printa no arquivo de saida .txt
}

void ArqDeSaida(std::vector<Article> Artigos, int IndexSaida)   //cria o arquivo de saida .txt
{
	int i = 0;
	int j = 0;
	std::vector<Author> aux;

	std::ofstream outfile("SaidaArtigos " + std::to_string(IndexSaida) + ".txt");   //Cria artigo com um mesmo nome porem com um indice para que um novo arquivo não apague um antigo

    //printa descrição dos campos
	outfile << "ano; tipo; natureza; titulo; evento; anais; edicao; isbn; pais; cidade; volume; fasciculo; serie; pinicial; pfinal; idioma; url; obs; area; linha; projeto; autor; tipo" << std::endl
		<< std::endl << Artigos.size() << " - Resultados" << std::endl << std::endl << std::endl;

	while (i < Artigos.size())
	{   //printa artigos
		outfile << std::to_string(i+1) << ") - " << Artigos[i].getTitle() << std::endl << Artigos[i].getYear() << " - " << Artigos[i].getType() << " - " << Artigos[i].getNature() << " - "
			<< Artigos[i].getEvent() << " - " << Artigos[i].getAnals() << " - " << Artigos[i].getEdition() << " - " << Artigos[i].getISBN() << " - " << Artigos[i].getCountry() << " - "
			<< Artigos[i].getCity() << " - "	<< Artigos[i].getVolume() << " - " << Artigos[i].getFascicle() << " - " << Artigos[i].getSeries() << " - " << Artigos[i].getInitialP() << " - "
			<< Artigos[i].getFinalP() << " - " << Artigos[i].getLanguage() << " - " << Artigos[i].getURL() << " - " << Artigos[i].getOBS() << " - " << Artigos[i].getLine() << " - "
			<< Artigos[i].getProject() << ";" << std::endl << " - " << Artigos[i].getArea() << " - " << std::endl;

		aux = Artigos[i].getAuthors();

		while (j < aux.size())  //printa autores
		{
			outfile << aux[j].getName() << ";" << aux[j].getType() << std::endl;
			j++;
		}
		j = 0;

		i++;

		outfile << std::endl << std::endl;
	}
	outfile.close();            //fecha arquivo
}

void ArqDeSaidaArea(std::vector<Dupla> Duplas, int IndexSaida)   //cria o arquivo de saida .txt da area
{
	int i = 0;

	std::ofstream outfile("SaidaArtigos " + std::to_string(IndexSaida) + ".txt");   //Cria artigo com um mesmo nome porem com um indice para que um novo arquivo não apague um antigo

	outfile << Duplas.size() << " Autores" << std::endl << std::endl << "Autores - Num. de Artigos" << std::endl;   //printa descrição dos campos

	while (i < Duplas.size())
	{
		outfile << std::endl << Duplas[i].GetAutor() << " - " << std::to_string(Duplas[i].GetNum());        //printa duplas
		i++;
	}

	outfile.close();    //fecha o artigo
}


bool StringCompare(Article a, Article b)				//Retirado e adaptado da resposta de Antonio em Apr 27 at 22:41 de http://stackoverflow.com/questions/29907135/how-to-sort-vector-of-objects-by-a-private-string-variable-alphabetically
{
	std::string a_name = ToUpper(a.getTitle());         //faz a comparação entre as strings para ordenação alfabetica
	std::string b_name = ToUpper(b.getTitle());

	return (a_name < b_name);
}

std::string ToUpper(std::string in)						//Retirado e adaptado da resposta de Antonio em Apr 27 at 22:41 de http://stackoverflow.com/questions/29907135/how-to-sort-vector-of-objects-by-a-private-string-variable-alphabetically
{
	std::transform(in.begin(), in.end(), in.begin(), ::toupper);      //ignora capslock na ordenação alfabetica
	return in;
}


bool IntCompare(Dupla a, Dupla b)
{
	return (a.GetNum() > b.GetNum());                   //faz a comparação entre os ints para ordenação em ordem decrescente do numero de publicações
}
