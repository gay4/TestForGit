#include "PathFinder.h"
#include <list>
//#include <algorithm>
using std::list;

PathFinder::PathFinder(const vector<vector<int> >&gridTable,
	const Grid& start, const Grid& end) :
	_mapWidth(gridTable.size()),_mapHeight(gridTable[0].size()),
	 _start(nullptr),
	_end(nullptr) {
	//初始化格点表
	_gridTable.assign(_mapWidth,
		vector<grid>(_mapHeight, grid()));
	//初始化起点终点指针
	_start = &_gridTable[start._x][start._y];
	_end = &_gridTable[end._x][end._y];
	//循环计算g值需要用到终点坐标，循环内会再计算一次终点的xy，无伤大雅
	//_start->x = start._x, _start->y = start._y;
	_end->x = end._x, _end->y = end._y;

	for (int i = 0; i < _mapWidth;++i)
	{
		for (int j = 0;i < _mapHeight;++i)
		{
			grid& rg = _gridTable[i][j];
			rg.x = i, rg.y = j;		

			rg.hValue = calculateHValue(&rg, _end);

			if (gridTable[i][j] == 1)//default state is UNOCCUPIED
			{
				setState(&rg, grid::OCCUPIED);
			}
		}
	
	}

	assert(_end != nullptr&&_start != nullptr);

	setState(_start, grid::State::START);
	setState(_end, grid::State::END);

	_start->gValue = 0;
	//_end->hValue = 0;//already calculated in the for loop
	//Initialize openlist
	_openList.push_back(_start);
}

bool PathFinder::isGridValid(const grid* pg)
{
	int x = pg->x, y = pg->y;

	if (x < 0 || x >= _mapWidth ||
		y < 0 || y >= _mapHeight)
	{
		return false;
	}

	grid::State state = _gridTable[x][y].state;
	return state != grid::OCCUPIED&&state != grid::INCLOSELIST;
}

void PathFinder::checkSurroundGrid(const grid* pg)
{
	for (int i = 0;i < DIRECTION_NUM;++i)
	{
		int x =pg->x + DIRECTIONS[i][0], y = pg->y + DIRECTIONS[i][1];

		//pointer to candidate grid
		grid* pcg = nullptr;
		pcg = &_gridTable[x][y];
		if (!isGridValid(pcg) || !checkCorner(pg, pcg))
		{
			continue;
		}
		//remember hValue of every grid has been calculated in PathFindther constructor
		int gValueByPg = calculateGValue(pg, pcg);
		if (gValueByPg < pcg->gValue)
		{
			pcg->parent = const_cast<grid*>(pg);
			pcg->gValue = gValueByPg;
			pcg->fValue = pcg->gValue + pcg->hValue;
		}
	
		if (!isInOpenList(pcg))
		{
			_openList.push_back(pcg);
			//flag
			setState(pcg, grid::INOPENLIST);
		}

		assert(pcg->parent != nullptr);
	}
}

bool PathFinder::checkCorner(const grid* lhs, const grid* rhs)
{
	if (lhs->x == rhs->x || lhs->y == rhs->y)
	{
		return true;
	}

	if (_gridTable[lhs->x][rhs->y] == grid::OCCUPIED ||
		_gridTable[rhs->x][lhs->y] == grid::OCCUPIED)
	{
		return false;
	}

	return true;
}

void PathFinder::setState(grid* g, grid::State state)
{
	g->state = state;
}

bool PathFinder::isInCloseList(const grid* g)
{
	return g->state == grid::INCLOSELIST;
}

bool PathFinder::isInOpenList(const grid*g)
{
	return g->state == grid::INOPENLIST;
}

void PathFinder::removeFromOpenList(grid* g)
{
	assert(g != nullptr);
	for (auto it = _openList.begin();it!=_openList.end();++it)
	{
		if (g != *it)
		{
			continue;
		}

		_openList.erase(it);
		setState(g, grid::INCLOSELIST);

		return;
	}
}

int PathFinder::calculateGValue(const grid* parent, const grid* cur)
{
	if (parent->x == cur->x ||
		parent->y == cur->y)
	{
		return DISTANCE0;//10
	}
	return DISTANCE1;//14
}

int PathFinder::calculateHValue(const grid*cur, const grid* end)
{
	return (abs(cur->x - end->x) + abs(cur->y - end->y))*DISTANCE0;//10
}

PathFinder::grid* PathFinder::nextToSearch()
{
	assert(!_openList.empty());

	grid* ret = _openList.front();

	for (auto pg : _openList)
	{
		if (pg->fValue > ret->fValue)
		{
			ret = pg;
		}
	}
	return ret;
}

vector<Grid> PathFinder::getPath()
{
	generatePath();

	return _resultPath;
}

void PathFinder::generatePath()
{
	grid* cur = _end;

	//call list for hlep through member cuncction reverse
	list<Grid> resultPathList;
	while (cur->parent != nullptr)//cur is not the FATHER
	{
		resultPathList.push_front(Grid(cur->x, cur->y));

		cur = cur->parent;
	}
	resultPathList.reverse();
	_resultPath.assign(resultPathList.begin(), resultPathList.end());
}

void PathFinder::searchPath()
{
	while (!_openList.empty())
	{
		grid* next = nextToSearch();
		if (next == _end)return;
		removeFromOpenList(next);
		checkSurroundGrid(next);
	}
}