#pragma once
#include "Generator.h"

struct Student
{
	bool isSelect;
	string id;
	vector<pair<int, int> > time;
	vector<string> app;
	vector<string> tags;
	Student() :isSelect(false) {}
};

struct Department
{
	int curNum;
	int limit;
	string id;
	vector<pair<int, int> > time;
	vector<string> tags;
	Department():curNum(0){}
};

struct Node
{
	int stu_no;
	int dep_no;
	int match_coef;
	bool operator < (const Node& r) const
	{
		return match_coef > r.match_coef;
	}
};

class Match
{
public:
	Match();
	~Match();
	void init();
	void stu_dep_matching(const char *infile, const char *outfile, int Pattern = 1);
	int getAPP_COEF();
	void setAPP_COEF(int coef);
	int getTAG_COEF();
	void setTAG_COEF(int coef);
	int getTIME_COEF();
	void setTIME_COEF(int coef);
private:
	int APP_COEF;
	int TIME_COEF;
	int TAG_COEF;
	Student students[studentNum + 5];
	Department departments[departmentNum + 5];
	string numToTime(int num);
	int timeToNum(string s);
	int getWeekNo(string s);
	pair<int, int> dateToNum(string s);
	void translate(const char *infile);
	vector<Node> matching();
	void writing(vector<Node> &match, const char *outfile);
};

