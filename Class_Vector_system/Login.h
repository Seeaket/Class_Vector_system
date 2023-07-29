#pragma once
#include<string>
#include<vector>
struct Users
{
	std::string userName;
	std::string userPass;
	int rank;//等级
};

class Login
{
private:
	std::vector<Users>vect;
	Users messageUser;
	//typedef bool (Login::* Functionptr)();//定义一个函数指针类型
	void SaveUser();
	void LoadUser();
	bool Enter();//登入
	bool Enroll();//注册
	bool Visitor();
public:
	Users LoginMenu();
};

