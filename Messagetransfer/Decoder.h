#pragma once

#include "cocos2d.h"
#include "iostream"
#include "GridMap.h"
#include <string>
#include <vector>

using namespace std;
typedef GridMap::GridVector GridVector;


class Decoder {
private:
	GridVector _path;

	//从服务器端取到的信息
	string _message;

	//信息表示的操作类型
	string _type;//

	//信息中士兵的的id
	int _id;
public:

	//用取到的信息构造Decoder
	Decoder(const string& message);

	//返回信息中士兵的id
	int getId();

	//返回操作类型
	char getType();

	int decodeTargetId();

	int decodeCreateType();

	Grid decodeCreateGrid();

	//从信息中解码出路径
	GridVector decodePath();
};
