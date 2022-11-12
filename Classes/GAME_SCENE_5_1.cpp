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

	//�� ���� ����
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

	//plist �ҷ�����
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("./Characters/sprites.plist");

	//Ÿ�ϸ� �ҷ�����
	_tileMap = CCTMXTiledMap::create("./Maps/Map5-1.tmx");
	_background = _tileMap->getLayer("Background51");
	this->addChild(_tileMap, 0);

	//��ǥ����, �÷��̾� ������ǥ �� ������Ʈ �߰�
	playerSpawn = _tileMap->objectGroupNamed("PlayerSpawn51");

	if (playerSpawn == NULL){
		return false;
	}

	ValueMap spawnPoint = playerSpawn->getObject("PlayerSpawnXY51");

	//ĳ���� ���� ��ǥ����
	characterX = spawnPoint["x"].asInt();
	characterY = spawnPoint["y"].asInt();

	//�÷��̾� �����
	playerSprite = Sprite::createWithSpriteFrameName("sprites4.png");
	playerSprite->setPosition(Point(characterX, characterY));
	playerSprite->setTag(11);
	this->addChild(playerSprite, 1, 11);

	//�վ ��������Ʈ
	DrainCleaner = Sprite::create("./Items/Map5-1/DrainCleaner.png");
	DrainCleaner->setPosition(Point(1216, 1152));
	DrainCleaner->setAnchorPoint(Point::ZERO);
	this->addChild(DrainCleaner, 0);

	//�ݰ� ��������Ʈ
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

	//â�� ����
	windowCutIn = Sprite::create("./Items/Map5-1/window.png");
	windowCutIn->setPosition(Point(playerSprite->getPosition()));
	windowCutIn->setVisible(false);
	this->addChild(windowCutIn, 2);

	//���� ���� ����
	womanFrameCutin = Sprite::create("./Items/Map5-1/frame.png");
	womanFrameCutin->setPosition(Point(playerSprite->getPosition()));
	womanFrameCutin->setVisible(false);
	this->addChild(womanFrameCutin, 2);

	//��ȭâ �����
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

//Ÿ�ϸ�
CCPoint GameScene5_1::tileCoordForPosition(CCPoint position){
	int x = position.x / _tileMap->getTileSize().width;
	int y = ((_tileMap->getMapSize().height* _tileMap->getTileSize().height) - position.y) / _tileMap->getTileSize().height;
	return ccp(x, y);
}

//ī�޶�
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

//��ȭâ �ҷ�����
void GameScene5_1::CallCommunicationWindow(std::string info){

	communication->setPosition(playerSprite->getPosition() + Point(0, -254));
	communication->setVisible(true);

	Texts = Label::createWithTTF(info, "./Moris.ttf", 30, Size(630, 150));
	Texts->setPosition(playerSprite->getPosition() + Point(0, -262));
	Texts->setColor(ccc3(0, 0, 0));
	this->addChild(Texts, 4);
}

//��ȭâ ��������
void GameScene5_1::BackCommunicationWindow(){
	communication->setVisible(false);
	Texts->setVisible(false);
	Texts->removeChild(Texts, true);
}

//�޴������� ��ȯ
void GameScene5_1::changeMenuScene_R(Ref *sender){
	Director::getInstance()->replaceScene(MenuScene::createScene());
}

//������ �Ѿ��
void GameScene5_1::changeGameScene6_R(Ref *sender){
	auto scene = TransitionFade::create(3, GameScene6::createScene());
	Director::getInstance()->replaceScene(scene);
}

