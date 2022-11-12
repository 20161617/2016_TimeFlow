#ifndef __GAME_SCENE_2_H__
#define __GAME_SCENE_2_H__

#include "cocos2d.h"
USING_NS_CC;

class GameScene2 : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	CREATE_FUNC(GameScene2);

	//�޴� ȭ������ ���ư���
	void GameScene2::menuCallback(cocos2d::Ref* sender);
	void changeMenuScene_R(Ref *sender);
	//���������� �̵�
	void changeGameScene3_R(Ref *sender);
	//������ȣ��
	void CallEveryFrame(float f);

	//��ȭâ ȣ��
	void CallCommunicationWindow(std::string info);
	void BackCommunicationWindow();

	//Ű���� ������, ����
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	//���콺 ������, ����
	void onMouseDown(Event* event);
	void onMouseUp(Event* event);

	//ĳ���� ī�޶� �̵�
	void setViewPointCenter(CCPoint position);

	//ĳ���� �浹����
	CCPoint tileCoordForPosition(CCPoint position);

	Sprite* playerSprite;
	Sprite* communication;
	Label* Texts;

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

	CCTMXTiledMap* _tileMap;
	CCTMXLayer* _background;
	CCTMXObjectGroup* playerSpawn;

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
	bool laptop = false, deskDrawer = false;
	bool safe = false, door = false;
	bool drawer = false, bookshelf = false, bed = false;

	//������ ����
	bool deskDrawerItem = false, safeItem = false, coinBank = false;

	//���忭��, USB�ȱ�
	bool openCloset = false, putUSB = false;

	//�������
	bool continueTalk = false;

	//��Ϲ���, ������ �Ѿ�� �Ǵ�
	bool clockGear2 = false, nextMap = false;

	//�� ����
	Sprite* mapChange;
	//��Ʈ�� ����
	Sprite* laptopCutIn;

	//������� �ݰ�
	Sprite* safeSPR;
	Sprite* star1;
	Sprite* star2;
	Sprite* star3;
	Sprite* star4;
	int blink = 1;
	int password1 = NULL;
	int password2 = NULL;
	int password3 = NULL;
	int password4 = NULL;

	//�ݰ� ��ư ��ǥ
	const int SAFE_BUTTON_X1 = 531;
	const int SAFE_BUTTON_X2 = 617;
	const int SAFE_BUTTON_X3 = 703;
	const int SAFE_BUTTON_Y1 = 515;
	const int SAFE_BUTTON_Y2 = 447;
	const int SAFE_BUTTON_Y3 = 379;
	const int SAFE_BUTTON_Y4 = 311;

	//�ݰ� ��ư ������
	const int SAFE_BUTTON_SIZE = 56;

	//�ݰ�  �� ��ǥ
	const int safeStarX1 = 46;
	const int safeStarX2 = 105;
	const int safeStarX3 = 164;
	const int safeStarX4 = 223;
	const int safeStarY = 259;
};
#endif