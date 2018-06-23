#include "UnitManager.h"
#include <utility>//for make_pair
//#include "GridMap.h"
#include "RealUnit.h"
#include "MainScene.h"
#include "Messagetransfer/Encoder.h"
#include "Messagetransfer/Decoder.h"
#include "Scenes/EndScene.h"

class MainScene;

UnitManager* UnitManager::createWithScene(MainScene* mainScene)
{
	UnitManager* ret = new UnitManager();
	if (ret&&ret->initWithScene(mainScene))
	{
		ret->autorelease();
		return ret;
	}

	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool UnitManager::initWithScene(MainScene* mainScene)
{
	_client = mainScene->_client;
	_tiledMap = mainScene->_tiledMap;
	_gridMap = mainScene->_gridMap;
	_controlPanel = mainScene->_controlPanel;
	_notice = mainScene->_notice;
	_goldLabel = mainScene->_goldLabel;
	_powerLabel = mainScene->_powerLabel;

	//----------//
	_displayValueLabel[0] = mainScene->_displayValueLabel[0];
	_displayValueLabel[1] = mainScene->_displayValueLabel[1];

	assert(_displayValueLabel[0] != nullptr);
	assert(_displayValueLabel[1] != nullptr);
	//----------//

	assert(_client != nullptr);
	assert(_tiledMap != nullptr);
	assert(_gridMap != nullptr);
	assert(_controlPanel != nullptr);
	assert(_notice != nullptr);
	assert(_goldLabel != nullptr);
	assert(_powerLabel != nullptr);

	//_playerId = 0;//������˴��ø�
	//_nextId = _playerId + MAX_PLAYER_NUM;

	return true;
}

//����
bool UnitManager::init()
{
	_playerId = 0;
	_nextId = _playerId;


	return true;
}

bool UnitManager::hasSelectIdNow()
{
	return !_selectId.empty();
}

void UnitManager::selectUnitByRect(const Rect& rect)
{
	assert(_gridMap != nullptr);

	if (rect.getMaxX()==rect.getMinX())//��������ǿ�ѡ
	{
		selectUnitByPoint(Point(rect.getMinX(), rect.getMinY()));
		return;
	}

	if (hasSelectIdNow())
	{
		//���¿�ѡ
		abandonSelectedId();
	}

	//��ѡ�е�λʱ��ѡ
	selectId(rect);
}

void UnitManager::selectBuilding(Unit* building)
{
	Building* camp = dynamic_cast<Building*>(building);
	assert(camp != nullptr);
	
	camp->localCreateUnit();
}

void UnitManager::selectUnitByPoint(const Point& point)
{
	//���û��ѡ�еĵ�λ
	if (!hasSelectIdNow())
	{
		for (auto &item : _getUnitById)
		{
			if (isOurBro(item.first) &&
				item.second->getBoundingBox().containsPoint(point))
			{
				if (item.second->isBuilding())
				{
					selectBuilding(item.second);
					return;
				}

				selectOneUnit(item.first);//ѡ��һ����λ������
				return;
			}
		}
	//��ǰû��ѡ�в��Ҵ˴ε����ĵ㲻���Լ��ĵ�λ��ֱ�ӷ���
		return;
	}

	//���Ƶ�������һ���е�λ�Ѿ���ѡ��
	for (auto& item : _getUnitById)
	{
		//�ез������ҷ��ĵ�λ��ѡ��
		if (item.second->getBoundingBox().containsPoint(point))
		{
			if (isOurBro(item.first))
			{
				abandonSelectedId();
				
				if (item.second->isBuilding())//ѡ�н���
				{
					selectBuilding(item.second);
					return;
				}
				selectOneUnit(item.first);//ѡ��һ����λ������
				return;
			}
			else {//�з���λ������
				//!!!-----��δʵ��ѡ�ез����߼�-----!!!//
				for (auto id : _selectId)
				{
					if (_getUnitById.count(id) == 0)
					{
						continue;
					}
					//auto unit = _getUnitById.at(id);
					
					//assert(unit != nullptr);
					Encoder encoder("p", id);
					std::string msg = encoder.encodeAttack(item.first);
					_client->sendMessage(msg);
					
				}

				return;
			}
		}
	}


	//��������е�λ��֮ǰ�Ŀ�ѡ��ѡ�У��ñ�ѡ�еĵ��������
	auto destPoint = point;//dest grid
	auto destGrid = _gridMap->getGrid(destPoint);

	//find valid grid around dest depend on size
	int size = _selectId.size();
	GridMap::GridVector gridVector = _gridMap->findValidGridsNear(destGrid, size);

	//ȷ�Ϸ������㹻�������
	assert(gridVector.size() == size);

	for (int id : _selectId)
	{
		auto pUnit = _getUnitById[id];
		if (pUnit == nullptr)
		{
			continue;//��λ�����Ѿ���ɾ��
		}

		auto path = pUnit->getPath(gridVector[--size]);//->>>>>>>>>������Ļ���
		Encoder encoder("m", id);
		string message = encoder.encodePath(path);
		_client->sendMessage(message);//id,path

	}

}

void UnitManager::selectId(const Rect& rect)
{
	for (const auto&idWithUnit : _getUnitById)
	{
		if (isOurBro(idWithUnit.first) && //�Լ��˲����п���Ȩ
			rect.containsPoint(idWithUnit.second->getPosition())&&
			!idWithUnit.second->isBuilding())//����������ѡ
		{
			selectOneUnit(idWithUnit.first);
		}
	}
}

void UnitManager::selectOneUnit(int id)
{
	_selectId.push_back(id);
	_getUnitById[id]->setOpacity(200);
}

void UnitManager::localCreateUnit(int type, const Point& point)
{
	//!!!--------�Ӹ��жϲ���pointѡȡ���ϰ���֮��--------!!!//
	auto createGrid = _gridMap->getGrid(point);
	//auto nearValidGrid = _gridMap->findValidGridNear(createGrid);

	int id = getNextId();

	//����type,id,position����Ϣ���ͻ���
	Encoder encoder("c", id);
	std::string createMsg = encoder.encodeCreate(type, createGrid);
	_client->sendMessage(createMsg);
}

void UnitManager::createUnit(int id, int type, const Grid& createGrid)
{
	if (type > Unit::Type::FIGHTER)
	{
		//�������Ŷ���
		displayAnimate(_gridMap->getPoint(createGrid));
	}

	auto sequence = Sequence::create(
		DelayTime::create(2.0f),
		CallFunc::create([=] {
		createUnit_(id, type, createGrid);//ת��
	}),
		NULL
		);

	runAction(sequence);
}

void UnitManager::createUnit_(int id, int type, const Grid& createGrid)
{
	Unit* unit = nullptr;
	switch(type)
	{
	case Unit::Type::TANK: {
		unit = Tank::create(id);
		break;
	}
	case Unit::Type::SOILDER: {
		unit = Soldier::create(id);
		break;
	}
	case Unit::Type::SOLDIERCAMP: {
		unit = SoldierCamp::create(id);
		break;
	}
	case Unit::Type::BASE: {
		unit = Base::create(id);
		break;
	}
	case Unit::Type::FIGHTER: {
		unit = Fighter::create(id);
		break;
	}
	case Unit::Type::FACTORY: {
		unit = Factory::create(id);
		break;
	}
	case Unit::Type::ELECTRICITYFACTORY: {
		unit = ElectricityFactory::create(id);
		break;
	}
	case Unit::Type::MINE: {
		unit = Mine::create(id);
		break;
	}
	default:
		assert(0);//���Ʋ�Ӧ�õ�������
		break;
	}
	

	unit->setPosition(_gridMap->getPoint(createGrid));
	unit->addToMap(_gridMap, _tiledMap);//ע��setPosition��addToMap���Ⱥ�˳���¹�Building

	unit->setManager(this);
	unit->setId(id);

	_getUnitById.insert(std::make_pair(id, unit));

	unit->setProperties();
}

void UnitManager::displayAnimate(Point pos)
{
	auto creation = AnimationCache::getInstance()->getAnimation("create");

	auto animate = Animate::create(creation);
	//auto repeat = Repeat::create(animate, 2.f / 2 + 1);

	auto animationSprite = Sprite::createWithSpriteFrameName("animate1.png");
	_tiledMap->addChild(animationSprite, 10);
	animationSprite->setPosition(pos);


	Sequence* seq = Sequence::create(animate, RemoveSelf::create(true), NULL);
	animationSprite->runAction(seq);
}

void UnitManager::deleteUnit(int id)
{
	if (_getUnitById.count(id) == 0)
	{
		return;
	}
	auto unit = _getUnitById.at(id);
	assert(unit != nullptr);

	if (unit->isBuilding())//������Ҫȥ�����ڸ���ͼռλ���߼�
	{
		auto area = unit->getOccupiedArea();//��ȡռ������
		_gridMap->setAreaValid(area);//����������bool�߼�����Ϊ0

		if (unit->_id < 4 && unit->_id >= 0)//��...���ǻ��ص�����
		{
			if (unit->_id == _playerId)
			{
				notice("Loser!");//loser
				//�л�����
				auto transiton = TransitionSlideInL::create(2.f, EndScene::createScene(false));
				Director::getInstance()->replaceScene(transiton);
			}
			else if (++_loserNum == _playerNum - 1)//�޵��Ƕ�ô��ô�ؼ�į
			{
				notice("Winner!");//winner
				auto transiton = TransitionSlideInL::create(2.f, EndScene::createScene(true));
				Director::getInstance()->replaceScene(transiton);
			}
		}
	}
	_tiledMap->removeChild(unit->_hp,true);
	_tiledMap->removeChild(unit, true);
	_getUnitById.erase(id);
	
}
void UnitManager::deleteUnit(Unit* unit)
{
	assert(unit != nullptr);

	int id = getIdByUnit(unit);
	if (id == -1)//�����ڸ�Unit
	{
		return;
	}
	deleteUnit(id);
}

int UnitManager::getNextId()
{
	int retId = _nextId;

	_nextId += MAX_PLAYER_NUM;

	return retId;
}

void UnitManager::abandonSelectedId()
{
	for (int id : _selectId)
	{
		//ԭʼ͸������255
		_getUnitById[id]->setOpacity(255);
	}

	_selectId.clear();
}

bool UnitManager::isOurBro(int id)
{
	return id%MAX_PLAYER_NUM == _playerId;
}

void UnitManager::setPath(int id, GridMap::GridVector path)
{
	auto unit = _getUnitById[id];
	assert(unit != nullptr);

	unit->_gridPath = path;
}

void UnitManager::updateUnitState()
{
	//static bool startFlag = false;
	static bool imreadyFlag = false;

	string order = _client->getMessage();
	if (!_startFlag)//δ��ʼ
	{
		if (!imreadyFlag&&order[0] == 'I') {//Id(%d
			_playerId = order[3] - '1';
			_nextId = _playerId + MAX_PLAYER_NUM;
			imreadyFlag = true;
			//_client->sendMessage("Client ready!");

			return;
		}
		else if (order[0] == 'S')//Start!
		{
			_playerNum = order[7] - '0';
			initAllBase();
			_startFlag = true;
			notice(Notice::GAME_START);
			return;
		}
		return;
	}

	if (order[0] == 'n')//û����Ϣ
	{
		return;
	}


	Decoder decoder(order);
	int id = decoder.getId();

	switch (decoder.getType()) {
	case 't':
	case 'm': {
		auto path = decoder.decodePath();
		auto pUnit = _getUnitById[id];

		assert(pUnit != nullptr);

		if (path.empty())
		{
			break;
		}
		pUnit->setGridPath(path);

		pUnit->schedule(schedule_selector(Unit::update));

		if (decoder.getType() == 'm')
			pUnit->setState(Unit::MOVING);//����traceFlag��ȷ��״̬������

		break;
	}
	case 'a': {
		int targetId = decoder.decodeTargetId();
		
		if (_getUnitById.count(id) != 1)break;
		auto atker = _getUnitById[id];
		auto atkee = _getUnitById[targetId];
		atker->shoot(atkee);
		if (targetId == _playerId)
		{
			notice(Notice::BASE_ATTACKED);
		}
		if (unitMayDead(atkee))//Ϊ��ʱ��λ�ڴ˺�����ɾ��
		{
			atker->setTraceId(-1);
			atker->setState(Unit::WONDERING);
		}

		break;
	}
	case 'p': {
		int targetId = decoder.decodeTargetId();
		if (_getUnitById.count(id) != 1)break;
		auto unit = _getUnitById[id];

		unit->setTraceId(targetId);
		unit->_gridPath.clear();//�������
		unit->setState(Unit::TRACING);
		//unit->_timer = 59;//60-1
		
		break;
	}
	case 'c': {
		int type = decoder.decodeCreateType();
		auto grid = decoder.decodeCreateGrid();
		createUnit(id, type, grid);

		break;
	}
	case 'g': {//gossip
		std::string temp(decoder.decodeChat());
		
		_displayValueLabel[isLabelFree[0]^1]->setString(temp);
		isLabelFree[0] ^= 1;//���
		isLabelFree[1] ^= 1;

		break;
	}
	default:
		break;
	}
	
}

void UnitManager::update(float delta)
{
	updateLabel();//������Դ
	updateUnitState();
}

bool UnitManager::unitMayDead(Unit* attackee)
{
	if (attackee->_lifeValue < 0)
	{
		attackee->unschedule(schedule_selector(Unit::update));
		deleteUnit(attackee);
		return true;
	}
	return false;
}

int UnitManager::getIdByUnit(Unit* unit)
{
	for (auto& item : _getUnitById)
	{
		if (item.second == unit)
		{
			return item.first;
		}
	}

	return -1;//�õ�λ�Ѱݰ�
}

void UnitManager::initAllBase()
{
	assert(_playerNum > 0);
	for (int id = 0;id < _playerNum;++id)
	{
		createUnit_(id, Unit::Type::BASE, basePos[id]);
	}

	assert(_playerId >= 0 && _playerId < MAX_PLAYER_NUM);
	_basePos = basePos[_playerId];
}

bool UnitManager::canCreate(int type)
{
	return getGold() > costGold[type] &&
		getElectricity() > costElectricity[type];
}

void UnitManager::costForCreate(int type)
{
	_gold -= costGold[type];
	_electricity -= costElectricity[type];
}

void UnitManager::notice(Notice note)
{
	static std::string msg[10] = {
		"No enough money!",
		"Base is attacked!",
		"Position is occupied!",
		"Please wait!",
		"Relax, game hasn't been started.",
		"Start now!"
	};
	
	_notice->setVisible(true);
	_notice->setString(msg[note]);
	//��ʱ��ʧ
	auto sequence = Sequence::create(
		DelayTime::create(2.0f),
		CallFunc::create([=] {
		_notice->setVisible(false);
	}),
		NULL
		);
	runAction(sequence);
}

void UnitManager::notice(std::string note)
{
	_notice->setColor(Color3B::RED);
	_notice->setString(note);
}

void UnitManager::updateLabel()
{
	static int timer = 0;
	static char gold[20] = "";//����������
	static char power[20] = "";
	static std::string gold_;
	static std::string power_;


	if (++timer == 60)
	{
		timer = 0;
		sprintf(gold, "%d", _gold);
		sprintf(power, "%d", _electricity);
		gold_.assign(gold);
		power_.assign(power);

		_goldLabel->setString(gold_);
		_powerLabel->setString(power_);
	}
}