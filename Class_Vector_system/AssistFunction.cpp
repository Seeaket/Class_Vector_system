#include "AssistFunction.h"
#include<string>
#include<iostream>
#include<chrono>
#include<thread>
#include<iomanip>


std::string Assist::Blank(int num)
{
	std::string tbs(num, '\t');
	return tbs;
}

int Assist::Entry()
{
	char c[20];
	std::cin >> c;
	int num = atoi(c);
	return num;
}

void Assist::Delay(int num)
{
	std::cout << Blank(6)<< "     ";
	while (num -= 200)
	{
		auto time_t = std::chrono::high_resolution_clock::now() + std::chrono::milliseconds(num);
		std::cout << ".";
		std::this_thread::sleep_until(time_t);
	}
	auto time_t = std::chrono::high_resolution_clock::now() + std::chrono::milliseconds(num);
	std::this_thread::sleep_until(time_t);
}

int Assist::Judge()
{
	std::string c;
	std::cin >> c;
	if (c == "y" || c == "Y")
		return 1;
	if (c == "n" || c == "N")
		return 0;
	return -1;
}

void Assist::LocalTime()
{
	const char* wday[] = { "日" ,"一" ,"二"  ,"三"  ,"四"  ,"五" ,"六" };
	time_t t = time(NULL);//获取时间戳
	struct tm t1;
	localtime_s(&t1, &t);
	//std::cout << std::setfill('0');
	std::cout << std::endl << Blank(4) << "本地时间:" << t1.tm_year + 1900 << "年" << t1.tm_mon + 1 << "月" << t1.tm_mday
		<< "日_星期" << wday[t1.tm_wday];
	std::cout << "\t" << t1.tm_hour << ":" << t1.tm_min << ":" << t1.tm_sec << std::endl;
}







