#include <iostream>
#include <string>
#include <vector>


#include "Indexador.h"
#include "TrieTree.h"
#include "Interface.h"

int main()
{
    Trie* Autor = new Trie();       //Objeto para guardar os autores
    Trie* Anos = new Trie();        //Objeto para guardar os anos
    Trie* Area = new Trie();        //Objeto para guardar as areas
    Trie* Titulos = new Trie();     //Objeto para guardar os titulos
    Article IndexadorObj;

    std::string NomeArq;            //Nome/caminho do arquivo
    std::vector<int> ListaTamanhos; //lista de tamanho de cada artigo para facilitar retirada do bin
    bool Continua = true;           //while true, continua executando novas indexações em cima do mesmo arquivo
    bool NewFile = true;            //if false é porque o usuario não deseja escolher um novo arquivo
    int IndexSaida = 0;             //indice para que o usuario possa fazer varias indexações diferentes e poder acessar todos os resultados, sem a nova indexação apagar o arquivo antigo

    while (NewFile)
    {
        Continua = true;            //inicializa as variaveis
        NomeArq = "";

        cabecalho(NomeArq);         //cabeçalho do programa
        NomeArq = EscolheArq();     //nome do arquivo
        std::cout << std::endl << std::endl << "Lendo arquivo & Indexando indices";     //msg de espera
        ListaTamanhos = IndexadorObj.LeituraEIndexa(Autor, Area, Anos, Titulos, NomeArq);   //salva titulos, autores, areas e anos nas arvores especificas e os indices de quais artigos possuem a palavra guradada

        if (ListaTamanhos.empty())     //se a lista for vazia é porque o arquivo é invalido ou não existe
        {
            std::cout << std::endl << std::endl << "Arquivo vazio ou invalido!" << std::endl << std::endl;
            NovoArq(&NewFile);
        }
        else
        {

            while (Continua)    //enquanto o usuario quiser continuar escolhendo novos metodos
            {
                cabecalho(NomeArq);
                Menu(Autor, Area, Anos, Titulos, ListaTamanhos, IndexSaida);
                IndexSaida++;

                Para(&Continua, &NewFile);  //verifica se o usuario deseja parar
            }

            if(!Continua)
            {
                delete Autor;   //impede que em uma nova escolha de arquivo os artigos antigos permaneçam
                delete Anos;
                delete Area;
                delete Titulos;

                Autor = new Trie();     //aloca novas arvores trie para caso o usuario escolha outro arquivo
                Anos = new Trie();
                Area = new Trie();
                Titulos = new Trie();
            }
        }
    }

    delete Autor;   //Libera a memoria
    delete Anos;
    delete Area;
    delete Titulos;

    return 0;
}
