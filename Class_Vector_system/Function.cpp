#define _CRT_SECURE_NO_WARNINGS
#include"AssistFunction.h"
#include "Function.h"
#include<iostream>
#include<fstream>
#include<iomanip>
#include<sstream>

void Function::Save()
{
	std::ofstream openfile("Message.csh");
	if (openfile.is_open())
	{
		for (const auto& storage : vec)
		{
			openfile << storage.name << std::endl << storage.numb << std::endl << storage.wage;
		}
	}
	openfile.close();
}

void Function::Load()
{
	std::ifstream openfile("Message.csh");
	if (openfile.is_open())
	{
		while (openfile >> news.name >> news.numb >> news.wage)
		{
			vec.push_back(news);
		}
	}
	openfile.close();
}

void Function::Menu(Users ranks)
{
	while(1)
	{
		system("cls");
		Assist::LocalTime();
		std::cout << Assist::Blank(5) << "  ����������������������������" << std::endl;
		std::cout << Assist::Blank(5) << "   ClassVector-ModeManagement" << std::endl;
		std::cout << Assist::Blank(6) << "   1�������Ϣ" << std::endl;
		std::cout << Assist::Blank(6) << "   2��ɾ����Ϣ" << std::endl;
		std::cout << Assist::Blank(6) << "   3���޸���Ϣ" << std::endl;
		std::cout << Assist::Blank(6) << "   4�������Ϣ" << std::endl;
		std::cout << Assist::Blank(6) << "   5��������Ϣ" << std::endl;
		std::cout << Assist::Blank(6) << "   6����Ϣ����" << std::endl;
		std::cout << Assist::Blank(6) << "   7���˳�ϵͳ" << std::endl;
		std::cout << Assist::Blank(5) << "  ����������������������������" << std::endl;
		std::cout << Assist::Blank(6) << "  ��ѡ��:";
		typedef void(Function::* Func)();
		Func funcs[] = { &Function::Addperson,&Function::Delete,&Function::Modify,&Function::View,&Function::Find,
			&Function::Sort };
		int num = Assist::Entry();
		if (num >= 8 || num <= 0)
			std::cout << std::endl << Assist::Blank(6) << "������Ч��������ȷ��Ϣ!" << std::endl;
		else if (num == 7)
		{
			std::cout << Assist::Blank(4) << "������������������������������������������������" << std::endl;
			std::cout << Assist::Blank(4) << "     �Ƿ�ȷ���˳�ϵͳ?        y[Y]/n[N]" << std::endl 
				<< Assist::Blank(6) << "    ��ѡ��:";
			int num = Assist::Judge();
			if (num == 1)
			{
				vec.clear();
				vec.shrink_to_fit();
				return;
			}
			std::cout << std::endl << Assist::Blank(6) << (num == 0 ? "   ��ȡ���˳�!" : "��Ч������ȡ���˳�ϵͳ!") << std::endl;
		}
		else
		{
			if (ranks.rank == 2)
				(this->*funcs[num - 1])();
			else
			{
				if (num > 3)
					(this->*funcs[num - 1])();
				else
				{
					std::cout << std::endl << Assist::Blank(6) << "һ���û��޷����ʸù���!" << std::endl;
				}
			}
		}
		std::cout << std::endl << Assist::Blank(6);
		system("pause");
	}
}

void Function::Addperson()
{
	std::cout << Assist::Blank(4) << "������������������¼��������ʾ��Ϣ������������������" << std::endl;
	std::cout << std::endl << Assist::Blank(6) << "����:";
	std::cin >> news.name;
	int num = 1;
	while(num--)
	{
		std::cout << std:: endl << Assist::Blank(6) << "���:";
		std::cin >> news.numb;
		for (const auto& message : vec)
		{
			if (message.numb == news.numb)
			{
				std::cout << Assist::Blank(6) << "����ظ�!";
				num++;
				break;
			}
		}
	}
	std::cout << std::endl << Assist::Blank(6) << "����:";
	std::cin >> news.wage;
	vec.push_back(news);
	Save();
	Assist::Delay(800);
	std::cout << std::endl << Assist::Blank(6) << "  �����ɹ�!";
}

