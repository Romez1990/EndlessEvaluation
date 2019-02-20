#include "Registry.hpp"

void delete_key(HKEY parent_key, const wstring& parent_path, const string& key_name)
{
	HKEY key = nullptr;
	const wstring w_key_name(key_name.begin(), key_name.end());
	const wstring w_key_path = parent_path + w_key_name;
	const LSTATUS res = RegOpenKey(HKEY_CURRENT_USER, w_key_path.c_str(), &key);
	RegCloseKey(key);
	if (res != ERROR_SUCCESS)
		return;

	const string key_path(w_key_path.begin(), w_key_path.end());
	if (RegDeleteTree(parent_key, w_key_name.c_str()) != ERROR_SUCCESS)
		cout << "Can't delete registry key " << key_path.c_str() << endl;
	else
		cout << "Deleting registry key " << key_path.c_str() << endl;
}

void edit_registry(const vector<string>& programs)
{
	const wstring parent_path = LR"(Software\JavaSoft\Prefs\jetbrains\)";
	HKEY parent_key = nullptr;
	if (RegOpenKey(HKEY_CURRENT_USER, parent_path.c_str(), &parent_key) != ERROR_SUCCESS)
		return;

	delete_key(parent_key, parent_path, "jetprofile");

	for (const auto& program : programs)
		delete_key(parent_key, parent_path, program);

	RegCloseKey(parent_key);
}
