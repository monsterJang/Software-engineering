#pragma comment(lib, "json_vc71_libmtd.lib")
#include "Generator.h"
using namespace std;

int main(int argc, char *argv[])
{
	srand((unsigned)time(NULL));
	Generator gen;
	if (argc == 2)
	{
		gen.Generate(argv[1]);
	}
	else
	{
		int depNum = atoi(argv[2]);
		int stuNum = atoi(argv[3]);
		int clsNum = atoi(argv[4]);
		if (depNum > 20 || depNum <= 0 || stuNum > 300 || stuNum <= 0 || clsNum > 6 || clsNum <= 0)
		{
			printf("out of range!\n");
		}
		else if (stuNum < clsNum)
		{
			printf("input error!\n");
		}
		else
		{
			gen.Generate(argv[1], depNum, stuNum, clsNum);
		}
	}
	

	return 0;
}