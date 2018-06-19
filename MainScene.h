#pragma once

#include "GridMap.h"
#include "cocos2d.h"
#include "UnitManager.h"
#include "GameManager.h"
#include"ui/CocosGUI.h"
#include"Building.h"

using namespace ui;
USING_NS_CC;

//����ѡ��
struct MouseRect:public DrawNode {
	CREATE_FUNC(MouseRect);
	Point _touchStart, _touchEnd;

	Point start, end;//in the _tileMap
	//derive from DrawNode for memfun DrawRect
};

class ControlPanel;
class GameManager;
class MainScene :public Scene {
	friend class GameManager;
	friend class ControlPanel;//for create callback function

public:
	void animationInit();

	static MainScene* create();

	static MainScene* createScene();

	void updateRes(float dt);

		Label* _goldLabel;

		Label* _electricityLabel;


	virtual bool init();

	//֡��ʱ��
	int _count;

	//virtual void update(float delta);

private:
	ControlPanel* _controlPanel = nullptr;

	cocos2d::Point _cursorPosition{ 0, 0 };

	int _screenWidth, _screenHeight;

	int _playerId;

	MouseRect* _mouseRect;

	//��λ������
	UnitManager* _unitManager;

	//��Ϸ��ͼ������
	GameManager* _gameManager;

	GridMap* _gridMap = nullptr;
	TMXTiledMap* _tiledMap = nullptr;

	void update(float delta);

private:
	//void createFighterCallBack(Ref* pSender);
};

class ControlPanel :public Menu {
public:
	CREATE_FUNC(ControlPanel);
	bool init();

	void createFighterCallBack(Ref* pSender);
private:
	//children
	MenuItemImage* _fighter = nullptr;

	/*��mainScene��ʼ��panel�����ڴ���init*/
	bool initWithScene(MainScene* scene);

};