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

void Login::LoginAccount()
{
	LoadUser();
	int num, x = 1,s;
	while (1)
	{
		system("cls");
		std::cout << Assist::Blank(5) << "  ����������������������������" << std::endl;
		std::cout << Assist::Blank(5) << "   �˺Ź���-��ǰ�˺ŵȼ�:" << messageUser.rank << std::endl;
		std::cout << Assist::Blank(6) << "   1���޸��˻���Ϣ" << std::endl;
		std::cout << Assist::Blank(6) << "   2��ע���˻�" << std::endl;
		std::cout << Assist::Blank(6) << "   3���������˵�" << std::endl;
		std::cout << Assist::Blank(5) << "  ����������������������������" << std::endl;
		std::cout << Assist::Blank(6) << "  ��ѡ��:";
		num = Assist::Entry();
		if (num >= 4 || num <= 0)
			std::cout << std::endl << Assist::Blank(6) << "������Ч��������ȷ��Ϣ!" << std::endl;
		else if (num == 3)
			break;
		else
		{
			if (num == 1)
			{
				std::cout << Assist::Blank(4) << "  ��������������������ǰ�û���Ϣ������������������" << std::endl;
				std::cout << Assist::Blank(5) << std::right << std::setw(15) << "�˻���:" << messageUser.userName << std::endl ;
				std::cout << Assist::Blank(5) << std::right << std::setw(15) << "����:" << messageUser.userPass << std::endl ;
				std::cout << Assist::Blank(4) << "  ��������������������¼������Ϣ������������������" << std::endl;
				std::cout << std::endl << Assist::Blank(5) << std::right << std::setw(15) << "�˻���:";
				std::string sName;
				std::cin >> sName;
				std::cout << std::endl << Assist::Blank(5) << std::right << std::setw(15) << "����:";
				std::string nPass;
				std::cin >> nPass;
				while(x--)
				{
					for (auto messages : vect)
					{
						if (messages.userName == sName)
						{
							std::cout << Assist::Blank(6) << "�˻����Ѵ���!" << std::endl;
							std::cout << Assist::Blank(4) << "  ������������������������������������������������" << std::endl;
							std::cout << Assist::Blank(5) << "�Ƿ�����޸�?        y[Y]/n[N]" << std::endl
								<< Assist::Blank(6) << "    ��ѡ��:";
							s = Assist::Judge();
							if (s == 1)
							{
								std::cout << std::endl << Assist::Blank(5) << std::right << std::setw(15) << "�˻���:";
								std::cin >> sName;
								x++;
								break;
							}
							else
							{
								goto cc;
							}
						}
					}
				}
				for (int i = 0; i < vect.size(); i++)
				{
					if (vect.at(i).userName == messageUser.userName)
					{
						messageUser.userName = sName, messageUser.userPass = nPass;
						vect.at(i) = messageUser;
						SaveUser();
						Assist::Delay(800);
						std::cout << std::endl << Assist::Blank(6) << "�޸ĳɹ�!" << std::endl;
					}
				}
			}
			else if (num == 2)
			{
				std::cout << Assist::Blank(4) << "  ��������������������ǰ�û���Ϣ������������������" << std::endl;
				std::cout << Assist::Blank(5) << std::right << std::setw(15) << "�˻���:" << messageUser.userName << std::endl;
				std::cout << Assist::Blank(5) << std::right << std::setw(15) << "����:" << messageUser.userPass << std::endl;
				std::cout << Assist::Blank(4) << "  ������������������������������������������������" << std::endl;
				std::cout << Assist::Blank(4) << "       �Ƿ�ȷ��ע���˻�?        y[Y]/n[N]" << std::endl
					<< Assist::Blank(6) << "    ��ѡ��:";
				int num = Assist::Judge();
				if (num == 1)
				{
					for (int i = 0; i < vect.size(); i++)
					{
						if (vect.at(i).userName == messageUser.userName)
						{
							vect.erase(vect.begin() + i);
							SaveUser();
							Assist::Delay(800);
							std::cout << std::endl << Assist::Blank(5) << "ע���ɹ�!�����˳�ϵͳ!" << std::endl;
						}
					}
					vect.clear();
					vect.shrink_to_fit();
					std::cout << Assist::Blank(6);
					system("pause");
					exit(0);
				}
				std::cout << std::endl << Assist::Blank(6) << (num == 0 ? "   ��ȡ������!" : "��Ч������ȡ��!") << std::endl;
			}
			cc:
			x++;
			std::cout << Assist::Blank(6);
			system("pause");
		}
	}
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
	messageUser.userName = "1", messageUser.userPass = "1"; messageUser.rank = 0;
	return false;
}

