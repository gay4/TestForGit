#pragma once

#include "GridMap.h"
#include "cocos2d.h"
#include "UnitManager.h"
#include "GameManager.h"
#include "Network/Client.h"
#include <string>

USING_NS_CC;

//����ѡ��
struct MouseRect :public DrawNode {
	CREATE_FUNC(MouseRect);
	Point _touchStart, _touchEnd;

	Point start, end;//in the _tileMap
					 //derive from DrawNode for memfun DrawRect
};

class ControlPanel;
class GameManager;
class UnitManager;
class BButton;
class MainScene :public Scene {
	friend class GameManager;
	friend class ControlPanel;//for create callback function
	friend class UnitManager;
	friend class BButton;

public:
	static MainScene* create();

	static MainScene* createScene(Client* client);

	virtual bool init();

	void initButton(EventListenerTouchOneByOne* buildingListener);

	void initLabel();

	void textFieldEvent(Ref *pSender, cocos2d::ui::TextField::EventType type);

	//virtual void update(float delta);

private:
	
	int _playerId;
	Text * _displayValueLabel1 = nullptr;           //������Ϣ��ʾ��
	Text * _displayValueLabel2 = nullptr;
	TextField* _chatWindow = nullptr;
	Sprite* _inputBar = nullptr;
	Button* _sendMessageButton = nullptr;

	bool isInput = false;

	Label* _goldLabel = nullptr;//��Ǯ����ʾ
	Label* _powerLabel = nullptr;//��������ʾ

	ControlPanel* _controlPanel = nullptr;//�����ɻ���̹�˵Ŀ������
	Label* _notice = nullptr;//��Ϣ��ʾ

	cocos2d::Point _cursorPosition{ 0, 0 };

	int _screenWidth, _screenHeight;

	//int _playerId;

	MouseRect* _mouseRect;

	//��λ������
	UnitManager* _unitManager;

	//��Ϸ��ͼ������
	GameManager* _gameManager;

	GridMap* _gridMap = nullptr;
	TMXTiledMap* _tiledMap = nullptr;

	void update(float delta);

private:

	Client * _client = nullptr;
	//void createFighterCallBack(Ref* pSender);
};

class ControlPanel:public Menu {
	friend class Factory;
public:
	CREATE_FUNC(ControlPanel);
	bool init();

	void createFighterCallBack(Ref* pSender);
	void createTankCallBack(Ref* pSender);
private:
	//children
	MenuItemImage * _fighter = nullptr;
	MenuItemImage* _tank = nullptr;
	Factory* _factory = nullptr;//��ǰ�Ϳ���������ӵ�factory��ʵ�ֻص�

	/*��mainScene��ʼ��panel�����ڴ���init*/
	bool initWithScene(MainScene* scene);

};