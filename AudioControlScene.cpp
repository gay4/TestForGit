#include"AudioControlScene.h"
#include"ui/CocosGUI.h"
#include"SimpleAudioEngine.h"
#include"MenuScene.h"
USING_NS_CC;
using namespace ui;
using namespace CocosDenshion;

Scene* AudioControl::createScene()
{
	auto scene = Scene::create();
	auto layer = AudioControl::create();
	scene->addChild(layer);
	return scene;
}



char* EncodeToUTF81(const char* mbcsStr)
{
	wchar_t*  wideStr;
	char*     utf8Str;
	int       charLen;
	charLen = MultiByteToWideChar(936, 0, mbcsStr, -1, NULL, 0);
	wideStr = (wchar_t*)malloc(sizeof(wchar_t)*charLen);
	MultiByteToWideChar(936, 0, mbcsStr, -1, wideStr, charLen);
	charLen = WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, NULL, 0, NULL, NULL);
	utf8Str = (char*)malloc(charLen);
	WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, utf8Str, charLen, NULL, NULL);
	free(wideStr);
	return utf8Str;
}


bool::AudioControl::init()
{

	//���ø����init����

	if (!Layer::init())
	{
		return false;
	}

	//����豸�ɼ���ͼ��С

	Size visibleSize = Director::getInstance()->getVisibleSize();

	//�������ֱ�ǩ�ͻ��������
	//�������������֡��ı������Ϊ��ǰ����ӽڵ�

	auto music_text = Text::create(EncodeToUTF81("��������"), "Arial", 32);
	music_text->setPosition(Vec2(visibleSize.width*0.25, visibleSize.height*0.7));
	this->addChild(music_text);

	//����һ��������

	auto music_slider = Slider::create();

	//���û�����������

	music_slider->loadBarTexture("sliderTrack.png");

	//���û������Ĺ�������

	music_slider->loadSlidBallTextures("sliderThumb.png", "sliderThumb.png", "");

	//���ô��������Ľ���������

	music_slider->loadProgressBarTexture("sliderProgress.png");
	music_slider->setScale(0.7);

	//����֮ǰ���õı�����������

	float musicPercent = UserDefault::getInstance()->getFloatForKey("musicPercent");

	//����ǵ�һ�ν������ó��������ñ������ֻ�����Ĭ�ϳ�ʼֵΪ100

	if (musicPercent == 0.0f)
	{
		musicPercent = 100.0f;
	}

	//���ñ������ֻ������ĳ�ʼֵ

	music_slider->setPercent(musicPercent);
	music_slider->setPosition(Vec2(visibleSize.width*0.6, visibleSize.height*0.7));

	//����¼�������������������������

	music_slider->addEventListener([=](Ref* pSender, Slider::EventType type)
	{

		//������İٷֱȷ����仯ʱ

		if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
		{

			//��û������ٷֱ�

			int percent = music_slider->getPercent();

			//���ñ�������ֵΪ�������ٷֱ�/100����ΪSlider�İٷֱ���1~100,��MusicVolume��ȡֵ��0.0~1.0

			SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(float(percent) / 100);

			//�洢���õı�������ֵ

			UserDefault::getInstance()->setFloatForKey("musicPercent", percent);
		}
	});
	this->addChild(music_slider);

	//��Ч������ǩ
	//��������Ч�������ı������Ϊ��ǰ����ӽڵ�
	auto sound_text = Text::create(EncodeToUTF81("��Ч����"), "Arial", 32);
	sound_text->setPosition(Vec2(visibleSize.width*0.25, visibleSize.height*0.5));
	this->addChild(sound_text);

	//����һ��������

	auto effects_slider = Slider::create();

	//���û�����������

	effects_slider->loadBarTexture("sliderTrack.png");

	//���û������Ĺ�������

	effects_slider->loadSlidBallTextures("sliderThumb.png", "sliderThumb.png", "");

	//���ô��������Ľ���������

	effects_slider->loadProgressBarTexture("sliderProgress.png");

	//��ȡ֮ǰ���õ���Ч����

	float effectPercent = UserDefault::getInstance()->getFloatForKey("effectPercent");

	//����ǵ�һ�ν������ó�����������Ч������Ĭ�ϳ�ʼֵΪ100

	if (effectPercent == 0.0f)
	{
		effectPercent = 100.0f;
	}

	//������Ч�������ĳ�ʼֵ

	effects_slider->setPercent(effectPercent);
	effects_slider->setPosition(Vec2(visibleSize.width*0.6, visibleSize.height*0.5));
	effects_slider->setScale(0.7);

	//���ʱ���������������Ч����

	effects_slider->addEventListener([=](Ref* pSender, Slider::EventType type)
	{

		//������İٷֱȷ����仯ʱ

		if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
		{

			//��û������ٷֱ�

			int percent = effects_slider->getPercent();

			//���ñ�����Чֵ

			SimpleAudioEngine::getInstance()->setEffectsVolume(float(percent) / 100);

			//�洢���õı�������ֵ

			UserDefault::getInstance()->setFloatForKey("effectPercent", percent);
		}
	});
	this->addChild(effects_slider);

	//����������"��ť�����ʱ����returnMenu����

	auto return_button = Button::create("b1.jpg");
	return_button->setPosition(Vec2(visibleSize.width - return_button->getContentSize().width / 2*0.1, return_button->getContentSize().height / 2*0.1));
	return_button->setScale(0.1);
	return_button->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{

			//�л���MenuScene����

			auto transition = TransitionSlideInL::create(2.0, GameMenu::createScene());
			Director::getInstance()->replaceScene(transition);
		}
	});
	this->addChild(return_button);

	//����

	auto banner_text = Text::create(EncodeToUTF81("�Ľ���"), "Arial-BoldMT", 32);
	banner_text->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.15));
	this->addChild(banner_text);
	return true;
}



