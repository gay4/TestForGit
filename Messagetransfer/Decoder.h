#pragma once

#include "cocos2d.h"
#include "iostream"
#include "GridMap.h"
#include <string>
#include <vector>
#include "Data.h"
using namespace std;
typedef vector<Grid> GridVector;

//ȫ�ֱ������洢�����ĸ������
GridVector path;

class Decoder {
private:

	//�ӷ�������ȡ������Ϣ
	string _message;

	//��Ϣ��ʾ�Ĳ�������
	string _type;

	//��Ϣ��ʿ���ĵ�id
	int _id;
public:

	//��ȡ������Ϣ����Decoder
	Decoder(const string& message);

	//����Ϣ�н����·��
	GridVector& decodePath();

	//������Ϣ��ʿ����id
	int getId();


	//���ز�������
	char getType();

};
