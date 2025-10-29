#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
    std::string inputFileName;
    std::string outputFileName = "out.mp4";

    if (argc > 1) {
        for (int i = 1; i < argc; ++i) {
            std::string a = argv[i];
            if (a == "-h" || a == "--help") {
                std::cout << "pixanimation command line tool\n"
                          << "Usage: pixanimation [options] <inputfile>\n"
                          << "Options:\n"
                          << "  --help, -h               Show this help message\n"
                          << "  -o, --output <file>      Specify output file (default: out.mp4)\n"
                          << "  --syntax, -s             Show syntax guide\n";
                return 0;
            } else if (a == "-o" || a == "--output") {
                if (i + 1 < argc) {
                    outputFileName = argv[++i];
                } else {
                    std::cerr << "Error: missing value for " << a << "\n";
                    return 1;
                }
            } else if (a == "-s" || a == "--syntax") {
                std::cout << "Syntax guide: frames separated by ':'; colors as r/g/b/y/o/v (or uppercase), 1 = white, 0 = black, ';' = end of frame, newline for new row\n";
                return 0;
            } else if (a.size() > 0 && a[0] == '-') {
                std::cerr << "Unknown option: " << a << "\n";
                return 1;
            } else {
                inputFileName = a;
            }
        }
    }

    if (inputFileName.empty()) {
        std::cerr << "Error: no input file specified\n";
        return 1;
    }

    std::ifstream inputFile(inputFileName, std::ios::binary);
    if (!inputFile.is_open()) {
        std::cerr << "Unable to open input file: " << inputFileName << "\n";
        return 1;
    }

    std::ofstream outputFile(outputFileName, std::ios::out | std::ios::trunc);
    if (!outputFile.is_open()) {
        std::cerr << "Unable to open output file: " << outputFileName << "\n";
        return 1;
    }

    std::vector<std::string> sections;
    std::string section;
    // Read using ':' as a frame separator (matches original intent)
    while (std::getline(inputFile, section, ':')) {
        sections.push_back(section);
    }
    sections.erase(sections.begin());
    std::cout << "Processing input file and generating output file: " << outputFileName << std::endl;

    for (const auto& sec : sections) {
        for (char c : sec) {
            // skip common whitespace except explicit newline marker if present in input
            if (c == ' ' || c == '\t') continue;

            outputFile << "Detected ";
            if (c == 'r' || c == 'R') outputFile << "red\n";
            else if (c == 'o' || c == 'O') outputFile << "orange\n";
            else if (c == 'y' || c == 'Y') outputFile << "yellow\n";
            else if (c == 'g' || c == 'G') outputFile << "green\n";
            else if (c == 'b' || c == 'B') outputFile << "blue\n";
            else if (c == 'v' || c == 'V') outputFile << "violet\n";
            else if (c == '1') outputFile << "white\n";
            else if (c == '0') outputFile << "black\n";
            else if (c == '\n') outputFile << "new pixel row\n";
            else if (c == ':') outputFile << "end of frame\n";
            else outputFile << "error\n";
        }
        outputFile << "\n";
    }

    outputFile.close();
    inputFile.close();
    return 0;
}