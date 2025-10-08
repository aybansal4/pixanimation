#include <iostream>
#include <fstream>
#include <string>
#include <vector>
int main(int argc, char* argv[]) {
	if (argc > 1) {
		std::vector u_args;
		for (int i = 1: i <= sizeof(argv); i++) u_args.push(argv[i]);
		std::runtime_error(("Unexpected Arguments: " + u_args).c_str());
		return 1;
	} else if (argc <= 0) {
		std::runtime_error("No arguments passed to pixanimation command. Unable to do anything".c_str());
		return 1;
	}
	std::ifstream inputFile(argv[0]);
}