#include "UnitManager.h"
#include <utility>//for make_pair
//#include "GridMap.h"
#include "RealUnit.h"
#include "MainScene.h"
#include "Messagetransfer/Encoder.h"
#include "Messagetransfer/Decoder.h"
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

	assert(_client != nullptr);
	assert(_tiledMap != nullptr);
	assert(_gridMap != nullptr);

	_playerId = 0;//������˴��ø�
	_nextId = _playerId;

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
				selectOneUnit(item.first);//ѡ��һ����λ������
				return;
			}
			else {//�з���λ������
				//!!!-----��δʵ��ѡ�ез����߼�-----!!!//
				for (auto id : _selectId)
				{
					assert(_getUnitById.count(id) == 1);
					auto unit = _getUnitById.at(id);
					
					assert(unit != nullptr);
					Encoder encoder("p", id);
					std::string msg = encoder.encodeAttack(item.first);
					_client->sendMessage(msg);
					//unit->setTraceId(item.first);
					//unit->setGridPath(GridMap::GridVector());//�ÿո��·������
					//unit->_gridPath.clear();//�������
					//unit->setState(Unit::TRACING);
					//>>>>>>>>>>>>>>>>>>>>>>send traceMessage 
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

		if(0)
		{
			string order = _client->getMessage();
			while(order[0] == 'y' || order[0] == 'c'||order[0]=='n') {
				order = _client->getMessage();
			}
			Decoder decoder(order);
			Encoder test("m", decoder.getId());
			auto dpath = decoder.decodePath();
			string testmsg = test.encodePath(dpath);
			testmsg.push_back('T');

			_client->sendMessage(testmsg);
		}

		if(0)//��û������Ŷ
		{
			pUnit->setState(Unit::WONDERING);
			pUnit->setDestination(gridVector[size]);

			pUnit->findPath();
			pUnit->schedule(schedule_selector(Unit::update));

			pUnit->setState(Unit::MOVING);
		}
	}

	
}

void UnitManager::selectId(const Rect& rect)
{
	for (const auto&idWithUnit : _getUnitById)
	{
		if (isOurBro(idWithUnit.first) && //�Լ��˲����п���Ȩ
			rect.containsPoint(idWithUnit.second->getPosition()))
		{
			selectOneUnit(idWithUnit.first);
		}
	}
}

void UnitManager::selectOneUnit(int id)
{
	_selectId.push_back(id);
	_getUnitById[id]->setOpacity(100);
}

void UnitManager::localCreateUnit(int/* type*/, const Point& point)
{
	//!!!--------�Ӹ��жϲ���pointѡȡ���ϰ���֮��--------!!!//
	auto createGrid = _gridMap->getGrid(point);
	auto nearValidGrid = _gridMap->findValidGridNear(createGrid);

	int id = getNextId();

	//����type,id,position����Ϣ���ͻ���
	_client->sendMessage("create a unit");
}

void UnitManager::createUnit(int id, int type, const Grid& createGrid)
{
	//����type��playerIdѡȡ��ӦͼƬ
	auto unit = Tank::create("tank.png");

	unit->addToMap(_gridMap, _tiledMap);
	unit->setPosition(_gridMap->getPoint(createGrid));
	unit->setManager(this);
	unit->setId(id);

	_getUnitById.insert(std::make_pair(id, unit));

	unit->setProperties();
}

void UnitManager::deleteUnit(int id)
{
	auto unit = _getUnitById.at(id);
	assert(unit != nullptr);

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
	static bool startFlag = false;
	static bool imreadyFlag = false;

	string order = _client->getMessage();
	if (!startFlag)//δ��ʼ
	{
		if (!imreadyFlag&&order[0] == 'I') {//Id(%d
			_playerId = order[3] - '1';
			imreadyFlag = true;
			_client->sendMessage("Client ready!");
			return;
		}
		else if (order[0] == 'S')//Start!
		{
			startFlag = true;
			return;
		}
		return;
	}

	if (order[0] == 'n')//û����Ϣ
	{
		return;
	}
	
	Decoder decoder(order);	
	
	switch (decoder.getType()) {
	case 't':
	case 'm': {
		int id = decoder.getId();
		auto path = decoder.decodePath();
		auto pUnit = _getUnitById[id];

		assert(pUnit != nullptr);	

		//pUnit->setState(Unit::WONDERING);
		pUnit->setGridPath(path);
		
		pUnit->schedule(schedule_selector(Unit::update));

		if(decoder.getType()=='m')
			pUnit->setState(Unit::MOVING);//����traceFlag��ȷ��״̬������
		
		break;
	}
	case 'a': {
		int id = decoder.getId();
		int targetId = decoder.decodeTargetId();
		/*Encoder encoder("a", id);
		auto msg = encoder.encodeAttack(targetId);
		msg.append("T");
		_client->sendMessage(msg);*/
		if (_getUnitById.count(id) != 1)break;
		auto atker = _getUnitById[id];
		auto atkee = _getUnitById[targetId];
		atker->shoot(atkee);
		if (unitMayDead(atkee))//Ϊ��ʱ��λ�ڴ˺�����ɾ��
		{
			atker->setTraceId(-1);
			atker->setState(Unit::WONDERING);
		}

		break;
	}
	case 'p': {
		int id = decoder.getId();
		int targetId = decoder.decodeTargetId();
		if (_getUnitById.count(id) != 1)break;
		auto unit = _getUnitById[id];

		unit->setTraceId(targetId);
		unit->_gridPath.clear();//�������
		unit->setState(Unit::TRACING);
		//>>>>>>>>>>>>>>>>>>>>>>send traceMessage 
		break;
	}
	case 'c': {
		
		break;
	}
	default:
		break;
	}
}

void UnitManager::update(float delta)
{
	updateUnitState();
}

bool UnitManager::unitMayDead(Unit* attackee)
{
	if (attackee->_lifeValue < 0)
	{
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