#pragma once
#include "cocos2d.h"
#include <vector>
#include <cassert>

using std::vector;
USING_NS_CC;

//��㣬������Ϸ���ж�λ�õ�ռ��
struct Grid {
	int _x;//�����꣬���Ͻ�Ϊԭ��
	int _y;

	Grid(int x, int y):_x(x),_y(y){}
};

bool operator==(const Grid& lhs, const Grid& rhs);

Grid operator+(const Grid& lhs, const Grid&rhs);

Grid operator-(const Grid& lhs, const Grid&rhs);

//GridMap������ϵ��TiledMap��ͬ
class GridMap:public cocos2d::Node {
private:
	int _mapWidth, _mapHeight;//����ͼ�ĳ���
	int _gridWidth, _gridHeight;//ÿ����������

	bool initWithTiledMap(TMXTiledMap* tileMap);//�ø����͵�map��ʼ��

	vector<vector<int> > _isOccupied;//�Ƿ�ռ�ݣ����effective stl�в���vector<bool>
	vector<vector<int> > _occupiedId;//ռ�ݶ�Ӧλ�õ�id
	Vec2 _pointOffset;//�����ĵ���ȡ���ƫ�ƣ���������int������ɵ�

	void occupyGrid(int id, const Grid& g);//ռ�����ʵ�ʹ�����
public:
	static GridMap* create(TMXTiledMap* tileMap);
	bool isGridInMap(const Grid& g);//�ж��Ƿ��ڵ�ͼ��
	//bool isPointOccupied(const Point& p);
	bool isGridOccupied(const Grid& g);//����ռ�췵��1

	bool tryToOccupyGrid(int id, const Grid& g);//id��λ����ռ��ĳλ�ã�ռ��ɹ�����true
	void leaveGrid(int id, const Grid& g);//id�뿪��ǰ���
	
	typedef vector<Grid> GridVector;

	//��ѰP�㸽�����еĵ㣬����һ����СΪsize������
	GridVector findValidGridNear(const Grid& p, int size);
	Grid findValidGridNear(const Grid& p);//��ѰP�㸽�����еĵ�

	Point getPoint(const Grid& g);//����任��ע����������ķ����ѵ���ƫ����
	Grid getGrid(const Point& p);

};

