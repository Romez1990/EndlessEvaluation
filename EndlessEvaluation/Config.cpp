#include "Config.hpp"

// #pragma comment(lib, "shell32.lib")
string get_home_dir()
{
	// CoInitialize(NULL);
	TCHAR* path = nullptr;
	SHGetKnownFolderPath(FOLDERID_Profile, /*KF_FLAG_DEFAULT*/KF_FLAG_SIMPLE_IDLIST, nullptr, &path);
	// CoTaskMemFree(path);
	const wstring w_path(&path[0]);
	return string(w_path.begin(), w_path.end());
}

void remove_file(const fs::path& file)
{
	if (exists(file))
	{
		if (!remove(file))
			cout << "Can't remove file " << file.string() << endl;
		else
			cout << "Removing file " << file.string() << endl;
	}
}

void remove_dir(const fs::path& dir)
{
	if (exists(dir))
	{
		if (!remove_all(dir))
			cout << "Can't remove directory " << dir.string() << endl;
		else
			cout << "Removing directory " << dir.string() << endl;
	}
}

void clean_dir(const fs::path& dir)
{
	remove_file(dir / R"(config\options\options.xml)");
	remove_dir(dir / R"(config\eval)");
}

void edit_config(const vector<string>& programs)
{
	for (const auto& dir : fs::directory_iterator(get_home_dir()))
	{
		if (!dir.is_directory()) continue;

		const string dir_name = dir.path().filename().string();
		if (dir_name[0] != '.') continue;

		for (const auto& program : programs)
		{
			bool match = true;
			const int program_len = program.size();
			const int dir_name_len = dir_name.size();
			int i = 0;
			for (int j = 1; i < program_len && j < dir_name_len && match; ++i, ++j)
			{
				match &= program[i] == tolower(dir_name[j]);
			}
			match |= i == program_len;

			if (match)
				clean_dir(dir);
		}
	}
}
