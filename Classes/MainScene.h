#pragma once

#include "GridMap.h"
#include "cocos2d.h"
#include "UnitManager.h"
#include "GameManager.h"

USING_NS_CC;

//����ѡ��
struct MouseRect:public DrawNode {
	CREATE_FUNC(MouseRect);
	Point _touchStart, _touchEnd;

	Point start, end;//in the _tileMap
	//derive from DrawNode for memfun DrawRect
};

class GameManager;
class MainScene :public Scene {
	friend class GameManager;

public:
	static MainScene* create();

	static MainScene* createScene();

	virtual bool init();

	//virtual void update(float delta);

private:
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
};

