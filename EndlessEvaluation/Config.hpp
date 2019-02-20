#pragma once
#include "Main.hpp"
#include <filesystem>
#include <shlobj.h>

namespace fs = filesystem;

string get_home_dir();
void remove_file(const fs::path& file);
void remove_dir(const fs::path& dir);
void clean_dir(const fs::path& dir);
void edit_config(const vector<string>& programs);
