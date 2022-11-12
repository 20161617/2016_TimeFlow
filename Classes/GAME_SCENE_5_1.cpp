#include "GAME_SCENE_5_1.h"
#include "SimpleAudioEngine.h"
#include "MENU_SCENE.h"
#include "Menu_Layer.h"
#include "ExpandLayer.h"
#include "MixLayer.h"
#include "Hint_Layer.h"
#include "GAME_SCENE_6.h"

ExpandMenuLayer* expandLayer5_1;
MenuLayer* menuLayer5_1;
MixMenuLayer* mixLayer5_1;
HintLayer* hintLayer5_1;

Scene* GameScene5_1::createScene()
{
	auto scene = Scene::create();

	auto layer = GameScene5_1::create();

	scene->addChild(layer);

	expandLayer5_1 = ExpandMenuLayer::create();
	expandLayer5_1->setVisible(false);
	scene->addChild(expandLayer5_1, 4);

	mixLayer5_1 = MixMenuLayer::create();
	mixLayer5_1->setVisible(false);
	scene->addChild(mixLayer5_1, 4);

	menuLayer5_1 = MenuLayer::create();
	menuLayer5_1->setVisible(false);
	scene->addChild(menuLayer5_1, 5);

	hintLayer5_1 = HintLayer::create();
	hintLayer5_1->setVisible(false);
	scene->addChild(hintLayer5_1, 4);

	//맵 레벨 구별
	expandLayer5_1->KnowMapLevel(51);
	mixLayer5_1->KnowMapLevel(51);
	hintLayer5_1->findHint(0);
	hintLayer5_1->findHint(1);
	hintLayer5_1->findHint(2);
	hintLayer5_1->findHint(3);
	hintLayer5_1->findHint(4);

	mixLayer5_1->expandLayer = expandLayer5_1;
	mixLayer5_1->gameScene5_1 = layer;

	return scene;
}

