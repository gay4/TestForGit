#pragma once

/*��������Ӧ�Ľ����࣬����Ϣ�������Ҳ���*/

#include "cocos2d.h"
#include "iostream"
#include "GridMap.h"
#include <string>
#include <vector>

using std::string;
typedef GridMap::GridVector GridVector;


class Decoder {
private:
	GridVector _path;

	//�ӷ�������ȡ������Ϣ
	string _message;

	//��Ϣ��ʾ�Ĳ�������
	string _type;//

	//��Ϣ��ʿ���ĵ�id
	int _id;
public:

	//��ȡ������Ϣ����Decoder
	Decoder(const string& message);

	//������Ϣ��ʿ����id
	int getId();

	//���ز�������
	char getType();

	int decodeTargetId();

	int decodeCreateType();

	Grid decodeCreateGrid();

	//����Ϣ�н����·��
	GridVector decodePath();

	const string decodeChat();
};
