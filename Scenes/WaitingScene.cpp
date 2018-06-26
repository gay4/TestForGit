#include "WaitingScene.h"
#include <string>
#include "Network/Client.h"
#include "Classes/MainScene.h"
#include <vector>

using std::string;
using std::vector;

namespace {//�����ռ�
	bool connectSuccess = false;//�Ƿ����ӳɹ�
	bool connecting = false;//��������
	bool canInput = true;//�������ӻ����Ѿ����ӳɹ��������ٴ�����ip
	int timer = 0;
	Client* client = nullptr;//�ͻ���
	Label* noteLabel = nullptr;//��Ϣ��ʾ��ǩ

	vector<Button*> buttons;
	Size visibleSize;
}

bool WaitingScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	ScenePool::preScene = this;

	visibleSize = Director::getInstance()->getVisibleSize();
	auto background = Sprite::create("scene/waiting.jpg");
	this->addChild(background);
	background->setAnchorPoint(cocos2d::Vec2::ZERO);


	//��ǩ��ʼ��
	noteLabel = Label::create();
	noteLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.9));
	this->addChild(noteLabel);
	

//----------
	//����ͼƬ
	auto roomlistbg = Sprite::create("scene/roomlist.jpg");
	this->addChild(roomlistbg);
	roomlistbg->setScale(2.0f);
	roomlistbg->setPosition(visibleSize.width * 0.8f, visibleSize.height*0.5f);

	auto refreshButton = Button::create("scene/input.png");
	this->addChild(refreshButton);
	refreshButton->setPosition(Vec2(visibleSize.width*0.8f, visibleSize.height*0.1));
	refreshButton->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type) {
		if (Widget::TouchEventType::ENDED == type)
		{
			refresh();
		}
	});
	refreshButton->setTitleText("refresh!");

	//�״�ˢ�·����б�
	refresh();
//----------

	//һ������ip�Ĵ��� + һ��ȷ�����ӵİ�ť
	_inputIpWindow = cocos2d::ui::TextField::create("  ", "Arial", 7);
	_inputIpWindow->setMaxLengthEnabled(true);
	_inputIpWindow->setMaxLength(15);//ipv4��ַ�Ϊ15
	_inputIpWindow->setTouchSize(Size(200, 60));
	_inputIpWindow->setTouchAreaEnabled(true);
	_inputIpWindow->setPosition(Point(visibleSize.width / 4, visibleSize.height / 2));
	
	//����ʵ��
	auto realWindow = Sprite::create("scene/InputBar.png");
	realWindow->setPosition(Point(visibleSize.width / 4, visibleSize.height / 2));

	this->addChild(_inputIpWindow, 2);
	this->addChild(realWindow, 1);

	//�س�����
	auto enterButton = Button::create("scene/enter.png");
	enterButton->setScale(0.6f);
	this->addChild(enterButton);
	enterButton->setPosition(Point(visibleSize.width / 4, visibleSize.height / 2 - 50));
	//enterButton->setTitleText("enter");
	enterButton->setTitleFontSize(7);
	enterButton->addTouchEventListener(CC_CALLBACK_2(WaitingScene::EnterHandle, this));

	scheduleUpdate();

	return true;
}//init

void WaitingScene::refresh()
{
	for (auto& button : buttons)
	{
		button->setVisible(false);
		this->removeChild(button, true);
	}
	buttons.clear();

	Client::lanSearch();
	auto roomlist = Client::getRoomlist();
	float width = 4 * visibleSize.width / 5, height = visibleSize.height*0.7f;
	for (const auto& item : roomlist)
	{
		auto button = Button::create("scene/input.png");
		button->setPosition(Vec2(width, height));
		buttons.push_back(button);
		height += 90;
		this->addChild(button);
		button->setTitleText(item.first);
		button->addTouchEventListener([=](Ref* pSender,
			cocos2d::ui::Widget::TouchEventType type) {
			if (cocos2d::ui::Widget::TouchEventType::ENDED == type && canInput)
			{
				client = Client::create(item.second);
				this->addChild(client);

				canInput = false;
				connecting = true;
				notice(Notice::CONNECT_TRY);
			}
		});
	}
}

void WaitingScene::update(float delta)
{
	if (connecting)
	{
		if (++timer <= 120)
		{
			if (timer < 50)return;//��Ҫ�Ｑ
			
			if (client->isConnected())
			{
				connecting = false;
				connectSuccess = true;
				notice(Notice::CONNECT_SUCCESS);
				client->sendMessage("Client is ready");//������Բ�����
			}
			
		}
		else {
			canInput = true;
			connecting = false;
			connectSuccess = false;
			notice(Notice::CONNET_FAIL);

			this->removeChild(client, true);
			client = nullptr;
		}
	}
	else if(timer != 0){
		//ȷ��ÿ�ο�ʼ����timer����0
		timer = 0;
	}
	
	if (connectSuccess)
	{
		if (client->isStart())
		{
			auto transiton = TransitionSlideInL::create(2.f, MainScene::create(client));
			Director::getInstance()->pushScene(transiton);
		}
	}
}

void WaitingScene::EnterHandle(Ref* pSender, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED && canInput) {
		string ip = _inputIpWindow->getString();
		_inputIpWindow->setString("");//�ÿ�

		if (!isIpValid(ip))
		{
			notice(Notice::VALID_IP);
			return;
		}

		client = Client::create(ip);
		this->addChild(client);


		canInput = false;
		connecting = true;
		notice(Notice::CONNECT_TRY);
	}
}

void WaitingScene::notice(Notice type)
{
	static string infos[10] = {
		"Connecting, be patient.",
		"Wow, Connect Success! Just wait for game start",
		"Emmm, Connect Failed~, try again",
		"Valid ip! try again",
	};
	noteLabel->setString(infos[type]);
}

bool WaitingScene::isIpValid(const string& ip)
{
	for (int size_ = ip.size();size_ > 0;--size_)
	{
		if ((ip[size_ - 1]<'0' || ip[size_ - 1]>'9') && ip[size_ - 1] != '.')
			return false;
	}

	int pointCount = 0;
	int beginPos, endPos;
	for (beginPos = 0, endPos = ip.find('.');
		endPos!=string::npos;
		beginPos = endPos + 1, endPos = ip.find('.', endPos + 1))
	{
		++pointCount;
		if (!isPartOfIp(ip.substr(beginPos, endPos - beginPos)))
		{
			return false;
		}
	}
	if (!isPartOfIp(ip.substr(beginPos)))
		return false;
	return pointCount == 3;
}

bool WaitingScene::isPartOfIp(const string& str)
{
	int num;
	sscanf(str.c_str(), "%d", &num);

	return 0 <= num && 255 >= num
		&& str.size() < 4;
}