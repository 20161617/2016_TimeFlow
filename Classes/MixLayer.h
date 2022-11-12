#ifndef __MIX_LAYER_H__
#define __MIX_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class ExpandMenuLayer;
class GameScene3;
class GameScene4;
class GameScene5;
class GameScene5_1;
class GameScene6;

class MixMenuLayer : public Layer
{
public:

	virtual bool init();

	ExpandMenuLayer* expandLayer;
	GameScene3* gameScene3;
	GameScene4* gameScene4;
	GameScene5* gameScene5;
	GameScene5_1* gameScene5_1;
	GameScene6* gameScene6;

	CREATE_FUNC(MixMenuLayer);

	bool MixMenuLayer::MapItemEvents(int itemNumber);
	bool MixMenuLayer::KnowMapLevel(int MapLevel);
	void MixMenuLayer::MixItems(int itemNum1, int itemNum2);

	//마우스 누르기, 때기
	void onMouseDown(cocos2d::Event* event);
	void onMouseUp(cocos2d::Event* event);

	bool MixLayerOnOff = false;

	//아이템창
	Sprite* mixWindow;

	//Map1
	Sprite* leftCarpetLetter;
	Sprite* bedLetter;
	int bedLetterNum = 100, leftCarpetNum = 101;
	bool leftCarpetItem = false, bedItem = false;

	//Map2
	Sprite* USB;
	Sprite* coin;
	int USBNum = 100, coinNum = 101;
	bool USBItem = false, coinItem = false;

	//Map3
	Sprite* stick;
	Sprite* rubber;
	Sprite* cellphone;
	Sprite* puzzlePiece;
	Sprite* memo;
	Sprite* hammer;
	int stickNum = NULL, rubberNum = NULL;
	int cellphoneNum = 100, puzzlePieceNum = 101, memoNum = 102, hammerNum = 103;
	bool stickItem = false, rubberItem = false;
	bool cellphoneItem = false, puzzlePieceItem = false, memoItem = false, hammerItem = false;

	//Map4
	Sprite* jarMessage;
	Sprite* key;
	Sprite* needle;
	Sprite* cloth;
	Sprite* cotton;
	Sprite* cloth_2;
	Sprite* teddyHead;
	int jarMessageNum = 100, keyNum = 101, teddyHeadNum = 102;
	int needleNum = NULL, clothNum = NULL, cottonNum = NULL, cloth_2Num = NULL;
	bool jarMessageItem = false, keyItem = false, teddyHeadItem = false;
	bool needleItem = false, clothItem = false, cottonItem = false, cloth_2Item = false;

	//Map5
	Sprite* knife;
	Sprite* shovelHead;
	Sprite* shovelTail;
	Sprite* drawerKey;
	Sprite* doorHandle;
	Sprite* shovel;
	int knifeNum = 100, drawerKeyNum = 101, doorHandleNum = 102, shovelNum = 103;
	int shovelHeadNum = NULL, shovelTailNum = NULL;
	bool knifeItem = false, drawerKeyItem = false, doorHandleItem = false, shovelItem = false;
	bool shovelHeadItem = false, shovelTailItem = false;

	//Map5_1
	Sprite* drainCleaner;
	Sprite* message;
	Sprite* rag;
	Sprite* dice;
	Sprite* faucet;
	Sprite* key3;
	int drainCleanerNum = 100, messageNum = 101, ragNum = 102, diceNum = 103;
	int faucetNum = 104, key3Num = 105;
	bool drainCleanerItem = false, messageItem = false, ragItem = false;
	bool diceItem = false, faucetItem = false, key3Item = false;

	//Map6
	Sprite* pianoMessage;
	Sprite* frameMessage;
	Sprite* pianoKey;
	Sprite* map;
	int pianoMessageNum = 100, frameMessageNum = 101;
	int pianoKeyNum = 102, mapNum = 103;
	bool pianoMessageItem = false, frameMessageItem = false;
	bool pianoKeyItem = false, mapItem = false;

	//아이템 큰 창 y추가로 올라간 좌표
	const int ITEM_WINDOW_Y = 114;

	//아이템 창 좌표
	const int POINT_LONG_X_LEFT = 226;
	const int POINT_LONG_X_RIGHT = 225;
	const int POINT_X_LEFT = 76;
	const int POINT_X_RIGHT = 75;
	const int POINT_Y_UP = 160;
	const int POINT_Y_MIDDLE = 4;
	const int POINT_Y_DOWN = 154;
	const int POINT_MIX_X_LEFT = 102;
	const int POINT_MIX_X_RIGHT = 102;
	//아이템창 Rect
	const int ORIGIN_X1 = 229;
	const int ORIGIN_X2 = 379;
	const int ORIGIN_X3 = 529;
	const int ORIGIN_X4 = 679;

	const int ORIGIN_Y1 = 435;
	const int ORIGIN_Y2 = 591;

	const int ORIGIN_MIX_X1 = 308;
	const int ORIGIN_MIX_X2 = 616;

	//plus창 Rect
	const int ORIGIN_PLUS_X = 487;
	const int ORIGIN_PLUS_Y = 321;

	//아이템창 크기
	const int ITEM_WINDOW_SIZE_X = 114;
	const int ITEM_WINDOW_SIZE_Y = 134;

	//plus창 크기
	const int PLUS_WINDOW_SIZE_X = 50;
	const int PLUS_WINDOW_SIZE_Y = 50;

	//아이템 조합창에 아이템이 들어갔는지의 유무
	bool fullMixWindow1 = false;
	bool fullMixWindow2 = false;

	//어떤 아이탬이 선택되었는지 알아내는 용도
	int selectItem1 = 0;
	int selectItem2 = 0;

	bool Map1 = false;
	bool Map2 = false;
	bool Map3 = false;
	bool Map4 = false;
	bool Map5 = false;
	bool Map5_1 = false;
	bool Map6 = false;
};

#endif