#pragma once

/*������Ϊ����˺��л���ĳ������ɸ��ݵȴ���ҵ�����ѡ���Ƿ�ʼ��Ϸ
�ڴ˳�������Ҫ��ʼ���ͻ��˺ͷ����*/

#include "cocos2d.h"
#include "Network/Client.h"
#include "Network/LocalServer.h"
#include <string>

using std::string;
USING_NS_CC;

class RoomScene :public Scene {
public:
	CREATE_FUNC(RoomScene);

	//�����������
	void update(float delta)override;
private:
	bool init()override;

	LocalServer* _server = nullptr;
	Client* _client = nullptr;

	Label* _clientNum = nullptr;//��ʾ�����
	Label* _readyClientNum = nullptr;//��ʾ�Ѿ�׼���õ������

	const string num2Str(int num);
};