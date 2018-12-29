#pragma once
#include <Windows.h>
#include <iostream>

void registry_error();
void registry_error(const char* path);
void registry_warning(const char* path);
const wchar_t* get_wc(const char* c);
const wchar_t* wc_concat(const wchar_t* wc1, const wchar_t* wc2);
void edit_registry(const char** programs, const int& program_number);
