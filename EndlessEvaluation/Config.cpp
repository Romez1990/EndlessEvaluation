#include "Config.hpp"

void config_warning(const char* path, const bool is_file)
{
	std::cout << "Warning. There is no " << (is_file ? "file" : "folder") << " " << path << " to remove" << std::endl;
}

void config_error(const char* path, const bool is_file)
{
std::cout << "Error. Can't remove " << (is_file ? "file" : "folder") << " " << path << std::endl;
}

const char* get_homedir()
{
	const size_t MAX_PATH = 260; // From Windows.h;
	char homedir[MAX_PATH];
#ifdef _WIN32
	snprintf(homedir, MAX_PATH, "%s%s", getenv("HOMEDRIVE"), getenv("HOMEPATH"));
#else
	snprintf(homedir, MAX_PATH, "%s", getenv("HOME"));
#endif
	return strdup(homedir);
}

const char* c_str_concat(const char* c1, const char* c2)
{
	const int wc1_len = strlen(c1);
	const int wc2_len = strlen(c2);
	const int wc_res_len = wc1_len + wc2_len;
	char* c_res = new char[wc_res_len + 1];

	int i;
	for (i = 0; i < wc1_len; ++i)
		c_res[i] = c1[i];

	for (int j = 0; j < wc2_len; ++i, ++j)
		c_res[i] = c2[j];

	c_res[wc_res_len] = '\0';

	return c_res;
}

void clean_dir(const char* dir)
{
	const char* file_path = c_str_concat(dir, R"(\config\options\options.xml)");
	const fs::path file(file_path);
	if (!exists(file))
		config_warning(file_path, true);
	else if (!remove(file))
		config_error(file_path, true);

	const char* folder_path = c_str_concat(dir, R"(\config\eval)");
	const fs::path folder(folder_path);
	if (!exists(folder))
		config_warning(folder_path, false);
	else if (!remove_all(folder))
		config_error(file_path, false);
}

void edit_config(const char** programs, const int& program_number)
{
	const fs::directory_iterator end_itr;
	for (fs::directory_iterator file(get_homedir()); file != end_itr; ++file)
	{
		if (!(*file).is_directory()) continue;

		std::string s = (*file).path().filename().string();
		const char* dir_name = s.c_str();
		if (dir_name[0] != '.') continue;

		for (int n = 0; n < program_number; ++n)
		{
			bool match = true;
			const int program_len = strlen(programs[n]);
			const int dir_name_len = strlen(dir_name);
			int i = 0;
			for (int j = 1; i < program_len && j < dir_name_len && match; ++i, ++j)
			{
				match &= programs[n][i] == tolower(dir_name[j]);
			}
			match |= i == program_len;

			if (match)
				clean_dir((*file).path().string().c_str());
		}
	}
}
