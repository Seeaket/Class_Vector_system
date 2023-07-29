#pragma once
#include"Login.h"
#include<vector>
struct Message
{
	int numb;
	char name[20];
	float wage;
};
class Function
{
protected:
	std::vector<Message>vec;
	Message news;
	void Load();
	void View();
private:
	void Save();
	void Menu(Users ranks);
	void Addperson();
	void Delete();
	void Modify();
	void Find();
	void Sort();
public:
	int Main(Users rank);
};

class Search :private Function
{
private:
	using Function::Load;
	using Function::vec;
	bool NameSearch(Message s, std::string xx1);
	bool IdSearch(Message s, std::string xx1);
	bool WageSearch(Message s, std::string xx1);
	bool SimilaritySearch(Message s, std::string xx1);
public:
	void FindFunction();
};

class Sorts :private Function
{
private:
	using Function::Load;
	using Function::vec;
	bool NameSort(std::vector<Message>vec, int j, int i);
	bool IdSort(std::vector<Message>vec, int j, int i);
	bool WageSort(std::vector<Message>vec, int j, int i);
public:
	void SortFunction();
};