bool GameScene5_1::init()
{
	if (!Layer::init())
	{
		return false;
	}

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Item_get.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/door_open.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Map5/Door_Spigot_Put.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Mouse_click.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/password.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Safe_Close.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Closet_Door_Close.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Closet_Door_Safe_Carrier_Open.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Wrong_Answer/mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Drawer_close.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Map4/Curtain.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/desk_drawer_close.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Map2/USB_Laptop.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Map5-1/Cleaning_Window.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Map5-1/Toilet_Flush.mp3");

	//plist 불러오기
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("./Characters/sprites.plist");

	//타일맵 불러오기
	_tileMap = CCTMXTiledMap::create("./Maps/Map5-1.tmx");
	_background = _tileMap->getLayer("Background51");
	this->addChild(_tileMap, 0);

	//좌표생성, 플레이어 스폰좌표 등 오브젝트 추가
	playerSpawn = _tileMap->objectGroupNamed("PlayerSpawn51");

	if (playerSpawn == NULL){
		return false;
	}

	ValueMap spawnPoint = playerSpawn->getObject("PlayerSpawnXY51");

	//캐릭터 스폰 좌표설정
	characterX = spawnPoint["x"].asInt();
	characterY = spawnPoint["y"].asInt();

	//플레이어 만들기
	playerSprite = Sprite::createWithSpriteFrameName("sprites4.png");
	playerSprite->setPosition(Point(characterX, characterY));
	playerSprite->setTag(11);
	this->addChild(playerSprite, 1, 11);

	//뚫어뻥 스프라이트
	DrainCleaner = Sprite::create("./Items/Map5-1/DrainCleaner.png");
	DrainCleaner->setPosition(Point(1216, 1152));
	DrainCleaner->setAnchorPoint(Point::ZERO);
	this->addChild(DrainCleaner, 0);

	//금고 스프라이트
	safeSPR = Sprite::create("./Layers/SAFE2.png");
	safeSPR->setPosition(Point(playerSprite->getPosition() + Point(0, ITEM_WINDOW_Y)));
	safeSPR->setVisible(false);
	this->addChild(safeSPR, 2);

	star1 = Sprite::create("./Layers/star.png");
	star1->setPosition(Point(safeStarX1, safeStarY));
	star1->setVisible(false);
	this->addChild(star1, 2);

	star2 = Sprite::create("./Layers/star.png");
	star2->setPosition(Point(safeStarX2, safeStarY));
	star2->setVisible(false);
	this->addChild(star2, 2);

	star3 = Sprite::create("./Layers/star.png");
	star3->setPosition(Point(safeStarX3, safeStarY));
	star3->setVisible(false);
	this->addChild(star3, 2);

	star4 = Sprite::create("./Layers/star.png");
	star4->setPosition(Point(safeStarX4, safeStarY));
	star4->setVisible(false);
	this->addChild(star4, 2);

	//창문 컷인
	windowCutIn = Sprite::create("./Items/Map5-1/window.png");
	windowCutIn->setPosition(Point(playerSprite->getPosition()));
	windowCutIn->setVisible(false);
	this->addChild(windowCutIn, 2);

	//여자 액자 컷인
	womanFrameCutin = Sprite::create("./Items/Map5-1/frame.png");
	womanFrameCutin->setPosition(Point(playerSprite->getPosition()));
	womanFrameCutin->setVisible(false);
	this->addChild(womanFrameCutin, 2);

	//대화창 만들기
	communication = Sprite::create("./Layers/communication.png");
	communication->setPosition(playerSprite->getPosition() + Point(0, -254));
	communication->setOpacity(255);
	communication->setVisible(false);
	this->addChild(communication, 3);

	this->schedule(schedule_selector(GameScene5_1::CallEveryFrame));

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(GameScene5_1::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(GameScene5_1::onKeyReleased, this);

	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseDown = CC_CALLBACK_1(GameScene5_1::onMouseDown, this);
	// regist listener to dispatcher
	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
	eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

	Director::getInstance()->resume();

	return true;
}

//타일맵
CCPoint GameScene5_1::tileCoordForPosition(CCPoint position){
	int x = position.x / _tileMap->getTileSize().width;
	int y = ((_tileMap->getMapSize().height* _tileMap->getTileSize().height) - position.y) / _tileMap->getTileSize().height;
	return ccp(x, y);
}

//카메라
void GameScene5_1::setViewPointCenter(CCPoint position){
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	cameraX = MAX(position.x, winSize.width / 2);
	cameraY = MAX(position.y, winSize.height / 2);

	cameraX = MIN(cameraX, (_tileMap->getMapSize().width* _tileMap->getTileSize().width) - winSize.width / 2);
	cameraY = MIN(cameraY, (_tileMap->getMapSize().height* _tileMap->getTileSize().height) - winSize.height / 2);

	CCPoint actualposition = ccp(cameraX, cameraY);
	CCPoint centerOfView = ccp(winSize.width / 2, winSize.height / 2);
	CCPoint viewPoint = ccpSub(centerOfView, actualposition);
	this->setPosition(viewPoint);
}

//대화창 불러오기
void GameScene5_1::CallCommunicationWindow(std::string info){

	communication->setPosition(playerSprite->getPosition() + Point(0, -254));
	communication->setVisible(true);

	Texts = Label::createWithTTF(info, "./Moris.ttf", 30, Size(630, 150));
	Texts->setPosition(playerSprite->getPosition() + Point(0, -262));
	Texts->setColor(ccc3(0, 0, 0));
	this->addChild(Texts, 4);
}

//대화창 내보내기
void GameScene5_1::BackCommunicationWindow(){
	communication->setVisible(false);
	Texts->setVisible(false);
	Texts->removeChild(Texts, true);
}

//메뉴씬으로 전환
void GameScene5_1::changeMenuScene_R(Ref *sender){
	Director::getInstance()->replaceScene(MenuScene::createScene());
}

//다음맵 넘어가기
void GameScene5_1::changeGameScene6_R(Ref *sender){
	auto scene = TransitionFade::create(3, GameScene6::createScene());
	Director::getInstance()->replaceScene(scene);
}

//키보드 입력
void GameScene5_1::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event){

	//플레이어 태그
	auto sprPlayer = (Sprite*)this->getChildByTag(11);

	switch (keyCode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_A:{ //A를 눌렀을때
		checkLeft = true, Go_Left = true;

		if (Go_Event == false) { //모든 이벤트 변수 초기화
			cleanBox = false, window = false, drainCleaner = false, toilet = false;
			pot = false, spigot = false, womanFrame = false, door = false;
			bath = false, manFrame = false;
		}
		//진행중 액션 삭제
		auto actionD = (Action*)sprPlayer->getActionByTag(17);//(TAG_PLAYER_ACTION_D)
		sprPlayer->getActionManager()->removeAction(actionD);
		auto actionW = (Action*)sprPlayer->getActionByTag(18);//(TAG_PLAYER_ACTION_W)
		sprPlayer->getActionManager()->removeAction(actionW);
		auto actionS = (Action*)sprPlayer->getActionByTag(19);//(TAG_PLAYER_ACTION_S)
		sprPlayer->getActionManager()->removeAction(actionS);
		//진행중 애니메이션 삭제
		auto animationActionD = (Action*)sprPlayer->getActionByTag(22);//(TAG_PLAYER_ACTION_D)
		sprPlayer->getActionManager()->removeAction(animationActionD);
		auto animationActionW = (Action*)sprPlayer->getActionByTag(23);//(TAG_PLAYER_ACTION_W)
		sprPlayer->getActionManager()->removeAction(animationActionW);
		auto animationActionS = (Action*)sprPlayer->getActionByTag(24);//(TAG_PLAYER_ACTION_S)
		sprPlayer->getActionManager()->removeAction(animationActionS);

		//왼쪽으로 이동하는 액션
		auto action1 = MoveBy::create(MOVE_TIME, Point(-SPEED, 0));
		auto action2 = RepeatForever::create(action1);
		action2->setTag(16);//Tag_SPRITE_PLAYER_ACTION_A
		sprPlayer->runAction(action2);

		//왼쪽키만 눌려져있을시의 애니메이션
		auto animation = Animation::create();
		animation->setDelayPerUnit(ANI_SPEED);

		for (int i = 5; i < 9; i++){
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
			animation->addSpriteFrame(frame);
		}

		auto animate = Animate::create(animation);
		auto action = RepeatForever::create(animate);
		action->setTag(21);//왼쪽 애니메이션
		sprPlayer->runAction(action);

		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_D:{ //D를 눌렀을 때
		checkRight = true, Go_Right = true;

		if (Go_Event == false) { //모든 이벤트변수 초기화
			cleanBox = false, window = false, drainCleaner = false, toilet = false;
			pot = false, spigot = false, womanFrame = false, door = false;
			bath = false, manFrame = false;
		}
		//진행중 액션 삭제
		auto actionA = (Action*)sprPlayer->getActionByTag(16);//(TAG_PLAYER_ACTION_D)
		sprPlayer->getActionManager()->removeAction(actionA);
		auto actionW = (Action*)sprPlayer->getActionByTag(18);//(TAG_PLAYER_ACTION_W)
		sprPlayer->getActionManager()->removeAction(actionW);
		auto actionS = (Action*)sprPlayer->getActionByTag(19);//(TAG_PLAYER_ACTION_S)
		sprPlayer->getActionManager()->removeAction(actionS);
		//진행중 애니메이션 삭제
		auto animationActionA = (Action*)sprPlayer->getActionByTag(21);//(TAG_PLAYER_ACTION_D)
		sprPlayer->getActionManager()->removeAction(animationActionA);
		auto animationActionW = (Action*)sprPlayer->getActionByTag(23);//(TAG_PLAYER_ACTION_W)
		sprPlayer->getActionManager()->removeAction(animationActionW);
		auto animationActionS = (Action*)sprPlayer->getActionByTag(24);//(TAG_PLAYER_ACTION_S)
		sprPlayer->getActionManager()->removeAction(animationActionS);

		//오른쪽으로 이동하는 액션
		auto action1 = MoveBy::create(MOVE_TIME, Point(SPEED, 0));
		auto action2 = RepeatForever::create(action1);
		action2->setTag(17);//Tag_SPRTIE_PLAYER_ACTION_D
		sprPlayer->runAction(action2);

		//오른쪽키만 눌려있을때 실행되는 애니메이션
		auto animation = Animation::create();
		animation->setDelayPerUnit(ANI_SPEED);

		for (int i = 9; i < 13; i++)	{
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
			animation->addSpriteFrame(frame);
		}

		auto animate = Animate::create(animation);
		auto action = RepeatForever::create(animate);
		action->setTag(22);//오른쪽 애니메이션
		sprPlayer->runAction(action);

		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_W:{ //W키를 눌렀을 때

		checkUp = true, Go_Up = true;

		if (Go_Event == false) {//이벤트 변수 초기화
			cleanBox = false, window = false, drainCleaner = false, toilet = false;
			pot = false, spigot = false, womanFrame = false, door = false;
			bath = false, manFrame = false;
		}
		//진행중 액션 삭제
		auto actionA = (Action*)sprPlayer->getActionByTag(16);//(TAG_PLAYER_ACTION_W)
		sprPlayer->getActionManager()->removeAction(actionA);
		auto actionD = (Action*)sprPlayer->getActionByTag(17);//(TAG_PLAYER_ACTION_D)
		sprPlayer->getActionManager()->removeAction(actionD);
		auto actionS = (Action*)sprPlayer->getActionByTag(19);//(TAG_PLAYER_ACTION_S)
		sprPlayer->getActionManager()->removeAction(actionS);
		//진행중 애니메이션 삭제
		auto animationActionA = (Action*)sprPlayer->getActionByTag(21);//(TAG_PLAYER_ACTION_W)
		sprPlayer->getActionManager()->removeAction(animationActionA);
		auto animationActionD = (Action*)sprPlayer->getActionByTag(22);//(TAG_PLAYER_ACTION_D)
		sprPlayer->getActionManager()->removeAction(animationActionD);
		auto animationActionS = (Action*)sprPlayer->getActionByTag(24);//(TAG_PLAYER_ACTION_S)
		sprPlayer->getActionManager()->removeAction(animationActionS);

		//캐릭터 이동
		auto action1 = MoveBy::create(MOVE_TIME, Point(0, SPEED));
		auto action2 = RepeatForever::create(action1);
		action2->setTag(18);//Tag_SPRTIE_PLAYER_ACTION_W
		sprPlayer->runAction(action2);

		//위쪽키만 눌려있을때 애니메이션
		auto animation = Animation::create();
		animation->setDelayPerUnit(ANI_SPEED);

		for (int i = 13; i < 17; i++)
		{
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
			animation->addSpriteFrame(frame);
		}

		auto animate = Animate::create(animation);
		auto action = RepeatForever::create(animate);
		action->setTag(23);//위쪽 애니메이션
		sprPlayer->runAction(action);

		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_S:{ //S키를 눌렀을 때
		checkDown = true, Go_Down = true;

		if (Go_Event == false) { //이벤트 변수 초기화
			cleanBox = false, window = false, drainCleaner = false, toilet = false;
			pot = false, spigot = false, womanFrame = false, door = false;
			bath = false, manFrame = false;
		}

		auto actionA = (Action*)sprPlayer->getActionByTag(16);//(TAG_PLAYER_ACTION_S)
		sprPlayer->getActionManager()->removeAction(actionA);
		auto actionD = (Action*)sprPlayer->getActionByTag(17);//(TAG_PLAYER_ACTION_D)
		sprPlayer->getActionManager()->removeAction(actionD);
		auto actionW = (Action*)sprPlayer->getActionByTag(18);//(TAG_PLAYER_ACTION_W)
		sprPlayer->getActionManager()->removeAction(actionW);

		auto animationActionA = (Action*)sprPlayer->getActionByTag(21);//(TAG_PLAYER_ACTION_S)
		sprPlayer->getActionManager()->removeAction(animationActionA);
		auto animationActionD = (Action*)sprPlayer->getActionByTag(22);//(TAG_PLAYER_ACTION_D)
		sprPlayer->getActionManager()->removeAction(animationActionD);
		auto animationActionW = (Action*)sprPlayer->getActionByTag(23);//(TAG_PLAYER_ACTION_W)
		sprPlayer->getActionManager()->removeAction(animationActionW);

		//캐릭터 이동 액션
		auto action1 = MoveBy::create(MOVE_TIME, Point(0, -SPEED));
		auto action2 = RepeatForever::create(action1);
		action2->setTag(19);//Tag_SPRTIE_PLAYER_ACTION_S
		sprPlayer->runAction(action2);

		//아래쪽키만 눌려있을때 캐릭터 애니메이션
		auto animation = Animation::create();
		animation->setDelayPerUnit(ANI_SPEED);

		for (int i = 1; i < 5; i++)
		{
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
			animation->addSpriteFrame(frame);
		}

		auto animate = Animate::create(animation);

		auto action = RepeatForever::create(animate);
		action->setTag(24);//아래쪽 애니메이션

		sprPlayer->runAction(action);

		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE:{ //ESC레이어(일시정지, 메뉴)
		if (Go_Menu == false){ //메뉴 창이 꺼져있을때
			Go_Menu = true;
			menuLayer5_1->setPosition(Point::ZERO);	//레이어 띄우기 
			menuLayer5_1->setVisible(true);
			CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic(); //음악
			Director::getInstance()->pause(); //게임 퍼즈
		}
		else if (Go_Menu == true)	{ //ESC레이어가 활성화 되있을 때
			menuLayer5_1->setVisible(false); //레이어 숨기기
			Go_Menu = false;
			CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
			if (Go_Menu == false && goExpand == false && goMix == false && Go_Event == false && goHint == false){
				//다른 창들이 다 꺼져있을 때만 게임 재개
				Director::getInstance()->resume();
			}
		}
		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_Q:{	//확대레이어
		if (Go_Menu == false && goExpand == false && Go_Event == false){	//ESC레이어와 확대 레이어가 비활성화 일때
			if (goMix == true){
				mixLayer5_1->setVisible(false); //조합레이어가 켜져있으면 비활성화시킴
				goMix = false;
			}
			else if (goHint == true){ //힌트레이어가 켜져있으면 비활성화시킴
				hintLayer5_1->setVisible(false);
				goHint = false;
			}
			goExpand = true; //확대 레이어 활성화
			expandLayer5_1->setPosition(Point(Point(512, 384) + Point(0, 114)));
			expandLayer5_1->setVisible(true);
			mixLayer5_1->MixLayerOnOff = false;
			hintLayer5_1->HintLayerOnOff = false;
			expandLayer5_1->ExpandLayerOnOff = true;
			Director::getInstance()->pause();
		}
		else if (Go_Menu == false && goExpand == true){ //확대 레이어가 활성화 일때
			expandLayer5_1->setVisible(false); //확대레이어 비활성화
			goExpand = false;
			expandLayer5_1->ExpandLayerOnOff = false;
			if (Go_Menu == false && goExpand == false && goMix == false && Go_Event == false && goHint == false){
				//다른 레이어들이 모두 비활성화 일때 개임 재개
				Director::getInstance()->resume();
			}
		}
		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_E:{	//조합레이어
		if (Go_Menu == false && goMix == false && Go_Event == false){
			if (goExpand == true){	//확대레이어 활성화시 비활성화 시킴
				expandLayer5_1->setVisible(false);
				goExpand = false;
			}
			else if (goHint == true){	//힌트레이어 활성화시 비활성화 시킴
				hintLayer5_1->setVisible(false);
				goHint = false;
			}
			goMix = true;	//조합레이어 활성화
			mixLayer5_1->setPosition(Point(Point(512, 498)));
			mixLayer5_1->setVisible(true);
			mixLayer5_1->MixLayerOnOff = true;
			hintLayer5_1->HintLayerOnOff = false;
			expandLayer5_1->ExpandLayerOnOff = false;
			Director::getInstance()->pause();
		}
		else if (Go_Menu == false && goMix == true){	//조합레이어 활성화시 비활성화 시키기
			mixLayer5_1->setVisible(false);
			goMix = false;
			mixLayer5_1->MixLayerOnOff = false;
			if (Go_Menu == false && goExpand == false && goMix == false && Go_Event == false && goHint == false){
				//모든 레이어들이 비활성화일때 게임재개
				Director::getInstance()->resume();
			}
		}
		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_H:{	//힌트레이어
		if (Go_Menu == false && goHint == false && Go_Event == false){
			if (goMix == true){	//조합레이어 활성화시 비활성화시키기
				mixLayer5_1->setVisible(false);
				goMix = false;
			}
			else if (goExpand == true){	//확대레이어 활성화시 비활성화 시키기
				expandLayer5_1->setVisible(false);
				goExpand = false;
			}
			goHint = true;	//힌트레이어 활성화
			hintLayer5_1->setPosition(Point(Point(512, 384) + Point(0, 114)));
			hintLayer5_1->setVisible(true);
			mixLayer5_1->MixLayerOnOff = false;
			hintLayer5_1->HintLayerOnOff = true;
			expandLayer5_1->ExpandLayerOnOff = false;
			Director::getInstance()->pause();
		}
		else if (Go_Menu == false && goHint == true){	//힌트레이어 활성화시 비활성화 시키기
			hintLayer5_1->setVisible(false);
			goHint = false;
			hintLayer5_1->HintLayerOnOff = false;
			if (Go_Menu == false && goExpand == false && goMix == false && Go_Event == false && goHint == false){
				//모든레이어가 비활성화일시 게임재개
				Director::getInstance()->resume();
			}
		}
		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:{	//이벤트 활성화 시키기(이벤트 오브젝트에서만)
		if (goExpand == false && goMix == false && Go_Menu == false && Go_Event == false && goHint == false){
			//모든 레이어가 꺼져있을때만 활성가능하다.
			if (cleanBox == true){
				Go_Event = true;
				if (cleanBoxItem == false){
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Item_get.wav");
					GameScene5_1::CallCommunicationWindow(UTF8("냄새나는 걸레를 얻었다."));
					mixLayer5_1->MapItemEvents(3);
					expandLayer5_1->MapItemEvents(51, 3);
					cleanBoxItem = true;
				}
				else if (cleanBoxItem == true && boxItem == false){
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Closet_Door_Safe_Carrier_Open.mp3");
					findBox = true;
					GameScene5_1::CallCommunicationWindow(UTF8("비밀번호를 입력하세요."));
					safeSPR->setPosition(Point(playerSprite->getPosition() + Point(0, ITEM_WINDOW_Y)));
					safeSPR->setVisible(true);
					star1->setPosition(Point(playerSprite->getPosition() + Point(46, 259)));
					star2->setPosition(Point(playerSprite->getPosition() + Point(105, 259)));
					star3->setPosition(Point(playerSprite->getPosition() + Point(164, 259)));
					star4->setPosition(Point(playerSprite->getPosition() + Point(223, 259)));
				}
				else if (cleanBoxItem == true && boxItem == true){
					GameScene5_1::CallCommunicationWindow(UTF8("아무것도 없다."));
				}
				Director::getInstance()->pause();
			}
			else if (window == true){
				Go_Event = true;
				if (cleanBoxItem == false){
					GameScene5_1::CallCommunicationWindow(UTF8("창문이 많이 더럽다."));
				}
				else if (cleanBoxItem == true && cleanWindow == false){
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Map5-1/Cleaning_Window.mp3");
					GameScene5_1::CallCommunicationWindow(UTF8("걸레로 창문을 닦았다.\n\n창문에 무언가가 적혀있다."));
					cleanWindow = true;
				}
				else if (cleanBoxItem == true && cleanWindow == true){
					windowCutIn->setPosition(Point(playerSprite->getPosition() + Point(0, ITEM_WINDOW_Y)));
					windowCutIn->setVisible(true);
					windowCutInOn = true;
				}
				Director::getInstance()->pause();
			}
			else if (drainCleaner == true){
				Go_Event = true;
				if (drainCleanerItem == false){
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Item_get.wav");
					GameScene5_1::CallCommunicationWindow(UTF8("뚫어뻥을 얻었다."));
					mixLayer5_1->MapItemEvents(1);
					expandLayer5_1->MapItemEvents(51, 1);
					drainCleanerItem = true;
					DrainCleaner->setVisible(false);
					DrainCleaner->removeChild(DrainCleaner, true);
				}
				else if (drainCleanerItem == true){
					GameScene5_1::CallCommunicationWindow(UTF8("이제 여기에는 아무것도 없다."));
				}
				Director::getInstance()->pause();
			}
			else if (toilet == true){
				Go_Event = true;
				if (drainCleanerItem == false){
					GameScene5_1::CallCommunicationWindow(UTF8("변기가 막혀 있다. 도대체 언제 청소를 한 거지?"));
				}
				else if (drainCleanerItem == true && toiletItem == false){
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Map5-1/Toilet_Flush.mp3");
					GameScene5_1::CallCommunicationWindow(UTF8("변기를 뚫어뻥으로 뚫었다.\n\n주사위를 획득했다.\n\n이게 왜 여기에있지?"));
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Item_get.wav");
					mixLayer5_1->MapItemEvents(4);
					expandLayer5_1->MapItemEvents(51, 4);
					toiletItem = true;
				}
				else if (drainCleanerItem == true && toiletItem == true){
					GameScene5_1::CallCommunicationWindow(UTF8("아무것도 나오지 않는다."));
				}
				Director::getInstance()->pause();
			}
			else if (pot == true){
				Go_Event = true;
				if (potItems == false){
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Item_get.wav");
					GameScene5_1::CallCommunicationWindow(UTF8("항아리 안에 있던 쪽지를 획득했다."));
					potItems = true;
					mixLayer5_1->MapItemEvents(2);
					expandLayer5_1->MapItemEvents(51, 2);
				}
				else if (potItems == true){
					GameScene5_1::CallCommunicationWindow(UTF8("쓰레기나 버릴까?"));
				}
				Director::getInstance()->pause();
			}
			else if (spigot == true){
				Go_Event = true;
				if (boxItem == false){
					GameScene5_1::CallCommunicationWindow(UTF8("수도꼭지가 없다."));
				}
				else if (boxItem == true && spigotItem == false){
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Item_get.wav");
					GameScene5_1::CallCommunicationWindow(UTF8("수도꼭지를 끼워 넣었다.\n\n\n열쇠를 획득했다."));
					mixLayer5_1->MapItemEvents(51);
					expandLayer5_1->MapItemEvents(51, 51);
					mixLayer5_1->MapItemEvents(6);
					expandLayer5_1->MapItemEvents(51, 6);
					spigotItem = true;
				}
				else if (boxItem == true && spigotItem == true){
					GameScene5_1::CallCommunicationWindow(UTF8("이제 물이 잘 나온다."));
				}
				Director::getInstance()->pause();
			}
			else if (womanFrame == true){
				Go_Event = true;
				if (spigotItem == false){
					GameScene5_1::CallCommunicationWindow(UTF8("열쇠 구멍이 있다."));
					womanFrameCutin->setPosition(Point(playerSprite->getPosition() + Point(0, ITEM_WINDOW_Y)));
					womanFrameCutin->setVisible(true);
				}
				else if (spigotItem == true && clockGear5 == false){
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Item_get.wav");
					GameScene5_1::CallCommunicationWindow(UTF8("열쇠로 잠금을 풀었다.\n\n\n톱니바퀴를 획득했다."));
					mixLayer5_1->MapItemEvents(61);
					expandLayer5_1->MapItemEvents(51, 61);
					hintLayer5_1->findHint(5);
					clockGear5 = true;					
				}
				else if (spigotItem == true && clockGear5 == true){
					GameScene5_1::CallCommunicationWindow(UTF8("텅텅 비어있다."));
				}
				Director::getInstance()->pause();
			}
			else if (door == true){
				Go_Event = true;
				if (clockGear5 == false){
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Map5/Door_Spigot_Put.mp3");
					GameScene5_1::CallCommunicationWindow(UTF8("아직 톱니바퀴를 찾지 못했어."));
				}
				else if (clockGear5 == true){
					GameScene5_1::CallCommunicationWindow(UTF8("이제 다음 집이 마지막 집이야. 어서 다음 집으로 향하자."));
					NextMap = true;
				}
				Director::getInstance()->pause();
			}
			else if (manFrame == true){
				Go_Event = true;
				GameScene5_1::CallCommunicationWindow(UTF8("화장실 인테리어도 상당히 신경 쓴 것 같다."));
				Director::getInstance()->pause();
			}
			else if (bath == true){
				Go_Event = true;
				GameScene5_1::CallCommunicationWindow(UTF8("욕조 안에 오리가 있다."));
				Director::getInstance()->pause();
			}
		}
		else if (Go_Menu == false && Go_Event == true){ // 이벤트 활성화 시
			if (drainCleaner == true || pot == true || spigot == true || bath == true || manFrame == true ||
				toilet == true){
				Go_Event = false;
				GameScene5_1::BackCommunicationWindow();
				Director::getInstance()->resume();
			}
			else if (window == true){
				Go_Event = false;
				if (cleanWindow == false){
					GameScene5_1::BackCommunicationWindow();
				}
				else if (cleanWindow == true && windowCutInOn == false){
					GameScene5_1::BackCommunicationWindow();
				}
				else if (cleanWindow == true && windowCutInOn == true){
					windowCutIn->setVisible(false);
					windowCutInOn = false;
				}
				Director::getInstance()->resume();
			}
			else if (cleanBox == true){
				Go_Event = false;
				if (cleanBoxItem == true && findBox == false){
					GameScene5_1::BackCommunicationWindow();
				}
				else if (cleanBoxItem == true && findBox == true && boxItem == false){
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Closet_Door_Close.mp3");
					GameScene5_1::BackCommunicationWindow();
					safeSPR->setVisible(false);
					star1->setVisible(false);
					star2->setVisible(false);
					star3->setVisible(false);
					star4->setVisible(false);
					blink = 1;
					password1 = NULL, password2 = NULL, password3 = NULL, password4 = NULL;
				}
		    	else if (cleanBoxItem == true && findBox == true && boxItem == true){
			    	GameScene5_1::BackCommunicationWindow();
		    	}
				Director::getInstance()->resume();
			}
			else if (womanFrame == true){
				Go_Event = false;
				if (spigotItem == false){
					GameScene5_1::BackCommunicationWindow();
					womanFrameCutin->setVisible(false);
				}
				else if (spigotItem == true){
				    GameScene5_1::BackCommunicationWindow();
				}
				Director::getInstance()->resume();
			}
			else if (door == true){
				Go_Event = false;
				if (clockGear5 == false){
					GameScene5_1::BackCommunicationWindow();
				}
				else if (clockGear5 == true){
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/door_open.mp3");
					GameScene5_1::BackCommunicationWindow();
					GameScene5_1::changeGameScene6_R(this);
				}
				Director::getInstance()->resume();
			}
		}
		break;
	}
	}
}

//키입력->키를 땠을때
void GameScene5_1::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	auto sprPlayer = (Sprite*)this->getChildByTag(11);	//플레이어 태그(11)

	switch (keyCode){
	case cocos2d::EventKeyboard::KeyCode::KEY_A:{	//왼쪽키를 땠을 때
		//키 체크, 애니메이션 초기화
		Go_Left = false, checkLeft = false;
		checkRightAnimation = false, checkUpAnimation = false, checkDownAnimation = false;

		//캐릭터 이동 액션 중지
		auto action = (Action*)sprPlayer->getActionByTag(16);//(TAG_PLAYER_ACTION_A)
		sprPlayer->getActionManager()->removeAction(action);
		//캐릭터 애니메이션 중지
		auto animationAction = (Action*)sprPlayer->getActionByTag(21);
		sprPlayer->getActionManager()->removeAction(animationAction);

		//캐릭터 중지 스프라이트 지정
		if (checkLeft == false && checkRight == false && checkUp == false && checkDown == false &&
			goExpand == false && goMix == false && Go_Menu == false && Go_Event == false){
			sprPlayer->setSpriteFrame("sprites8.png");
		}

		if (checkRight == true && checkRightAnimation != true){//왼쪽키 땐후 오른쪽키가 눌려있을때

			auto actionD = (Action*)sprPlayer->getActionByTag(17);
			sprPlayer->getActionManager()->removeAction(actionD);

			auto animationActionD = (Action*)sprPlayer->getActionByTag(22);
			sprPlayer->getActionManager()->removeAction(animationActionD);

			checkRightAnimation = true;
			auto animation = Animation::create();
			animation->setDelayPerUnit(ANI_SPEED);

			//애니메이션 실행
			for (int i = 9; i < 13; i++){
				auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
				animation->addSpriteFrame(frame);
			}

			auto animate = Animate::create(animation);
			auto action = RepeatForever::create(animate);
			action->setTag(22);//오른쪽 애니메이션2

			sprPlayer->runAction(action);

			auto action1 = MoveBy::create(MOVE_TIME, Point(SPEED, 0));
			auto action2 = RepeatForever::create(action1);
			action2->setTag(17);
			sprPlayer->runAction(action2);
		}
		if (checkUp == true && checkUpAnimation != true){// 왼쪽키 땐후 위쪽키가 눌려있을때

			auto actionW = (Action*)sprPlayer->getActionByTag(18);//(TAG_PLAYER_ACTION_W)
			sprPlayer->getActionManager()->removeAction(actionW);

			auto animationActionW = (Action*)sprPlayer->getActionByTag(23);
			sprPlayer->getActionManager()->removeAction(animationActionW);

			checkUpAnimation = true;
			auto animation = Animation::create();
			animation->setDelayPerUnit(ANI_SPEED);

			//애니메이션 실행
			for (int i = 13; i < 17; i++){
				auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
				animation->addSpriteFrame(frame);
			}

			auto animate = Animate::create(animation);
			auto action = RepeatForever::create(animate);
			action->setTag(23);//위쪽 애니메이션2

			sprPlayer->runAction(action);

			auto action1 = MoveBy::create(MOVE_TIME, Point(0, SPEED));
			auto action2 = RepeatForever::create(action1);
			action2->setTag(18);//Tag_SPRTIE_PLAYER_ACTION_W
			sprPlayer->runAction(action2);
		}
		if (checkDown == true && checkDownAnimation != true){//왼쪽키 땐후 아래쪽키가 눌려있을때

			auto actionS = (Action*)sprPlayer->getActionByTag(19);//(TAG_PLAYER_ACTION_S)
			sprPlayer->getActionManager()->removeAction(actionS);

			auto animationActionS = (Action*)sprPlayer->getActionByTag(24);
			sprPlayer->getActionManager()->removeAction(animationActionS);

			checkDownAnimation = true;
			auto animation = Animation::create();
			animation->setDelayPerUnit(ANI_SPEED);

			//애니메이션 실행
			for (int i = 1; i < 5; i++){
				auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
				animation->addSpriteFrame(frame);
			}

			auto animate = Animate::create(animation);
			auto action = RepeatForever::create(animate);
			action->setTag(24);//아래쪽 애니메이션2

			sprPlayer->runAction(action);

			auto action1 = MoveBy::create(MOVE_TIME, Point(0, -SPEED));
			auto action2 = RepeatForever::create(action1);
			action2->setTag(19);//Tag_SPRTIE_PLAYER_ACTION_S
			sprPlayer->runAction(action2);
		}
		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_D:{//오른쪽 키를 땠을 때
		//체크, 애니메이션 초기화
		Go_Right = false, checkRight = false;
		checkLeftAnimation = false, checkDownAnimation = false, checkUpAnimation = false;

		//오른쪽 이동액션 중지
		auto action = (Action*)sprPlayer->getActionByTag(17);//(TAG_PLAYER_ACTION_D)
		sprPlayer->getActionManager()->removeAction(action);
		//애니메이션 중지
		auto animationAction = (Action*)sprPlayer->getActionByTag(22);
		sprPlayer->getActionManager()->removeAction(animationAction);

		//캐릭터 중지 스프라이트 지정
		if (checkLeft == false && checkRight == false && checkUp == false && checkDown == false &&
			goExpand == false && goMix == false && Go_Menu == false && Go_Event == false){
			sprPlayer->setSpriteFrame("sprites12.png");
		}

		if (checkLeft == true && checkLeftAnimation != true){//오른쪽키를 땐후 왼쪽키가 눌려있을때

			auto actionA = (Action*)sprPlayer->getActionByTag(16);//(TAG_PLAYER_ACTION_A)
			sprPlayer->getActionManager()->removeAction(actionA);

			auto animationActionA = (Action*)sprPlayer->getActionByTag(21);
			sprPlayer->getActionManager()->removeAction(animationActionA);

			checkLeftAnimation = true;
			auto animation = Animation::create();
			animation->setDelayPerUnit(ANI_SPEED);

			//애니메이션 실행
			for (int i = 5; i < 9; i++){
				auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
				animation->addSpriteFrame(frame);
			}

			auto animate = Animate::create(animation);
			auto action = RepeatForever::create(animate);
			action->setTag(21);//왼쪽 애니메이션2

			sprPlayer->runAction(action);

			auto action1 = MoveBy::create(MOVE_TIME, Point(-SPEED, 0));
			auto action2 = RepeatForever::create(action1);
			action2->setTag(16);//Tag_SPRITE_PLAYER_ACTION_A
			sprPlayer->runAction(action2);
		}
		if (checkUp == true && checkUpAnimation != true){//오른쪽키를 땐후 위쪽키가 눌려있을때

			auto actionW = (Action*)sprPlayer->getActionByTag(18);//(TAG_PLAYER_ACTION_W)
			sprPlayer->getActionManager()->removeAction(actionW);

			auto animationActionW = (Action*)sprPlayer->getActionByTag(23);
			sprPlayer->getActionManager()->removeAction(animationActionW);

			checkUpAnimation = true;
			auto animation = Animation::create();
			animation->setDelayPerUnit(ANI_SPEED);

			//애니메이션 실행
			for (int i = 13; i < 17; i++){
				auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
				animation->addSpriteFrame(frame);
			}

			auto animate = Animate::create(animation);
			auto action = RepeatForever::create(animate);
			action->setTag(23);//위쪽 애니메이션2

			sprPlayer->runAction(action);

			auto action1 = MoveBy::create(MOVE_TIME, Point(0, SPEED));
			auto action2 = RepeatForever::create(action1);
			action2->setTag(18);//Tag_SPRTIE_PLAYER_ACTION_W
			sprPlayer->runAction(action2);
		}
		if (checkDown == true && checkDownAnimation != true){//오른쪽키를 땐후 아래쪽키가 눌려있을때

			auto actionS = (Action*)sprPlayer->getActionByTag(19);//(TAG_PLAYER_ACTION_S)
			sprPlayer->getActionManager()->removeAction(actionS);

			auto animationActionS = (Action*)sprPlayer->getActionByTag(24);
			sprPlayer->getActionManager()->removeAction(animationActionS);

			checkDownAnimation = true;
			auto animation = Animation::create();
			animation->setDelayPerUnit(ANI_SPEED);

			//애니메이션 실행
			for (int i = 1; i < 5; i++){
				auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
				animation->addSpriteFrame(frame);
			}

			auto animate = Animate::create(animation);
			auto action = RepeatForever::create(animate);
			action->setTag(24);//아래쪽 애니메이션2

			sprPlayer->runAction(action);

			auto action1 = MoveBy::create(MOVE_TIME, Point(0, -SPEED));
			auto action2 = RepeatForever::create(action1);
			action2->setTag(19);//Tag_SPRTIE_PLAYER_ACTION_S
			sprPlayer->runAction(action2);
		}
		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_W:{//위쪽키를 땠을 때
		//체크, 애니메이션 초기화
		Go_Up = false, checkUp = false;
		checkLeftAnimation = false, checkRightAnimation = false, checkDownAnimation = false;

		//캐릭터 이동 액션 중지
		auto action = (Action*)sprPlayer->getActionByTag(18);//(TAG_PLAYER_ACTION_W)
		sprPlayer->getActionManager()->removeAction(action);
		//애니메이션 중지
		auto animationAction = (Action*)sprPlayer->getActionByTag(23);
		sprPlayer->getActionManager()->removeAction(animationAction);

		//캐릭터 중지 스프라이트 지정
		if (checkLeft == false && checkRight == false && checkUp == false && checkDown == false &&
			goExpand == false && goMix == false && Go_Menu == false && Go_Event == false){
			sprPlayer->setSpriteFrame("sprites16.png");
		}
		if (checkLeft == true && checkLeftAnimation != true){//위쪽키를 땐후 왼쪽키가 눌려있을때

			auto actionA = (Action*)sprPlayer->getActionByTag(16);//(TAG_PLAYER_ACTION_A)
			sprPlayer->getActionManager()->removeAction(actionA);

			auto animationActionA = (Action*)sprPlayer->getActionByTag(21);
			sprPlayer->getActionManager()->removeAction(animationActionA);

			checkLeftAnimation = true;
			auto animation = Animation::create();
			animation->setDelayPerUnit(ANI_SPEED);

			//애니메이션 실행
			for (int i = 5; i < 9; i++){
				auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
				animation->addSpriteFrame(frame);
			}

			auto animate = Animate::create(animation);
			auto action = RepeatForever::create(animate);
			action->setTag(21);//왼쪽 애니메이션2

			sprPlayer->runAction(action);

			auto action1 = MoveBy::create(MOVE_TIME, Point(-SPEED, 0));
			auto action2 = RepeatForever::create(action1);
			action2->setTag(16);//Tag_SPRITE_PLAYER_ACTION_A
			sprPlayer->runAction(action2);
		}
		if (checkRight == true && checkRightAnimation != true){//윗쪽키를 땐후 오른쪽키가 눌려있을때
			auto actionD = (Action*)sprPlayer->getActionByTag(17);//(TAG_PLAYER_ACTION_D)
			sprPlayer->getActionManager()->removeAction(actionD);

			auto animationActionD = (Action*)sprPlayer->getActionByTag(22);
			sprPlayer->getActionManager()->removeAction(animationActionD);

			checkRightAnimation = true;
			auto animation = Animation::create();
			animation->setDelayPerUnit(ANI_SPEED);

			//애니메이션 실행
			for (int i = 9; i < 13; i++){
				auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
				animation->addSpriteFrame(frame);
			}

			auto animate = Animate::create(animation);
			auto action = RepeatForever::create(animate);
			action->setTag(22);//오른쪽 애니메이션2

			sprPlayer->runAction(action);

			auto action1 = MoveBy::create(MOVE_TIME, Point(SPEED, 0));
			auto action2 = RepeatForever::create(action1);
			action2->setTag(17);//Tag_SPRTIE_PLAYER_ACTION_D
			sprPlayer->runAction(action2);
		}
		if (checkDown == true && checkDownAnimation != true){//윗쪽키를 땐후 아래쪽키가 눌려있을때
			auto actionS = (Action*)sprPlayer->getActionByTag(19);//(TAG_PLAYER_ACTION_S)
			sprPlayer->getActionManager()->removeAction(actionS);

			auto animationActionS = (Action*)sprPlayer->getActionByTag(24);
			sprPlayer->getActionManager()->removeAction(animationActionS);

			checkDownAnimation = true;
			auto animation = Animation::create();
			animation->setDelayPerUnit(ANI_SPEED);

			//애니메이션 실행
			for (int i = 1; i < 5; i++){
				auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
				animation->addSpriteFrame(frame);
			}

			auto animate = Animate::create(animation);
			auto action = RepeatForever::create(animate);
			action->setTag(24);//아래쪽 애니메이션2

			sprPlayer->runAction(action);

			auto action1 = MoveBy::create(MOVE_TIME, Point(0, -SPEED));
			auto action2 = RepeatForever::create(action1);
			action2->setTag(19);//Tag_SPRTIE_PLAYER_ACTION_S
			sprPlayer->runAction(action2);
		}
		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_S:{//아래쪽 키를 땠을때
		//체크, 애니메이션 초기화
		Go_Down = false, checkDown = false;
		checkLeftAnimation = false, checkRightAnimation = false, checkUpAnimation = false;

		//캐릭터 이동 액션 중지
		auto action = (Action*)sprPlayer->getActionByTag(19);//(TAG_PLAYER_ACTION_S)
		sprPlayer->getActionManager()->removeAction(action);

		//애니메이션 중지
		auto animationAction = (Action*)sprPlayer->getActionByTag(24);
		sprPlayer->getActionManager()->removeAction(animationAction);

		//캐릭터 중지 스프라이트 지정
		if (checkLeft == false && checkRight == false && checkUp == false && checkDown == false &&
			goExpand == false && goMix == false && Go_Menu == false && Go_Event == false){
			sprPlayer->setSpriteFrame("sprites4.png");
		}

		if (checkLeft == true && checkLeftAnimation != true){//아래쪽키를 땐후 왼쪽키가 눌려있을때
			auto actionA = (Action*)sprPlayer->getActionByTag(16);//(TAG_PLAYER_ACTION_A)
			sprPlayer->getActionManager()->removeAction(actionA);

			auto animationActionA = (Action*)sprPlayer->getActionByTag(21);
			sprPlayer->getActionManager()->removeAction(animationActionA);

			checkLeftAnimation = true;
			auto animation = Animation::create();
			animation->setDelayPerUnit(ANI_SPEED);

			//애니메이션 실행
			for (int i = 5; i < 9; i++){
				auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
				animation->addSpriteFrame(frame);
			}
			auto animate = Animate::create(animation);
			auto action = RepeatForever::create(animate);
			action->setTag(21);//왼쪽 애니메이션2

			sprPlayer->runAction(action);

			auto action1 = MoveBy::create(MOVE_TIME, Point(-SPEED, 0));
			auto action2 = RepeatForever::create(action1);
			action2->setTag(16);//Tag_SPRITE_PLAYER_ACTION_A
			sprPlayer->runAction(action2);
		}
		if (checkRight == true && checkRightAnimation != true){//아래쪽키를 땐후 오른쪽키가 눌려있을때
			auto actionD = (Action*)sprPlayer->getActionByTag(17);//(TAG_PLAYER_ACTION_D)
			sprPlayer->getActionManager()->removeAction(actionD);

			auto animationActionD = (Action*)sprPlayer->getActionByTag(22);
			sprPlayer->getActionManager()->removeAction(animationActionD);

			checkRightAnimation = true;
			auto animation = Animation::create();
			animation->setDelayPerUnit(ANI_SPEED);

			//애니메이션 실행
			for (int i = 9; i < 13; i++){
				auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
				animation->addSpriteFrame(frame);
			}

			auto animate = Animate::create(animation);
			auto action = RepeatForever::create(animate);
			action->setTag(22);//오른쪽 애니메이션2

			sprPlayer->runAction(action);

			auto action1 = MoveBy::create(MOVE_TIME, Point(SPEED, 0));
			auto action2 = RepeatForever::create(action1);
			action2->setTag(17);//Tag_SPRTIE_PLAYER_ACTION_D
			sprPlayer->runAction(action2);
		}
		if (checkUp == true && checkUpAnimation != true){//아래쪽키를 땐후 위쪽키가 눌려있을때
			auto actionW = (Action*)sprPlayer->getActionByTag(18);//(TAG_PLAYER_ACTION_W)
			sprPlayer->getActionManager()->removeAction(actionW);

			auto animationActionW = (Action*)sprPlayer->getActionByTag(23);
			sprPlayer->getActionManager()->removeAction(animationActionW);

			checkUpAnimation = true;
			auto animation = Animation::create();
			animation->setDelayPerUnit(ANI_SPEED);

			//애니메이션 실행
			for (int i = 13; i < 17; i++){
				auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
				animation->addSpriteFrame(frame);
			}

			auto animate = Animate::create(animation);
			auto action = RepeatForever::create(animate);
			action->setTag(23);//위쪽 애니메이션2

			sprPlayer->runAction(action);

			auto action1 = MoveBy::create(MOVE_TIME, Point(0, SPEED));
			auto action2 = RepeatForever::create(action1);
			action2->setTag(18);//Tag_SPRTIE_PLAYER_ACTION_W
			sprPlayer->runAction(action2);
		}
		break;
	}
	}
}

// 1초에 60프레임
void GameScene5_1::CallEveryFrame(float f)
{
	auto sprPlayer = (Sprite*)this->getChildByTag(11); //플레이어 태그
	this->setViewPointCenter(playerSprite->getPosition()); //카메라

	if (checkLeft){
		CCPoint playerPos1 = sprPlayer->getPosition();
		CCPoint playerPos2 = sprPlayer->getPosition();

		CCPoint tileCoord1 = this->tileCoordForPosition(playerPos1 + Point(-BREAK_TOO_X, BREAK_ZERO_Y));//좌상단
		CCPoint tileCoord2 = this->tileCoordForPosition(playerPos2 + Point(-BREAK_TOO_X, -BREAK_DOWN_Y));//좌하단

		unsigned int tileGid1 = _background->tileGIDAt(tileCoord1);
		unsigned int tileGid2 = _background->tileGIDAt(tileCoord2);

		auto properties1 = _tileMap->propertiesForGID(tileGid1);
		auto properties2 = _tileMap->propertiesForGID(tileGid2);

		ValueMap map1 = properties1.asValueMap();
		ValueMap map2 = properties2.asValueMap();

		String propertyValue1 = map1["Collidable"].asString();//충돌체크
		String propertyValue2 = map2["Collidable"].asString();
		String pot1 = map1["Pot"].asString();//항아리
		String pot2 = map2["Pot"].asString();

		if (propertyValue1.compare("True") == 0 || propertyValue2.compare("True") == 0){
			auto action = (Action*)sprPlayer->getActionByTag(16);

			sprPlayer->getActionManager()->removeAction(action);
			Go_Left = false;
		}
		else{
			if (!Go_Left){
				Go_Left = true;
				//캐릭터 이동 액션
				auto action1 = MoveBy::create(MOVE_TIME, Point(-SPEED, 0));
				auto action2 = RepeatForever::create(action1);
				action2->setTag(16);//Tag_SPRITE_PLAYER_ACTION_A
				sprPlayer->runAction(action2);
			}
		}
		if (pot1.compare("True") == 0 && pot2.compare("True") == 0){
			pot = true;
		}
	}

	if (checkRight){
		CCPoint playerPos1 = sprPlayer->getPosition();
		CCPoint playerPos2 = sprPlayer->getPosition();

		CCPoint tileCoord1 = this->tileCoordForPosition(playerPos1 + Point(BREAK_TOO_X, BREAK_ZERO_Y));//우상단
		CCPoint tileCoord2 = this->tileCoordForPosition(playerPos2 + Point(BREAK_TOO_X, -BREAK_DOWN_Y));//우하단

		unsigned int tileGid1 = _background->tileGIDAt(tileCoord1);
		unsigned int tileGid2 = _background->tileGIDAt(tileCoord2);

		auto properties1 = _tileMap->propertiesForGID(tileGid1);
		auto properties2 = _tileMap->propertiesForGID(tileGid2);

		ValueMap map1 = properties1.asValueMap();
		ValueMap map2 = properties2.asValueMap();

		String propertyValue1 = map1["Collidable"].asString();//충돌체크
		String propertyValue2 = map2["Collidable"].asString();
		String bath1 = map1["Bath"].asString();//욕조
		String bath2 = map2["Bath"].asString();
		String toilet1 = map1["Toilet"].asString();//변기
		String toilet2 = map2["Toilet"].asString();

		if (propertyValue1.compare("True") == 0 || propertyValue2.compare("True") == 0){
			auto action = (Action*)sprPlayer->getActionByTag(17);

			sprPlayer->getActionManager()->removeAction(action);

			Go_Right = false;
		}
		else{
			if (!Go_Right){
				Go_Right = true;
				//캐릭터 이동 액션
				auto action1 = MoveBy::create(MOVE_TIME, Point(SPEED, 0));
				auto action2 = RepeatForever::create(action1);
				action2->setTag(17);//Tag_SPRTIE_PLAYER_ACTION_D
				sprPlayer->runAction(action2);
			}
		}
		if (bath1.compare("True") == 0 && bath2.compare("True") == 0){
			bath = true;
		}
		if (toilet1.compare("True") == 0 && toilet2.compare("True") == 0){
			toilet = true;
		}

	}
	if (checkUp){
		CCPoint playerPos1 = sprPlayer->getPosition();
		CCPoint playerPos2 = sprPlayer->getPosition();

		CCPoint tileCoord1 = this->tileCoordForPosition(playerPos1 + Point(BREAK_X, BREAK_UP_Y));//우상단
		CCPoint tileCoord2 = this->tileCoordForPosition(playerPos2 + Point(-BREAK_X, BREAK_UP_Y));//좌상단

		unsigned int tileGid1 = _background->tileGIDAt(tileCoord1);
		unsigned int tileGid2 = _background->tileGIDAt(tileCoord2);

		auto properties1 = _tileMap->propertiesForGID(tileGid1);
		auto properties2 = _tileMap->propertiesForGID(tileGid2);

		ValueMap map1 = properties1.asValueMap();
		ValueMap map2 = properties2.asValueMap();

		String propertyValue1 = map1["Collidable"].asString();//충돌체크
		String propertyValue2 = map2["Collidable"].asString();
		String cleanBox1 = map1["CleanBox"].asString();//청소도구함, 상자
		String cleanBox2 = map2["CleanBox"].asString();
		String window1 = map1["Window"].asString();//창문
		String window2 = map2["Window"].asString();
		String manFrame1 = map1["ManFrame"].asString();//남자 액자
		String manFrame2 = map2["ManFrame"].asString();
		String womanFrame1 = map1["WomanFrame"].asString();//여자 액자
		String womanFrame2 = map2["WomanFrame"].asString();
		String spigot1 = map1["Spigot"].asString();//세면대
		String spigot2 = map2["Spigot"].asString();
		String drainCleaner1 = map1["DrainCleaner"].asString();//뚫어뻥
		String drainCleaner2 = map2["DrainCleaner"].asString();
		String toilet1 = map1["Toilet"].asString();//변기
		String toilet2 = map2["Toilet"].asString();

		if (propertyValue1.compare("True") == 0 || propertyValue2.compare("True") == 0){
			auto action = (Action*)sprPlayer->getActionByTag(18);

			sprPlayer->getActionManager()->removeAction(action);
			Go_Up = false;
		}
		else{
			if (!Go_Up){
				Go_Up = true;
				//캐릭터 이동 액션 
				auto action1 = MoveBy::create(MOVE_TIME, Point(0, SPEED));
				auto action2 = RepeatForever::create(action1);
				action2->setTag(18);//Tag_SPRTIE_PLAYER_ACTION_W
				sprPlayer->runAction(action2);
			}
		}
		if (cleanBox1.compare("True") == 0 && cleanBox2.compare("True") == 0){
			cleanBox = true;
		}
		if (window1.compare("True") == 0 && window2.compare("True") == 0){
			window = true;
		}
		if (manFrame1.compare("True") == 0 && manFrame2.compare("True") == 0){
			manFrame = true;
		}
		if (womanFrame1.compare("True") == 0 && womanFrame2.compare("True") == 0){
			womanFrame = true;
		}
		if (spigot1.compare("True") == 0 && spigot2.compare("True") == 0){
			spigot = true;
		}
		if (drainCleaner1.compare("True") == 0 && drainCleaner2.compare("True") == 0){
			drainCleaner = true;
		}
		if (toilet1.compare("True") == 0 && toilet2.compare("True") == 0){
			toilet = true;
		}
	}
	if (checkDown){
		CCPoint playerPos1 = sprPlayer->getPosition();
		CCPoint playerPos2 = sprPlayer->getPosition();

		CCPoint tileCoord1 = this->tileCoordForPosition(playerPos1 + Point(BREAK_X, -BREAK_TOO_DOWN_Y));//우하단
		CCPoint tileCoord2 = this->tileCoordForPosition(playerPos2 + Point(-BREAK_X, -BREAK_TOO_DOWN_Y));//좌하단

		unsigned int tileGid1 = _background->tileGIDAt(tileCoord1);
		unsigned int tileGid2 = _background->tileGIDAt(tileCoord2);

		auto properties1 = _tileMap->propertiesForGID(tileGid1);
		auto properties2 = _tileMap->propertiesForGID(tileGid2);

		ValueMap map1 = properties1.asValueMap();
		ValueMap map2 = properties2.asValueMap();

		String propertyValue1 = map1["Collidable"].asString();//충돌체크
		String propertyValue2 = map2["Collidable"].asString();
		String pot1 = map1["Pot"].asString();//항아리
		String pot2 = map2["Pot"].asString();
		String door1 = map1["Door"].asString();//문
		String door2 = map2["Door"].asString();

		if (propertyValue1.compare("True") == 0 || propertyValue2.compare("True") == 0){
			auto action = (Action*)sprPlayer->getActionByTag(19);

			sprPlayer->getActionManager()->removeAction(action);
			Go_Down = false;
		}
		else{
			if (!Go_Down){
				Go_Down = true;
				//캐릭터 이동 액션
				auto action1 = MoveBy::create(MOVE_TIME, Point(0, -SPEED));
				auto action2 = RepeatForever::create(action1);
				action2->setTag(19);//Tag_SPRTIE_PLAYER_ACTION_S
				sprPlayer->runAction(action2);
			}
		}
		if (pot1.compare("True") == 0 && pot2.compare("True") == 0){
			pot = true;
		}
		if (door1.compare("True") == 0 && door2.compare("True") == 0){
			door = true;
		}
	}

}

//마우스 사용용도 -> 선택지
void GameScene5_1::onMouseDown(cocos2d::Event* event){
	EventMouse* e = (EventMouse*)event;

	Point result = Point(e->getCursorX(), e->getCursorY());
	//마우스 커서 위치 받기

	Rect button1 = Rect(531, 515, 56, 56); //금고 1번 버튼
	Rect button2 = Rect(617, 515, 56, 56); //금고 2번 버튼
	Rect button3 = Rect(703, 515, 56, 56); //금고 3번 버튼
	Rect button4 = Rect(531, 447, 56, 56); //금고 4번 버튼
	Rect button5 = Rect(617, 447, 56, 56); //금고 5번 버튼
	Rect button6 = Rect(703, 447, 56, 56); //금고 6번 버튼
	Rect button7 = Rect(531, 379, 56, 56); //금고 7번 버튼
	Rect button8 = Rect(617, 379, 56, 56); //금고 8번 버튼
	Rect button9 = Rect(703, 379, 56, 56); //금고 9번 버튼 
	Rect buttonC = Rect(531, 311, 56, 56); //금고 C번 버튼
	Rect button0 = Rect(617, 311, 56, 56); //금고 0번 버튼
	Rect buttonE = Rect(703, 311, 56, 56); //금고 E번 버튼

	/*
	시스템 구성

	버튼을 누르면 blink변수가 1씩 증가한다 이걸로 비밀번호의 위치를 알아낸다.
	4개를 다 입력했을 때 다르면 다 초기화 맞을 시 아이템 획득

	C버튼 누를시 번호 초기화 -> 지우개 버튼
	E버튼 누를시 번호 입력 ->맞는 번호인지 판단
	*/
	if (Go_Event == true){ //음식 수납장(금고) 이벤트 활성화 시
		if (button1.containsPoint(result)){
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/password.mp3");
			if (blink == 1){
				star1->setVisible(true);
				password1 = 1;
				blink++;
			}
			else if (blink == 2){
				star2->setVisible(true);
				password2 = 1;
				blink++;
			}
			else if (blink == 3){
				star3->setVisible(true);
				password3 = 1;
				blink++;
			}
			else if (blink == 4){
				star4->setVisible(true);
				password4 = 1;
				blink++;
			}
		}
		if (button2.containsPoint(result)){
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/password.mp3");
			if (blink == 1){
				star1->setVisible(true);
				password1 = 2;
				blink++;
			}
			else if (blink == 2){
				star2->setVisible(true);
				password2 = 2;
				blink++;
			}
			else if (blink == 3){
				star3->setVisible(true);
				password3 = 2;
				blink++;
			}
			else if (blink == 4){
				star4->setVisible(true);
				password4 = 2;
				blink++;
			}

		}
		if (button3.containsPoint(result)){
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/password.mp3");
			if (blink == 1){
				star1->setVisible(true);
				password1 = 3;
				blink++;
			}
			else if (blink == 2){
				star2->setVisible(true);
				password2 = 3;
				blink++;
			}
			else if (blink == 3){
				star3->setVisible(true);
				password3 = 3;
				blink++;
			}
			else if (blink == 4){
				star4->setVisible(true);
				password4 = 3;
				blink++;
			}
		}
		if (button4.containsPoint(result)){
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/password.mp3");
			if (blink == 1){
				star1->setVisible(true);
				password1 = 4;
				blink++;
			}
			else if (blink == 2){
				star2->setVisible(true);
				password2 = 4;
				blink++;
			}
			else if (blink == 3){
				star3->setVisible(true);
				password3 = 4;
				blink++;
			}
			else if (blink == 4){
				star4->setVisible(true);
				password4 = 4;
				blink++;
			}
		}
		if (button5.containsPoint(result)){
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/password.mp3");
			if (blink == 1){
				star1->setVisible(true);
				password1 = 5;
				blink++;
			}
			else if (blink == 2){
				star2->setVisible(true);
				password2 = 5;
				blink++;
			}
			else if (blink == 3){
				star3->setVisible(true);
				password3 = 5;
				blink++;
			}
			else if (blink == 4){
				star4->setVisible(true);
				password4 = 5;
				blink++;
			}
		}
		if (button6.containsPoint(result)){
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/password.mp3");
			if (blink == 1){
				star1->setVisible(true);
				password1 = 6;
				blink++;
			}
			else if (blink == 2){
				star2->setVisible(true);
				password2 = 6;
				blink++;
			}
			else if (blink == 3){
				star3->setVisible(true);
				password3 = 6;
				blink++;
			}
			else if (blink == 4){
				star4->setVisible(true);
				password4 = 6;
				blink++;
			}
		}
		if (button7.containsPoint(result)){
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/password.mp3");
			if (blink == 1){
				star1->setVisible(true);
				password1 = 7;
				blink++;
			}
			else if (blink == 2){
				star2->setVisible(true);
				password2 = 7;
				blink++;
			}
			else if (blink == 3){
				star3->setVisible(true);
				password3 = 7;
				blink++;
			}
			else if (blink == 4){
				star4->setVisible(true);
				password4 = 7;
				blink++;
			}
		}
		if (button8.containsPoint(result)){
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/password.mp3");
			if (blink == 1){
				star1->setVisible(true);
				password1 = 8;
				blink++;
			}
			else if (blink == 2){
				star2->setVisible(true);
				password2 = 8;
				blink++;
			}
			else if (blink == 3){
				star3->setVisible(true);
				password3 = 8;
				blink++;
			}
			else if (blink == 4){
				star4->setVisible(true);
				password4 = 8;
				blink++;
			}
		}
		if (button9.containsPoint(result)){
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/password.mp3");
			if (blink == 1){
				star1->setVisible(true);
				password1 = 9;
				blink++;
			}
			else if (blink == 2){
				star2->setVisible(true);
				password2 = 9;
				blink++;
			}
			else if (blink == 3){
				star3->setVisible(true);
				password3 = 9;
				blink++;
			}
			else if (blink == 4){
				star4->setVisible(true);
				password4 = 9;
				blink++;
			}
		}
		if (button0.containsPoint(result)){
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/password.mp3");
			if (blink == 1){
				star1->setVisible(true);
				password1 = 0;
				blink++;
			}
			else if (blink == 2){
				star2->setVisible(true);
				password2 = 0;
				blink++;
			}
			else if (blink == 3){
				star3->setVisible(true);
				password3 = 0;
				blink++;
			}
			else if (blink == 4){
				star4->setVisible(true);
				password4 = 0;
				blink++;
			}
		}
		if (buttonC.containsPoint(result)){
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/password.mp3");
			blink = 1;
			password1 = NULL, password2 = NULL, password3 = NULL, password4 = NULL;
			star1->setVisible(false);
			star2->setVisible(false);
			star3->setVisible(false);
			star4->setVisible(false);
		}
		if (buttonE.containsPoint(result)){
			if (password1 == 7 && password2 == 1 && password3 == 7 && password4 == 9){
				safeSPR->setVisible(false);
				star1->setVisible(false);
				star2->setVisible(false);
				star3->setVisible(false);
				star4->setVisible(false);
				BackCommunicationWindow();
				CallCommunicationWindow(UTF8("금고의 잠금을 풀었다.\n\n\n수도꼭지를 발견했다."));
				boxItem = true;
				mixLayer5_1->MapItemEvents(5);
				expandLayer5_1->MapItemEvents(51, 5);
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Item_get.wav");
			}
			else{
				star1->setVisible(false);
				star2->setVisible(false);
				star3->setVisible(false);
				star4->setVisible(false);
				BackCommunicationWindow();
				CallCommunicationWindow(UTF8("잘못된 비밀번호였다."));
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Safe_Close.mp3");
			}
			blink = 1;
			password1 = NULL;
			password2 = NULL;
			password3 = NULL;
			password4 = NULL;
			star1->setVisible(false);
			star2->setVisible(false);
			star3->setVisible(false);
			star4->setVisible(false);
		}
	}
}