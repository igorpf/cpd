#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "TrieTree.h"

class Author
{
private:
	std::string name;
	std::string type;
public:
	Author();
	Author(std::string, std::string);
	std::string getName(){ return name; }
	std::string getType(){ return type; }
};
class Article
{
private:
	int year;
	std::string type;
	std::string nature;
	std::string title;
	std::string evento;
	std::string anals;
	std::string edition;
	std::string ISBN;
	std::string country;
	std::string city;
	std::string volume;
	std::string fascicle;
	std::string series;
	std::string initialP;
	std::string finalP;
	std::string language;
	std::string url;
	std::string obs;
	std::string area;
	std::string line;
	std::string project;
	std::vector<Author> listOfAuthors;
public:
	Article();
	Article(int, std::string, std::string, std::string, std::string,
		std::string, std::string, std::string, std::string, std::string,
		std::string, std::string, std::string, std::string, std::string,
		std::string, std::string, std::string, std::string, std::string,
		std::string);
	std::string getYear(){ return std::to_string(year); }
	std::string getType(){ return type; }
	std::string getNature(){ return nature; }
	std::string getTitle(){ return title; }
	std::string getEvent(){ return evento; }
	std::string getAnals(){ return anals; }
	std::string getEdition(){ return edition; }
	std::string getISBN(){ return ISBN; }
	std::string getCountry(){ return country; }
	std::string getCity(){ return city; }
	std::string getVolume(){ return volume; }
	std::string getFascicle(){ return fascicle; }
	std::string getSeries(){ return series; }
	std::string getInitialP(){ return initialP; }
	std::string getFinalP(){ return finalP; }
	std::string getLanguage(){ return language; }
	std::string getURL(){ return url; }
	std::string getOBS(){ return obs; }
	std::string getArea(){ return area; }
	std::string getLine(){ return line; }
	std::string getProject(){ return project; }
	void addAuthor(std::string, std::string);
	std::vector<Author> getAuthors(){ return listOfAuthors; }
	std::vector<Article> fetchArticlesBin(std::vector<int> indices, std::vector<int> listaTam);
	std::vector<int> LeituraEIndexa(Trie* autores, Trie* area, Trie* ano, Trie* titulo, std::string Caminhodoarq);
};