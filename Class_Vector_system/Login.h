#pragma once
#include<string>
#include<vector>
struct Users
{
	std::string userName;
	std::string userPass;
	int rank;//�ȼ�
};

class Login
{
private:
	std::vector<Users>vect;
	Users messageUser;
	//typedef bool (Login::* Functionptr)();//����һ������ָ������
	void SaveUser();
	void LoadUser();
	bool Enter();//����
	bool Enroll();//ע��
	bool Visitor();
public:
	Users LoginMenu();
};

