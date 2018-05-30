//
//  BattleScene.h
//  MX2
//
//  Created by apple on 14-5-8.
//
//

#ifndef __MX2__BattleScene__
#define __MX2__BattleScene__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

using namespace std;

// ��Ϸ��������
#define MUSIC_FILE        "background.mp3"
#define FIGHT_FILE        "fight.mp3"
#define SHOOT_FILE        "shoot.wav"
#define BOMB_FILE        "bomb.mp3"

// ��Ϸ������
class BattleScene : public cocos2d::Layer
{
private:
	TMXTiledMap * _battleMap;  // ��ͼ
	Sprite* _player;  // ��Ҿ���
	
	TMXLayer* _collidable;  // �ϰ���
	int _screenWidth, _screenHeight;  // ��Ļ��Ⱥ͸߶�
	int _count;  // ��Ϸ֡������
	
public:
	/**
	* ��̬����������Scene����
	* ע�⣺��Cocos2d-x��û��Cocos2d-iPhone�еġ�id��,���鷵����ʵ����ָ��
	*/
	static cocos2d::Scene* createScene();
	/**
	* init��������ɳ�ʼ��������
	* ע�⣺init������Cocos2d-x�з���boolֵ�������Ƿ���Cocos2d-iPhone�еġ�id��
	*/
	virtual bool init();
	virtual void onEnter();

	

	// �ص����º������ú���ÿһ֡�������
	void update(float delta);
	/**
	* ʹ��CREATE_FUNC�괴����ǰ��Ķ��󣬷��صĶ��󽫻����Զ��ͷųع����ڴ���ͷ�
	*/
	CREATE_FUNC(BattleScene);
};

#endif /* defined(__MX2__BattleSceneScene__) */
