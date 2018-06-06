#pragma once

#include "cocos2d.h"
#include "iostream"
#include "GridMap.h"
#include <string>
#include <vector>
#include "Data.h"
using namespace std;

//�������
typedef vector<Grid> GridVector;

class Encoder {
private:

	//��������
	string _type;

	//����id
	int _id;

	//Ҫ���͵�string����Ϣ
	string _message;
public:

	//�����ò������ͺ�ʿ��id����Encoder
	Encoder(const string& type, int id);

	//Encoder�����������ת����Ҫ���͵��ַ���
	string& encodePath(GridVector& path);

};
