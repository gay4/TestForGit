#pragma once

#include "cocos2d.h"
#include <map>
#include "Unit.h"
#include "Data.h"//for MAX_PLAYER_NUM
#include "NotGay.h"

using std::map;
USING_NS_CC;

class Unit;
class UnitManager:public Node {
	//test'
	friend class MainScene;

private:
	Point _basePos = Point(100, 100);

	int _playerId = 0;

	//add a MAX_PLAYER_NUM every time, initialize with playerId
	int _nextId = -1;
	vector<int> _selectId;

public:
	bool init();
	CREATE_FUNC(UnitManager);
	void selectUnitByRect(const Rect& rect);

	map<int, Unit* > _getUnitById;
	//��ѡ֮��
	bool hasSelectIdNow();

	GridMap* _gridMap = nullptr;
	TMXTiledMap* _tiledMap = nullptr;

	//������Ĭ���ڻ���
	//����Ǳ��ذ汾��create������unit��id������Ϣ���ݸ�client
	void localCreateUnit(int type /*const Grid& g*/);

	//�з����ҷ�����unit���߼���������������
	void createUnit(int id, int type, Point postion);

	int getNextId();

	//���ѡ��
	void selectId(const Rect& rect);

	//�����ο�ѡ��ʵ�ʹ���
	void abandonSelectedId();

	//���id��Ӧ��Unit�ǲ����Լ���
	bool isOurBro(int id);

	
};