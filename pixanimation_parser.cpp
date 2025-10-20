#include <iostream>
#include <fstream>
#include <string>
#include <vector>
int main(int argc, char* argv[]) {
	std::ofstream outputFile("out.mp4");
	if (argc > 1) {
		if (argv[1] == "--help" || argv[1] == "-h") {
			std::cout << "pixanimation command line tool\n"
					  << "Usage: pixanimation <inputfile>\n"
					  << "Options:\n"
					  << "  --help, -h    Show this help message\n"
					  << "  -o, --output <file>  Specify output file (default: out.mp4)\n"
					  << "  --syntax, -s  Show syntax guide\n";
			return 0;
		} else if (argv[1] == std::string("-o") || argv[1] == std::string("--output")) {
			if (argc == 3) outputFile(argv[2]);
			std::ifstream inputFile(argv[0]);
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
		std::getline(inputFile, line, ":");
		sections.push_back(line);
	}
	for (const auto& section : sections) {
		for (int i = 0; i < section.size(); i++) {
			outputFile << "Detected ";
			if (section[i] == "r" || "R") outputFile << "red\n";
			else if (section[i] == "o" || "O") outputFile << "orange\n";
			else if (section[i] == "y" || "Y") outputFile << "yellow\n";
			else if (section[i] == "g" || "G") outputFile << "green\n";
			else if (section[i] == "b" || "B") outputFile << "blue\n";
			else if (section[i] == "v" || "V") outputFile << "violet\n";
			else if (section[i] == "1") outputFile << "white";
			else if (section[i] == "0") outputFile << "black";
			else if (section[i] == " " || section[i] == "\t") continue;
			else if (section[i] == "\n") outputFile << "new pixel row";
			else if (section[i] == ";") outputFile << "end of frame";
			else outputFile << "error";
		}
		outputFile << "\n\n";
	}
	outputFile.close();
	inputFile.close();
	return 0;

}