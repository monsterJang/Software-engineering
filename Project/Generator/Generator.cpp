#include "Generator.h"

string weeks[] = {
	"Sun", "Mon", "Tues", "Wed", "Thu", "Fri", "Sat"
};
string departments_no[] = {
	"D000", "D001", "D002", "D003", "D004", "D005", "D006", "D0007", "D008", "D009",
	"D010", "D011", "D012", "D013", "D014", "D015", "D016", "D0017", "D018", "D019"
};
string tags[] = {
	"reading", "programming", "film", "English", "reading",
	"music", "dance", "basketball", "chess", "football",
	"swimming", "singing", "climbing", "runing", "drawing",
	"writing", "cooking", "speeching", "piano", "Go"
};

Generator::Generator()
{
}


Generator::~Generator()
{
}

void Generator::Generate(const char *fileToGenerate, int depNum, int stuNum, int clsNum)
{
	setDepartmentNum(depNum);
	setStudentNum(stuNum);
	setClassNum(clsNum);
	generate(fileToGenerate);
}

void Generator::setDepartmentNum(int depNum)
{
	this->departmentNum = depNum;
}

int Generator::getDepartmentNum()
{
	return this->departmentNum;
}

void Generator::setStudentNum(int stuNum)
{
	this->studentNum = stuNum;
}

int Generator::getStudentNum()
{
	return this->studentNum;
}

void Generator::setClassNum(int clsNum)
{
	this->classNum = clsNum;
}

int Generator::getClassNum()
{
	return this->classNum;
}

/*
@param num, range[0, 1439]
@return retTime, range "00:00"~"23:59"
*/
string Generator::numToTime(int num)
{
	num %= 1440;
	int h = num / 60;
	int m = num % 60;
	char retTime[6];
	sprintf_s(retTime, "%02d:%02d", h, m);
	return retTime;
}

/*
@param num: range[0, studentNum-1]
@return student_no, range [031502100~031502659]
*/
string Generator::getStudentNo(int num)
{
	char student_no[10] = "031502000";
	int studentPerClass = studentNum / classNum;
	int	studentIdInClass = num % studentPerClass;
	student_no[6] = num / studentPerClass + '1';
	student_no[7] = studentIdInClass / 10 + '0';
	student_no[8] = studentIdInClass % 10 + '0';
	return student_no;
}

void Generator::generateStudent(Json::Value &root)
{
	for (int num = 0; num < studentNum; ++num)
	{
		Json::Value stu;

		// free_time: count range [2, 15]
		int free_time_count = 2 + rand() % 14;
		for (int i = 0; i < free_time_count; ++i)
		{
			int weekNo = rand() % 7;
			int beginTime = 60 * 8 + 30 * (rand() % 26);  // range [8:00~20:00]
			int endTime = beginTime + 60 + 30 * (rand() % 5);  // duration range [1:00~3:00]
			string Date = weeks[weekNo] + "." + (numToTime(beginTime)) + "~" + (numToTime(endTime));
			stu["free_time"].append(Date);
		}

		// student_no: range [031502100~031502659]
		stu["student_no"] = getStudentNo(num);

		// applications_department: count range[0, 5]
		int app_count = rand() % 6;
		bool vis_app[20] = { false };
		for (int i = 0; i < app_count; ++i)
		{
			int app_no;
			while (vis_app[(app_no = rand() % 20)]);
			vis_app[app_no] = true;
			stu["applications_department"].append(departments_no[app_no]);
		}

		// tags: count range[2, 20]
		int tag_count = 2 + rand() % 19;
		bool vis_tag[20] = { false };
		for (int i = 0; i < tag_count; ++i)
		{
			int tag_no;
			while (vis_tag[(tag_no = rand() % 20)]);
			vis_tag[tag_no] = true;
			stu["tags"].append(tags[tag_no]);
		}

		// add student
		root["students"].append(stu);
	}
}

void Generator::generateDepartment(Json::Value &root)
{
	for (int num = 0; num < departmentNum; ++num)
	{
		Json::Value dep;

		// event_schedules: count range [2, 10]
		int free_time_count = 2 + rand() % 14;
		for (int i = 0; i < free_time_count; ++i)
		{
			int weekNo = rand() % 7;
			int beginTime = 60 * 8 + 30 * rand() % 26;  // range [8:00~20:00]
			int endTime = beginTime + 60 + 30 * rand() % 5;  // duration range [1:00~3:00]
			string Date = weeks[weekNo] + "." + (numToTime(beginTime)) + "~" + (numToTime(endTime));
			dep["free_time"].append(Date);
		}

		// member_limit: range [10, 15]
		dep["member_limit"] = 10 + rand() % 6;

		// department_no
		dep["department_no"] = departments_no[num];

		// tags: count range[2, 20]
		int tag_count = 2 + rand() % 19;
		int vis_tag[20] = { false };
		for (int i = 0; i < tag_count; ++i)
		{
			int tag_no;
			while (vis_tag[(tag_no = rand() % 20)]);
			vis_tag[tag_no] = true;
			dep["tags"].append(tags[tag_no]);
		}

		// add department
		root["departments"].append(dep);
	}
}

void Generator::writeJsonToFile(Json::Value &root, const char *fileToWrite)
{
	ofstream ofs;
	ofs.open(fileToWrite, std::ios::binary);
	Json::StyledWriter writer;
	string strWrite = writer.write(root);
	ofs << strWrite;
	ofs.close();
}

void Generator::generate(const char *fileToWrite)
{
	Json::Value root;
	generateStudent(root);
	generateDepartment(root);
	writeJsonToFile(root, fileToWrite);
}

