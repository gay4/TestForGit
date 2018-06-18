#pragma once

#include "cocos2d.h"
#include <map>
#include "Unit.h"
#include "Data.h"//for MAX_PLAYER_NUM
#include "NotGay.h"
#include "Network/Client.h"
//#include "MainScene.h"

using std::map;
USING_NS_CC;

enum Notice {
	NO_ENOUGH_MONEY=0,//��Ǯ����
	BASE_ATTACKED,//�������ܹ���
	OCCUPIED_POSITION,//�ط���ռ�ݣ�����
	PLEASE_WAIT,//��������Ҫcd
	WAIT_FOR_START,//��Ҫ�Ｑ
};

class Unit;
class ControlPanel;
class UnitManager:public Node {
	//test'
	friend class MainScene;
	friend class Unit;
	friend class SoldierCamp;
	friend class Factory;
	friend class Mine;
	friend class ElectricityFactory;
	friend class BButton;
private:
	Grid basePos[MAX_PLAYER_NUM] = {//��������
		Grid(12,8),Grid(119,118),Grid(114,9),Grid(11,119),
	};
private:
	//ÿ����λ�������ĵĽ�Ǯ
	int costGold[10] = {
		200,100,300,500,700,0,300,400
	};
	//ÿ����λ�������ĵĵ���
	int costElectricity[10] = {
		100,50,200,300,400,0,100,200
	};
	bool _startFlag = false;
public:
	bool isStart() { return _startFlag; }

	bool canCreate(int type);
	//�϶�Ҫ��Ǯ��
	void costForCreate(int type);
//private:
	Grid _basePos;//��������
	void initAllBase();
private:
	int _gold = 10000;
	int _electricity = 10000;
	Label* _goldLabel = nullptr;
	Label* _powerLabel = nullptr;

	int _playerNum = 0;
	int _loserNum = 0;

	int _playerId = 0;
	int _nextId = -1;//��һ������id
	vector<int> _selectId;//�Ѿ�ѡ�е�id
	map<int, Unit* > _getUnitById;

	GridMap* _gridMap = nullptr;
	TMXTiledMap* _tiledMap = nullptr;
	Client* _client = nullptr;
	ControlPanel* _controlPanel = nullptr;
	Label* _notice = nullptr;

private:
	bool initWithScene(MainScene* mainScene);

	bool init();

	void selectId(const Rect& rect);//�����ο�ѡ��ʵ�ʹ���

	int getNextId();//�¸�id��			

	void abandonSelectedId();//���ѡ��			

	bool isOurBro(int id);//���id��Ӧ��Unit�ǲ����Լ���

public:
	//��õ�ǰ�Ľ�Ǯ����
	int getGold()
	{
		return _gold;
	}
	//��õ�ǰ�ĵ�������
	int getElectricity()
	{
		return _electricity;
	}

	static UnitManager* createWithScene(MainScene* mainScene);

	//CREATE_FUNC(UnitManager);

	void selectUnitByRect(const Rect& rect);

private:
	void selectBuilding(Unit* building);

	bool hasSelectIdNow();//�ж��Ƿ��Ѿ���ѡ�е�id

	//����Ǳ��ذ汾��create������unit��id������Ϣ���ݸ�client
	void localCreateUnit(int type, const Point& createPoint);

	//������ʱЧ��������createUnit_
	void createUnit(int id, int type, const Grid& createGrid = Grid(6,6));
	//�з����ҷ�����unit���߼���������������
	void createUnit_(int id, int type, const Grid& createGrid = Grid(6, 6));

	void setPath(int id, GridMap::GridVector path);

	void selectUnitByPoint(const Point& point);

	void selectOneUnit(int id);

	void updateLabel();

	void updateUnitState();

	void update(float delta);

	void deleteUnit(int id);
	void deleteUnit(Unit* unit);

	//���unit�Ƿ�����
	bool unitMayDead(Unit* attackee);

	int getIdByUnit(Unit* unit);
public:
	void notice(Notice note);
	void notice(std::string);
};