#pragma comment(lib, "json_vc71_libmtd.lib")
#include "Generator.h"
using namespace std;

int main(int argc, char *argv[])
{
	srand((unsigned)time(NULL));
	Generator gen;
	gen.Generate(argv[1]);

	return 0;
}