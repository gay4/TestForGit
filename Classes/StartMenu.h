#ifndef _StartMenu__
#define _StartMenu__

#include <iostream>
#include "cocos2d.h"

// 1. GameMenu�����������ʾһ���˵����������û�ѡ�񡰿�ʼ��Ϸ�����ǡ���Ϸ���á���
class StartMenu : public cocos2d::Layer
{
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

	/**
	* ʹ��CREATE_FUNC�괴����ǰ��Ķ��󣬷��صĶ��󽫻����Զ��ͷųع����ڴ���ͷ�
	*/
	CREATE_FUNC(StartMenu);
};

#endif /* defined(__AirfightGame__GameMenuScene__) */
