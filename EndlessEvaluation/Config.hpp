#pragma once
#include "Main.hpp"
#include <filesystem>

namespace fs = std::filesystem;

void config_warning(const char* path, const bool is_file);
void config_error(const char* path, const bool is_file);
const char* get_homedir();
const char* c_str_concat(const char* c1, const char* c2);
void clean_dir(const char* dir);
void edit_config(const char** programs, const int& program_number);
