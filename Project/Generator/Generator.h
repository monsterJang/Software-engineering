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
const int departmentNum = 20;
const int studentNum = 300;
const int classNum = 6;
class Generator
{
public:
	Generator();
	~Generator();
	void Generate(const char *fileToGenerate);
private:
	string numToTime(int num);
	string getStudentNo(int num);
	void generateStudent(Json::Value & root);
	void generateDepartment(Json::Value & root);
	void writeJsonToFile(Json::Value & root, const char * fileToWrite);
	void generate(const char *fileToGenerate);
};

