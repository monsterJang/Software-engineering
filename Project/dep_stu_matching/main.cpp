#pragma comment(lib, "json_vc71_libmtd.lib")
#include "Generator.h"
#include "Match.h"
#include "json\json.h"
#include <cstdio>
#include <iostream>
#include <fstream>
#include <ctime>
#include <algorithm>
using namespace std;

int main(int argc, char *argv[])
{
	srand((unsigned)time(NULL));
	//Generator gen;
	//gen.Generate(argv[1]);
	Match match;
	match.init();
	match.stu_dep_matching(argv[1], argv[2]);

	return 0;
}