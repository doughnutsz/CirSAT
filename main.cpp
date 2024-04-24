#include "include/parser.h"
#include "include/Time.h"
#include "include/solver.h"
#include <fstream>
#include <time.h>
#include <cstdlib>  // 包含 getopt 函数的头文件
#include <unistd.h> // 包含 getopt 函数的头文件
#include <vector>
#include <string>


int main(int argc, char **argv) {
    int c;
    int ConfLimit = 10000;
    int Verbose = 0;

    while ((c = getopt(argc, argv, "C:I:vh")) != -1) {
        switch (c) {
            case 'C':
                ConfLimit = atoi(optarg);
                if (ConfLimit < 0) {
                    std::cerr << "Invalid value for -C option." << std::endl;
                    return 1;
                }
                break;
            case 'v':
                Verbose = 1;
                break;
            case 'h':
                std::cout << "Usage: " << argv[0] << " [input] [-c num] [-vh]" << std::endl;
                std::cout << "\tinput      path to the input file" << std::endl;
                std::cout << "\t-C num : limit on the number of conflicts [default = " << ConfLimit << "]" << std::endl;
                std::cout << "\t-v     : prints verbose information [default = " << (Verbose ? "yes" : "no") << "]" << std::endl;
                std::cout << "\t-h     : print the command usage" << std::endl;
                return 0;
            case '?':
                std::cerr << "Invalid option." << std::endl;
                return 1;
            default:
                break;
        }
    }
    if (optind >= argc) {
        std::cout << "no input file specified!" << std::endl;
        return 1;
    }
    std::ifstream ifs(argv[optind]);
    if (!ifs.good()) {
        std::cout << "can't open file " << argv[optind] << "!" << std::endl;
        return 1;
    }

	// clock_t begin, Par, Run;
	// begin = clock();
	AigGraph aig;
	Parser parser;
	if (!parser.parse(ifs, aig))
	{
		std::cout << "can't parse file" << argv[1] << "!" << std::endl;
		return 1;
	}
	// Par = clock();
	solver m_solver(aig);
	// aig.printf_graph();
	m_solver.run(ConfLimit, Verbose);
	// Run = clock();
    
	// std::cout << "the time of parser:   " << 1.0 * (Par - begin) / 1000 << "  ms" << std :: endl;
	// std::cout << "Time:   " << 1.0 * (Run - Par) / 1000 << "  ms" << std :: endl;
  	return 0;
}
