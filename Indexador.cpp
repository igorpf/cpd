#include <iostream>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <set>
#include <stdexcept>
#include "Indexador.h"

#define SPLIT ';' //macro que define o separador do arquivo csv
std::vector<Article> fetchArticlesBin(std::vector<int> indices, std::vector<int> listaTam);
Article fetchArticle(const char*);
std::vector<std::string> split(const char *, char);


Author::Author() {}
Author::Author(std::string nome, std::string tipo)
{
    name = nome;
    type = tipo;
}
Article::Article() {}
Article::Article(int ano, std::string tipo, std::string natureza, std::string titulo, std::string eve,
                 std::string anais, std::string edicao, std::string isb, std::string pais, std::string cidade,
                 std::string volum, std::string fasciculo, std::string serie, std::string pInicial, std::string pFinal,
                 std::string idioma, std::string ur, std::string ob, std::string ar, std::string linha,
                 std::string projeto)
{
    year = ano;
    type = tipo;
    nature = natureza;
    title = titulo;
    evento = eve;
    anals = anais;
    edition = edicao;
    ISBN = isb;
    country = pais;
    volume = volum;
    fascicle = fasciculo;
    series = serie;
    initialP = pInicial;
    finalP = pFinal;
    language = idioma;
    url = ur;
    obs = ob;
    area = ar;
    line = linha;
    project = project;
}
//Adds a new author to the list of authors
void Article::addAuthor(std::string name, std::string type)
{
    listOfAuthors.push_back(Author(name, type));
}

std::vector<Article> Article::fetchArticlesBin(std::vector<int> indices, std::vector<int> listaTam)
{
    std::vector<Article> artigos;
    std::ifstream arq;
    arq.open("dados.bin", std::ifstream::binary | std::ifstream::in);
    if (arq.is_open())
    {
        std::string buffer;
        for (std::vector<int>::iterator it = indices.begin(); it != indices.end(); ++it)
        {
            //std::cout << std::to_string(*it);
            if (*it != 0)
                arq.seekg(listaTam[*it - 1], std::ofstream::beg);
            else
                arq.seekg(0, std::ofstream::beg);
            getline(arq, buffer);
            const char *buf = buffer.c_str();
            if (buffer.empty() == false)//necessary not to have segmentation fault in case the string is empty!
                artigos.push_back(fetchArticle(buf));
        }
    }
    arq.close();

    return artigos;
}
/*
*Receives a line read from the input file containing articles
*and returns a object of the class Article
*/
Article fetchArticle(const char *article)
{

    std::vector<std::string> buffer = split(article, SPLIT);
    std::vector<std::string>::iterator it = buffer.begin();
    const int quantidadeDeCampos = 33;
    if(buffer.size() != quantidadeDeCampos)
        return Article(); //para o programa nao ter seg fault caso o formato esteja errado
    try
    {
        Article temp(std::stoi(*it), *(it + 1), *(it + 2), *(it + 3), *(it + 4), *(it + 5),
                     *(it + 6), *(it + 7), *(it + 8), *(it + 9), *(it + 10),
                     *(it + 11), *(it + 12), *(it + 13), *(it + 14), *(it + 15),
                     *(it + 16), *(it + 17), *(it + 18), *(it + 19), *(it + 20));
        it += 21; //std::cout << *it;
        for (; it != buffer.end(); ++it)
        {
            if (it->empty())
                break;
            temp.addAuthor(*it, *(it + 1));
            it++;
            if (it == buffer.end())
                break;//consistencia necessaria para evitar seg fault
        }
        return temp;
    }
    catch(const std::out_of_range& erro)
    {
        std::cerr << std::endl <<"Arquivo está no formato inválido!";
        return Article();
    }


}
std::vector<std::string> split(const char *str, char c = ' ')
{
    std::vector<std::string> result;

    do
    {
        const char *begin = str;

        while (*str != c && *str)
            str++;

        result.push_back(std::string(begin, str));
    }
    while (0 != *str++);

    return result;
}

std::vector<int> Article::LeituraEIndexa(Trie* autores, Trie* area, Trie* ano, Trie* titulo, std::string Caminhodoarq)
{
    std::ifstream arq;
    std::vector<int> empty;
    arq.open(Caminhodoarq, std::ifstream::in);
    std::vector<int> listaTamanhos;

    if (arq.is_open())
    {
        Article artigo;
        std::string buffer;
        getline(arq, buffer);
        int indice = 0; //Será gerado um índice numa sequencia crescente, como o cartão UFRGS
        std::ofstream bin;
        bin.open("dados.bin", std::ofstream::out | std::ofstream::binary);
        int soma = 0;
        if (bin.is_open() == false)
        {
            arq.close();
            return empty;
        }
        while (arq.eof() == false)
        {
            getline(arq, buffer);
            bin << buffer << std::endl;
            soma += buffer.size();
            soma += 1;//+1 por causa do LF
            listaTamanhos.push_back(soma);
            //std::cout << listaTamanhos[indice] << " ";
            //  std::cout << buffer;
            const char *buf = buffer.c_str();
            if (buffer.empty() == false)//necessary not to have segmentation fault in case the string is empty!
                artigo = fetchArticle(buf);
            std::vector<Author> aut = artigo.getAuthors();
            for (std::vector<Author>::iterator it = aut.begin(); it != aut.end(); ++it)
                autores->addString(it->getName(), indice);
            area->addString(artigo.getArea(), indice);
            titulo->addString(artigo.getTitle(), indice);
            ano->addString(artigo.getYear(), indice);
            ++indice;
        }
        bin.close();
    }
    arq.close();

    return listaTamanhos;
}
