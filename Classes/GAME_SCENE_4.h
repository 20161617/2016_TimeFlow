#ifndef __GAME_SCENE_4_H__
#define __GAME_SCENE_4_H__

#include "cocos2d.h"
USING_NS_CC;

class GameScene4 : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	CREATE_FUNC(GameScene4);

	//�޴� ȭ������ ���ư���
	void GameScene4::menuCallback(cocos2d::Ref* sender);
	void changeMenuScene_R(Ref *sender);

	//������ȣ��
	void CallEveryFrame(float f);

	//��ȭâ ȣ��
	void CallCommunicationWindow(std::string info);
	void BackCommunicationWindow();

	//�̺�Ʈ �߻� �ޱ�
	bool GameScene4::knowEvent(int mapLevel, int eventCode);

	//������ �Ѿ��
	void GameScene4::changeGameScene5_R(Ref *sender);

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

	//�̺�Ʈ �߻� �Ǵ�
	bool curtain = false, carrier = false, jar = false, drawer = false;
	bool chair = false, desk = false, teddyBear = false, closet = false;
	bool vanity = false, floor = false, door = false;

	//�̺�Ʈ ����
	bool makeHead = false, openCurtain = false, drawerItem = false, useKey = false;
	bool carrierItem = false, jarItem = false, chairItem = false, deskItem = false;
	bool makeCloth = false, makeTeddyBear = false;
	//��Ϲ���, ������ �Ѿ�� �Ǵ�
	bool clockGear4 = false;

	//Ŀư ����
	Sprite* curtainCutIn;

	//������ ��������Ʈ (�Ӹ��޾��ָ� ����)
	Sprite* teddyMake;
	const int TEDDY_X = 768;
	const int TEDDY_Y = 896;

	//ĳ���� ��й�ȣ ����
	Layer* carrierLayer;
	Sprite* carrierLock;
	Sprite* carrierNumber1;
	Sprite* carrierNumber2;
	Sprite* carrierNumber3;
	Sprite* carrierNumber4;

	int carrierPassWord1 = 0;
	int carrierPassWord2 = 0;
	int carrierPassWord3 = 0;
	int carrierPassWord4 = 0;

	const int CARRIER_BUTTON_X1 = 632;
	const int CARRIER_BUTTON_Y1 = 599;
	const int CARRIER_BUTTON_Y2 = 523;
	const int CARRIER_BUTTON_Y3 = 444;
	const int CARRIER_BUTTON_Y4 = 368;

	const int CARRIER_BUTTON_SIZE_X = 30;
	const int CARRIER_BUTTON_SIZE_Y = 30;
};
#endif