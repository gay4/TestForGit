#pragma once

/*������Ϸ�����������Ͽ�ץ��С���һ�������ˣ�ɣ�*/

#include "GridMap.h"
#include "cocos2d.h"
#include "UnitManager.h"
#include "GameManager.h"
#include "Network/Client.h"
//#include "Network/LocalServer.h"
//#include "RealUnit.h"

USING_NS_CC;

namespace ScenePool {
	static cocos2d::Scene* preScene = nullptr;
}

//����ѡ��
struct MouseRect:public DrawNode {
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
	static MainScene* create(Client* client = nullptr);

	void initNetwork(Client* client);

	static MainScene* createScene();
private:
	bool init();

	void initButton(EventListenerTouchOneByOne* buildingListener);

	void initLabel();
private:
	Label* _goldLabel = nullptr;//��Ǯ����ʾ
	Label* _powerLabel = nullptr;//��������ʾ
	//---------------//
	Text * _displayValueLabel[2] = { nullptr ,nullptr , };         //������Ϣ��ʾ��
	//Text * _displayValueLabel2 = nullptr;
	TextField* _chatWindow = nullptr;
	Sprite* _inputBar = nullptr;
	Button* _sendMessageButton = nullptr;

	bool _isInput = false;
	//-------------//
	ControlPanel* _controlPanel = nullptr;//�����ɻ���̹�˵Ŀ������
	Label* _notice = nullptr;//��Ϣ��ʾ

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

	Client * _client = nullptr;
	//LocalServer* _server = nullptr;

	void textFieldEvent(Ref *pSender, cocos2d::ui::TextField::EventType type);
	void animationInit();
	//void createFighterCallBack(Ref* pSender);
};

class ControlPanel :public Menu {
	friend class Factory;
public:
	CREATE_FUNC(ControlPanel);
	bool init();

	void createFighterCallBack(Ref* pSender);
	void createTankCallBack(Ref* pSender);
private:
	//children
	MenuItemImage* _fighter = nullptr;
	MenuItemImage* _tank = nullptr;
	Factory* _factory = nullptr;//��ǰ�Ϳ���������ӵ�factory��ʵ�ֻص�
	

	/*��mainScene��ʼ��panel�����ڴ���init*/
	bool initWithScene(MainScene* scene);

};