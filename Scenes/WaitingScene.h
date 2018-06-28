#pragma once

/*����ڴ˳������������������µķ����б�ѡ���
�룬��������ip��ַ��������ʧ������Ҫ��������ip����
�ɹ���ȴ�����˿�ʼ��Ϸ���Զ��е�������*/

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

class WaitingScene :public Scene {
public:
	CREATE_FUNC(WaitingScene);

private:
	enum Notice {//��ʾ��Ϣ���Ͷ���
		CONNECT_TRY = 0,//�������ӣ���ȴ�
		CONNECT_SUCCESS,//���ӳɹ����ȴ�������ʼ��Ϸ
		CONNET_FAIL,//����ʧ�ܣ���������
		VALID_IP,//ip���Ϸ�����������
	};

	bool init()override;

	void update(float delta)override;

	void notice(Notice type);//��Ϣ��ʾ

	void EnterHandle(Ref* pSender, Widget::TouchEventType type);

	TextField* _inputIpWindow = nullptr;

	bool isIpValid(const std::string& ip);//����ip�Ƿ�Ϸ�

	bool isPartOfIp(const std::string& str);//����str�Ƿ�Ϊ�Ϸ�ip��ַ��һ����

	void refresh(int mode);
};
