#include"AssistFunction.h"
#include "Login.h"
#include<iostream>
#include<iomanip>
#include<fstream>

void Login::SaveUser()
{
	std::ofstream openfile("Users.csh");
	if (openfile.is_open())
	{
		for (auto messages : vect)
		{
			openfile << messages.userName << std::endl << messages.userPass << std::endl << messages.rank << std::endl;
		}
	}
	openfile.close();
}

void Login::LoadUser()
{
	std::ifstream openfile("Users.csh");
	if (openfile.is_open())
	{
		while (openfile >> messageUser.userName >> messageUser.userPass >> messageUser.rank)
		{
			vect.push_back(messageUser);
		}
	}
	openfile.close();
}

Users Login::LoginMenu()
{
	LoadUser();//�����û�����
	bool result = true;
	while(result)
	{
		system("cls");
		std::cout << Assist::Blank(5) << "  ����������������������������" << std::endl;
		std::cout << Assist::Blank(6) << "  Login-System" << std::endl;
		std::cout << Assist::Blank(6) << "    1������" << std::endl;
		std::cout << Assist::Blank(6) << "    2��ע��" << std::endl;
		std::cout << Assist::Blank(6) << "   3���ο͵���" << std::endl;
		std::cout << Assist::Blank(5) << "  ����������������������������" << std::endl;
		std::cout << Assist::Blank(6) << "  ��ѡ��:";
		int num = Assist::Entry();
		if (num < 1 || num > 3)
		{
			std::cout << Assist::Blank(6) << "   ��Ч����!" << std::endl;
			std::cout << Assist::Blank(6);
			system("pause");
			continue;
		}
		typedef bool(Login::*Fa)();
		Fa start[] = { &Login::Enter,&Login::Enroll,&Login::Visitor };
		result = (this->*start[num - 1])();//��ΪLogin��һ�����ʵ����ʹ�ó�Ա����ָ����Ҫʹ��->*�����������
	}
	std::cout << std::endl << Assist::Blank(6) << "     ����ɹ�!" << std::endl;
	Assist::Delay(800);
	return messageUser;
}

bool Login::Enter()
{
	int num = 1;
	while(num)
	{
		system("cls");
		std::cout << std::endl << Assist::Blank(4) << "    ����������������¼���Ӧ��Ϣ��������������" << std::endl;
		std::cout << std::endl << Assist::Blank(5) << std::right << std::setw(15) << "�˻���:";
		std::string sName;
		std::cin >> sName;
		std::cout << std::endl << Assist::Blank(5) << std::right << std::setw(15) << "����:";
		std::string nPass;
		std::cin >> nPass;
		for (auto messages : vect)
		{
			if (messages.userName == sName && messages.userPass == nPass)
			{
				messageUser.userName = sName, messageUser.userPass = nPass; messageUser.rank = messages.rank;
				return false;
			}
		}
		std::cout << Assist::Blank(5) << "      �˻��������ڻ��������!" << std::endl;
		std::cout << std::endl << Assist::Blank(5) << "�Ƿ��������\t\ty[Y]/n[N]" << std::endl;
		std::cout << Assist::Blank(6) << "     ��ѡ��:";
		num = Assist::Judge();
		if (num == -1)
		{
			std::cout << std::endl << Assist::Blank(6) << "������Ч��������ȷ��Ϣ!" << std::endl;
			std::cout << Assist::Blank(6);
			system("pause");
		}
	}
	return true;
}

bool Login::Enroll()
{
	int num = 1;
	while(num)
	{
		system("cls");
		std::cout << Assist::Blank(5) << "����������������¼���Ӧ��Ϣ��������������" << std::endl;
		std::cout << std::endl << Assist::Blank(5) << std::right << std::setw(15) << "�˻���:";
		std::string sName;
		std::cin >> sName;
		std::cout << std::endl << Assist::Blank(5) << std::right << std::setw(15) << "����:";
		std::string nPass1, nPass2;
		std::cin >> nPass1;
		std::cout << std::endl << Assist::Blank(5) << std::right << std::setw(15) << "ȷ������:";
		std::cin >> nPass2;
		if (nPass1 == nPass2)
		{
			messageUser.userName = sName, messageUser.userPass = nPass1, messageUser.rank = 1;
			vect.push_back(messageUser);
			SaveUser();
			Assist::Delay(800);
			std::cout << std::endl <<Assist::Blank(5) << "ע��ɹ�!�뷵�ص���" << std::endl;
			std::cout << Assist::Blank(6) << "    ";
			system("pause");
			return true;
		}
		std::cout << std::endl << Assist::Blank(5) << "�������!�Ƿ����¼��\t\ty[Y]/n[N]" << std::endl;
		std::cout << Assist::Blank(6) << "     ��ѡ��:";
		num = Assist::Judge();
		if (num == -1)
		{
			std::cout << std::endl << Assist::Blank(6) << "������Ч��������ȷ��Ϣ!" << std::endl;
			std::cout << Assist::Blank(6);
			system("pause");
		}
	}
	return true;
}

bool Login::Visitor()
{
	messageUser.userName = "1", messageUser.userPass = "1"; messageUser.rank = 2;
	return false;
}

