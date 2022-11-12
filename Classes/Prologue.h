#ifndef __PROLOGUE__H_
#define __PROLOGUE__H_

#include "cocos2d.h"
USING_NS_CC;

class PrologueScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	CREATE_FUNC(PrologueScene);

	//�޴� ȭ������ ���ư���
	void PrologueScene::menuCallback(cocos2d::Ref* sender);
	void changeMenuScene_R(Ref *sender);

	//������ �Ѿ��
	void PrologueScene::changeGameScene1_R(Ref* sender);

	//Ű���� ������
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

private:
	//���ѷα� ȭ�� ��ȯ Ƚ�� 10�Ǹ� ���� ����
	int count = 1;

	//���ѷα� ȭ��
	Sprite* prologue1;
	Sprite* prologue2;
	Sprite* prologue3;
	Sprite* prologue4;
	Sprite* prologue5;
	Sprite* prologue6;
	Sprite* prologue7;
	Sprite* prologue8;
	Sprite* prologue9;
};
#endif