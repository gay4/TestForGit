#pragma once

#include "cocos2d.h"
#include "iostream"
#include "GridMap.h"
#include <string>
#include <vector>
#include "Data.h"
using namespace std;

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
	Encoder(const string& type, int id = 0);        //Ϊ���������ṩĬ��id

	//Encoder�����������ת����Ҫ���͵��ַ���
	string& encodePath(GridMap::GridVector& path);


	//��Ҫ������ʿ����Id��ִ�й�����ʿ����id, ��������ת�����ַ�����������
	string& encodeAttack(int id);


	//��Ҫ������ʿ��������ȵ�����ת�����ַ����������ء���produceTypeΪÿ�������Ķ�����const �ַ����Ĵ��ţ���糧Ϊ"el"��
	string& encodeProduce(const string& produceType);
};
