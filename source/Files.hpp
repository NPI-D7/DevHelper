#pragma once
#include <3ds.h>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <charconv>
#include <cstdlib>

#define WORKING_DIR	"/"

Result makeDirs(const char * path);
Result openFile(Handle* fileHandle, const char * path, bool write);
Result deleteFile(const char * path);
Result removeDir(const char * path);
Result removeDirRecursive(const char * path);