#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include"pugixml.hpp"
#include"pugiconfig.hpp"
#include <iostream>
#include <cstring>
#include <winsock2.h>
#include <Windows.h>
#include <fstream>
#include <sstream>
#include <thread>
#include<filesystem>
#include <string>
#include <iterator>
#include <algorithm>
#include<conio.h>

using namespace std;

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib,"Crypt32.lib")

const int MAX_BUFFER_SIZE = 1025;