//Ű���� �Է�
void GameScene5_1::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event){

	//�÷��̾� �±�
	auto sprPlayer = (Sprite*)this->getChildByTag(11);

	switch (keyCode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_A:{ //A�� ��������
		checkLeft = true, Go_Left = true;

		if (Go_Event == false) { //��� �̺�Ʈ ���� �ʱ�ȭ
			cleanBox = false, window = false, drainCleaner = false, toilet = false;
			pot = false, spigot = false, womanFrame = false, door = false;
			bath = false, manFrame = false;
		}
		//������ �׼� ����
		auto actionD = (Action*)sprPlayer->getActionByTag(17);//(TAG_PLAYER_ACTION_D)
		sprPlayer->getActionManager()->removeAction(actionD);
		auto actionW = (Action*)sprPlayer->getActionByTag(18);//(TAG_PLAYER_ACTION_W)
		sprPlayer->getActionManager()->removeAction(actionW);
		auto actionS = (Action*)sprPlayer->getActionByTag(19);//(TAG_PLAYER_ACTION_S)
		sprPlayer->getActionManager()->removeAction(actionS);
		//������ �ִϸ��̼� ����
		auto animationActionD = (Action*)sprPlayer->getActionByTag(22);//(TAG_PLAYER_ACTION_D)
		sprPlayer->getActionManager()->removeAction(animationActionD);
		auto animationActionW = (Action*)sprPlayer->getActionByTag(23);//(TAG_PLAYER_ACTION_W)
		sprPlayer->getActionManager()->removeAction(animationActionW);
		auto animationActionS = (Action*)sprPlayer->getActionByTag(24);//(TAG_PLAYER_ACTION_S)
		sprPlayer->getActionManager()->removeAction(animationActionS);

		//�������� �̵��ϴ� �׼�
		auto action1 = MoveBy::create(MOVE_TIME, Point(-SPEED, 0));
		auto action2 = RepeatForever::create(action1);
		action2->setTag(16);//Tag_SPRITE_PLAYER_ACTION_A
		sprPlayer->runAction(action2);

		//����Ű�� �������������� �ִϸ��̼�
		auto animation = Animation::create();
		animation->setDelayPerUnit(ANI_SPEED);

		for (int i = 5; i < 9; i++){
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
			animation->addSpriteFrame(frame);
		}

		auto animate = Animate::create(animation);
		auto action = RepeatForever::create(animate);
		action->setTag(21);//���� �ִϸ��̼�
		sprPlayer->runAction(action);

		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_D:{ //D�� ������ ��
		checkRight = true, Go_Right = true;

		if (Go_Event == false) { //��� �̺�Ʈ���� �ʱ�ȭ
			cleanBox = false, window = false, drainCleaner = false, toilet = false;
			pot = false, spigot = false, womanFrame = false, door = false;
			bath = false, manFrame = false;
		}
		//������ �׼� ����
		auto actionA = (Action*)sprPlayer->getActionByTag(16);//(TAG_PLAYER_ACTION_D)
		sprPlayer->getActionManager()->removeAction(actionA);
		auto actionW = (Action*)sprPlayer->getActionByTag(18);//(TAG_PLAYER_ACTION_W)
		sprPlayer->getActionManager()->removeAction(actionW);
		auto actionS = (Action*)sprPlayer->getActionByTag(19);//(TAG_PLAYER_ACTION_S)
		sprPlayer->getActionManager()->removeAction(actionS);
		//������ �ִϸ��̼� ����
		auto animationActionA = (Action*)sprPlayer->getActionByTag(21);//(TAG_PLAYER_ACTION_D)
		sprPlayer->getActionManager()->removeAction(animationActionA);
		auto animationActionW = (Action*)sprPlayer->getActionByTag(23);//(TAG_PLAYER_ACTION_W)
		sprPlayer->getActionManager()->removeAction(animationActionW);
		auto animationActionS = (Action*)sprPlayer->getActionByTag(24);//(TAG_PLAYER_ACTION_S)
		sprPlayer->getActionManager()->removeAction(animationActionS);

		//���������� �̵��ϴ� �׼�
		auto action1 = MoveBy::create(MOVE_TIME, Point(SPEED, 0));
		auto action2 = RepeatForever::create(action1);
		action2->setTag(17);//Tag_SPRTIE_PLAYER_ACTION_D
		sprPlayer->runAction(action2);

		//������Ű�� ���������� ����Ǵ� �ִϸ��̼�
		auto animation = Animation::create();
		animation->setDelayPerUnit(ANI_SPEED);

		for (int i = 9; i < 13; i++)	{
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
			animation->addSpriteFrame(frame);
		}

		auto animate = Animate::create(animation);
		auto action = RepeatForever::create(animate);
		action->setTag(22);//������ �ִϸ��̼�
		sprPlayer->runAction(action);

		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_W:{ //WŰ�� ������ ��

		checkUp = true, Go_Up = true;

		if (Go_Event == false) {//�̺�Ʈ ���� �ʱ�ȭ
			cleanBox = false, window = false, drainCleaner = false, toilet = false;
			pot = false, spigot = false, womanFrame = false, door = false;
			bath = false, manFrame = false;
		}
		//������ �׼� ����
		auto actionA = (Action*)sprPlayer->getActionByTag(16);//(TAG_PLAYER_ACTION_W)
		sprPlayer->getActionManager()->removeAction(actionA);
		auto actionD = (Action*)sprPlayer->getActionByTag(17);//(TAG_PLAYER_ACTION_D)
		sprPlayer->getActionManager()->removeAction(actionD);
		auto actionS = (Action*)sprPlayer->getActionByTag(19);//(TAG_PLAYER_ACTION_S)
		sprPlayer->getActionManager()->removeAction(actionS);
		//������ �ִϸ��̼� ����
		auto animationActionA = (Action*)sprPlayer->getActionByTag(21);//(TAG_PLAYER_ACTION_W)
		sprPlayer->getActionManager()->removeAction(animationActionA);
		auto animationActionD = (Action*)sprPlayer->getActionByTag(22);//(TAG_PLAYER_ACTION_D)
		sprPlayer->getActionManager()->removeAction(animationActionD);
		auto animationActionS = (Action*)sprPlayer->getActionByTag(24);//(TAG_PLAYER_ACTION_S)
		sprPlayer->getActionManager()->removeAction(animationActionS);

		//ĳ���� �̵�
		auto action1 = MoveBy::create(MOVE_TIME, Point(0, SPEED));
		auto action2 = RepeatForever::create(action1);
		action2->setTag(18);//Tag_SPRTIE_PLAYER_ACTION_W
		sprPlayer->runAction(action2);

		//����Ű�� ���������� �ִϸ��̼�
		auto animation = Animation::create();
		animation->setDelayPerUnit(ANI_SPEED);

		for (int i = 13; i < 17; i++)
		{
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
			animation->addSpriteFrame(frame);
		}

		auto animate = Animate::create(animation);
		auto action = RepeatForever::create(animate);
		action->setTag(23);//���� �ִϸ��̼�
		sprPlayer->runAction(action);

		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_S:{ //SŰ�� ������ ��
		checkDown = true, Go_Down = true;

		if (Go_Event == false) { //�̺�Ʈ ���� �ʱ�ȭ
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

		//ĳ���� �̵� �׼�
		auto action1 = MoveBy::create(MOVE_TIME, Point(0, -SPEED));
		auto action2 = RepeatForever::create(action1);
		action2->setTag(19);//Tag_SPRTIE_PLAYER_ACTION_S
		sprPlayer->runAction(action2);

		//�Ʒ���Ű�� ���������� ĳ���� �ִϸ��̼�
		auto animation = Animation::create();
		animation->setDelayPerUnit(ANI_SPEED);

		for (int i = 1; i < 5; i++)
		{
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
			animation->addSpriteFrame(frame);
		}

		auto animate = Animate::create(animation);

		auto action = RepeatForever::create(animate);
		action->setTag(24);//�Ʒ��� �ִϸ��̼�

		sprPlayer->runAction(action);

		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE:{ //ESC���̾�(�Ͻ�����, �޴�)
		if (Go_Menu == false){ //�޴� â�� ����������
			Go_Menu = true;
			menuLayer5_1->setPosition(Point::ZERO);	//���̾� ���� 
			menuLayer5_1->setVisible(true);
			CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic(); //����
			Director::getInstance()->pause(); //���� ����
		}
		else if (Go_Menu == true)	{ //ESC���̾ Ȱ��ȭ ������ ��
			menuLayer5_1->setVisible(false); //���̾� �����
			Go_Menu = false;
			CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
			if (Go_Menu == false && goExpand == false && goMix == false && Go_Event == false && goHint == false){
				//�ٸ� â���� �� �������� ���� ���� �簳
				Director::getInstance()->resume();
			}
		}
		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_Q:{	//Ȯ�뷹�̾�
		if (Go_Menu == false && goExpand == false && Go_Event == false){	//ESC���̾�� Ȯ�� ���̾ ��Ȱ��ȭ �϶�
			if (goMix == true){
				mixLayer5_1->setVisible(false); //���շ��̾ ���������� ��Ȱ��ȭ��Ŵ
				goMix = false;
			}
			else if (goHint == true){ //��Ʈ���̾ ���������� ��Ȱ��ȭ��Ŵ
				hintLayer5_1->setVisible(false);
				goHint = false;
			}
			goExpand = true; //Ȯ�� ���̾� Ȱ��ȭ
			expandLayer5_1->setPosition(Point(Point(512, 384) + Point(0, 114)));
			expandLayer5_1->setVisible(true);
			mixLayer5_1->MixLayerOnOff = false;
			hintLayer5_1->HintLayerOnOff = false;
			expandLayer5_1->ExpandLayerOnOff = true;
			Director::getInstance()->pause();
		}
		else if (Go_Menu == false && goExpand == true){ //Ȯ�� ���̾ Ȱ��ȭ �϶�
			expandLayer5_1->setVisible(false); //Ȯ�뷹�̾� ��Ȱ��ȭ
			goExpand = false;
			expandLayer5_1->ExpandLayerOnOff = false;
			if (Go_Menu == false && goExpand == false && goMix == false && Go_Event == false && goHint == false){
				//�ٸ� ���̾���� ��� ��Ȱ��ȭ �϶� ���� �簳
				Director::getInstance()->resume();
			}
		}
		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_E:{	//���շ��̾�
		if (Go_Menu == false && goMix == false && Go_Event == false){
			if (goExpand == true){	//Ȯ�뷹�̾� Ȱ��ȭ�� ��Ȱ��ȭ ��Ŵ
				expandLayer5_1->setVisible(false);
				goExpand = false;
			}
			else if (goHint == true){	//��Ʈ���̾� Ȱ��ȭ�� ��Ȱ��ȭ ��Ŵ
				hintLayer5_1->setVisible(false);
				goHint = false;
			}
			goMix = true;	//���շ��̾� Ȱ��ȭ
			mixLayer5_1->setPosition(Point(Point(512, 498)));
			mixLayer5_1->setVisible(true);
			mixLayer5_1->MixLayerOnOff = true;
			hintLayer5_1->HintLayerOnOff = false;
			expandLayer5_1->ExpandLayerOnOff = false;
			Director::getInstance()->pause();
		}
		else if (Go_Menu == false && goMix == true){	//���շ��̾� Ȱ��ȭ�� ��Ȱ��ȭ ��Ű��
			mixLayer5_1->setVisible(false);
			goMix = false;
			mixLayer5_1->MixLayerOnOff = false;
			if (Go_Menu == false && goExpand == false && goMix == false && Go_Event == false && goHint == false){
				//��� ���̾���� ��Ȱ��ȭ�϶� �����簳
				Director::getInstance()->resume();
			}
		}
		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_H:{	//��Ʈ���̾�
		if (Go_Menu == false && goHint == false && Go_Event == false){
			if (goMix == true){	//���շ��̾� Ȱ��ȭ�� ��Ȱ��ȭ��Ű��
				mixLayer5_1->setVisible(false);
				goMix = false;
			}
			else if (goExpand == true){	//Ȯ�뷹�̾� Ȱ��ȭ�� ��Ȱ��ȭ ��Ű��
				expandLayer5_1->setVisible(false);
				goExpand = false;
			}
			goHint = true;	//��Ʈ���̾� Ȱ��ȭ
			hintLayer5_1->setPosition(Point(Point(512, 384) + Point(0, 114)));
			hintLayer5_1->setVisible(true);
			mixLayer5_1->MixLayerOnOff = false;
			hintLayer5_1->HintLayerOnOff = true;
			expandLayer5_1->ExpandLayerOnOff = false;
			Director::getInstance()->pause();
		}
		else if (Go_Menu == false && goHint == true){	//��Ʈ���̾� Ȱ��ȭ�� ��Ȱ��ȭ ��Ű��
			hintLayer5_1->setVisible(false);
			goHint = false;
			hintLayer5_1->HintLayerOnOff = false;
			if (Go_Menu == false && goExpand == false && goMix == false && Go_Event == false && goHint == false){
				//��緹�̾ ��Ȱ��ȭ�Ͻ� �����簳
				Director::getInstance()->resume();
			}
		}
		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:{	//�̺�Ʈ Ȱ��ȭ ��Ű��(�̺�Ʈ ������Ʈ������)
		if (goExpand == false && goMix == false && Go_Menu == false && Go_Event == false && goHint == false){
			//��� ���̾ ������������ Ȱ�������ϴ�.
			if (cleanBox == true){
				Go_Event = true;
				if (cleanBoxItem == false){
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Item_get.wav");
					GameScene5_1::CallCommunicationWindow(UTF8("�������� �ɷ��� �����."));
					mixLayer5_1->MapItemEvents(3);
					expandLayer5_1->MapItemEvents(51, 3);
					cleanBoxItem = true;
				}
				else if (cleanBoxItem == true && boxItem == false){
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Closet_Door_Safe_Carrier_Open.mp3");
					findBox = true;
					GameScene5_1::CallCommunicationWindow(UTF8("��й�ȣ�� �Է��ϼ���."));
					safeSPR->setPosition(Point(playerSprite->getPosition() + Point(0, ITEM_WINDOW_Y)));
					safeSPR->setVisible(true);
					star1->setPosition(Point(playerSprite->getPosition() + Point(46, 259)));
					star2->setPosition(Point(playerSprite->getPosition() + Point(105, 259)));
					star3->setPosition(Point(playerSprite->getPosition() + Point(164, 259)));
					star4->setPosition(Point(playerSprite->getPosition() + Point(223, 259)));
				}
				else if (cleanBoxItem == true && boxItem == true){
					GameScene5_1::CallCommunicationWindow(UTF8("�ƹ��͵� ����."));
				}
				Director::getInstance()->pause();
			}
			else if (window == true){
				Go_Event = true;
				if (cleanBoxItem == false){
					GameScene5_1::CallCommunicationWindow(UTF8("â���� ���� ������."));
				}
				else if (cleanBoxItem == true && cleanWindow == false){
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Map5-1/Cleaning_Window.mp3");
					GameScene5_1::CallCommunicationWindow(UTF8("�ɷ��� â���� �۾Ҵ�.\n\nâ���� ���𰡰� �����ִ�."));
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
					GameScene5_1::CallCommunicationWindow(UTF8("�վ�� �����."));
					mixLayer5_1->MapItemEvents(1);
					expandLayer5_1->MapItemEvents(51, 1);
					drainCleanerItem = true;
					DrainCleaner->setVisible(false);
					DrainCleaner->removeChild(DrainCleaner, true);
				}
				else if (drainCleanerItem == true){
					GameScene5_1::CallCommunicationWindow(UTF8("���� ���⿡�� �ƹ��͵� ����."));
				}
				Director::getInstance()->pause();
			}
			else if (toilet == true){
				Go_Event = true;
				if (drainCleanerItem == false){
					GameScene5_1::CallCommunicationWindow(UTF8("���Ⱑ ���� �ִ�. ����ü ���� û�Ҹ� �� ����?"));
				}
				else if (drainCleanerItem == true && toiletItem == false){
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Map5-1/Toilet_Flush.mp3");
					GameScene5_1::CallCommunicationWindow(UTF8("���⸦ �վ���� �վ���.\n\n�ֻ����� ȹ���ߴ�.\n\n�̰� �� ���⿡����?"));
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Item_get.wav");
					mixLayer5_1->MapItemEvents(4);
					expandLayer5_1->MapItemEvents(51, 4);
					toiletItem = true;
				}
				else if (drainCleanerItem == true && toiletItem == true){
					GameScene5_1::CallCommunicationWindow(UTF8("�ƹ��͵� ������ �ʴ´�."));
				}
				Director::getInstance()->pause();
			}
			else if (pot == true){
				Go_Event = true;
				if (potItems == false){
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Item_get.wav");
					GameScene5_1::CallCommunicationWindow(UTF8("�׾Ƹ� �ȿ� �ִ� ������ ȹ���ߴ�."));
					potItems = true;
					mixLayer5_1->MapItemEvents(2);
					expandLayer5_1->MapItemEvents(51, 2);
				}
				else if (potItems == true){
					GameScene5_1::CallCommunicationWindow(UTF8("�����⳪ ������?"));
				}
				Director::getInstance()->pause();
			}
			else if (spigot == true){
				Go_Event = true;
				if (boxItem == false){
					GameScene5_1::CallCommunicationWindow(UTF8("���������� ����."));
				}
				else if (boxItem == true && spigotItem == false){
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Item_get.wav");
					GameScene5_1::CallCommunicationWindow(UTF8("���������� ���� �־���.\n\n\n���踦 ȹ���ߴ�."));
					mixLayer5_1->MapItemEvents(51);
					expandLayer5_1->MapItemEvents(51, 51);
					mixLayer5_1->MapItemEvents(6);
					expandLayer5_1->MapItemEvents(51, 6);
					spigotItem = true;
				}
				else if (boxItem == true && spigotItem == true){
					GameScene5_1::CallCommunicationWindow(UTF8("���� ���� �� ���´�."));
				}
				Director::getInstance()->pause();
			}
			else if (womanFrame == true){
				Go_Event = true;
				if (spigotItem == false){
					GameScene5_1::CallCommunicationWindow(UTF8("���� ������ �ִ�."));
					womanFrameCutin->setPosition(Point(playerSprite->getPosition() + Point(0, ITEM_WINDOW_Y)));
					womanFrameCutin->setVisible(true);
				}
				else if (spigotItem == true && clockGear5 == false){
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Item_get.wav");
					GameScene5_1::CallCommunicationWindow(UTF8("����� ����� Ǯ����.\n\n\n��Ϲ����� ȹ���ߴ�."));
					mixLayer5_1->MapItemEvents(61);
					expandLayer5_1->MapItemEvents(51, 61);
					hintLayer5_1->findHint(5);
					clockGear5 = true;					
				}
				else if (spigotItem == true && clockGear5 == true){
					GameScene5_1::CallCommunicationWindow(UTF8("���� ����ִ�."));
				}
				Director::getInstance()->pause();
			}
			else if (door == true){
				Go_Event = true;
				if (clockGear5 == false){
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Map5/Door_Spigot_Put.mp3");
					GameScene5_1::CallCommunicationWindow(UTF8("���� ��Ϲ����� ã�� ���߾�."));
				}
				else if (clockGear5 == true){
					GameScene5_1::CallCommunicationWindow(UTF8("���� ���� ���� ������ ���̾�. � ���� ������ ������."));
					NextMap = true;
				}
				Director::getInstance()->pause();
			}
			else if (manFrame == true){
				Go_Event = true;
				GameScene5_1::CallCommunicationWindow(UTF8("ȭ��� ���׸�� ����� �Ű� �� �� ����."));
				Director::getInstance()->pause();
			}
			else if (bath == true){
				Go_Event = true;
				GameScene5_1::CallCommunicationWindow(UTF8("���� �ȿ� ������ �ִ�."));
				Director::getInstance()->pause();
			}
		}
		else if (Go_Menu == false && Go_Event == true){ // �̺�Ʈ Ȱ��ȭ ��
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

//Ű�Է�->Ű�� ������
void GameScene5_1::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	auto sprPlayer = (Sprite*)this->getChildByTag(11);	//�÷��̾� �±�(11)

	switch (keyCode){
	case cocos2d::EventKeyboard::KeyCode::KEY_A:{	//����Ű�� ���� ��
		//Ű üũ, �ִϸ��̼� �ʱ�ȭ
		Go_Left = false, checkLeft = false;
		checkRightAnimation = false, checkUpAnimation = false, checkDownAnimation = false;

		//ĳ���� �̵� �׼� ����
		auto action = (Action*)sprPlayer->getActionByTag(16);//(TAG_PLAYER_ACTION_A)
		sprPlayer->getActionManager()->removeAction(action);
		//ĳ���� �ִϸ��̼� ����
		auto animationAction = (Action*)sprPlayer->getActionByTag(21);
		sprPlayer->getActionManager()->removeAction(animationAction);

		//ĳ���� ���� ��������Ʈ ����
		if (checkLeft == false && checkRight == false && checkUp == false && checkDown == false &&
			goExpand == false && goMix == false && Go_Menu == false && Go_Event == false){
			sprPlayer->setSpriteFrame("sprites8.png");
		}

		if (checkRight == true && checkRightAnimation != true){//����Ű ���� ������Ű�� ����������

			auto actionD = (Action*)sprPlayer->getActionByTag(17);
			sprPlayer->getActionManager()->removeAction(actionD);

			auto animationActionD = (Action*)sprPlayer->getActionByTag(22);
			sprPlayer->getActionManager()->removeAction(animationActionD);

			checkRightAnimation = true;
			auto animation = Animation::create();
			animation->setDelayPerUnit(ANI_SPEED);

			//�ִϸ��̼� ����
			for (int i = 9; i < 13; i++){
				auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
				animation->addSpriteFrame(frame);
			}

			auto animate = Animate::create(animation);
			auto action = RepeatForever::create(animate);
			action->setTag(22);//������ �ִϸ��̼�2

			sprPlayer->runAction(action);

			auto action1 = MoveBy::create(MOVE_TIME, Point(SPEED, 0));
			auto action2 = RepeatForever::create(action1);
			action2->setTag(17);
			sprPlayer->runAction(action2);
		}
		if (checkUp == true && checkUpAnimation != true){// ����Ű ���� ����Ű�� ����������

			auto actionW = (Action*)sprPlayer->getActionByTag(18);//(TAG_PLAYER_ACTION_W)
			sprPlayer->getActionManager()->removeAction(actionW);

			auto animationActionW = (Action*)sprPlayer->getActionByTag(23);
			sprPlayer->getActionManager()->removeAction(animationActionW);

			checkUpAnimation = true;
			auto animation = Animation::create();
			animation->setDelayPerUnit(ANI_SPEED);

			//�ִϸ��̼� ����
			for (int i = 13; i < 17; i++){
				auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
				animation->addSpriteFrame(frame);
			}

			auto animate = Animate::create(animation);
			auto action = RepeatForever::create(animate);
			action->setTag(23);//���� �ִϸ��̼�2

			sprPlayer->runAction(action);

			auto action1 = MoveBy::create(MOVE_TIME, Point(0, SPEED));
			auto action2 = RepeatForever::create(action1);
			action2->setTag(18);//Tag_SPRTIE_PLAYER_ACTION_W
			sprPlayer->runAction(action2);
		}
		if (checkDown == true && checkDownAnimation != true){//����Ű ���� �Ʒ���Ű�� ����������

			auto actionS = (Action*)sprPlayer->getActionByTag(19);//(TAG_PLAYER_ACTION_S)
			sprPlayer->getActionManager()->removeAction(actionS);

			auto animationActionS = (Action*)sprPlayer->getActionByTag(24);
			sprPlayer->getActionManager()->removeAction(animationActionS);

			checkDownAnimation = true;
			auto animation = Animation::create();
			animation->setDelayPerUnit(ANI_SPEED);

			//�ִϸ��̼� ����
			for (int i = 1; i < 5; i++){
				auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
				animation->addSpriteFrame(frame);
			}

			auto animate = Animate::create(animation);
			auto action = RepeatForever::create(animate);
			action->setTag(24);//�Ʒ��� �ִϸ��̼�2

			sprPlayer->runAction(action);

			auto action1 = MoveBy::create(MOVE_TIME, Point(0, -SPEED));
			auto action2 = RepeatForever::create(action1);
			action2->setTag(19);//Tag_SPRTIE_PLAYER_ACTION_S
			sprPlayer->runAction(action2);
		}
		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_D:{//������ Ű�� ���� ��
		//üũ, �ִϸ��̼� �ʱ�ȭ
		Go_Right = false, checkRight = false;
		checkLeftAnimation = false, checkDownAnimation = false, checkUpAnimation = false;

		//������ �̵��׼� ����
		auto action = (Action*)sprPlayer->getActionByTag(17);//(TAG_PLAYER_ACTION_D)
		sprPlayer->getActionManager()->removeAction(action);
		//�ִϸ��̼� ����
		auto animationAction = (Action*)sprPlayer->getActionByTag(22);
		sprPlayer->getActionManager()->removeAction(animationAction);

		//ĳ���� ���� ��������Ʈ ����
		if (checkLeft == false && checkRight == false && checkUp == false && checkDown == false &&
			goExpand == false && goMix == false && Go_Menu == false && Go_Event == false){
			sprPlayer->setSpriteFrame("sprites12.png");
		}

		if (checkLeft == true && checkLeftAnimation != true){//������Ű�� ���� ����Ű�� ����������

			auto actionA = (Action*)sprPlayer->getActionByTag(16);//(TAG_PLAYER_ACTION_A)
			sprPlayer->getActionManager()->removeAction(actionA);

			auto animationActionA = (Action*)sprPlayer->getActionByTag(21);
			sprPlayer->getActionManager()->removeAction(animationActionA);

			checkLeftAnimation = true;
			auto animation = Animation::create();
			animation->setDelayPerUnit(ANI_SPEED);

			//�ִϸ��̼� ����
			for (int i = 5; i < 9; i++){
				auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
				animation->addSpriteFrame(frame);
			}

			auto animate = Animate::create(animation);
			auto action = RepeatForever::create(animate);
			action->setTag(21);//���� �ִϸ��̼�2

			sprPlayer->runAction(action);

			auto action1 = MoveBy::create(MOVE_TIME, Point(-SPEED, 0));
			auto action2 = RepeatForever::create(action1);
			action2->setTag(16);//Tag_SPRITE_PLAYER_ACTION_A
			sprPlayer->runAction(action2);
		}
		if (checkUp == true && checkUpAnimation != true){//������Ű�� ���� ����Ű�� ����������

			auto actionW = (Action*)sprPlayer->getActionByTag(18);//(TAG_PLAYER_ACTION_W)
			sprPlayer->getActionManager()->removeAction(actionW);

			auto animationActionW = (Action*)sprPlayer->getActionByTag(23);
			sprPlayer->getActionManager()->removeAction(animationActionW);

			checkUpAnimation = true;
			auto animation = Animation::create();
			animation->setDelayPerUnit(ANI_SPEED);

			//�ִϸ��̼� ����
			for (int i = 13; i < 17; i++){
				auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
				animation->addSpriteFrame(frame);
			}

			auto animate = Animate::create(animation);
			auto action = RepeatForever::create(animate);
			action->setTag(23);//���� �ִϸ��̼�2

			sprPlayer->runAction(action);

			auto action1 = MoveBy::create(MOVE_TIME, Point(0, SPEED));
			auto action2 = RepeatForever::create(action1);
			action2->setTag(18);//Tag_SPRTIE_PLAYER_ACTION_W
			sprPlayer->runAction(action2);
		}
		if (checkDown == true && checkDownAnimation != true){//������Ű�� ���� �Ʒ���Ű�� ����������

			auto actionS = (Action*)sprPlayer->getActionByTag(19);//(TAG_PLAYER_ACTION_S)
			sprPlayer->getActionManager()->removeAction(actionS);

			auto animationActionS = (Action*)sprPlayer->getActionByTag(24);
			sprPlayer->getActionManager()->removeAction(animationActionS);

			checkDownAnimation = true;
			auto animation = Animation::create();
			animation->setDelayPerUnit(ANI_SPEED);

			//�ִϸ��̼� ����
			for (int i = 1; i < 5; i++){
				auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
				animation->addSpriteFrame(frame);
			}

			auto animate = Animate::create(animation);
			auto action = RepeatForever::create(animate);
			action->setTag(24);//�Ʒ��� �ִϸ��̼�2

			sprPlayer->runAction(action);

			auto action1 = MoveBy::create(MOVE_TIME, Point(0, -SPEED));
			auto action2 = RepeatForever::create(action1);
			action2->setTag(19);//Tag_SPRTIE_PLAYER_ACTION_S
			sprPlayer->runAction(action2);
		}
		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_W:{//����Ű�� ���� ��
		//üũ, �ִϸ��̼� �ʱ�ȭ
		Go_Up = false, checkUp = false;
		checkLeftAnimation = false, checkRightAnimation = false, checkDownAnimation = false;

		//ĳ���� �̵� �׼� ����
		auto action = (Action*)sprPlayer->getActionByTag(18);//(TAG_PLAYER_ACTION_W)
		sprPlayer->getActionManager()->removeAction(action);
		//�ִϸ��̼� ����
		auto animationAction = (Action*)sprPlayer->getActionByTag(23);
		sprPlayer->getActionManager()->removeAction(animationAction);

		//ĳ���� ���� ��������Ʈ ����
		if (checkLeft == false && checkRight == false && checkUp == false && checkDown == false &&
			goExpand == false && goMix == false && Go_Menu == false && Go_Event == false){
			sprPlayer->setSpriteFrame("sprites16.png");
		}
		if (checkLeft == true && checkLeftAnimation != true){//����Ű�� ���� ����Ű�� ����������

			auto actionA = (Action*)sprPlayer->getActionByTag(16);//(TAG_PLAYER_ACTION_A)
			sprPlayer->getActionManager()->removeAction(actionA);

			auto animationActionA = (Action*)sprPlayer->getActionByTag(21);
			sprPlayer->getActionManager()->removeAction(animationActionA);

			checkLeftAnimation = true;
			auto animation = Animation::create();
			animation->setDelayPerUnit(ANI_SPEED);

			//�ִϸ��̼� ����
			for (int i = 5; i < 9; i++){
				auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
				animation->addSpriteFrame(frame);
			}

			auto animate = Animate::create(animation);
			auto action = RepeatForever::create(animate);
			action->setTag(21);//���� �ִϸ��̼�2

			sprPlayer->runAction(action);

			auto action1 = MoveBy::create(MOVE_TIME, Point(-SPEED, 0));
			auto action2 = RepeatForever::create(action1);
			action2->setTag(16);//Tag_SPRITE_PLAYER_ACTION_A
			sprPlayer->runAction(action2);
		}
		if (checkRight == true && checkRightAnimation != true){//����Ű�� ���� ������Ű�� ����������
			auto actionD = (Action*)sprPlayer->getActionByTag(17);//(TAG_PLAYER_ACTION_D)
			sprPlayer->getActionManager()->removeAction(actionD);

			auto animationActionD = (Action*)sprPlayer->getActionByTag(22);
			sprPlayer->getActionManager()->removeAction(animationActionD);

			checkRightAnimation = true;
			auto animation = Animation::create();
			animation->setDelayPerUnit(ANI_SPEED);

			//�ִϸ��̼� ����
			for (int i = 9; i < 13; i++){
				auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
				animation->addSpriteFrame(frame);
			}

			auto animate = Animate::create(animation);
			auto action = RepeatForever::create(animate);
			action->setTag(22);//������ �ִϸ��̼�2

			sprPlayer->runAction(action);

			auto action1 = MoveBy::create(MOVE_TIME, Point(SPEED, 0));
			auto action2 = RepeatForever::create(action1);
			action2->setTag(17);//Tag_SPRTIE_PLAYER_ACTION_D
			sprPlayer->runAction(action2);
		}
		if (checkDown == true && checkDownAnimation != true){//����Ű�� ���� �Ʒ���Ű�� ����������
			auto actionS = (Action*)sprPlayer->getActionByTag(19);//(TAG_PLAYER_ACTION_S)
			sprPlayer->getActionManager()->removeAction(actionS);

			auto animationActionS = (Action*)sprPlayer->getActionByTag(24);
			sprPlayer->getActionManager()->removeAction(animationActionS);

			checkDownAnimation = true;
			auto animation = Animation::create();
			animation->setDelayPerUnit(ANI_SPEED);

			//�ִϸ��̼� ����
			for (int i = 1; i < 5; i++){
				auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
				animation->addSpriteFrame(frame);
			}

			auto animate = Animate::create(animation);
			auto action = RepeatForever::create(animate);
			action->setTag(24);//�Ʒ��� �ִϸ��̼�2

			sprPlayer->runAction(action);

			auto action1 = MoveBy::create(MOVE_TIME, Point(0, -SPEED));
			auto action2 = RepeatForever::create(action1);
			action2->setTag(19);//Tag_SPRTIE_PLAYER_ACTION_S
			sprPlayer->runAction(action2);
		}
		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_S:{//�Ʒ��� Ű�� ������
		//üũ, �ִϸ��̼� �ʱ�ȭ
		Go_Down = false, checkDown = false;
		checkLeftAnimation = false, checkRightAnimation = false, checkUpAnimation = false;

		//ĳ���� �̵� �׼� ����
		auto action = (Action*)sprPlayer->getActionByTag(19);//(TAG_PLAYER_ACTION_S)
		sprPlayer->getActionManager()->removeAction(action);

		//�ִϸ��̼� ����
		auto animationAction = (Action*)sprPlayer->getActionByTag(24);
		sprPlayer->getActionManager()->removeAction(animationAction);

		//ĳ���� ���� ��������Ʈ ����
		if (checkLeft == false && checkRight == false && checkUp == false && checkDown == false &&
			goExpand == false && goMix == false && Go_Menu == false && Go_Event == false){
			sprPlayer->setSpriteFrame("sprites4.png");
		}

		if (checkLeft == true && checkLeftAnimation != true){//�Ʒ���Ű�� ���� ����Ű�� ����������
			auto actionA = (Action*)sprPlayer->getActionByTag(16);//(TAG_PLAYER_ACTION_A)
			sprPlayer->getActionManager()->removeAction(actionA);

			auto animationActionA = (Action*)sprPlayer->getActionByTag(21);
			sprPlayer->getActionManager()->removeAction(animationActionA);

			checkLeftAnimation = true;
			auto animation = Animation::create();
			animation->setDelayPerUnit(ANI_SPEED);

			//�ִϸ��̼� ����
			for (int i = 5; i < 9; i++){
				auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
				animation->addSpriteFrame(frame);
			}
			auto animate = Animate::create(animation);
			auto action = RepeatForever::create(animate);
			action->setTag(21);//���� �ִϸ��̼�2

			sprPlayer->runAction(action);

			auto action1 = MoveBy::create(MOVE_TIME, Point(-SPEED, 0));
			auto action2 = RepeatForever::create(action1);
			action2->setTag(16);//Tag_SPRITE_PLAYER_ACTION_A
			sprPlayer->runAction(action2);
		}
		if (checkRight == true && checkRightAnimation != true){//�Ʒ���Ű�� ���� ������Ű�� ����������
			auto actionD = (Action*)sprPlayer->getActionByTag(17);//(TAG_PLAYER_ACTION_D)
			sprPlayer->getActionManager()->removeAction(actionD);

			auto animationActionD = (Action*)sprPlayer->getActionByTag(22);
			sprPlayer->getActionManager()->removeAction(animationActionD);

			checkRightAnimation = true;
			auto animation = Animation::create();
			animation->setDelayPerUnit(ANI_SPEED);

			//�ִϸ��̼� ����
			for (int i = 9; i < 13; i++){
				auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
				animation->addSpriteFrame(frame);
			}

			auto animate = Animate::create(animation);
			auto action = RepeatForever::create(animate);
			action->setTag(22);//������ �ִϸ��̼�2

			sprPlayer->runAction(action);

			auto action1 = MoveBy::create(MOVE_TIME, Point(SPEED, 0));
			auto action2 = RepeatForever::create(action1);
			action2->setTag(17);//Tag_SPRTIE_PLAYER_ACTION_D
			sprPlayer->runAction(action2);
		}
		if (checkUp == true && checkUpAnimation != true){//�Ʒ���Ű�� ���� ����Ű�� ����������
			auto actionW = (Action*)sprPlayer->getActionByTag(18);//(TAG_PLAYER_ACTION_W)
			sprPlayer->getActionManager()->removeAction(actionW);

			auto animationActionW = (Action*)sprPlayer->getActionByTag(23);
			sprPlayer->getActionManager()->removeAction(animationActionW);

			checkUpAnimation = true;
			auto animation = Animation::create();
			animation->setDelayPerUnit(ANI_SPEED);

			//�ִϸ��̼� ����
			for (int i = 13; i < 17; i++){
				auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
				animation->addSpriteFrame(frame);
			}

			auto animate = Animate::create(animation);
			auto action = RepeatForever::create(animate);
			action->setTag(23);//���� �ִϸ��̼�2

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

// 1�ʿ� 60������
void GameScene5_1::CallEveryFrame(float f)
{
	auto sprPlayer = (Sprite*)this->getChildByTag(11); //�÷��̾� �±�
	this->setViewPointCenter(playerSprite->getPosition()); //ī�޶�

	if (checkLeft){
		CCPoint playerPos1 = sprPlayer->getPosition();
		CCPoint playerPos2 = sprPlayer->getPosition();

		CCPoint tileCoord1 = this->tileCoordForPosition(playerPos1 + Point(-BREAK_TOO_X, BREAK_ZERO_Y));//�»��
		CCPoint tileCoord2 = this->tileCoordForPosition(playerPos2 + Point(-BREAK_TOO_X, -BREAK_DOWN_Y));//���ϴ�

		unsigned int tileGid1 = _background->tileGIDAt(tileCoord1);
		unsigned int tileGid2 = _background->tileGIDAt(tileCoord2);

		auto properties1 = _tileMap->propertiesForGID(tileGid1);
		auto properties2 = _tileMap->propertiesForGID(tileGid2);

		ValueMap map1 = properties1.asValueMap();
		ValueMap map2 = properties2.asValueMap();

		String propertyValue1 = map1["Collidable"].asString();//�浹üũ
		String propertyValue2 = map2["Collidable"].asString();
		String pot1 = map1["Pot"].asString();//�׾Ƹ�
		String pot2 = map2["Pot"].asString();

		if (propertyValue1.compare("True") == 0 || propertyValue2.compare("True") == 0){
			auto action = (Action*)sprPlayer->getActionByTag(16);

			sprPlayer->getActionManager()->removeAction(action);
			Go_Left = false;
		}
		else{
			if (!Go_Left){
				Go_Left = true;
				//ĳ���� �̵� �׼�
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

		CCPoint tileCoord1 = this->tileCoordForPosition(playerPos1 + Point(BREAK_TOO_X, BREAK_ZERO_Y));//����
		CCPoint tileCoord2 = this->tileCoordForPosition(playerPos2 + Point(BREAK_TOO_X, -BREAK_DOWN_Y));//���ϴ�

		unsigned int tileGid1 = _background->tileGIDAt(tileCoord1);
		unsigned int tileGid2 = _background->tileGIDAt(tileCoord2);

		auto properties1 = _tileMap->propertiesForGID(tileGid1);
		auto properties2 = _tileMap->propertiesForGID(tileGid2);

		ValueMap map1 = properties1.asValueMap();
		ValueMap map2 = properties2.asValueMap();

		String propertyValue1 = map1["Collidable"].asString();//�浹üũ
		String propertyValue2 = map2["Collidable"].asString();
		String bath1 = map1["Bath"].asString();//����
		String bath2 = map2["Bath"].asString();
		String toilet1 = map1["Toilet"].asString();//����
		String toilet2 = map2["Toilet"].asString();

		if (propertyValue1.compare("True") == 0 || propertyValue2.compare("True") == 0){
			auto action = (Action*)sprPlayer->getActionByTag(17);

			sprPlayer->getActionManager()->removeAction(action);

			Go_Right = false;
		}
		else{
			if (!Go_Right){
				Go_Right = true;
				//ĳ���� �̵� �׼�
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

		CCPoint tileCoord1 = this->tileCoordForPosition(playerPos1 + Point(BREAK_X, BREAK_UP_Y));//����
		CCPoint tileCoord2 = this->tileCoordForPosition(playerPos2 + Point(-BREAK_X, BREAK_UP_Y));//�»��

		unsigned int tileGid1 = _background->tileGIDAt(tileCoord1);
		unsigned int tileGid2 = _background->tileGIDAt(tileCoord2);

		auto properties1 = _tileMap->propertiesForGID(tileGid1);
		auto properties2 = _tileMap->propertiesForGID(tileGid2);

		ValueMap map1 = properties1.asValueMap();
		ValueMap map2 = properties2.asValueMap();

		String propertyValue1 = map1["Collidable"].asString();//�浹üũ
		String propertyValue2 = map2["Collidable"].asString();
		String cleanBox1 = map1["CleanBox"].asString();//û�ҵ�����, ����
		String cleanBox2 = map2["CleanBox"].asString();
		String window1 = map1["Window"].asString();//â��
		String window2 = map2["Window"].asString();
		String manFrame1 = map1["ManFrame"].asString();//���� ����
		String manFrame2 = map2["ManFrame"].asString();
		String womanFrame1 = map1["WomanFrame"].asString();//���� ����
		String womanFrame2 = map2["WomanFrame"].asString();
		String spigot1 = map1["Spigot"].asString();//�����
		String spigot2 = map2["Spigot"].asString();
		String drainCleaner1 = map1["DrainCleaner"].asString();//�վ
		String drainCleaner2 = map2["DrainCleaner"].asString();
		String toilet1 = map1["Toilet"].asString();//����
		String toilet2 = map2["Toilet"].asString();

		if (propertyValue1.compare("True") == 0 || propertyValue2.compare("True") == 0){
			auto action = (Action*)sprPlayer->getActionByTag(18);

			sprPlayer->getActionManager()->removeAction(action);
			Go_Up = false;
		}
		else{
			if (!Go_Up){
				Go_Up = true;
				//ĳ���� �̵� �׼� 
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

		CCPoint tileCoord1 = this->tileCoordForPosition(playerPos1 + Point(BREAK_X, -BREAK_TOO_DOWN_Y));//���ϴ�
		CCPoint tileCoord2 = this->tileCoordForPosition(playerPos2 + Point(-BREAK_X, -BREAK_TOO_DOWN_Y));//���ϴ�

		unsigned int tileGid1 = _background->tileGIDAt(tileCoord1);
		unsigned int tileGid2 = _background->tileGIDAt(tileCoord2);

		auto properties1 = _tileMap->propertiesForGID(tileGid1);
		auto properties2 = _tileMap->propertiesForGID(tileGid2);

		ValueMap map1 = properties1.asValueMap();
		ValueMap map2 = properties2.asValueMap();

		String propertyValue1 = map1["Collidable"].asString();//�浹üũ
		String propertyValue2 = map2["Collidable"].asString();
		String pot1 = map1["Pot"].asString();//�׾Ƹ�
		String pot2 = map2["Pot"].asString();
		String door1 = map1["Door"].asString();//��
		String door2 = map2["Door"].asString();

		if (propertyValue1.compare("True") == 0 || propertyValue2.compare("True") == 0){
			auto action = (Action*)sprPlayer->getActionByTag(19);

			sprPlayer->getActionManager()->removeAction(action);
			Go_Down = false;
		}
		else{
			if (!Go_Down){
				Go_Down = true;
				//ĳ���� �̵� �׼�
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

//���콺 ���뵵 -> ������
void GameScene5_1::onMouseDown(cocos2d::Event* event){
	EventMouse* e = (EventMouse*)event;

	Point result = Point(e->getCursorX(), e->getCursorY());
	//���콺 Ŀ�� ��ġ �ޱ�

	Rect button1 = Rect(531, 515, 56, 56); //�ݰ� 1�� ��ư
	Rect button2 = Rect(617, 515, 56, 56); //�ݰ� 2�� ��ư
	Rect button3 = Rect(703, 515, 56, 56); //�ݰ� 3�� ��ư
	Rect button4 = Rect(531, 447, 56, 56); //�ݰ� 4�� ��ư
	Rect button5 = Rect(617, 447, 56, 56); //�ݰ� 5�� ��ư
	Rect button6 = Rect(703, 447, 56, 56); //�ݰ� 6�� ��ư
	Rect button7 = Rect(531, 379, 56, 56); //�ݰ� 7�� ��ư
	Rect button8 = Rect(617, 379, 56, 56); //�ݰ� 8�� ��ư
	Rect button9 = Rect(703, 379, 56, 56); //�ݰ� 9�� ��ư 
	Rect buttonC = Rect(531, 311, 56, 56); //�ݰ� C�� ��ư
	Rect button0 = Rect(617, 311, 56, 56); //�ݰ� 0�� ��ư
	Rect buttonE = Rect(703, 311, 56, 56); //�ݰ� E�� ��ư

	/*
	�ý��� ����

	��ư�� ������ blink������ 1�� �����Ѵ� �̰ɷ� ��й�ȣ�� ��ġ�� �˾Ƴ���.
	4���� �� �Է����� �� �ٸ��� �� �ʱ�ȭ ���� �� ������ ȹ��

	C��ư ������ ��ȣ �ʱ�ȭ -> ���찳 ��ư
	E��ư ������ ��ȣ �Է� ->�´� ��ȣ���� �Ǵ�
	*/
	if (Go_Event == true){ //���� ������(�ݰ�) �̺�Ʈ Ȱ��ȭ ��
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
				CallCommunicationWindow(UTF8("�ݰ��� ����� Ǯ����.\n\n\n���������� �߰��ߴ�."));
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
				CallCommunicationWindow(UTF8("�߸��� ��й�ȣ����."));
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