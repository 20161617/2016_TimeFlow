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

	//마우스 누르기, 때기
	void onMouseDown(cocos2d::Event* event);
	void onMouseUp(cocos2d::Event* event);

	//아이템 변경
	void ExpandMenuLayer::knowMix(int itemNum);

	bool ExpandLayerOnOff = false;

	//아이템큰창, 아이템 작은창
	Sprite* itemWindow;
	
	//아이템 map1
	Sprite* leftCarpetLetter;
	Sprite* bedLetter;
	//아이템 확대
	Sprite* leftCatpetLetterExpand;
	Sprite* bedLetterExpand;

	//아이템 map2
	Sprite* USB;
	Sprite* coin;

	//아이템 map3
	Sprite* cellphone;
	Sprite* puzzlePiece;
	Sprite* memo;
	Sprite* stick;
	Sprite* rubber;
	Sprite* hammer;

	//아이템 확대
	Sprite* cellphoneExpand;
	Sprite* puzzlePieceExpand;
	Sprite* memoExpand;

	//아이템 map4
	Sprite* jarMessage;
	Sprite* key;
	Sprite* needle;
	Sprite* cloth;
	Sprite* cotton;
	Sprite* cloth_2;
	Sprite* teddyHead;

	//아이템 확대
	Sprite* jarMessageExpand;

	//아이템 map5
	Sprite* knife;
	Sprite* shovelHead;
	Sprite* shovelTail;
	Sprite* drawerKey;
	Sprite* doorHandle;
	Sprite* shovel;

	//아이템 map5-1
	Sprite* drainCleaner;
	Sprite* message;
	Sprite* rag;
	Sprite* dice;
	Sprite* faucet;
	Sprite* key3;

	//아이템 확대
	Sprite* messageExpand;
	Sprite* diceExpand;

	//아이템 map6
	Sprite* pianoMessage;
	Sprite* frameMessage;
	Sprite* pianoKey;
	Sprite* map;

	//아이템 확대
	Sprite* pianoMessageExpand;
	Sprite* frameMessageExpand;
	Sprite* mapExpand;

	//뒤로가기
	Sprite* exit;

	//아이템 큰 창 y추가로 올라간 좌표
	const int ITEM_WINDOW_Y = 114;

	//아이템 창 좌표
	const int POINT_LONG_X_LEFT = 227;
	const int POINT_LONG_X_RIGHT = 229;
	const int POINT_X_LEFT = 75;
	const int POINT_X_RIGHT = 77;
	const int POINT_Y_UP = 104;
	const int POINT_Y_DOWN = 103;

	//아이템 Rect
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

	//확대창 켜짐 유무
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

	//아이템 레벨 가르기
	bool Map1 = false;
	bool Map2 = false;
	bool Map3 = false;
	bool Map4 = false;
	bool Map5 = false;
	bool Map5_1 = false;
	bool Map6 = false;
};

#endif