#pragma once

#include "cocos2d.h"
#include "iostream"
#include "GridMap.h"
#include <string>
#include <vector>
#include "Data.h"
using namespace std;


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
	string& encodePath(GridMap::GridVector& path);


	//��Ҫ������ʿ����Id��ִ�й�����ʿ����id, ��������ת�����ַ�����������
	string& encodeAttack(int targetId);


	//��Ҫ������ʿ��������ȵ�����, ת�����ַ����������ء���produceTypeΪÿ�������Ķ�����const �ַ����Ĵ��ţ���糧Ϊ"el"��
	string& encodeCreate(int unitType, const Grid& createGrid);


	//���������Ϣ���뵽�ַ�����
	string encodeChat(string& chatMessage);
};
