#pragma once

#include <iostream>
#include <set>
#include <vector>

// Retirado e adapatado do post de SorceTricks, Friday, June 17, 2011. Link http://www.sourcetricks.com/2011/06/c-tries.html#.VWsf6M9VhBc
// Funções próprias - addString, SizeChildren, findWildChild, addString, FindWild, AddIndex, GetIndex, AcessaLista, GetIndexPeriodo, SearchString.

class Node
{
public:
	Node() { mContent = ' '; mMarker = false; }
	~Node() {}

	char content() { return mContent; }
	void setContent(char c) { mContent = c; }
	bool wordMarker() { return mMarker; }
	void setWordMarker() { mMarker = true; }
	Node* findChild(char c);																				//EDITADA
	void AddIndex(int i){ IndexList.push_back(i); }																	//Implementação própria
	std::vector<int> AcessaLista(){ return IndexList; }																//Implementação própria
	int SizeChildren(Node pai){ return pai.mChildren.size(); }														//Implementação própria
	std::vector<std::string> findWildChild(std::string aux, Node* atual, std::vector<std::string> *Wilds);			//Implementação própria
	void appendChild(Node* child) { mChildren.push_back(child); }
	std::vector<Node*> children() { return mChildren; }
	Node* GetISon(int i){ return mChildren[i]; }

private:
	char mContent;
	bool mMarker;
	std::vector<int> IndexList;			// Parametro novo - vetor de indices, salva os indices dos artigos onde essa palavra aparece no titulo
	std::vector<Node*> mChildren;
};

class Trie
{
public:
	Trie();
	~Trie();
	void addWord(std::string s, int indice);								//EDITADA
	void addString(std::string Words, int indice);								//Implementação própria
	std::string FindWild(std::string WildString);								//Implementação própria
	std::vector<int> GetIndex(std::string palavra);								//Implementação Própria
	std::vector<int> GetIndexPeriodo(std::string start, std::string end);		//Implementação Própria
	std::vector<int> SearchString(std::string strComposta);						//Implementação Própria
	std::vector<int> SetToVector(std::set<int> SET);							//Implementação Própria
	std::string VectorToString(std::vector<std::string> Vector);			    //Implementação Própria
	std::vector<int> SearchStringWild(std::string strComposta);                 //Implementação Própria
	bool searchWord(std::string s);
	void deleteWord(std::string s);

private:
	Node* root;
};
