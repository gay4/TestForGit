#include "Unit.h"
#include "PathFinder.h"
#include "NotGay.h"

Unit::Unit():Sprite(),
_state(WONDERING),
_moveSpeed(0),
_gridMap(nullptr){}

void Unit::addToMap(GridMap* gridMap, TMXTiledMap* _tiledMap)
{
	_gridMap = gridMap;

	_tiledMap->addChild(this, 5);
}

Unit* Unit::create(const std::string& filename)
{
	Unit *ret = new Unit();

	if (ret && ret->initWithFile(filename))
	{
		ret->autorelease();

		return ret;
	}

	CC_SAFE_DELETE(ret);

	return nullptr;
}

void Unit::setProperties()
{
	_state = Unit::State::WONDERING;

	_moveSpeed = 2;
}

void Unit::setGridPath(const GridMap::GridVector& path)
{
	_gridPath = path;

	//�ȶ�һ���յ�
	_curDest = _gridPath.back();
}

void Unit::setDestination(const Grid& g)
{
	_finalDest = g;
}

void Unit::findPath()
{
	assert(_gridMap->isGridInMap(_finalDest));

	PathFinder pathFinder(_gridMap->_isOccupied, _gridMap->getGrid(getPosition()), _finalDest);
	pathFinder.searchPath();
	pathFinder.generatePath();

	_gridPath = pathFinder.getPath();
}

void Unit::move()
{
	//assume that the path and finalDest is already sure
	//����������β��
	if (_gridPath.empty())
	{
		setState(WONDERING);
		_curDest = Grid(-1, -1);//set flag for next time to initialize curDest

		return;
	}

	auto destPos = _gridMap->getPoint(_curDest);

	//����
	auto dirVec = (destPos - getPosition()).getNormalized();
	//dirVec.normalize();//��λ��

	//��ǰ֡��ƫ����
	auto curMoveVec = dirVec * _moveSpeed;

	auto nextPos = curMoveVec + getPosition();

	if (!_gridMap->isGridInMap(_curDest)
		||willBeyondDest(getPosition(),destPos,curMoveVec))
	{
		//�ڴ˲�����Խ����Ϊspeed����32̫������
		setPosition(nextPos);

		_curDest = _gridPath.back();
		_gridPath.pop_back();

		return;
	}
	


	auto nextGrid = _gridMap->getGrid(nextPos);
	auto curGrid = _gridMap->getGrid(getPosition());
	

	if (nextGrid == curGrid)
	{
		setPosition(nextPos);
		return;
	}

	

	setPosition(nextPos);
}

void Unit::moveTest()
{
	if (_gridPath.empty())
		return;

	_curDest = _gridPath.back();
	_gridPath.pop_back();

	/*auto point = _gridMap->getPoint(_curDest);
	auto moveTo = MoveTo::create(5.0f, point + getParent()->getPosition());

	runAction(moveTo);*/
	setPosition(_gridMap->getPoint(_curDest));
}

void Unit::update(float delta)
{
	
	switch (_state) {
	case MOVING:
		moveTest();
		//move();
		break;
	default:
		break;
	}
}

void Unit::setState(Unit::State state)
{
	_state = state;
}