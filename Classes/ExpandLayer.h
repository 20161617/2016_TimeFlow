#ifndef __EXPAND_LAYER_H__
#define __EXPAND_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class ExpandMenuLayer : public Layer
{
public:

	virtual bool init();
	
	CREATE_FUNC(ExpandMenuLayer);
	bool ExpandMenuLayer::MapItemEvents(int level, int itemNumber);
	bool ExpandMenuLayer::KnowMapLevel(int MapLevel);

	//���콺 ������, ����
	void onMouseDown(cocos2d::Event* event);
	void onMouseUp(cocos2d::Event* event);

	//������ ����
	void ExpandMenuLayer::knowMix(int itemNum);

	bool ExpandLayerOnOff = false;

	//������ūâ, ������ ����â
	Sprite* itemWindow;
	
	//������ map1
	Sprite* leftCarpetLetter;
	Sprite* bedLetter;
	//������ Ȯ��
	Sprite* leftCatpetLetterExpand;
	Sprite* bedLetterExpand;

	//������ map2
	Sprite* USB;
	Sprite* coin;

	//������ map3
	Sprite* cellphone;
	Sprite* puzzlePiece;
	Sprite* memo;
	Sprite* stick;
	Sprite* rubber;
	Sprite* hammer;

	//������ Ȯ��
	Sprite* cellphoneExpand;
	Sprite* puzzlePieceExpand;
	Sprite* memoExpand;

	//������ map4
	Sprite* jarMessage;
	Sprite* key;
	Sprite* needle;
	Sprite* cloth;
	Sprite* cotton;
	Sprite* cloth_2;
	Sprite* teddyHead;

	//������ Ȯ��
	Sprite* jarMessageExpand;

	//������ map5
	Sprite* knife;
	Sprite* shovelHead;
	Sprite* shovelTail;
	Sprite* drawerKey;
	Sprite* doorHandle;
	Sprite* shovel;

	//������ map5-1
	Sprite* drainCleaner;
	Sprite* message;
	Sprite* rag;
	Sprite* dice;
	Sprite* faucet;
	Sprite* key3;

	//������ Ȯ��
	Sprite* messageExpand;
	Sprite* diceExpand;

	//������ map6
	Sprite* pianoMessage;
	Sprite* frameMessage;
	Sprite* pianoKey;
	Sprite* map;

	//������ Ȯ��
	Sprite* pianoMessageExpand;
	Sprite* frameMessageExpand;
	Sprite* mapExpand;

	//�ڷΰ���
	Sprite* exit;

	//������ ū â y�߰��� �ö� ��ǥ
	const int ITEM_WINDOW_Y = 114;

	//������ â ��ǥ
	const int POINT_LONG_X_LEFT = 227;
	const int POINT_LONG_X_RIGHT = 229;
	const int POINT_X_LEFT = 75;
	const int POINT_X_RIGHT = 77;
	const int POINT_Y_UP = 104;
	const int POINT_Y_DOWN = 103;

	//������ Rect
	const int ORIGIN_X1 = 229;
	const int ORIGIN_X2 = 381;
	const int ORIGIN_X3 = 533;
	const int ORIGIN_X4 = 685;

	const int ORIGIN_Y1 = 326;
	const int ORIGIN_Y2 = 533;

	const int ITEM_WINDOW_SIZE_X = 114;
	const int ITEM_WINDOW_SIZE_Y = 134;

	const int MAX_SIZE_X = 1024;
	const int MAX_SIZE_Y = 768;
	//exit Point
	const int EXIT_X = 362;
	const int EXIT_Y = 498;
	//exit Rect
	const int EXIT_RECT_X = 874;
	const int EXIT_RECT_SIZE_X = 150;
	const int EXIT_RECT_SIZE_Y = 56;

	//Ȯ��â ���� ����
	bool expandOn = false;

	//MAP1
	bool leftCarpetItem = false;
	bool bedItem = false;
	bool leftCarpetExpandOn = false;
	bool bedExpandOn = false;

	//MAP2
	bool USBItem = false;
	bool coinItem = false;

	//MAP3
	bool stickItem = false;
	bool rubberItem = false;
	bool cellphoneItem = false;
	bool puzzlePieceItem = false;
	bool memoItem = false;
	bool hammerItem = false;

	bool cellphoneExpandOn = false;
	bool puzzlepieceExpandOn = false;
	bool memoExpandOn = false;

	//Map4
	bool jarMessageItem = false, keyItem = false, teddyHeadItem = false;
	bool needleItem = false, clothItem = false, cottonItem = false, cloth_2Item = false;

	bool jarMessageExpandon = false;

	//Map5
	bool knifeItem = false, drawerKeyItem = false, doorHandleItem = false, shovelItem = false;
	bool shovelHeadItem = false, shovelTailItem = false;

	//Map5_1
	bool drainCleanerItem = false, messageItem = false, ragItem = false;
	bool diceItem = false, faucetItem = false, key3Item = false;

	bool messageExpandOn = false, diceExpandOn = false;

	//Map6
	bool pianoMessageItem = false, frameMessageItem = false;
	bool pianoKeyItem = false, mapItem = false;

	bool pianoMessageExpandOn = false, frameMessageExpandOn = false, mapExpandOn = false;

	//������ ���� ������
	bool Map1 = false;
	bool Map2 = false;
	bool Map3 = false;
	bool Map4 = false;
	bool Map5 = false;
	bool Map5_1 = false;
	bool Map6 = false;
};

#endif