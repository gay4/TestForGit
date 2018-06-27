#pragma once

/*����ͼ�࣬��ͼ��ʵ���߼����ڴ˻���Grid������㣬���������������͵�Point*/

#include "cocos2d.h"
#include <vector>
#include <cassert>

using std::vector;
USING_NS_CC;

//��㣬������Ϸ���ж�λ�õ�ռ��
struct Grid {
	int _x;//�����꣬���Ͻ�Ϊԭ��
	int _y;

	Grid(int x = -1, int y = -1):_x(x),_y(y){}
};

bool operator==(const Grid& lhs, const Grid& rhs);

Grid operator+(const Grid& lhs, const Grid&rhs);

Grid operator-(const Grid& lhs, const Grid&rhs);

//GridMap������ϵ��TiledMap��ͬ
class GridMap:public cocos2d::Node {
private:
	int _mapWidth, _mapHeight;//����ͼ�ĳ���
	float _gridWidth, _gridHeight;//ÿ����������

	bool initWithTiledMap(TMXTiledMap* tileMap);//�ø����͵�map��ʼ��

	
	Vec2 _pointOffset;//�����ĵ���ȡ���ƫ�ƣ���������int������ɵ�

	void occupyGrid(int id, const Grid& g);//ռ�����ʵ�ʹ�����
public:

	vector<vector<int> > _isOccupied;//�Ƿ�ռ�ݣ����effective stl�в���vector<bool>
	vector<vector<int> > _occupiedId;//ռ�ݶ�Ӧλ�õ�id

	static GridMap* create(TMXTiledMap* tileMap);
	bool isGridInMap(const Grid& g);//�ж��Ƿ��ڵ�ͼ��
	//bool isPointOccupied(const Point& p);
	bool isGridOccupied(const Grid& g);//����ռ�췵��1

	bool tryToOccupyGrid(int id, const Grid& g);//id��λ����ռ��ĳλ�ã�ռ��ɹ�����true
	void leaveGrid(int id, const Grid& g);//id�뿪��ǰ���
	
	typedef vector<Grid> GridVector;

	//��ѰP�㸽�����еĵ㣬����һ����СΪsize������
	GridVector findValidGridsNear(const Grid& p, int size);

	//��ѰP�㸽�����еĵ�
	Grid findValidGridNear(const Grid& p);

	//����任��ע����������ķ����ѵ���ƫ����
	Point getPoint(const Grid& g);
	Grid getGrid(const Point& p);

	bool isGridValid(const Grid& g);
	bool isAreaValid(const GridVector& area);

	//����size�����ĵ�õ���Ӧ��Χ�ĸ������
	GridMap::GridVector getArea(const Size& size, const Point& pos);
	//��������ռ��
	void setAreaOccupied(const GridVector& area);
	//�������ռ�ݵ��߼�
	void setAreaValid(const GridVector& area);

	void setGridOccupied(const Grid& grid);

	void setGridValid(const Grid& grid);
};

