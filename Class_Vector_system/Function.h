#pragma once
//#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include"Login.h"
#include<vector>
#include<sstream>
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
	Users userranks;
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
	void Account();
public:
	int Main(Users rank);
};

class Search :private Function
{
private:
	using Function::Load;
	using Function::vec;
	bool NameSearch(Message s, std::string xx1)
	{
		return s.name == xx1;
	}
	bool IdSearch(Message s, std::string xx1)
	{
		std::string numb = std::to_string(s.numb);
		return numb == xx1;
	}
	bool WageSearch(Message s, std::string xx1)
	{
		double EPS = 1e-6;
		std::stringstream ss(xx1);
		std::string s1, s2;
		getline(ss, s1, ',');
		getline(ss, s2);
		double x1, x2, x3;
		x1 = atof(s1.c_str());
		x2 = atof(s2.c_str());
		if (x1 > x2)
		{
			x3 = x1;
			x1 = x2;
			x2 = x3;
		}
		return s.wage > x1 + EPS && s.wage < x2 + EPS;
	}
	bool SimilaritySearch(Message s, std::string xx1)
	{
		char id[20], wage[20];
		const char* xx2 = xx1.c_str();
		sprintf_s(id, "%d", s.numb);
		sprintf_s(wage, "%f", s.wage);
		return strstr(id, xx2) || strstr(wage, xx2) || strstr(s.name, xx2);
	}
public:
	void FindFunction();
};

class Sorts :private Function
{
private:
	using Function::Load;
	using Function::vec;
	bool NameSort(std::vector<Message>vec, int j, int i)
	{
		return strcmp(vec.at(j).name, vec.at(i).name) > 0;
	}
	bool IdSort(std::vector<Message>vec, int j, int i)
	{
		return vec.at(j).numb > vec.at(i).numb;
	}
	bool WageSort(std::vector<Message>vec, int j, int i)
	{
		double EPS = 1e-6;
		return vec.at(j).wage > (vec.at(i).wage + EPS);
	}
public:
	void SortFunction();
};
