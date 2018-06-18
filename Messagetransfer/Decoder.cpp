#include "Decoder.h"
#include <iostream>
#include <string>
#include "GridMap.h"


const char MOVE = 'm';
const char ATTACK = 'a';
const char CREATE = 'c';
const char TRACE = 't';
const char PREATTACK = 'p';

//������Ϸ������Ĳ�������Ϊ'g'
const char GOSSIP = 'o';


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
	assert(_type[0] == MOVE || _type[0] == TRACE);
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

int Decoder::decodeTargetId()
{
	assert(_message[0] == ATTACK || _message[0] == PREATTACK);

	int targetId = -1;
	string temp = _message.substr(3, 2);
	sscanf(temp.c_str(), "%x", &targetId);
	assert(targetId != -1);//��ȡ�ɹ�

	return targetId;
}

int Decoder::decodeCreateType()
{
	assert(_message[0] == CREATE);

	int unitType = -1;
	string temp = _message.substr(3, 2);
	sscanf(temp.c_str(), "%x", &unitType);
	assert(unitType != -1);

	return unitType;
}
char Decoder::getType()
{
	return _message[0];
}

string Decoder::decodeChat()
{

	assert(_type[0] == GOSSIP);
	int id = getId();
	string temp = to_string(id).append(" : ");
	_chatMessage = _message.substr(3);
	_chatMessage = temp.append(_chatMessage);
	return _chatMessage;
}

Grid Decoder::decodeCreateGrid()
{
	assert(_message[0] == CREATE);

	Grid ret;
	string temp = _message.substr(5, 2);
	sscanf(temp.c_str(), "%x", &ret._x);
	temp = _message.substr(7, 2);
	sscanf(temp.c_str(), "%x", &ret._y);

	assert(ret._x != -1 && ret._y != -1);

	return ret;
}