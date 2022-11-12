#include "GAME_SCENE_2.h"
#include "SimpleAudioEngine.h"
#include "MENU_SCENE.h"
#include "Menu_Layer.h"
#include "ExpandLayer.h"
#include "MixLayer.h"
#include "Hint_Layer.h"
#include "GAME_SCENE_3.h"

ExpandMenuLayer* expandLayer2;
MenuLayer* menuLayer2;
MixMenuLayer* mixLayer2;
HintLayer* hintLayer2;

Scene* GameScene2::createScene()
{
	auto scene = Scene::create();

	auto layer = GameScene2::create();

	scene->addChild(layer);

	//Ȯ�� ���̾�
	expandLayer2 = ExpandMenuLayer::create();
	expandLayer2->setVisible(false);
	scene->addChild(expandLayer2, 4);

	//���� ���̾�
	mixLayer2 = MixMenuLayer::create();
	mixLayer2->setVisible(false);
	scene->addChild(mixLayer2, 4);

	//�޴� ���̾�
	menuLayer2 = MenuLayer::create();
	menuLayer2->setVisible(false);
	scene->addChild(menuLayer2, 5);

	//��Ʈ ���̾�
	hintLayer2 = HintLayer::create();
	hintLayer2->setVisible(false);
	scene->addChild(hintLayer2, 4);

	//�� ���� ����
	expandLayer2->KnowMapLevel(2);
	mixLayer2->KnowMapLevel(2);
	hintLayer2->findHint(0);
	hintLayer2->findHint(1);
	return scene;
}

bool GameScene2::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//ȿ���� �ҷ�����
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Map2/Coin.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Map2/USB_Laptop.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Closet_Door_Close.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Closet_Door_Safe_Carrier_Open.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/door_open.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Safe_Close.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/password.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Drawer_close.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Map5/Door_Spigot_Put.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/password.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Map6/Book_Turning_Pages.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Map1/Carpet_Bed.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Item_get.wav");
	
	//plist �ҷ�����
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("./Characters/sprites.plist");

	//Ÿ�ϸ� �ҷ�����
	_tileMap = CCTMXTiledMap::create("./Maps/Map2.tmx");
	_background = _tileMap->getLayer("Background2");
	this->addChild(_tileMap, 0);

	//�ʹٲٱ�
	mapChange = Sprite::create("./Maps/Map2OFF.png");
	mapChange->setPosition(Point::ZERO);
	mapChange->setAnchorPoint(Point::ZERO);
	this->addChild(mapChange, 0);

	//��ǥ����, �÷��̾� ������ǥ �� ������Ʈ �߰�
	playerSpawn = _tileMap->objectGroupNamed("PlayerSpawn2");

	if (playerSpawn == NULL){
		return false;
	}

	ValueMap spawnPoint = playerSpawn->getObject("PlayerSpawnXY2");

	//ĳ���� ���� ��ǥ����
	characterX = spawnPoint["x"].asInt();
	characterY = spawnPoint["y"].asInt();

	//�÷��̾� �����
	playerSprite = Sprite::createWithSpriteFrameName("sprites4.png");
	playerSprite->setPosition(Point(characterX, characterY));
	playerSprite->setTag(11);
	this->addChild(playerSprite, 1, 11);

	//��ȭâ ����
	communication = Sprite::create("./Layers/communication.png");
	communication->setPosition(playerSprite->getPosition() + Point(0, -254));
	communication->setOpacity(255);
	communication->setVisible(false);
	this->addChild(communication, 3);
	
	//��Ʈ�� ����
	laptopCutIn = Sprite::create("./Items/Map2/laptop.png");
	laptopCutIn->setPosition(Point(playerSprite->getPosition() + Point(0, ITEM_WINDOW_Y)));
	laptopCutIn->setVisible(false);
	this->addChild(laptopCutIn, 2);

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

	//������Ʈ
	this->schedule(schedule_selector(GameScene2::CallEveryFrame));

	//Ű���� ������
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(GameScene2::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(GameScene2::onKeyReleased, this);

	//���콺 ������
	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseDown = CC_CALLBACK_1(GameScene2::onMouseDown, this);
	mouseListener->onMouseUp = CC_CALLBACK_1(GameScene2::onMouseUp, this);

	// regist listener to dispatcher
	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
	eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

	Director::getInstance()->resume();
	return true;
}

