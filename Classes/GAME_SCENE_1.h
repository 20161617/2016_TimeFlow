#ifndef __GAME_SCENE_H___
#define __GAME_SCENE_H___

#include "cocos2d.h"
USING_NS_CC;

class ExpandMenuLayer;
class MixMenuLayer;

class GameScene : public cocos2d::Layer
{
public:
	
	/*       태그 정리
	캐릭터 태그 11
	왼쪽으로 이동 16
	오른쪽으로 이동 17
	위로 이동 18
	아래로 이동 19
	왼쪽 애니메이션 21
	오른쪽 애니메이션 22
	위쪽 애니메이션 23
	아래쪽 애니메이션 24
	25,26,27,28 애니메이션 1과 동일 수정바람
	(       예         정        )
	대각선 전용 왼쪽 12
	대각선 전용 오른쪽 13
	대각선 전용 위쪽 14
	대각선 전용 아래쪽 15
	*/


	static cocos2d::Scene* createScene();
	void GameScene::menuCallback(cocos2d::Ref* sender);
	virtual bool init();
	CREATE_FUNC(GameScene);
	//메뉴 화면으로 돌아가기
	void changeMenuScene_R(Ref *sender);

	//게임화면으로 넘어감
	void changeGameScene2_R(Ref *sender);

	//프레임호출
	void CallEveryFrame(float f);

	//대화창 호출
	void CallCommunicationWindow(std::string info);
	void BackCommunicationWindow();

	//선택지 호출
	void CallSelectWindow(std::string info1, std::string info2);
	void BackSelectWindow();

	//키보드 누르기, 때기
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	//마우스 누르기, 때기
	void onMouseDown(cocos2d::Event* event);
	
	//캐릭터 카메라 이동
	void setViewPointCenter(CCPoint position);

	//캐릭터 충돌판정
	CCPoint tileCoordForPosition(CCPoint position);

	Sprite* communication;	//대화창
	Label* Texts;	//텍스트
	Sprite* playerSprite;	//플레이어 스프라이트
private:
	CCTMXTiledMap* _tileMap;	//타일맵
	CCTMXLayer* _background;	//타일맵 백그라운드
	CCTMXObjectGroup* playerSpawn;	//캐릭터 스폰위치

	//이동 속도, 이동 시간, 애니메이션 변환 속도
	const int SPEED = 4;
	const float MOVE_TIME = 0.025;
	const float ANI_SPEED = 0.15;

	//아이템 큰 창 y추가로 올라간 좌표(금고 포함)
	const int ITEM_WINDOW_Y = 114;

	//대화창 좌표 내리기 y축
	const int COMMUNICATION_WINDOW_Y = 254;

	//대화 사이즈, 좌표
	const int TALK_SIZE_X = 630;
	const int TALK_SIZE_Y = 150;
	const int TALK_Y = 262;

	//조합, 확대, 힌트 레이어 위치
	const int LAYERS_X = 512;
	const int LAYERS_Y = 498;

	//캐릭터 이동용 true시 움직임, false시 멈춤
	bool Go_Left = false;
	bool Go_Right = false;
	bool Go_Down = false;
	bool Go_Up = false;
	bool checkLeft = false;
	bool checkRight = false;
	bool checkUp = false;
	bool checkDown = false;

	//캐릭터 대각선 애니메이션 겹침 판정 체크
	bool checkLeftAnimation = false;
	bool checkRightAnimation = false;
	bool checkUpAnimation = false;
	bool checkDownAnimation = false;

	//메뉴 활성
	bool Go_Menu = false;

	//이벤트 활성
	bool Go_Event = false;

	//확대 활성
	bool goExpand = false;

	//조합 활성
	bool goMix = false;

	//힌트 활성
	bool goHint = false;

	//텍스트 출력함수에 쓰임(초반 시험작 추후에 변경)
	std::string text = "";

	//캐릭터 좌표
	int characterX = NULL;
	int characterY = NULL;

	//카메라 좌표
	int cameraX = NULL;
	int cameraY = NULL;

	//충돌체크 좌표 
	const int BREAK_TOO_X = 28; //왼쪽,오른쪽 충돌체크시 x좌표용도
	const int BREAK_ZERO_Y = 0; //왼쪽,오른쪽 충돌체크시 y좌표용도
	const int BREAK_DOWN_Y = 48; //왼쪽,오른쪽 충돌체크시 y좌표용도

	const int BREAK_X = 24; //위,아래 충돌체크시 x좌표용도
	const int BREAK_UP_Y = 4; //위,아래 충돌체크시 y좌표용도
	const int BREAK_TOO_DOWN_Y = 52; //위,아래 충돌체크시 y좌표용도

	//이벤트 발생 판단
	bool cuttingBoard = false, gasRange = false, door = false, flavorDrawer = false;
	bool foodDrawer = false, rightCarpet = false, calender = false, bed = false;
	bool frame = false, leftCarpet = false;

	//이벤트 아이템 습득 제한
	bool leftCarpetItem = false, bedItem = false;

	//액자, 달력 컷인
	Sprite* calenderCutIn;
	Sprite* frameCutIn;

	//여기부터 금고
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

	//금고 버튼 좌표
	const int SAFE_BUTTON_X1 = 531;
	const int SAFE_BUTTON_X2 = 617;
	const int SAFE_BUTTON_X3 = 703;
	const int SAFE_BUTTON_Y1 = 515;
	const int SAFE_BUTTON_Y2 = 447;
	const int SAFE_BUTTON_Y3 = 379;
	const int SAFE_BUTTON_Y4 = 311;

	//금고 버튼 사이즈
	const int SAFE_BUTTON_SIZE = 56;

	//금고  별 좌표
	const int safeStarX1 = 46;
	const int safeStarX2 = 105;
	const int safeStarX3 = 164;
	const int safeStarX4 = 223;
	const int safeStarY = 259;

	//톱니바퀴, 다음맵 넘어가기 판단
	bool clockGear1 = false, nextmap = false;
};

#endif

