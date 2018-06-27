#pragma once

/*���Ǳ����࣬ͨ���ƶ�һ���Ĺ���ʵ�ֽ���Ҳ�������ɿɷ��͵���Ϣ
����UnitManager�����ͻ��˷�������*/

#include "cocos2d.h"
#include "iostream"
#include "GridMap.h"
#include <string>
#include <vector>
#include "Data.h"
using std::string;

//typedef GridMap::GridVector GridVector;

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
	const string& encodePath(const GridMap::GridVector& path);

	const string& encodeAttack(int targetId);

	const string& encodeCreate(int unitType, const Grid& createGrid);

	const string& encodeChat(string& chatMessage);
};
