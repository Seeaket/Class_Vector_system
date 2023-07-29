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
	LoadUser();//加载用户数据
	bool result = true;
	while(result)
	{
		system("cls");
		std::cout << Assist::Blank(5) << "  ——————————————" << std::endl;
		std::cout << Assist::Blank(6) << "  Login-System" << std::endl;
		std::cout << Assist::Blank(6) << "    1、登入" << std::endl;
		std::cout << Assist::Blank(6) << "    2、注册" << std::endl;
		std::cout << Assist::Blank(6) << "   3、游客登入" << std::endl;
		std::cout << Assist::Blank(5) << "  ——————————————" << std::endl;
		std::cout << Assist::Blank(6) << "  请选择:";
		int num = Assist::Entry();
		if (num < 1 || num > 3)
		{
			std::cout << Assist::Blank(6) << "   无效输入!" << std::endl;
			std::cout << Assist::Blank(6);
			system("pause");
			continue;
		}
		typedef bool(Login::*Fa)();
		Fa start[] = { &Login::Enter,&Login::Enroll,&Login::Visitor };
		result = (this->*start[num - 1])();//因为Login是一个类的实例，使用成员函数指针需要使用->*运算符来调用
	}
	std::cout << std::endl << Assist::Blank(6) << "     登入成功!" << std::endl;
	Assist::Delay(800);
	return messageUser;
}

bool Login::Enter()
{
	int num = 1;
	while(num)
	{
		system("cls");
		std::cout << std::endl << Assist::Blank(4) << "    ———————请录入对应信息———————" << std::endl;
		std::cout << std::endl << Assist::Blank(5) << std::right << std::setw(15) << "账户名:";
		std::string sName;
		std::cin >> sName;
		std::cout << std::endl << Assist::Blank(5) << std::right << std::setw(15) << "密码:";
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
		std::cout << Assist::Blank(5) << "      账户名不存在或密码错误!" << std::endl;
		std::cout << std::endl << Assist::Blank(5) << "是否继续登入\t\ty[Y]/n[N]" << std::endl;
		std::cout << Assist::Blank(6) << "     请选择:";
		num = Assist::Judge();
		if (num == -1)
		{
			std::cout << std::endl << Assist::Blank(6) << "输入无效请输入正确信息!" << std::endl;
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
		std::cout << Assist::Blank(5) << "———————请录入对应信息———————" << std::endl;
		std::cout << std::endl << Assist::Blank(5) << std::right << std::setw(15) << "账户名:";
		std::string sName;
		std::cin >> sName;
		std::cout << std::endl << Assist::Blank(5) << std::right << std::setw(15) << "密码:";
		std::string nPass1, nPass2;
		std::cin >> nPass1;
		std::cout << std::endl << Assist::Blank(5) << std::right << std::setw(15) << "确认密码:";
		std::cin >> nPass2;
		if (nPass1 == nPass2)
		{
			messageUser.userName = sName, messageUser.userPass = nPass1, messageUser.rank = 1;
			vect.push_back(messageUser);
			SaveUser();
			Assist::Delay(800);
			std::cout << std::endl <<Assist::Blank(5) << "注册成功!请返回登入" << std::endl;
			std::cout << Assist::Blank(6) << "    ";
			system("pause");
			return true;
		}
		std::cout << std::endl << Assist::Blank(5) << "密码错误!是否继续录入\t\ty[Y]/n[N]" << std::endl;
		std::cout << Assist::Blank(6) << "     请选择:";
		num = Assist::Judge();
		if (num == -1)
		{
			std::cout << std::endl << Assist::Blank(6) << "输入无效请输入正确信息!" << std::endl;
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

