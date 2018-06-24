#pragma once

/*�����ӵ��࣬��Ҫ��Ϊ�˱�֤�����ӵ���λɾ����Ѫ�������߼�������
����Ȼ�кܶ��ֱ���İ취��������д�����е�С���������Ϊ����������
��׷��Ч���ͱ�ը����������bug��˵����
ͻȻ���ֺ��񲻵ò�д��......*/

#include "cocos2d.h"
#include "Unit.h"

USING_NS_CC;

class Bullet :public Sprite {
public:
	static Bullet* create(Unit* atker, int targetId);

	//void update(float)override;

	void runBullet();

private:
	//�����ӵ�
	void destroy();

	bool init(Unit* atker, int targetId);


	Vec2 _start, _end;
	int _effect = 0;
	int _atkeeId = -1;
	float _speed = 96.f;
	Node* _map = nullptr;
	UnitManager* _unitManager = nullptr;
};