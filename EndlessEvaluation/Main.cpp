#include "Main.hpp"
#include "Registry.hpp"
#include "Config.hpp"

int main(const int argc, const char* argv[])
{
	const vector<string> programs = { "phpstorm", "webstorm" };

	edit_registry(programs);
	edit_config(programs);

	cout << endl << argv[0] << " ended his work." << endl;
	system("pause");

	return 0;
}
