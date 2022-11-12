#ifndef __CORRECT_H__
#define __CORRECT_H__

#include "cocos2d.h"
USING_NS_CC;

class CorrectScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	CREATE_FUNC(CorrectScene);

	//�޴� ȭ������ ���ư���
	void CorrectScene::menuCallback(Ref* sender);
	void changeMenuScene_R(Ref *sender);

	//��ȭ ���̱�, ���ֱ�
	void CorrectScene::CallCommunication(std::string info);
	void CorrectScene::BackCommunication();
	//Ű���� ������
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

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

	//�ؽ�Ʈ ����Լ��� ����(�ʹ� ������ ���Ŀ� ����)
	std::string text = "";

	//���ʷα� ȭ�� ��ȯ Ƚ�� ���� Ƚ�� �Ǹ� ���� ����
	int count = 1;

	//�ձ� ȭ��
	Sprite* palace;

	//���� ȭ��
	Sprite* epilogue1;
	Sprite* epilogue2;

	//��, ����, �� ��ȭ
	Sprite* daughter;

	Sprite* designer1;
	Sprite* designer2;
	Sprite* designer3;

	Sprite* king1;
	Sprite* king2;
	Sprite* king3;
	Sprite* king4;

};
#endif
