#pragma once

#include "cocos2d.h"
#include "iostream"
#include "GridMap.h"
#include <string>
#include <vector>

using namespace std;
typedef vector<Grid> GridVector;




class Decoder {
private:

	GridVector _path;

	//�ӷ�������ȡ������Ϣ
	string _message;

	//��Ϣ��ʾ�Ĳ�������
	string _type;

	//��Ϣ��ʿ���ĵ�id
	int _id;


	//��Ϣ��Ҫ����Ķ���������
	string _produceType;
public:

	//��ȡ������Ϣ����Decoder
	Decoder(const string& message);

	//����Ϣ�н����·��
	GridVector& decodePath();

	//����Ϣ�н����Ҫ���������Id
	int decodeAttackId();

	//����Ϣ�н����Ҫ�����Ľ�����ʿ��
	string& decodeProduceType();

	//������Ϣ��ʿ����id
	int getId();


	//���ز�������
	char getType();

};
