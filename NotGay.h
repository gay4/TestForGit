#pragma once

#include "GridMap.h"
#include "Data.h"
#define Debug 1
#include <fstream>

//static std::ofstream mylog;


//�ж��Ƿ�ִ��move��᲻����ֱ��Խ����Ŀ���
bool willBeyondDest(Point now, Point dest, Point offset);

bool rectTooSmall(const Rect& rect);