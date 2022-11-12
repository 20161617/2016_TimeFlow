#ifndef __GAME_SCENE_6_H__
#define __GAME_SCENE_6_H__

#include "cocos2d.h"
USING_NS_CC;

class GameScene6 : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	CREATE_FUNC(GameScene6);

	//�޴� ȭ������ ���ư���
	void GameScene6::menuCallback(cocos2d::Ref* sender);
	void changeMenuScene_R(Ref *sender);

	//������ȣ��
	void CallEveryFrame(float f);

	//��ȭâ ȣ��
	void CallCommunicationWindow(std::string info);
	void BackCommunicationWindow();

	//�̺�Ʈ �߻� �ޱ�
	bool GameScene6::knowEvent(int mapLevel, int eventCode);

	//������ �Ѿ��
	void GameScene6::changeThink_R(Ref *sender);

	//Ű���� ������, ����
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	//���콺 ������, ����
	void onMouseDown(Event* event);

	//ĳ���� ī�޶� �̵�
	void setViewPointCenter(CCPoint position);

	//ĳ���� �浹����
	CCPoint tileCoordForPosition(CCPoint position);

	Sprite* playerSprite; //�÷��̾� ��������Ʈ
	Sprite* communication; //��ȭâ
	Label* Texts; //��ȭ

	const std::string UTF8(const std::string& string)
	{
		int bufflen = MultiByteToWideChar(CP_ACP, 0, string.c_str(), -1, NULL, 0);
		WCHAR* widebuff = new WCHAR[bufflen + 1];
		memset(widebuff, 0, sizeof(WCHAR)* (bufflen + 1));
		MultiByteToWideChar(CP_ACP, 0, string.c_str(), -1, widebuff, bufflen);

		bufflen = WideCharToMultiByte(CP_UTF8, 0, widebuff, -1, NULL, 0, NULL, NULL);
		char* buff = new char[bufflen + 1];
		memset(buff, 0, sizeof(char)* (bufflen + 1));
		WideCharToMultiByte(CP_UTF8, 0, widebuff, -1, buff, bufflen, NULL, NULL);

		std::string strResult(buff);

		delete[] widebuff;
		delete[] buff;

		return strResult;
	}

private:
	CCTMXTiledMap* _tileMap; //Ÿ�ϸ�
	CCTMXLayer* _background; //Ÿ�ϸ� �� ���
	CCTMXObjectGroup* playerSpawn; //Ÿ�ϸ� �÷��̾� �������

	//�̵� �ӵ�, �̵� �ð�, �ִϸ��̼� ��ȯ �ӵ�
	const int SPEED = 4;
	const float MOVE_TIME = 0.025;
	const float ANI_SPEED = 0.15;

	//������ ū â y�߰��� �ö� ��ǥ(�ݰ� ����)
	const int ITEM_WINDOW_Y = 114;

	//��ȭâ ��ǥ ������ y��
	const int COMMUNICATION_WINDOW_Y = 254;

	//��ȭ ������, ��ǥ
	const int TALK_SIZE_X = 630;
	const int TALK_SIZE_Y = 150;
	const int TALK_Y = 262;

	//����, Ȯ��, ��Ʈ ���̾� ��ġ
	const int LAYERS_X = 512;
	const int LAYERS_Y = 498;

	//ĳ���� �̵��� true�� ������, false�� ����
	bool Go_Left = false;
	bool Go_Right = false;
	bool Go_Down = false;
	bool Go_Up = false;
	bool checkLeft = false;
	bool checkRight = false;
	bool checkUp = false;
	bool checkDown = false;

	//ĳ���� �밢�� �ִϸ��̼� ��ħ ���� üũ
	bool checkLeftAnimation = false;
	bool checkRightAnimation = false;
	bool checkUpAnimation = false;
	bool checkDownAnimation = false;

	//�޴� Ȱ��
	bool Go_Menu = false;

	//�̺�Ʈ Ȱ��
	bool Go_Event = false;

	//Ȯ�� Ȱ��
	bool goExpand = false;

	//���� Ȱ��
	bool goMix = false;

	//��Ʈ Ȱ��
	bool goHint = false;

	//�ؽ�Ʈ ����Լ��� ����(�ʹ� ������ ���Ŀ� ����)
	std::string text = "";

	//ĳ���� ��ǥ
	int characterX = NULL;
	int characterY = NULL;

	//ī�޶� ��ǥ
	int cameraX = NULL;
	int cameraY = NULL;

	//�浹üũ ��ǥ 
	const int BREAK_TOO_X = 28; //����,������ �浹üũ�� x��ǥ�뵵
	const int BREAK_ZERO_Y = 0; //����,������ �浹üũ�� y��ǥ�뵵
	const int BREAK_DOWN_Y = 48; //����,������ �浹üũ�� y��ǥ�뵵

	const int BREAK_X = 24; //��,�Ʒ� �浹üũ�� x��ǥ�뵵
	const int BREAK_UP_Y = 4; //��,�Ʒ� �浹üũ�� y��ǥ�뵵
	const int BREAK_TOO_DOWN_Y = 52; //��,�Ʒ� �浹üũ�� y��ǥ�뵵

	//�̺�Ʈ �Ǵ�
	bool pallete = false, book = false, piano = false, pianoChair = false, safe = false;
	bool flowerFrame = false, firePlace = false, vine = false, closet = false;
	bool pot = false, bookshelf = false, door = false;

	//�̺�Ʈ �߻�
	bool pianoItem = false, safeItem = false, flowerFrameItem = false, pianoChairItem = false;

	//������ ����
	Layer* firePlaceLayer;
	Sprite* firePlaceLock;
	Sprite* firePlaceNumber1;
	Sprite* firePlaceNumber2;
	Sprite* firePlaceNumber3;
	Sprite* firePlaceNumber4;

	const int FIRE_PLACE_X = 567;
	const int FIRE_PLACE_Y1 = 533;
	const int FIRE_PLACE_Y2 = 468;
	const int FIRE_PLACE_Y3 = 401;
	const int FIRE_PLACE_Y4 = 335;

	const int FIRE_PLACE_SIZE = 50;

	int firePlacePassword1 = 0;
	int firePlacePassword2 = 0;
	int firePlacePassword3 = 0;
	int firePlacePassword4 = 0;

	//�ķ�Ʈ ����
	Sprite* palleteCutIn;
	//å ����
	Sprite* bookCutIn;
	//�ǾƳ� ����
	Sprite* pianoCutin;

	const int PIANO_X1 = 273;
	const int PIANO_X2 = 346;
	const int PIANO_X3 = 417;
	const int PIANO_X4 = 489;
	const int PIANO_X5 = 559;
	const int PIANO_X6 = 631;
	const int PIANO_X7 = 700;
	const int PIANO_X8 = 306;
	const int PIANO_X9 = 385;
	const int PIANO_X10 = 522;
	const int PIANO_X11 = 595;
	const int PIANO_X12 = 669;

	const int PIANO_Y1 = 356;
	const int PIANO_Y2 = 480;

	const int PIANO_SIZE = 50;

	int piano_Num1 = NULL;
	int piano_Num2 = NULL;
	int piano_Num3 = NULL;
	bool piano_check1 = false;
	bool piano_check2 = false;
	bool piano_check3 = false;
	//��Ϲ���
	bool clockGear6 = false;
};
#endif