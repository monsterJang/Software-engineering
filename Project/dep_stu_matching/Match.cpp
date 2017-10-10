#include "Match.h"



Match::Match()
{
}


Match::~Match()
{
}

void Match::init()
{
	for (int i = 0; i < studentNum + 5; ++i)
	{
		students[i].isSelect = false;
		students[i].time.clear();
		students[i].app.clear();
		students[i].tags.clear();
	}
	for (int i = 0; i < departmentNum + 5; ++i)
	{
		departments[i].curNum = 0;
		departments[i].time.clear();
		departments[i].tags.clear();
	}
}

void Match::stu_dep_matching(const char *infile, const char *outfile, int Pattern)
{
	switch (Pattern)
	{
	case 1:  // APP first
		setAPP_COEF(20); setTIME_COEF(5); setTAG_COEF(1);
		break;
	case 2:  // time first
		setAPP_COEF(5); setTIME_COEF(20); setTAG_COEF(1);
		break;
	case 3:  // tag first
		setAPP_COEF(5); setTIME_COEF(1); setTAG_COEF(20);
		break;
	default:
		setAPP_COEF(20); setTIME_COEF(5); setTAG_COEF(1);
		break;
	}

	translate(infile);
	vector<Node> match = matching();
	writing(match, outfile);
}

int Match::getAPP_COEF()
{
	return this->APP_COEF;
}

void Match::setAPP_COEF(int coef)
{
	this->APP_COEF = coef;
}

int Match::getTAG_COEF()
{
	return this->TAG_COEF;
}

void Match::setTAG_COEF(int coef)
{
	this->TAG_COEF = coef;
}

int Match::getTIME_COEF()
{
	return this->TIME_COEF;
}

void Match::setTIME_COEF(int coef)
{
	this->TIME_COEF = coef;
}

string Match::numToTime(int num)
{
	num %= 1440;
	int h = num / 60;
	int m = num % 60;
	char ret[6];
	sprintf_s(ret, "%02d:%02d", h, m);
	return ret;
}

int Match::timeToNum(string s)
{
	int ret = 0;
	int idx = s.find(':');
	int h = atoi(s.substr(0, idx).c_str());
	int m = atoi(s.substr(idx + 1, string::npos).c_str());
	return h * 60 + m;
}

int Match::getWeekNo(string s)
{
	if (!s.compare("Sun"))  return 0;
	else if (!s.compare("Mon"))  return 1;
	else if (!s.compare("Tues"))  return 2;
	else if (!s.compare("Wed"))  return 3;
	else if (!s.compare("Thu"))  return 4;
	else if (!s.compare("Fri"))  return 5;
	else return 6;
}

pair<int, int> Match::dateToNum(string s)
{
	int ret1 = 0, ret2 = 0;
	int idx1, idx2;

	idx1 = s.find('.');
	string strWeek = s.substr(0, idx1);
	int week_no = getWeekNo(strWeek);
	ret1 += 1440 * week_no;
	ret2 += 1440 * week_no;

	idx2 = s.find('~');
	string strBegin = s.substr(idx1 + 1, idx2 - idx1 - 1);
	string strEnd = s.substr(idx2 + 1, string::npos);
	ret1 += timeToNum(strBegin);
	ret2 += timeToNum(strEnd);

	return make_pair(ret1, ret2);
}

