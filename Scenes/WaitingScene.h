#pragma once

/*����ڴ˳�������ip��ַ��������ʧ������Ҫ��������ip
����ȴ�����˿�ʼ��Ϸ���Զ��е�������*/

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

class WaitingScene :public Scene {
public:
	CREATE_FUNC(WaitingScene);

private:
	bool init()override;

	void update(float delta)override;
};
