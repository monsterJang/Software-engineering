#pragma once
#pragma comment(lib, "json_vc71_libmtd.lib")
#include "json\json.h"
#include <cstdio>
#include <ctime>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
class Generator
{
public:
	Generator();
	~Generator();
	void Generate(const char *fileToGenerate, int depNum = 20, int stuNum = 300, int clsNum = 6);
	void setDepartmentNum(int depNum);
	int getDepartmentNum();
	void setStudentNum(int stuNum);
	int getStudentNum();
	void setClassNum(int clsNum);
	int getClassNum();
private:
	int departmentNum = 20;
	int studentNum = 300;
	int classNum = 6;
	string numToTime(int num);
	string getStudentNo(int num);
	void generateStudent(Json::Value & root);
	void generateDepartment(Json::Value & root);
	void writeJsonToFile(Json::Value & root, const char * fileToWrite);
	void generate(const char *fileToGenerate);
};

