#pragma once

#include "cocos2d.h"
#include <map>
#include "Unit.h"
#include "Data.h"//for MAX_PLAYER_NUM
#include "NotGay.h"
#include "Network/Client.h"


using std::map;
USING_NS_CC;

class Unit;
class UnitManager:public Node {
	//test'
	friend class MainScene;
	friend class Unit;
private:
	Point _basePos = Point(100, 100);//��������

	int _playerId = 0;
	int _nextId = -1;//��һ������id
	vector<int> _selectId;//�Ѿ�ѡ�е�id
	map<int, Unit* > _getUnitById;

	GridMap* _gridMap = nullptr;
	TMXTiledMap* _tiledMap = nullptr;
	Client* _client = nullptr;

private:
	bool initWithScene(MainScene* mainScene);
	bool init();
	void selectId(const Rect& rect);//�����ο�ѡ��ʵ�ʹ���
	int getNextId();//�¸�id��			
	void abandonSelectedId();//���ѡ��							 
	bool isOurBro(int id);//���id��Ӧ��Unit�ǲ����Լ���
public:

	static UnitManager* createWithScene(MainScene* mainScene);

	//CREATE_FUNC(UnitManager);

	void selectUnitByRect(const Rect& rect);

private:
	bool hasSelectIdNow();//�ж��Ƿ��Ѿ���ѡ�е�id

	//����Ǳ��ذ汾��create������unit��id������Ϣ���ݸ�client
	void localCreateUnit(int type, const Point& createPoint);

	//�з����ҷ�����unit���߼���������������
	void createUnit(int id, int type, const Grid& createGrid = Grid(6,6));

	void setPath(int id, GridMap::GridVector path);

	void selectUnitByPoint(const Point& point);

	void selectOneUnit(int id);

};