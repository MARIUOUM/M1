#ifndef LIBS_HPP_INCLUDED
#define LIBS_HPP_INCLUDED

#include <iostream>
#include <fstream>
#include <experimental/filesystem>
#include <string>
#include <vector>
#include <list>
#include <cstdlib>
#include <stdio.h>

#if defined(_WIN32)

#include <Windows.h>
#include <vld.h>
#include <conio.h>


#define MOVE_UP ((GetKeyState('Z') & 0x8000) || (GetKeyState(VK_UP) & 0x8000))
#define MOVE_DOWN ((GetKeyState('S') & 0x8000) || (GetKeyState(VK_DOWN) & 0x8000))
#define MOVE_LEFT ((GetKeyState('Q') & 0x8000) || (GetKeyState(VK_LEFT) & 0x8000))
#define MOVE_RIGHT ((GetKeyState('D') & 0x8000) || (GetKeyState(VK_RIGHT) & 0x8000))

#define MOVE_UP_LEFT ((GetKeyState('A') & 0x8000) || ((GetKeyState(VK_UP) & 0x8000) && (GetKeyState(VK_LEFT) & 0x8000)))
#define MOVE_UP_RIGHT ((GetKeyState('E') & 0x8000) || ((GetKeyState(VK_UP) & 0x8000) && (GetKeyState(VK_RIGHT) & 0x8000)))


#define MOVE_DOWN_LEFT ((GetKeyState('W') & 0x8000) || ((GetKeyState(VK_DOWN) & 0x8000) && (GetKeyState(VK_LEFT) & 0x8000)))
#define MOVE_DOWN_RIGHT ((GetKeyState('C') & 0x8000) || ((GetKeyState(VK_DOWN) & 0x8000) && (GetKeyState(VK_RIGHT) & 0x8000)))


#define QUIT (GetKeyState(VK_ESCAPE) & 0x8000)
#define PACK (GetKeyState('I') & 0x8000)

#define MOVE (MOVE_UP || MOVE_DOWN || MOVE_LEFT || MOVE_RIGHT || MOVE_UP_LEFT || MOVE_UP_RIGHT || MOVE_DOWN_LEFT || MOVE_DOWN_RIGHT)
#define OK (QUIT || MOVE || PACK)

#else

#include <unistd.h>

#endif

using namespace std;
namespace fs = experimental::filesystem;

template<typename Base, typename T>
inline bool instanceof(const T *ptr) {
	return dynamic_cast<const Base*>(ptr) != nullptr;
}

#endif