void Function::Delete()
{
	std::cout << Assist::Blank(4) << "������������������������������������������������" << std::endl;
	std::cout << Assist::Blank(5) << "��������:";
	int numbs,i = 0;
	std::cin >> numbs;
	std::cout << Assist::Blank(4) << "  ��������������������������������������������" << std::endl;
	std::cout << Assist::Blank(4) << "   " << std::left << std::setw(20) << "����" << std::setw(20) 
		<< "���" << "����" << std::endl;
	for (const auto& message : vec)
	{
		if (message.numb == numbs)
		{
			std::cout << Assist::Blank(4) << "   " << std::left << std::setw(20) << message.name << std::setw(20) << message.numb
				<< message.wage << std::endl;
			std::cout << Assist::Blank(4) << "�Ƿ�ɾ��ƥ������?\t\t\ty[Y]/n[N]" << std::endl 
				<< std::endl << Assist::Blank(6) << "     ��ѡ��:";
			int num = Assist::Judge();
			if (num == 1)
			{
				vec.erase(vec.begin() + i);
				Save();
				Assist::Delay(800);
				std::cout << std::endl << Assist::Blank(6) << "    �����ɹ�!" << std::endl;
				return;
			}
			std::cout << std::endl << Assist::Blank(6) << (num == 0 ? "    ��ȡ��ɾ����" : "��Ч������ȡ��ɾ����") << std::endl;
			return;
		}
		i++;
	}
	std::cout << std::endl << Assist::Blank(6) << "    ��ƥ�����ݣ�" << std::endl;
}

void Function::Modify()
{
	std::cout << Assist::Blank(4) << "������������������������������������������������" << std::endl;
	std::cout << Assist::Blank(5) << "��������:";
	int numbs, i = 0;
	std::cin >> numbs;
	std::cout << Assist::Blank(4) << "  ��������������������������������������������" << std::endl;
	std::cout << Assist::Blank(4) << "   " << std::left << std::setw(20) << "����" << std::setw(20) 
		<< "���" << "����" << std::endl;
	for (const auto& message : vec)
	{
		if (message.numb == numbs)
		{
			std::cout << Assist::Blank(4) << "   " << std::left << std::setw(20) << message.name << std::setw(20) << message.numb
				<< message.wage << std::endl;
			std::cout << Assist::Blank(4) << "�Ƿ��޸�ƥ������?\t\t\ty[Y]/n[N]" << std::endl
				<< std::endl << Assist::Blank(6) << "     ��ѡ��:";
			int num = Assist::Judge();
			if (num == 1)
			{
				std::cout << Assist::Blank(4) << "������������������¼��������ʾ��Ϣ������������������" << std::endl;
				std::cout << Assist::Blank(6) << "����:";
				std::cin >> news.name;
				int num1 = 1;
				while (num1--)
				{
					std::cout << Assist::Blank(6) << "���:";
					std::cin >> news.numb;
					for (const auto& message : vec)
					{
						if (message.numb == news.numb)
						{
							std::cout << Assist::Blank(6) << "����ظ�!" << std::endl;
							num1++;
							break;
						}
					}
				}
				std::cout << Assist::Blank(6) << "����:";
				std::cin >> news.wage;
				vec.at(i) = news;
				Save();
				Assist::Delay(800);
				std::cout << std::endl << Assist::Blank(6) << "    �����ɹ�!" << std::endl;
				return;
			}
			std::cout << std::endl << Assist::Blank(6) << (num == 0 ? "    ��ȡ��ɾ����" : "��Ч������ȡ��ɾ����") << std::endl;
			return;
		}
		i++;
	}
	std::cout << std::endl << Assist::Blank(6) << "    ��ƥ�����ݣ�" << std::endl;
}

void Function::View()
{
	std::cout << Assist::Blank(4) << "  ��������������������������������������������" << std::endl;
	std::cout << Assist::Blank(4) << "   " << std::left << std::setw(20) << "����" << std::setw(20) << "���" << "����" << std::endl;
	for (const auto& message : vec)
	{
		if (vec.size() < 7)
			std::cout << std::endl;
		std::cout << Assist::Blank(4) << "   " << std::left << std::setw(20) << message.name << std::setw(20) << message.numb
			<< message.wage << std::endl;
	}
}

void Function::Find()
{
	Search s1;
	s1.FindFunction();
}

void Function::Sort()
{
	Sorts w1;
	w1.SortFunction();
}

int Function::Main(Users rank)
{
	Load();
    Menu(rank);
    return 0;
}

bool Search::NameSearch(Message s, std::string xx1)
{
	return s.name == xx1;
}

bool Search::IdSearch(Message s, std::string xx1)
{
	std::string numb = std::to_string(s.numb);
	return numb == xx1;
}

