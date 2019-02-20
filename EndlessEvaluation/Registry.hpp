#pragma once
#include "Main.hpp"

void delete_key(HKEY parent_key, const wstring& parent_path, const wstring& key_name);
void edit_registry(const vector<string>& programs);
