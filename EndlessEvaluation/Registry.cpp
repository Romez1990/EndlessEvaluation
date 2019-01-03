#include "Registry.hpp"

void registry_error()
{
	std::cout << "Error. Can't edit registry" << std::endl;
}

void registry_error(const char* path)
{
	std::cout << "Error. Can't edit registry at " << path << std::endl;
}

void registry_warning(const char* path)
{
	std::cout << "Warning. There is no " << path << " registry key to delete" << std::endl;
}

const wchar_t* get_wc(const char* c)
{
	const size_t c_len = strlen(c) + 1;
	wchar_t* wc = new wchar_t[c_len];
	mbstowcs(wc, c, c_len);
	return wc;
}

const wchar_t* wc_concat(const wchar_t* wc1, const wchar_t* wc2)
{
	const int wc1_len = wcslen(wc1);
	const int wc2_len = wcslen(wc2);
	const int wc_res_len = wc1_len + wc2_len;
	wchar_t* wc_res = new wchar_t[wc_res_len + 1];

	int i;
	for (i = 0; i < wc1_len; ++i)
		wc_res[i] = wc1[i];

	for (int j = 0; j < wc2_len; ++i, ++j)
		wc_res[i] = wc2[j];

	wc_res[wc_res_len] = '\0';

	return wc_res;
}

void edit_registry(const char** programs, const int& program_number)
{
	const wchar_t* parent_path = LR"(Software\JavaSoft\Prefs\jetbrains\)";
	HKEY parent_key = nullptr;
	if (RegOpenKey(HKEY_CURRENT_USER, parent_path, &parent_key) != ERROR_SUCCESS)
	{
		registry_error();
		return;
	}

	for (int i = 0; i < program_number; ++i)
	{
		const wchar_t* program = get_wc(programs[i]);

		HKEY program_key = nullptr;
		const LSTATUS res = RegOpenKey(HKEY_CURRENT_USER, wc_concat(parent_path, program), &program_key);
		RegCloseKey(program_key);
		if (res != ERROR_SUCCESS)
		{
			registry_warning(programs[i]);
			continue;
		}

		if (RegDeleteTree(parent_key, program) != ERROR_SUCCESS)
		{
			registry_error(programs[i]);
		}
	}

	RegCloseKey(parent_key);
}
