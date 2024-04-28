#include "include/parser.h"
#include "include/Time.h"
#include "include/solver.h"
#include <fstream>
#include <time.h>

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		std::cout << "no input file specified!" << std::endl;
		return 1;
	}
	std::ifstream ifs(argv[1]);
	if (!ifs.good())
	{
		std::cout << "can't open file" << argv[1] << "!" << std::endl;
		return 1;
	}

	clock_t begin, Par, Run;
	begin = clock();
	AigGraph aig;
	Parser parser;
	if (!parser.parse(ifs, aig))
	{
		std::cout << "can't parse file" << argv[1] << "!" << std::endl;
		return 1;
	}
	Par = clock();
	solver m_solver(aig);
	// aig.printf_graph();
	m_solver.run();
	Run = clock();
	std::cout << "the time of parser:   " << 1.0 * (Par - begin) / 1000 << "  ms" << std :: endl;
	std::cout << "the time of run:   " << 1.0 * (Run - Par) / 1000 << "  ms" << std :: endl;
	return 0;
}
