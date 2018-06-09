#pragma once

#include "cocos2d.h"
#include <vector>
#include <algorithm>//for heap
#include "GridMap.h"

using std::vector;
USING_NS_CC;

static const int DIRECTIONS[8][2] =
{ { -1,-1 },{ -1,0 },{ -1,1 },{ 0,-1 },{ 0,1 },{ 1,-1 },{ 1,0 },{ 1,1 } };

class PathFinder {
	static const int DISTANCE0 = 10;
	static const int DISTANCE1 = 14;

	static const int DIRECTION_NUM = 8;
	

private:
	struct grid {//��ΪPathFinder���ڲ�ʵ��
		static const int MAX_VALUE = (1 << 31) - 1;

		grid(int x = -1, int y = -1):
			x(x),y(y),state(UNOCCUPIED),fValue(MAX_VALUE),
			gValue(MAX_VALUE),hValue(MAX_VALUE),
			parent(nullptr){}


		//��������
		int x, y;

		enum State {
			INOPENLIST = 0,
			INCLOSELIST,
			START,
			END,
			OCCUPIED,
			UNOCCUPIED
		};

		State state;

		int fValue;//�����õ����Ȩֵ
		int gValue;//��㵽�õ�Ĺ���Ȩֵ
		int hValue;//�õ㵽�յ�Ĺ���Ȩֵ�������پ�����Ϊ��������

		grid* parent;

	
	};

	int _mapWidth, _mapHeight;

	//const vector<vector<int> >& _gridTable;//��������ͼ�Ƿ�ռ��
	vector<Grid> _resultPath;

	grid *_start, *_end;

	vector<vector<grid> > _gridTable;//����

	
	vector<grid*> _openList;//maybe use heap to make PA better

public:
	vector<Grid> getPath();
	PathFinder(const vector<vector<int> > &gridTable,
		const Grid& start, const Grid& end);
	bool searchPath();
	void generatePath();

private:
	bool isGridValid(const grid* g);

	void setState(grid* g, grid::State state);

	grid* nextToSearch();

	bool isInOpenList(const grid* g);
	bool isInCloseList(const grid* g);
	//remove from open list and make the state to be INCLOSELIST
	void removeFromOpenList(grid* g/**/);

	//����ǰ���㵽��ǰ��Ĺ���ֵ
	int calculateGValue(const grid* parent, const grid* cur);
	//��ǰ�㵽�յ�Ĺ���ֵ
	int calculateHValue(const grid* cur, const grid* end);

	void checkSurroundGrid(const grid* pg);

	/*�������ĸ�������һ�������Σ��ڴ˹涨���Խǵ�����������һ��ΪOCCUPIED��
	ʣ�µ��������޷����ӣ�����false*/
	bool checkCorner(const grid* rhs, const grid* lhs);
};