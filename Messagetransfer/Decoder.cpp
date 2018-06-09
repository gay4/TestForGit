#include "Decoder.h"
#include <iostream>
#include <string>
#include "GridMap.h"


//����move��������Ϊ'm'
const char MOVE = 'm';

//���幥����������Ϊ'p'
const char ATTACK = 'a';

//������������������������Ĳ�����Ϊ'p'
const char PRODUCE = 'p';

//���岻ͬ������(������ʿ����ָ���룩


const string ELECTRICITY = "el";     //����糧

const string MINE = "mi";           //�����

const string CAMP = "ca";           //�����Ӫ

const string FACTORY = "fa";         //����ս������

const string DOG = "do";             //���徯Ȯ

const string SOLDIER = "so";         //������

const string TANK = "ta";            //����̹��

Decoder::Decoder(const string& message) :_message(message)
{
		_type = _message.substr(0, 1);
		string id = _message.substr(1, 2);
		sscanf(id.c_str(), "%x", &_id);
}
int Decoder::getId()
{
	return _id;
}


GridVector& Decoder::decodePath()
{
	assert(_type[0] == MOVE);
	Grid point;
	int beginPos = 3;

	_path.clear();// �������
	while (beginPos < _message.length() - 1)
	{
		string temp = _message.substr(beginPos, 2);
		int x, y;
		sscanf(temp.c_str(), "%x", &point._x);
		beginPos += 2;
		temp = _message.substr(beginPos, 2);
		sscanf(temp.c_str(), "%x", &point._y);
		_path.emplace_back(point);
		beginPos += 2;
	}
	return _path;
}

int Decoder::decodeAttackId()
{
	assert(_type[0] == ATTACK);
	int id;
	string temp = _message.substr(3, 2);
	sscanf(temp.c_str(), "%x", &id);
	return id;
}

string& Decoder::decodeProduceType()
{
	assert(_type[0] == PRODUCE);

	_produceType = _message.substr(3, 2);
	return _produceType;
}
char Decoder::getType()
{
	return _message[0];
}