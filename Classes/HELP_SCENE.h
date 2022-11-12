#ifndef __HELP_SCENE_H___
#define __HELP_SCENE_H___

#include "cocos2d.h"

USING_NS_CC;

class HelpScene : public Layer
{
public:

	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(HelpScene);

	//���콺 �����̱�
	void onMouseMove(cocos2d::Event* event);
	void onMouseDown(cocos2d::Event* event);
	//�޴�ȭ������ ���ư���
	void changeMenuScene_R(Ref *sender);

private:
	//���� ȭ��2��
	Sprite* helpSprite1;
	Sprite* helpSprite2;
	//������ ��ư
	MenuItemSprite* spr_exit;
	Menu* exit;
	Sprite* back1;
	Sprite* back2;
	Sprite* BACK;
	//ȭ�� �ѱ��� ȭ��ǥ
	Sprite* leftArrow;
	Sprite* rightArrow;

	//���� ������ 1 = false, 2 = true
	bool helpPage = false;
};

#endif