void Match::translate(const char *infile)
{
	Json::Reader reader;
	Json::Value root;
	ifstream is;
	is.open(infile, std::ios::binary);

	if (reader.parse(is, root))
	{
		// department
		int dep_sz = root["departments"].size();
		for (int i = 0; i < dep_sz; ++i)
		{
			Json::Value dep = root["departments"][i];
			// time
			Json::Value Dates = dep["event_schedules"];
			for (int j = 0; j < (int)Dates.size(); ++j)
			{
				string date = Dates[j].asString();
				pair<int, int> t = dateToNum(date);
				departments[i].time.push_back(t);
			}

			// member_limit
			Json::Value Limit = dep["member_limit"];
			departments[i].limit = Limit.asInt();

			// department_no
			Json::Value Id = dep["department_no"];
			departments[i].id = Id.asString();

			// tags
			Json::Value Tags = dep["tags"];
			for (int j = 0; j < (int)Tags.size(); ++j)
			{
				string tag = Tags[j].asString();
				departments[i].tags.push_back(tag);
			}
		}


		// students
		int stu_sz = root["students"].size();
		for (int i = 0; i < stu_sz; ++i)
		{
			Json::Value stu = root["students"][i];
			// time
			Json::Value Dates = stu["free_time"];
			for (int j = 0; j < (int)Dates.size(); ++j)
			{
				string date = Dates[j].asString();
				pair<int, int> t = dateToNum(date);
				students[i].time.push_back(t);
			}

			// student_no
			Json::Value Id = stu["student_no"];
			students[i].id = Id.asString();

			// applications_department
			Json::Value App = stu["applications_department"];
			for (int j = 0; j < (int)App.size(); ++j)
			{
				string app = App[j].asString();
				students[i].app.push_back(app);
			}

			// tags
			Json::Value Tags = stu["tags"];
			for (int j = 0; j < (int)Tags.size(); ++j)
			{
				string tag = Tags[j].asString();
				students[i].tags.push_back(tag);
			}
		}
	}
}

vector<Node> Match::matching()
{
	vector<Node> list;
	vector<Node> match;

	for (int i = 0; i < studentNum; ++i)
	{
		for (int j = 0; j < departmentNum; ++j)
		{
			Student &stu = students[i];
			Department &dep = departments[j];

			int app_flag = -1;
			for (int k = 0; k < (int)stu.app.size(); ++k)
			{
				if (!stu.app[k].compare(dep.id))
				{
					app_flag = k;
					break;
				}
			}
			if (app_flag == -1)  continue;

			int time_flag = 0;
			for (int k = 0; k < (int)stu.time.size(); ++k)
			{
				for (int p = 0; p < (int)dep.time.size(); ++p)
				{
					int stuL = stu.time[k].first;
					int stuR = stu.time[k].second;
					int depL = dep.time[p].first;
					int depR = dep.time[p].second;
					if (stuL <= depL && depR <= stuR)  time_flag++;
				}
			}

			int tag_flag = 0;
			for (int k = 0; k < (int)stu.tags.size(); ++k)
			{
				for (int p = 0; p < (int)dep.tags.size(); ++p)
				{
					if (!stu.tags[k].compare(dep.tags[p]))
					{
						tag_flag++;
					}
				}
			}

			int coef = 0;
			coef += (5 - app_flag) * APP_COEF;
			coef += time_flag * TIME_COEF;
			coef += tag_flag * TAG_COEF;

			list.push_back(Node{ i, j, coef });
		}
	}
	sort(list.begin(), list.end());
	int list_sz = list.size();
	for (int i = 0; i < list_sz; ++i)
	{
		int stu_no = list[i].stu_no;
		int dep_no = list[i].dep_no;
		int coef = list[i].match_coef;
		Student &stu = students[stu_no];
		Department &dep = departments[dep_no];
		if (stu.isSelect)  continue;
		if (dep.curNum >= dep.limit)  continue;
		match.push_back(Node{ stu_no, dep_no, coef });
		stu.isSelect = true;
		dep.curNum++;
	}

	return match;
}

void Match::writing(vector<Node> &match, const char * outfile)
{
	Json::Value root;
	// unlucky_student
	for (int i = 0; i < studentNum; ++i)
	{
		if (!students[i].isSelect)
		{
			root["unlucky_student"].append(students[i].id);
		}
	}
	// unlucky_department
	for (int i = 0; i < departmentNum; ++i)
	{
		if (!departments[i].curNum)
		{
			root["unlucky_department"].append(departments[i].id);
		}
	}
	// admitted
	int match_sz = match.size();
	for (int i = 0; i < match_sz; ++i)
	{
		int stu_no = match[i].stu_no;
		int dep_no = match[i].dep_no;
		Json::Value match_item;
		match_item["member"] = students[stu_no].id;
		match_item["department_no"] = departments[dep_no].id;
		root["admitted"].append(match_item);
	}

	// writing
	ofstream ofs;
	ofs.open(outfile, std::ios::binary);
	Json::StyledWriter writer;
	string strWrite = writer.write(root);
	ofs << strWrite;
	ofs.close();
}
