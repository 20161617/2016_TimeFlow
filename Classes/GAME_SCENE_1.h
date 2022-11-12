#ifndef __GAME_SCENE_H___
#define __GAME_SCENE_H___

#include "cocos2d.h"
USING_NS_CC;

class ExpandMenuLayer;
class MixMenuLayer;

class GameScene : public cocos2d::Layer
{
public:
	
	/*       �±� ����
	ĳ���� �±� 11
	�������� �̵� 16
	���������� �̵� 17
	���� �̵� 18
	�Ʒ��� �̵� 19
	���� �ִϸ��̼� 21
	������ �ִϸ��̼� 22
	���� �ִϸ��̼� 23
	�Ʒ��� �ִϸ��̼� 24
	25,26,27,28 �ִϸ��̼� 1�� ���� �����ٶ�
	(       ��         ��        )
	�밢�� ���� ���� 12
	�밢�� ���� ������ 13
	�밢�� ���� ���� 14
	�밢�� ���� �Ʒ��� 15
	*/


	static cocos2d::Scene* createScene();
	void GameScene::menuCallback(cocos2d::Ref* sender);
	virtual bool init();
	CREATE_FUNC(GameScene);
	//�޴� ȭ������ ���ư���
	void changeMenuScene_R(Ref *sender);

	//����ȭ������ �Ѿ
	void changeGameScene2_R(Ref *sender);

	//������ȣ��
	void CallEveryFrame(float f);

	//��ȭâ ȣ��
	void CallCommunicationWindow(std::string info);
	void BackCommunicationWindow();

	//������ ȣ��
	void CallSelectWindow(std::string info1, std::string info2);
	void BackSelectWindow();

	//Ű���� ������, ����
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	//���콺 ������, ����
	void onMouseDown(cocos2d::Event* event);
	
	//ĳ���� ī�޶� �̵�
	void setViewPointCenter(CCPoint position);

	//ĳ���� �浹����
	CCPoint tileCoordForPosition(CCPoint position);

	Sprite* communication;	//��ȭâ
	Label* Texts;	//�ؽ�Ʈ
	Sprite* playerSprite;	//�÷��̾� ��������Ʈ
private:
	CCTMXTiledMap* _tileMap;	//Ÿ�ϸ�
	CCTMXLayer* _background;	//Ÿ�ϸ� ��׶���
	CCTMXObjectGroup* playerSpawn;	//ĳ���� ������ġ

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
	bool cuttingBoard = false, gasRange = false, door = false, flavorDrawer = false;
	bool foodDrawer = false, rightCarpet = false, calender = false, bed = false;
	bool frame = false, leftCarpet = false;

	//�̺�Ʈ ������ ���� ����
	bool leftCarpetItem = false, bedItem = false;

	//����, �޷� ����
	Sprite* calenderCutIn;
	Sprite* frameCutIn;

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

	//��Ϲ���, ������ �Ѿ�� �Ǵ�
	bool clockGear1 = false, nextmap = false;
};

#endif

