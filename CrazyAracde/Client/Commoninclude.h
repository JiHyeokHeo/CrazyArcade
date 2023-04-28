#pragma once
// Windows ��� ����
#include <windows.h>
// C ��Ÿ�� ��� �����Դϴ�.
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

std::uniform_real_distribution<> disX(150.0f, 750.0f);
std::uniform_real_distribution<> disY(60.0f, 480.0f);