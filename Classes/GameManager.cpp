#include "GameManager.h"
#include "MainScene.h"

USING_NS_CC;

GameManager* GameManager::create(MainScene* mainScene)
{
	GameManager *gameManager = new GameManager();
	if (gameManager && gameManager->initWithScene(mainScene))
	{
		gameManager->autorelease();
		return gameManager;
	}
	CC_SAFE_DELETE(gameManager);
	return nullptr;
}

bool GameManager::initWithScene(MainScene* mainScene)
{
	_mainScene = mainScene;
	return true;
}
void GameManager::focusOnBase()
{
	float duration = 0.1;
	Vec2 position = Vec2(100, 100);      //�ݶ��Ļ��ص�λ��

	int x = MAX(position.x, _mainScene->_screenWidth / 2);
	int y = MAX(position.y, _mainScene->_screenHeight / 2);

	// ������ʾ���򳬳���ͼ�ı߽�

	x = MIN(x, (_mainScene->_tiledMap->getMapSize().width *
		_mainScene->_tiledMap->getTileSize().width - _mainScene->_screenWidth / 2));
	y = MIN(y, (_mainScene->_tiledMap->getMapSize().height *
		_mainScene->_tiledMap->getTileSize().height - _mainScene->_screenHeight / 2));

	// ʵ���ƶ���λ������
	Point actualPosition = Point(x, y);

	// ��Ļ����λ������
	Point centerOfView = Point(MainScene::_screenWidth / 2, MainScene::_screenHeight / 2);

	// ��������λ�ú�ʵ���ƶ���λ������֮��Ĳ�ֵ
	Point viewPoint = centerOfView - actualPosition;
	//Point viewPoint = position;
	this->_mainScene->_tiledMap->setPosition(viewPoint);

	// ����������Ļλ��
	//this->_mainScene->runAction(MoveTo::create(duration, viewPoint));
}
void GameManager::scrollMap()
{
	//��Ƭ��ͼ��λ��
	auto mapCenter = _mainScene->_tiledMap->getPosition();  

	auto visibleSize = Director::getInstance()->getVisibleSize();           
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//ˮƽ����ʹ�ֱ������ƶ��ٶȱ���
	int horizontalRate = 0, verticalRate = 0;                                        


	//�ж����x�����Ƿ������ұ�����
	if (origin.x + visibleSize.width - BOX_EDGE_WITDH_SMALL < _mainScene->_crusorPosition.x)
	{
		++horizontalRate;
	}

	//�ж����x�����Ƿ��ڴ��ұ�����
	if (origin.x + visibleSize.width - BOX_EDGE_WITDH < _mainScene->_crusorPosition.x)
	{
		++horizontalRate;
	}

	//�ж����x�����Ƿ������������
	if (origin.x + BOX_EDGE_WITDH_SMALL > _mainScene->_crusorPosition.x)
	{
		--horizontalRate;
	}

	//�ж����x�����Ƿ��ڴ��������
	if (origin.x + BOX_EDGE_WITDH > _mainScene->_crusorPosition.x)
	{
		--horizontalRate;
	}





		//�ж����y�����Ƿ������ϱ�����
	if (origin.y + visibleSize.height - BOX_EDGE_WITDH_SMALL < _mainScene->_crusorPosition.y)
	{
		++verticalRate;
	}

	//�ж����y�����Ƿ��ڴ��ϱ�����
	if (origin.y + visibleSize.height - BOX_EDGE_WITDH < _mainScene->_crusorPosition.y)
	{
		++verticalRate;
	}

	//�ж����y�����Ƿ������±�����
	if (origin.y + BOX_EDGE_WITDH_SMALL > _mainScene->_crusorPosition.y)
	{
		--verticalRate;
	}

	//�ж����y�����Ƿ��ڴ��±�����
	if (origin.y + BOX_EDGE_WITDH > _mainScene->_crusorPosition.y)
	{
		--verticalRate;
	}




	Vec2 scroll(0, 0);
	
	scroll += Vec2(-SCROLL_LENGTH, 0)*horizontalRate;
	scroll += Vec2(0, -SCROLL_LENGTH)*verticalRate;

	//�ƶ�����Ƭ��ͼ��λ��
	mapCenter += scroll;        

	//�ж��ƶ����Ƿ����
	if (_mainScene->_tiledMap->getBoundingBox().containsPoint((-scroll) + Director::getInstance()->getVisibleSize())
		&& _mainScene->_tiledMap->getBoundingBox().containsPoint(-scroll))

	//�ƶ���ͼ
		_mainScene->_tiledMap->setPosition(mapCenter);
}
