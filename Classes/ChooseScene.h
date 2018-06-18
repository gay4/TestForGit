#ifndef _ChooseScene__
#define _ChooseScene__

#include <iostream>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <string>
USING_NS_CC;

// 1. GameMenu�����������ʾһ���˵����������û�ѡ�񡰿�ʼ��Ϸ�����ǡ���Ϸ���á���
class ChooseScene : public cocos2d::Layer
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
	* ʹ��CREATE_FUNC�괴����ǰ��Ķ��󣬷��صĶ��󽫻����Զ��ͷųع����ڴ���ͷ�*/

	void textFieldEvent(Ref *pSender, cocos2d::ui::TextField::EventType type);
	
	CREATE_FUNC(ChooseScene);

private:
	std::string _ip;

	ui::TextField * _chatWindow = nullptr;
};

#endif /* defined(__AirfightGame__GameMenuScene__) */
