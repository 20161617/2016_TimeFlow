#ifndef __INCORRECT_H__
#define __INCORRECT_H__

#include "cocos2d.h"
USING_NS_CC;

class IncorrectScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	CREATE_FUNC(IncorrectScene);

	//�޴� ȭ������ ���ư���
	void IncorrectScene::menuCallback(Ref* sender);
	void changeMenuScene_R(Ref *sender);

	//��ȭ ���̱�, ���ֱ�
	void IncorrectScene::CallCommunication(std::string info);
	void IncorrectScene::BackCommunication();
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

	//��, �� ��ȭ
	Sprite* daughter;
	Sprite* king1;
	Sprite* king2;
	
};
#endif
