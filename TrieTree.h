#pragma once

#include <iostream>
#include <set>
#include <vector>

// Retirado e adapatado do post de SorceTricks, Friday, June 17, 2011. Link http://www.sourcetricks.com/2011/06/c-tries.html#.VWsf6M9VhBc
// Fun��es pr�prias - addString, SizeChildren, findWildChild, addString, FindWild, AddIndex, GetIndex, AcessaLista, GetIndexPeriodo, SearchString.

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
	void AddIndex(int i){ IndexList.push_back(i); }																	//Implementa��o pr�pria
	std::vector<int> AcessaLista(){ return IndexList; }																//Implementa��o pr�pria
	int SizeChildren(Node pai){ return pai.mChildren.size(); }														//Implementa��o pr�pria
	std::vector<std::string> findWildChild(std::string aux, Node* atual, std::vector<std::string> *Wilds);			//Implementa��o pr�pria
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
	void addString(std::string Words, int indice);								//Implementa��o pr�pria
	std::string FindWild(std::string WildString);								//Implementa��o pr�pria
	std::vector<int> GetIndex(std::string palavra);								//Implementa��o Pr�pria
	std::vector<int> GetIndexPeriodo(std::string start, std::string end);		//Implementa��o Pr�pria
	std::vector<int> SearchString(std::string strComposta);						//Implementa��o Pr�pria
	std::vector<int> SetToVector(std::set<int> SET);							//Implementa��o Pr�pria
	std::string VectorToString(std::vector<std::string> Vector);			    //Implementa��o Pr�pria
	std::vector<int> SearchStringWild(std::string strComposta);                 //Implementa��o Pr�pria
	bool searchWord(std::string s);
	void deleteWord(std::string s);

private:
	Node* root;
};
