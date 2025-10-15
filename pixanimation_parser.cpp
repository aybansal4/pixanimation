#include <iostream>
#include <fstream>
#include <string>
#include <vector>
int main(int argc, char* argv[]) {
	if (argc > 1) {
		if (argv[1] == std::string("--help") || argv[1] == std::string("-h")) {
			std::cout << "pixanimation command line tool\n"
					  << "Usage: pixanimation <inputfile>\n"
					  << "Options:\n"
					  << "  --help, -h    Show this help message\n"
					  << "  -o, --output <file>  Specify output file (default: out.mp4)\n";
			return 0;
		} else if (argv[1] == std::string("-o") || argv[1] == std::string("--output")) {
			if (argc < 4) {
				std::runtime_error("Output file not specified after -o");
				return 1;
			}
			std::string outputFile = argv[3];
			std::ifstream inputFile(argv[2]);
			if (!inputFile.is_open()) {
				std::runtime_error("Unable to open file: " + std::string(argv[3]));
				return 1;
			}
			std::vector<std::string> sections;
			for (int i = 1; !inputFile.eof(); i++) {
				std::string line;
				std::getline(inputFile, line);
				sections.push_back(line);
			}
			// Process sections and generate output file
			std::cout << "Processing input file and generating output file: " << outputFile << std::endl;
			return 0;
		}
	} else if (argc <= 0) {
		std::runtime_error("No arguments passed to pixanimation command. Unable to do anything");
		return 1;
	}
	std::ifstream inputFile(argv[0]);
	if (!inputFile.is_open()) {
		std::runtime_error(("Unable to open file: " + std::string(argv[0])).c_str());
		return 1;
	}
	std::vector<std::string> sections;
	for (int i = 1; !inputFile.eof(); i++) {
		std::string line;
		std::getline(inputFile, line);
		sections.push_back(line);
	}
	for (const auto& section : sections) {
		std::cout << section << std::endl;
	}
	return 0;

}