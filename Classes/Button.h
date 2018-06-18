#pragma once

/*Ϊ��ʵ�ִ�������ʱ���϶�Ч��ʵ�ֵ�һ����*/

#include <string>
#include "cocos2d.h"
#include "Unit.h"


USING_NS_CC;
typedef  typename Unit::Type Type;

class UnitManager;
class BButton :public Sprite {
private:
	//�����������϶�ʱ����ʾ
	Sprite * _buttonCopy = nullptr;
	Type _type;
	UnitManager* _unitManager = nullptr;

public:
	static BButton* create(MainScene* scene, Type type, std::string filename);

	bool init(MainScene* scene, Type type, std::string filename);

	Sprite* copy()
	{
		return _buttonCopy;
	}

	bool isTouched(Touch* touch);

	void onPress();//����������Ϊ�ɼ�
	void onRelease();//�ͷ�ʱ������λ
					 //void setUnitManager(UnitManager* unitManager);
};