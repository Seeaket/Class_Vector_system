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

void Login::LoginAccount()
{
	LoadUser();
	int num, x = 1,s;
	while (1)
	{
		system("cls");
		std::cout << Assist::Blank(5) << "  ——————————————" << std::endl;
		std::cout << Assist::Blank(5) << "   账号管理-当前账号等级:" << messageUser.rank << std::endl;
		std::cout << Assist::Blank(6) << "   1、修改账户信息" << std::endl;
		std::cout << Assist::Blank(6) << "   2、注销账户" << std::endl;
		std::cout << Assist::Blank(6) << "   3、返回主菜单" << std::endl;
		std::cout << Assist::Blank(5) << "  ——————————————" << std::endl;
		std::cout << Assist::Blank(6) << "  请选择:";
		num = Assist::Entry();
		if (num >= 4 || num <= 0)
			std::cout << std::endl << Assist::Blank(6) << "输入无效请输入正确信息!" << std::endl;
		else if (num == 3)
			break;
		else
		{
			if (num == 1)
			{
				std::cout << Assist::Blank(4) << "  —————————当前用户信息—————————" << std::endl;
				std::cout << Assist::Blank(5) << std::right << std::setw(15) << "账户名:" << messageUser.userName << std::endl ;
				std::cout << Assist::Blank(5) << std::right << std::setw(15) << "密码:" << messageUser.userPass << std::endl ;
				std::cout << Assist::Blank(4) << "  —————————请录入新信息—————————" << std::endl;
				std::cout << std::endl << Assist::Blank(5) << std::right << std::setw(15) << "账户名:";
				std::string sName;
				std::cin >> sName;
				std::cout << std::endl << Assist::Blank(5) << std::right << std::setw(15) << "密码:";
				std::string nPass;
				std::cin >> nPass;
				while(x--)
				{
					for (auto messages : vect)
					{
						if (messages.userName == sName)
						{
							std::cout << Assist::Blank(6) << "账户名已存在!" << std::endl;
							std::cout << Assist::Blank(4) << "  ————————————————————————" << std::endl;
							std::cout << Assist::Blank(5) << "是否继续修改?        y[Y]/n[N]" << std::endl
								<< Assist::Blank(6) << "    请选择:";
							s = Assist::Judge();
							if (s == 1)
							{
								std::cout << std::endl << Assist::Blank(5) << std::right << std::setw(15) << "账户名:";
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
						std::cout << std::endl << Assist::Blank(6) << "修改成功!" << std::endl;
					}
				}
			}
			else if (num == 2)
			{
				std::cout << Assist::Blank(4) << "  —————————当前用户信息—————————" << std::endl;
				std::cout << Assist::Blank(5) << std::right << std::setw(15) << "账户名:" << messageUser.userName << std::endl;
				std::cout << Assist::Blank(5) << std::right << std::setw(15) << "密码:" << messageUser.userPass << std::endl;
				std::cout << Assist::Blank(4) << "  ————————————————————————" << std::endl;
				std::cout << Assist::Blank(4) << "       是否确认注销账户?        y[Y]/n[N]" << std::endl
					<< Assist::Blank(6) << "    请选择:";
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
							std::cout << std::endl << Assist::Blank(5) << "注销成功!即将退出系统!" << std::endl;
						}
					}
					vect.clear();
					vect.shrink_to_fit();
					std::cout << Assist::Blank(6);
					system("pause");
					exit(0);
				}
				std::cout << std::endl << Assist::Blank(6) << (num == 0 ? "   已取消操作!" : "无效操作已取消!") << std::endl;
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
			std::cout << std::endl <<Assist::Blank(6) << "注册成功!请返回登入" << std::endl;
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
	messageUser.userName = "1", messageUser.userPass = "1"; messageUser.rank = 0;
	return false;
}

