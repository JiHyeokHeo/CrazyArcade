#pragma once
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <assert.h>
#include <random>

#include <string>
#include <vector>
#include <list>
#include <map>
#include <functional>
#include <filesystem>

#pragma comment(lib, "Msimg32.lib")


#define TILE_SIZE_X 60
#define TILE_SIZE_Y 60


// Define a random number generator engine
std::mt19937 gen{ std::random_device{}() };
// Define a uniform distribution between 0 and 1
std::uniform_real_distribution<float> dist{ 0.0f, 1.0f };