//Ÿ�ϸ�
CCPoint GameScene2::tileCoordForPosition(CCPoint position){
	int x = position.x / _tileMap->getTileSize().width;
	int y = ((_tileMap->getMapSize().height* _tileMap->getTileSize().height) - position.y) / _tileMap->getTileSize().height;
	return ccp(x, y);
}
//ī�޶�
void GameScene2::setViewPointCenter(CCPoint position){
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
void GameScene2::CallCommunicationWindow(std::string info){

	communication->setPosition(playerSprite->getPosition() + Point(0, -254));
	communication->setVisible(true);

	Texts = Label::createWithTTF(info, "./Moris.ttf", 30, Size(630, 150));
	Texts->setPosition(playerSprite->getPosition() + Point(0, -262));
	Texts->setColor(ccc3(0, 0, 0));
	this->addChild(Texts, 4);
}
//��ȭâ �����
void GameScene2::BackCommunicationWindow(){
	communication->setVisible(false);
	Texts->setVisible(false);
	Texts->removeChild(Texts, true);
}
//�޴��� ���ư���
void GameScene2::changeMenuScene_R(Ref *sender){
	Director::getInstance()->replaceScene(MenuScene::createScene());
}
//������ �̵�
void GameScene2::changeGameScene3_R(Ref *sender){
	auto scene = TransitionFade::create(3, GameScene3::createScene());
	Director::getInstance()->replaceScene(scene);
}
//Ű �Է� �޾��� ��
void GameScene2::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event){
	//ĳ���� ��������Ʈ �±� �޾ƿ���
	auto sprPlayer = (Sprite*)this->getChildByTag(11);

	switch (keyCode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_A:{//AŰ�� ������ ��
		//�̵� ���� �ʱ�ȭ
		checkLeft = true, Go_Left = true;
		if (Go_Event == false){ //�̺�Ʈ ���� �ʱ�ȭ
			laptop = false, deskDrawer = false;
			safe = false, door = false, coinBank = false;
			drawer = false, bookshelf = false, bed = false;
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

		for (int i = 5; i < 9; i++){ //��������Ʈ �ִϸ��̼�
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
			animation->addSpriteFrame(frame);
		}

		auto animate = Animate::create(animation);
		auto action = RepeatForever::create(animate);
		action->setTag(21);//���� �ִϸ��̼�
		sprPlayer->runAction(action);

		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_D:{ //DŰ�� ������ ��
		//�̵� ���� �ʱ�ȭ
		checkRight = true, Go_Right = true;
		if (Go_Event == false) { //�̺�Ʈ ���� �ʱ�ȭ
			laptop = false, deskDrawer = false;
			safe = false, door = false, coinBank = false;
			drawer = false, bookshelf = false, bed = false;
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

		for (int i = 9; i < 13; i++)	{ //��������Ʈ �ִϸ��̼�
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
		//�̵� ���� �ʱ�ȭ
		checkUp = true, Go_Up = true;
		if (Go_Event == false) { //�̺�Ʈ ���� �ʱ�ȭ
			laptop = false, deskDrawer = false;
			safe = false, door = false, coinBank = false;
			drawer = false, bookshelf = false, bed = false;
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

		for (int i = 13; i < 17; i++){ //��������Ʈ �ִϸ��̼�
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
		//�̵� ���� �ʱ�ȭ
		checkDown = true, Go_Down = true;
		if (Go_Event == false){ //�̺�Ʈ ���� �ʱ�ȭ
			laptop = false, deskDrawer = false;
			safe = false, door = false, coinBank = false;
			drawer = false, bookshelf = false, bed = false;
		}
		//������ �׼� ����
		auto actionA = (Action*)sprPlayer->getActionByTag(16);//(TAG_PLAYER_ACTION_S)
		sprPlayer->getActionManager()->removeAction(actionA);
		auto actionD = (Action*)sprPlayer->getActionByTag(17);//(TAG_PLAYER_ACTION_D)
		sprPlayer->getActionManager()->removeAction(actionD);
		auto actionW = (Action*)sprPlayer->getActionByTag(18);//(TAG_PLAYER_ACTION_W)
		sprPlayer->getActionManager()->removeAction(actionW);
		//������ �ִϸ��̼� ����
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

		for (int i = 1; i < 5; i++){ //��������Ʈ �ִϸ��̼�
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
			animation->addSpriteFrame(frame);
		}

		auto animate = Animate::create(animation);
		auto action = RepeatForever::create(animate);
		action->setTag(24); //�Ʒ��� �ִϸ��̼�
		sprPlayer->runAction(action);

		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE:{ //�޴� ���̾�
		if (Go_Menu == false){
			Go_Menu = true;
			menuLayer2->setPosition(Point::ZERO);
			menuLayer2->setVisible(true);
			CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
			Director::getInstance()->pause();
		}
		else if (Go_Menu == true)	{
			menuLayer2->setVisible(false);
			Go_Menu = false;
			CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
			if (Go_Menu == false && goExpand == false && goMix == false && Go_Event == false && goHint == false){
				Director::getInstance()->resume();
			}
		}
		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_Q:{ //Ȯ�� ���̾�
		if (Go_Menu == false && goExpand == false && Go_Event == false){ //�ٸ� ���̾ ���������� ���ְ� ������ (�޴� ���̾� ����)
			if (goMix == true){
				mixLayer2->setVisible(false);
				goMix = false;
			}
			else if (goHint == true){
				hintLayer2->setVisible(false);
				goHint = false;
			}
			goExpand = true;
			expandLayer2->setPosition(Point(Point(LAYERS_X, LAYERS_Y)));
			expandLayer2->setVisible(true);
			mixLayer2->MixLayerOnOff = false;
			hintLayer2->HintLayerOnOff = false;
			expandLayer2->ExpandLayerOnOff = true;
			Director::getInstance()->pause();
		}
		else if (Go_Menu == false && goExpand == true){
			expandLayer2->setVisible(false);
			goExpand = false;
			expandLayer2->ExpandLayerOnOff = false;
			if (Go_Menu == false && goExpand == false && goMix == false && Go_Event == false && goHint == false){
				Director::getInstance()->resume();
			}
		}
		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_E:{ //���� ���̾�
		if (Go_Menu == false && goMix == false && Go_Event == false){ //�ٸ� ���̾ ���������� ���ְ� ������ (�޴� ���̾� ����)
			if (goExpand == true){
				expandLayer2->setVisible(false);
				goExpand = false;
			}
			else if (goHint == true){
				hintLayer2->setVisible(false);
				goHint = false;
			}
			goMix = true;
			mixLayer2->setPosition(Point(Point(LAYERS_X, LAYERS_Y)));
			mixLayer2->setVisible(true);
			mixLayer2->MixLayerOnOff = true;
			hintLayer2->HintLayerOnOff = false;
			expandLayer2->ExpandLayerOnOff = false;
			Director::getInstance()->pause();
		}
		else if (Go_Menu == false && goMix == true){
			mixLayer2->setVisible(false);
			goMix = false;
			mixLayer2->MixLayerOnOff = false;
			if (Go_Menu == false && goExpand == false && goMix == false && Go_Event == false && goHint == false){
				Director::getInstance()->resume();
			}
		}
		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_H:{ //��Ʈ ���̾�
		if (Go_Menu == false && goHint == false && Go_Event == false){ //�ٸ� ���̾ ���������� ���ְ� ������ (�޴� ���̾� ����)
			if (goMix == true){
				mixLayer2->setVisible(false);
				goMix = false;
			}
			else if (goExpand == true){
				expandLayer2->setVisible(false);
				goExpand = false;
			}
			goHint = true;
			hintLayer2->setPosition(Point(Point(LAYERS_X, LAYERS_Y)));
			hintLayer2->setVisible(true);
			mixLayer2->MixLayerOnOff = false;
			hintLayer2->HintLayerOnOff = true;
			expandLayer2->ExpandLayerOnOff = false;
			Director::getInstance()->pause();
		}
		else if (Go_Menu == false && goHint == true){
			hintLayer2->setVisible(false);
			goHint = false;
			hintLayer2->HintLayerOnOff = false;
			if (Go_Menu == false && goExpand == false && goMix == false && Go_Event == false && goHint == false){
				Director::getInstance()->resume();
			}
		}
		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:{ //�̺�Ʈ �߻�
		if (goExpand == false && goMix == false && Go_Menu == false && Go_Event == false && goHint == false){
			if (bed == true){ //ħ��
				Go_Event = true;
				GameScene2::CallCommunicationWindow(UTF8("ħ�밡 ǫ��ǫ�� �غ��δ�."));
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Map1/Carpet_Bed.mp3");
				Director::getInstance()->pause();
			}
			if (drawer == true){ //������
				Go_Event = true;
				GameScene2::CallCommunicationWindow(UTF8("å�� ������ ���� ���� ����..."));
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Closet_Door_Close.mp3");
				Director::getInstance()->pause();
			}
			if (bookshelf == true){ //å����
				Go_Event = true;
				GameScene2::CallCommunicationWindow(UTF8("å�� �ʹ�����."));
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Map6/Book_Turning_Pages.wav");
				Director::getInstance()->pause();
			}
			if (laptop == true){ //��Ʈ��
				Go_Event = true;
				if (deskDrawerItem == false && putUSB == false){
					GameScene2::CallCommunicationWindow(UTF8("��Ʈ�Ͽ� ���𰡸� ���� �� �ִ� ������ �ִ�."));
				}
				else if (deskDrawerItem == true && putUSB == false){
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Map2/USB_Laptop.mp3");
					GameScene2::CallCommunicationWindow(UTF8("USB�� �ȾҴ�."));
					expandLayer2->MapItemEvents(2, 11);
					mixLayer2->MapItemEvents(11);
					mapChange->setVisible(false);
					removeChild(mapChange, true);
					putUSB = true;
				}
				else if (deskDrawerItem == true && putUSB == true){
					GameScene2::CallCommunicationWindow(UTF8("�� �� ���� ���ڰ� �����ִ�."));
					laptopCutIn->setPosition(Point(playerSprite->getPosition() + Point(0, ITEM_WINDOW_Y)));
					laptopCutIn->setVisible(true);
				}
				Director::getInstance()->pause();
			}
			if (deskDrawer == true){ //å��
				Go_Event = true;
				if (deskDrawerItem == false){
					expandLayer2->MapItemEvents(2,1);
					mixLayer2->MapItemEvents(1);
					deskDrawerItem = true;
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Item_get.wav");
					GameScene2::CallCommunicationWindow(UTF8("USB�� �߰��ߴ�."));
				}
				else if (deskDrawerItem == true){
					GameScene2::CallCommunicationWindow(UTF8("å���̴�."));
				}
				Director::getInstance()->pause();
			}
			if (coinBank == true){ //������
				Go_Event = true;
				if (safeItem == false){
					GameScene2::CallCommunicationWindow(UTF8("�����뿡 ���� ���� ����."));
				}
				else if (safeItem == true){
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Map2/Coin.wav");
					GameScene2::CallCommunicationWindow(UTF8("������ �־����� �����ڿ��� ���𰡰� ���Դ�...\n\n\n��Ϲ����� ȹ���ߴ�."));
					hintLayer2->findHint(2);
					mixLayer2->MapItemEvents(21);
					expandLayer2->MapItemEvents(2, 21);
					continueTalk = true;
					clockGear2 = true;
					safeItem = false;
				}
				Director::getInstance()->pause();
			}
			if (door == true){ //��
				Go_Event = true;
				if (clockGear2 == false){
					GameScene2::CallCommunicationWindow(UTF8("���⿡�� ���� ��������..."));
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Map5/Door_Spigot_Put.mp3");
				}
				else if (clockGear2 == true){
					GameScene2::CallCommunicationWindow(UTF8("�Ƹ� ������ �����ڵ� ������ ��Ϲ����� ���ܳ��� �� ����.\n������ �ִ� ��� ��Ϲ����� ã�� �� ��¥ ��Ϲ����� ã�Ƴ���!"));
					nextMap = true;
				}
				Director::getInstance()->pause();
			}
			if (safe == true){ //�ݰ�
				Go_Event = true;
				if (openCloset == false){
					GameScene2::CallCommunicationWindow(UTF8("����ȿ� �ݰ� �־���."));
					openCloset = true;
				}
				else if (openCloset == true && safeItem == false){
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Closet_Door_Safe_Carrier_Open.mp3");
					GameScene2::CallCommunicationWindow(UTF8("��й�ȣ�� �ɷ��ִ�.."));
					safeSPR->setPosition(Point(playerSprite->getPosition() + Point(0, ITEM_WINDOW_Y)));
					safeSPR->setVisible(true);
					star1->setPosition(Point(playerSprite->getPosition() + Point(safeStarX1, safeStarY)));
					star2->setPosition(Point(playerSprite->getPosition() + Point(safeStarX2, safeStarY)));
					star3->setPosition(Point(playerSprite->getPosition() + Point(safeStarX3, safeStarY)));
					star4->setPosition(Point(playerSprite->getPosition() + Point(safeStarX4, safeStarY)));
					}
				else if (openCloset == true && safeItem == true){
					GameScene2::CallCommunicationWindow(UTF8("���� �ݰ� �ȿ��� �ƹ��͵� ������� �ʴ�."));
				}
				Director::getInstance()->pause();
			}
		}

		else if (Go_Menu == false && Go_Event == true){ //�̺�Ʈ ����
			if (door == true && nextMap == true && continueTalk == false){ //��
				GameScene2::BackCommunicationWindow();
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/door_open.mp3");
				//ü���� ��
				GameScene2::changeGameScene3_R(this);
			}
			else if (door == true && nextMap == true && continueTalk == true){
				GameScene2::BackCommunicationWindow();
				continueTalk = false;
				Go_Event = false;
				Director::getInstance()->resume();
			}
			else if (safe == true){ //�ݰ�
				Go_Event = false;
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Drawer_close.mp3");
				if (openCloset == true && safeItem == false){
					GameScene2::BackCommunicationWindow();
					safeSPR->setVisible(false);
					star1->setVisible(false);
					star2->setVisible(false);
					star3->setVisible(false);
					star4->setVisible(false);
					blink = 1;
					password1 = NULL;
					password2 = NULL;
					password3 = NULL;
					password4 = NULL;
				}
				else if (openCloset == true && safeItem == true){
					GameScene2::BackCommunicationWindow();
				}
				Director::getInstance()->resume();
			}
			else if (bed == true || drawer == true || bookshelf == true ||
				deskDrawer == true || door == true){ //ħ��, ������, å����. å��, ��
				Go_Event = false;
				GameScene2::BackCommunicationWindow();
				Director::getInstance()->resume();
			}
			else if (laptop == true){ // ��Ʈ��
				Go_Event = false;
				if (putUSB == false){
					GameScene2::BackCommunicationWindow();
				}
				else if (putUSB == true){
					laptopCutIn->setVisible(false);
					GameScene2::BackCommunicationWindow();
				}
				Director::getInstance()->resume();
			}
			else if (coinBank == true){ //������
				if (continueTalk == false){
					Go_Event = false;
					GameScene2::BackCommunicationWindow();
					Director::getInstance()->resume();
				}
				else if (continueTalk == true){
					GameScene2::BackCommunicationWindow();
					GameScene2::CallCommunicationWindow(UTF8("�̰� ��Ϲ����ݾ�? �׷� �Ʊ� ���� �߰��� �� ����?"));
					continueTalk = false;
				}
			}
		}
		break;
	}
	}
}
//Ű ������
void GameScene2::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event){

	auto sprPlayer = (Sprite*)this->getChildByTag(11);//PLAYER_SPRITE_TAG

	switch (keyCode){
	case cocos2d::EventKeyboard::KeyCode::KEY_A:{ //AŰ�� ���� ��
		//�̵� ���� �ʱ�ȭ
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
	case cocos2d::EventKeyboard::KeyCode::KEY_D:{ //DŰ�� ���� ��
		//�̵� ���� �ʱ�ȭ
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
	case cocos2d::EventKeyboard::KeyCode::KEY_W:{ //WŰ�� ���� ��
		//�̵����� �ʱ�ȭ
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
	case cocos2d::EventKeyboard::KeyCode::KEY_S:{ //SŰ�� ���� ��
		//�̵� ���� �ʱ�ȭ
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
//������Ʈ 60������
void GameScene2::CallEveryFrame(float f){

	auto sprPlayer = (Sprite*)this->getChildByTag(11);
	this->setViewPointCenter(playerSprite->getPosition());

	if (checkLeft){
		CCPoint playerPos1 = sprPlayer->getPosition();
		CCPoint playerPos2 = sprPlayer->getPosition();

		CCPoint tileCoord1 = this->tileCoordForPosition(playerPos1 + Point(-BREAK_TOO_X, BREAK_ZERO_Y));//���ϴ�
		CCPoint tileCoord2 = this->tileCoordForPosition(playerPos2 + Point(-BREAK_TOO_X, -BREAK_DOWN_Y));//�»��

		unsigned int tileGid1 = _background->tileGIDAt(tileCoord1);
		unsigned int tileGid2 = _background->tileGIDAt(tileCoord2);

		auto properties1 = _tileMap->propertiesForGID(tileGid1);
		auto properties2 = _tileMap->propertiesForGID(tileGid2);

		ValueMap map1 = properties1.asValueMap();
		ValueMap map2 = properties2.asValueMap();

		String propertyValue1 = map1["Collidable"].asString();//�浹üũ
		String propertyValue2 = map2["Collidable"].asString();
		String deskDrawer1 = map1["DeskDrawer"].asString();//å��
		String deskDrawer2 = map2["DeskDrawer"].asString();

		if (propertyValue1.compare("True") == 0 || propertyValue2.compare("True") == 0){
			auto action = (Action*)sprPlayer->getActionByTag(16);

			sprPlayer->getActionManager()->removeAction(action);
			Go_Left = false;
		}
		else{
			if (!Go_Left){
				Go_Left = true;

				auto action1 = MoveBy::create(MOVE_TIME, Point(-SPEED, 0));
				auto action2 = RepeatForever::create(action1);
				action2->setTag(16);//Tag_SPRITE_PLAYER_ACTION_A
				sprPlayer->runAction(action2);
			}
		}
		if (deskDrawer1.compare("True") == 0 && deskDrawer2.compare("True") == 0){
			deskDrawer = true;
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
		String Bed1 = map1["Bed"].asString();//ħ��
		String Bed2 = map2["Bed"].asString();

		if (propertyValue1.compare("True") == 0 || propertyValue2.compare("True") == 0){
			auto action = (Action*)sprPlayer->getActionByTag(17);

			sprPlayer->getActionManager()->removeAction(action);

			Go_Right = false;
		}
		else{
			if (!Go_Right){
				Go_Right = true;

				auto action1 = MoveBy::create(MOVE_TIME, Point(SPEED, 0));
				auto action2 = RepeatForever::create(action1);
				action2->setTag(17);//Tag_SPRTIE_PLAYER_ACTION_D
				sprPlayer->runAction(action2);
			}
		}
		if (Bed1.compare("True") == 0 && Bed2.compare("True") == 0){
			bed = true;
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
		String drawer1 = map1["Drawer"].asString();//������
		String drawer2 = map2["Drawer"].asString();
		String bookshelf1 = map1["Bookshelf"].asString();//å��
		String bookshelf2 = map2["Bookshelf"].asString();
		String coinBank1 = map1["CoinBank"].asString();//������
		String coinBank2 = map2["CoinBank"].asString();
		String safe1 = map1["Safe"].asString();//�ݰ�
		String safe2 = map2["Safe"].asString();

		if (propertyValue1.compare("True") == 0 || propertyValue2.compare("True") == 0){
			auto action = (Action*)sprPlayer->getActionByTag(18);

			sprPlayer->getActionManager()->removeAction(action);
			Go_Up = false;
		}
		else{
			if (!Go_Up){
				Go_Up = true;

				auto action1 = MoveBy::create(MOVE_TIME, Point(0, SPEED));
				auto action2 = RepeatForever::create(action1);
				action2->setTag(18);//Tag_SPRTIE_PLAYER_ACTION_W
				sprPlayer->runAction(action2);
			}
		}
		if (drawer1.compare("True") == 0 && drawer2.compare("True") == 0){
			drawer = true;
		}
		if (bookshelf1.compare("True") == 0 && bookshelf2.compare("True") == 0){
			bookshelf = true;
		}
		if (coinBank1.compare("True") == 0 && coinBank2.compare("True") == 0){
			coinBank = true;
		}
		if (safe1.compare("True") == 0 && safe2.compare("True") == 0){
			safe = true;
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
		String bed1 = map1["Bed"].asString();//ħ��
		String bed2 = map2["Bed"].asString();
		String door1 = map1["Door"].asString();//��
		String door2 = map2["Door"].asString();
		String laptop1 = map1["Laptop"].asString();//��Ʈ��
		String laptop2 = map2["Laptop"].asString();

		if (propertyValue1.compare("True") == 0 || propertyValue2.compare("True") == 0){
			auto action = (Action*)sprPlayer->getActionByTag(19);

			sprPlayer->getActionManager()->removeAction(action);
			Go_Down = false;
		}
		else{
			if (!Go_Down){
				Go_Down = true;

				auto action1 = MoveBy::create(MOVE_TIME, Point(0, -SPEED));
				auto action2 = RepeatForever::create(action1);
				action2->setTag(19);//Tag_SPRTIE_PLAYER_ACTION_S
				sprPlayer->runAction(action2);
			}
		}
		if (bed1.compare("True") == 0 && bed2.compare("True") == 0){
			bed = true;
		}
		if (door1.compare("True") == 0 && door2.compare("True") == 0){
			door = true;
		}
		if (laptop1.compare("True") == 0 && laptop2.compare("True") == 0){
			laptop = true;
		}

	}
}
//���콺 ���뵵 -> ������
void GameScene2::onMouseDown(cocos2d::Event* event){
	EventMouse* e = (EventMouse*)event;

	Point result = Point(e->getCursorX(), e->getCursorY());

	Rect button1 = Rect(SAFE_BUTTON_X1, SAFE_BUTTON_Y1, SAFE_BUTTON_SIZE, SAFE_BUTTON_SIZE); //�ݰ� 1�� ��ư
	Rect button2 = Rect(SAFE_BUTTON_X2, SAFE_BUTTON_Y1, SAFE_BUTTON_SIZE, SAFE_BUTTON_SIZE); //�ݰ� 2�� ��ư
	Rect button3 = Rect(SAFE_BUTTON_X3, SAFE_BUTTON_Y1, SAFE_BUTTON_SIZE, SAFE_BUTTON_SIZE); //�ݰ� 3�� ��ư
	Rect button4 = Rect(SAFE_BUTTON_X1, SAFE_BUTTON_Y2, SAFE_BUTTON_SIZE, SAFE_BUTTON_SIZE); //�ݰ� 4�� ��ư
	Rect button5 = Rect(SAFE_BUTTON_X2, SAFE_BUTTON_Y2, SAFE_BUTTON_SIZE, SAFE_BUTTON_SIZE); //�ݰ� 5�� ��ư
	Rect button6 = Rect(SAFE_BUTTON_X3, SAFE_BUTTON_Y2, SAFE_BUTTON_SIZE, SAFE_BUTTON_SIZE); //�ݰ� 6�� ��ư
	Rect button7 = Rect(SAFE_BUTTON_X1, SAFE_BUTTON_Y3, SAFE_BUTTON_SIZE, SAFE_BUTTON_SIZE); //�ݰ� 7�� ��ư
	Rect button8 = Rect(SAFE_BUTTON_X2, SAFE_BUTTON_Y3, SAFE_BUTTON_SIZE, SAFE_BUTTON_SIZE); //�ݰ� 8�� ��ư
	Rect button9 = Rect(SAFE_BUTTON_X3, SAFE_BUTTON_Y3, SAFE_BUTTON_SIZE, SAFE_BUTTON_SIZE); //�ݰ� 9�� ��ư 
	Rect buttonC = Rect(SAFE_BUTTON_X1, SAFE_BUTTON_Y4, SAFE_BUTTON_SIZE, SAFE_BUTTON_SIZE); //�ݰ� C�� ��ư
	Rect button0 = Rect(SAFE_BUTTON_X2, SAFE_BUTTON_Y4, SAFE_BUTTON_SIZE, SAFE_BUTTON_SIZE); //�ݰ� 0�� ��ư
	Rect buttonE = Rect(SAFE_BUTTON_X3, SAFE_BUTTON_Y4, SAFE_BUTTON_SIZE, SAFE_BUTTON_SIZE); //�ݰ� E�� ��ư

	/*
	�ý��� ����

	��ư�� ������ blink������ 1�� �����Ѵ� �̰ɷ� ��й�ȣ�� ��ġ�� �˾Ƴ���.
	4���� �� �Է����� �� �ٸ��� �ʱ�ȭ, ���� �� ������ ȹ��

	C��ư ������ ��ȣ �ʱ�ȭ -> ���찳 ��ư
	E��ư ������ ��ȣ �Է� ->�´� ��ȣ���� �Ǵ�
	*/

	if (safe == true && Go_Event == true && openCloset == true){
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
			if (password1 == 0 && password2 == 3 && password3 == 1 && password4 == 5){
				safeSPR->setVisible(false);
				star1->setVisible(false);
				star2->setVisible(false);
				star3->setVisible(false);
				star4->setVisible(false);
				BackCommunicationWindow();
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Item_get.wav");
				GameScene2::CallCommunicationWindow(UTF8("�ݰ��� ��й�ȣ�� Ǯ����.\n\n\n������ ȹ���ߴ�."));
				expandLayer2->MapItemEvents(2, 2);
				mixLayer2->MapItemEvents(2);
				safeItem = true;
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

void GameScene2::onMouseUp(cocos2d::Event* event){
	EventMouse* e = (EventMouse*)event;

}