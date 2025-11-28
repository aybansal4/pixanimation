#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>

int main(int argc, char* argv[]) {
    extern "C" {
        #include <libs/libs.h>
        av_register_all();
    }
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
                          << "  -d, --debug              Enable debug file (debug.txt)";
                return 0;
            } else if (a == "-d" || a == "--debug") {
                std::ofstream debugFile("debug.txt", std::ios::binary);
            } else if (a == "-o" || a == "--output") {
                if (i + 1 < argc) {
                    outputFileName = argv[++i];
                } else {
                    std::cerr << "Error: missing value for " << a << "\n";
                    return 1;
                }
            } else if (a == "-s" || a == "--syntax") {
                std::cout << "Syntax colors as r/g/b/y/o/v (or uppercase), 1 = white, 0 = black, ':' = end of frame, newline for new row\n";
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
            if (c == 'r' || c == 'R') {
                debugFile << "red\n";
            }
            else if (c == 'o' || c == 'O') {
                debugFile << "orange\n";
            }
            else if (c == 'y' || c == 'Y') {
                debugFile << "yellow\n";
            }
            else if (c == 'g' || c == 'G') {
                debugFile << "green\n";
            }
            else if (c == 'b' || c == 'B') {
                debugFile << "blue\n";
            }
            else if (c == 'v' || c == 'V') {
                debugFile << "violet\n";
            }
            else if (c == '1') {
                debugFile << "white\n";
            }
            else if (c == '0') {
                debugFile << "black\n";
            }
            else if (c == '\n') {
                debugFile << "new pixel row\n";
            }
            else {
                debugFile << "error\n";
            }
        }
        outputFile << "Detected end of frame\n";
    }

    outputFile.close();
    inputFile.close();
    if (debugFile.is_open()) debugFile.close();
    return 0;
}



