#include"Login.h"
#include"Function.h"
#include<iostream>


int main()
{
	Login s1;
	Users ranks;
	ranks = s1.LoginMenu();
	Function homepage;
	homepage.Main(ranks);
	return 0;
}