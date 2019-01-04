#include "Registry.hpp"
#include "Config.hpp"

int main(const int argc, const char* argv[])
{
	const int program_number = 2;
	const char** programs = new const char*[program_number];
	programs[0] = "phpstorm";
	programs[1] = "webstorm";

	edit_registry(programs, program_number);
	edit_config(programs, program_number);

	delete[] programs;

	std::cout << std::endl << argv[0] << " ended his work." << std::endl;
	system("pause");

	return 0;
}