bool Search::WageSearch(Message s, std::string xx1)
{
	double EPS = 1e-6;
	std::stringstream ss(xx1);
	std::string s1,s2;
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

bool Search::SimilaritySearch(Message s, std::string xx1)
{
	
	char id[20], wage[20];
	const char* xx2 = xx1.c_str();
	sprintf(id, "%d", s.numb);
	sprintf(wage, "%f", s.wage);
	return strstr(id, xx2) || strstr(wage, xx2) || strstr(s.name, xx2);
}

void Search::FindFunction()
{
	Load();
	while(1)
	{
		system("cls");
		std::cout << Assist::Blank(5) << ">---------------------------<" << std::endl;
		std::cout << Assist::Blank(5) << "    ManagementSystem-Search" << std::endl;
		std::cout << Assist::Blank(6) << "1����������" << std::endl;
		std::cout << Assist::Blank(6) << "2����Ų���" << std::endl;
		std::cout << Assist::Blank(6) << "3�����ʶβ���" << std::endl;
		std::cout << Assist::Blank(6) << "4��ģ������" << std::endl;
		std::cout << Assist::Blank(6) << "5�����ز˵�" << std::endl;
		std::cout << Assist::Blank(5) << ">---------------------------<" << std::endl << Assist::Blank(6) << "��ѡ��:";
		int num = Assist::Entry();
		if (num > 0 && num < 5)
		{
			typedef bool (Search::* Fs)(Message s,std::string xx1);
			Fs find[] = { &Search::NameSearch,&Search::IdSearch,&Search::WageSearch,&Search::SimilaritySearch };
			std::cout << Assist::Blank(4) << "   >--------------------------------------<" << std::endl;
			std::cout << Assist::Blank(5) << "�����������Ϣ:";
			std::string xx1, xx2;
			std::cin >> xx1;
			if (num == 3)
			{
				std::cout << Assist::Blank(5) << "�����������Ϣ2:";
				std::cin >> xx2;
				xx1 = xx1 + "," + xx2;
			}
			std::cout << Assist::Blank(4) << ">----------------------------------------------<" << std::endl;
			std::cout << Assist::Blank(4) << "   " << std::left << std::setw(20) << "����" << std::setw(20)
				<< "���" << "����" << std::endl;
			for (const auto& message : vec)
			{
				if ((this->*find[num - 1])(message,xx1))
				{
					std::cout << std::endl << Assist::Blank(4) << "   " << std::setw(20) << std::left << message.name
						<< std::setw(20) << message.numb << message.wage << std::endl;
				}
			}
		}
		else if (num == 5)
			return;
		else
		{
			std::cout << std::endl << Assist::Blank(6) << "������Ч��������ȷ��Ϣ!" << std::endl;
		}
		std::cout << std::endl << Assist::Blank(6);
		system("pause");
	}
}

bool Sorts::NameSort(std::vector<Message>vec, int j, int i)
{
	return strcmp(vec.at(j).name, vec.at(i).name) > 0;
}

bool Sorts::IdSort(std::vector<Message>vec, int j, int i)
{
	return vec.at(j).numb > vec.at(i).numb;
}

bool Sorts::WageSort(std::vector<Message>vec, int j, int i)
{
	double EPS = 1e-6;
	return vec.at(j).wage > (vec.at(i).wage + EPS);
}


void Sorts::SortFunction()
{
	Load();
	while(1)
	{
		system("cls");
		std::cout << Assist::Blank(5) << ">---------------------------<" << std::endl;
		std::cout << Assist::Blank(5) << "   Vector-List-System-Sort" << std::endl;
		std::cout << Assist::Blank(6) << "1����������" << std::endl;
		std::cout << Assist::Blank(6) << "2���������" << std::endl;
		std::cout << Assist::Blank(6) << "3����������" << std::endl;
		std::cout << Assist::Blank(6) << "4�����ز˵�" << std::endl;
		std::cout << Assist::Blank(5) << ">---------------------------<" << std::endl << Assist::Blank(6) << "��ѡ��:";
		int num = Assist::Entry();
		if (num > 0 && num < 4)
		{
			typedef bool (Sorts::*Fsort)(std::vector<Message>vec,int j,int i);
			Fsort fs[] = { &Sorts::NameSort,&Sorts::IdSort,&Sorts::WageSort };
			for (int j = 0; j < vec.size(); j++)
			{
				for (int i = j + 1; i < vec.size(); i++)
				{
					if ((this->*fs[num - 1])(vec,j,i))
					{
						news = vec.at(i);
						vec.at(i) = vec.at(j);
						vec.at(j) = news;
					}
				}
			}
			View();
		}
		else if (num == 4)
		{
			std::cout << Assist::Blank(5) << "     �����������˵�!" << std::endl;
			return;
		}
		else
		{
			std::cout << std::endl << Assist::Blank(6) << "������Ч��������ȷ��Ϣ!" << std::endl;
		}
		std::cout << std::endl << Assist::Blank(6);
		system("pause");
	}
}
