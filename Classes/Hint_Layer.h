#ifndef __HINT_LAYER__
#define __HINT_LAYER__

#include "cocos2d.h"

USING_NS_CC;

class HintLayer : public Layer
{
public:

	virtual bool init();
	CREATE_FUNC(HintLayer);

	//���콺 ������, ����
	void onMouseDown(cocos2d::Event* event);
	bool findHint(int hintNumber);
	bool HintLayerOnOff = false;
private:
	//������â��
	Sprite* HintWindow;
	Sprite* exit;

	//��Ʈ
	Sprite* map1Hint;
	Sprite* map2Hint;
	Sprite* map3Hint;
	Sprite* map4Hint;
	Sprite* map5Hint;
	Sprite* map6Hint;

	//��Ʈ Ȯ��
	Sprite* thiefExpand;
	Sprite* map1HintExpand;
	Sprite* map2HintExpand;
	Sprite* map3HintExpand;
	Sprite* map4HintExpand;
	Sprite* map5HintExpand;
	Sprite* map6HintExpand;
	//������ ū â y�߰��� �ö� ��ǥ
	const int ITEM_WINDOW_Y = 114;

	//������ â ��ǥ
	const int POINT_LONG_X1_LEFT = 214;
	const int POINT_LONG_X2_LEFT = 214;
	const int POINT_X = 0;
	const int POINT_LONG_X1_RIGHT = 212;
	const int POINT_LONG_X2_RIGHT = 213;
	const int POINT_Y1 = 143;
	const int POINT_Y2 = 139;

	//������ Rect
	const int ORIGIN_X1 = 248;
	const int ORIGIN_X2 = 462;
	const int ORIGIN_X3 = 674;

	const int ORIGIN_Y1 = 312;
	const int ORIGIN_Y2 = 595;

	const int THIEF_ORIGIN_X = 464;
	const int THIEF_ORIGIN_Y = 467;

	const int ITEM_WINDOW_SIZE_X = 100;
	const int ITEM_WINDOW_SIZE_Y = 120;
	const int THIEF_SIZE_X = 97;
	const int THIEF_SIZE_Y = 97;
	
	//exit Point
	const int EXIT_X = 240;
	const int EXIT_Y = 240;
	//exit Rect
	const int EXIT_RECT_X = 757;
	const int EXIT_RECT_Y = 258;
	const int EXIT_RECT_SIZE_X = 75;
	const int EXIT_RECT_SIZE_Y = 28;
	//��Ʈâ Ŀ��
	bool HintExpand = false;
	//�� ���� �Ǻ�
	bool Map1 = false;
	bool Map2 = false;
	bool Map3 = false;
	bool Map4 = false;
	bool Map5 = false;
	bool Map6 = false;
	//�� ��Ʈ ã��
	bool theifProfile = false;
	bool map1hintFind = false;
	bool map2hintFind = false;
	bool map3hintFind = false;
	bool map4hintFind = false;
	bool map5hintFind = false;
	bool map6hintFind = false;
};
#endif