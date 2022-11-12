#include "GAME_SCENE_4.h"
#include "SimpleAudioEngine.h"
#include "MENU_SCENE.h"
#include "Menu_Layer.h"
#include "ExpandLayer.h"
#include "MixLayer.h"
#include "Hint_Layer.h"
#include "GAME_SCENE_5.h"

ExpandMenuLayer* expandLayer4;
MenuLayer* menuLayer4;
MixMenuLayer* mixLayer4;
HintLayer* hintLayer4;

Scene* GameScene4::createScene()
{
	auto scene = Scene::create();

	auto layer = GameScene4::create();

	scene->addChild(layer);

	expandLayer4 = ExpandMenuLayer::create();
	expandLayer4->setVisible(false);
	scene->addChild(expandLayer4, 4);

	mixLayer4 = MixMenuLayer::create();
	mixLayer4->setVisible(false);
	scene->addChild(mixLayer4, 4);

	menuLayer4 = MenuLayer::create();
	menuLayer4->setVisible(false);
	scene->addChild(menuLayer4, 5);

	hintLayer4 = HintLayer::create();
	hintLayer4->setVisible(false);
	scene->addChild(hintLayer4, 4);

	//�� ���� ����
	expandLayer4->KnowMapLevel(4);
	mixLayer4->KnowMapLevel(4);
	hintLayer4->findHint(0);
	hintLayer4->findHint(1);
	hintLayer4->findHint(2);
	hintLayer4->findHint(3);

	mixLayer4->expandLayer = expandLayer4;
	mixLayer4->gameScene4 = layer;

	return scene;
}

bool GameScene4::init()
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
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Map2/USB_Laptop.mp3");

	//plist �ҷ�����
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("./Characters/sprites.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("./Items/Map4/number/Cnumber.plist");

	//Ÿ�ϸ� �ҷ�����
	_tileMap = CCTMXTiledMap::create("./Maps/Map4.tmx");
	_background = _tileMap->getLayer("Background4");
	this->addChild(_tileMap, 0);

	//��ǥ����, �÷��̾� ������ǥ �� ������Ʈ �߰�
	playerSpawn = _tileMap->objectGroupNamed("PlayerSpawn4");

	if (playerSpawn == NULL){
		return false;
	}

	ValueMap spawnPoint = playerSpawn->getObject("PlayerSpawnXY4");

	//ĳ���� ���� ��ǥ����
	characterX = spawnPoint["x"].asInt();
	characterY = spawnPoint["y"].asInt();

	//�÷��̾� �����
	playerSprite = Sprite::createWithSpriteFrameName("sprites4.png");
	playerSprite->setPosition(Point(characterX, characterY));
	playerSprite->setTag(11);
	this->addChild(playerSprite, 1, 11);

	//ĳ���� ����
	carrierLayer = Layer::create();
	carrierLayer->setVisible(false);
	this->addChild(carrierLayer, 2);

	carrierLock = Sprite::create("./Items/Map4/carrier.png");
	carrierLock->setPosition(Point(512, 498));
	carrierLayer->addChild(carrierLock, 2);

	carrierNumber1 = Sprite::createWithSpriteFrameName("C0.png");
	carrierNumber1->setPosition(Point(CARRIER_BUTTON_X1, CARRIER_BUTTON_Y1));
	carrierNumber1->setAnchorPoint(Point::ZERO);
	carrierLayer->addChild(carrierNumber1, 3);

	carrierNumber2 = Sprite::createWithSpriteFrameName("C0.png");
	carrierNumber2->setPosition(Point(CARRIER_BUTTON_X1, CARRIER_BUTTON_Y2));
	carrierNumber2->setAnchorPoint(Point::ZERO);
	carrierLayer->addChild(carrierNumber2, 3);

	carrierNumber3 = Sprite::createWithSpriteFrameName("C0.png");
	carrierNumber3->setPosition(Point(CARRIER_BUTTON_X1, CARRIER_BUTTON_Y3));
	carrierNumber3->setAnchorPoint(Point::ZERO);
	carrierLayer->addChild(carrierNumber3, 3);

	carrierNumber4 = Sprite::createWithSpriteFrameName("C0.png");
	carrierNumber4->setPosition(Point(CARRIER_BUTTON_X1, CARRIER_BUTTON_Y4));
	carrierNumber4->setAnchorPoint(Point::ZERO);
	carrierLayer->addChild(carrierNumber4, 3);

	//Ŀư����
	curtainCutIn = Sprite::create("./Items/Map4/window.png");
	curtainCutIn->setPosition(Point(playerSprite->getPosition() + Point(0, ITEM_WINDOW_Y)));
	curtainCutIn->setVisible(false);
	this->addChild(curtainCutIn, 2);

	//������ ����ü ��������Ʈ (���������� �Ӹ��� �޾��ָ� ����)
	teddyMake = Sprite::create("./Items/Map4/teddy_bearMake.png");
	teddyMake->setPosition(Point(TEDDY_X, TEDDY_Y));
	teddyMake->setAnchorPoint(Point::ZERO);
	teddyMake->setVisible(false);
	this->addChild(teddyMake, 0);

	//��ȭâ �����
	communication = Sprite::create("./Layers/communication.png");
	communication->setPosition(playerSprite->getPosition() + Point(0, -254));
	communication->setOpacity(255);
	communication->setVisible(false);
	this->addChild(communication, 3);

	this->schedule(schedule_selector(GameScene4::CallEveryFrame));

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(GameScene4::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(GameScene4::onKeyReleased, this);

	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseDown = CC_CALLBACK_1(GameScene4::onMouseDown, this);
	// regist listener to dispatcher
	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
	eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

	Director::getInstance()->resume();

	return true;
}
CCPoint GameScene4::tileCoordForPosition(CCPoint position){
	int x = position.x / _tileMap->getTileSize().width;
	int y = ((_tileMap->getMapSize().height* _tileMap->getTileSize().height) - position.y) / _tileMap->getTileSize().height;
	return ccp(x, y);
}

void GameScene4::setViewPointCenter(CCPoint position){
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

void GameScene4::CallCommunicationWindow(std::string info){

	communication->setPosition(playerSprite->getPosition() + Point(0, -254));
	communication->setVisible(true);

	Texts = Label::createWithTTF(info, "./Moris.ttf", 30, Size(630, 150));
	Texts->setPosition(playerSprite->getPosition() + Point(0, -262));
	Texts->setColor(ccc3(0, 0, 0));
	this->addChild(Texts, 4);
}

void GameScene4::BackCommunicationWindow(){
	communication->setVisible(false);
	Texts->setVisible(false);
	Texts->removeChild(Texts, true);
}

void GameScene4::changeMenuScene_R(Ref *sender){
	Director::getInstance()->replaceScene(MenuScene::createScene());
}

void GameScene4::changeGameScene5_R(Ref *sender){
	auto scene = TransitionFade::create(3, GameScene5::createScene());
	Director::getInstance()->replaceScene(scene);
}

bool GameScene4::knowEvent(int mapLevel, int eventCode){
	if (mapLevel == 4){
		if (eventCode == 1){
			return makeCloth = true;
		}
		else if (eventCode == 2){
			return makeHead = true;
		}
	}
	return 0;
}

void GameScene4::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event){

	auto sprPlayer = (Sprite*)this->getChildByTag(11);

	switch (keyCode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_A:{
		checkLeft = true, Go_Left = true;

		if (Go_Event == false){
			curtain = false, carrier = false, jar = false, drawer = false;
			chair = false, desk = false, teddyBear = false, closet = false;
			vanity = false, floor = false, door = false;
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
	case cocos2d::EventKeyboard::KeyCode::KEY_D:{
		checkRight = true, Go_Right = true;

		if (Go_Event == false) {
			curtain = false, carrier = false, jar = false, drawer = false;
			chair = false, desk = false, teddyBear = false, closet = false;
			vanity = false, floor = false, door = false;
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
	case cocos2d::EventKeyboard::KeyCode::KEY_W:{

		checkUp = true, Go_Up = true;

		if (Go_Event == false) {
			curtain = false, carrier = false, jar = false, drawer = false;
			chair = false, desk = false, teddyBear = false, closet = false;
			vanity = false, floor = false, door = false;
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
	case cocos2d::EventKeyboard::KeyCode::KEY_S:{
		checkDown = true, Go_Down = true;

		if (Go_Event == false){
			curtain = false, carrier = false, jar = false, drawer = false;
			chair = false, desk = false, teddyBear = false, closet = false;
			vanity = false, floor = false, door = false;
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
	case cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE:{
		if (Go_Menu == false){
			Go_Menu = true;
			menuLayer4->setPosition(Point::ZERO);
			menuLayer4->setVisible(true);
			CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
			Director::getInstance()->pause();
		}
		else if (Go_Menu == true)	{
			menuLayer4->setVisible(false);
			Go_Menu = false;
			CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
			if (Go_Menu == false && goExpand == false && goMix == false && Go_Event == false && goHint == false){
				Director::getInstance()->resume();
			}
		}
		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_Q:{
		if (Go_Menu == false && goExpand == false && Go_Event == false){
			if (goMix == true){
				mixLayer4->setVisible(false);
				goMix = false;
			}
			else if (goHint == true){
				hintLayer4->setVisible(false);
				goHint = false;
			}
			goExpand = true;
			expandLayer4->setPosition(Point(Point(512, 384) + Point(0, 114)));
			expandLayer4->setVisible(true);
			mixLayer4->MixLayerOnOff = false;
			hintLayer4->HintLayerOnOff = false;
			expandLayer4->ExpandLayerOnOff = true;
			Director::getInstance()->pause();
		}
		else if (Go_Menu == false && goExpand == true){
			expandLayer4->setVisible(false);
			goExpand = false;
			expandLayer4->ExpandLayerOnOff = false;
			if (Go_Menu == false && goExpand == false && goMix == false && Go_Event == false && goHint == false){
				Director::getInstance()->resume();
			}
		}
		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_E:{
		if (Go_Menu == false && goMix == false && Go_Event == false){
			if (goExpand == true){
				expandLayer4->setVisible(false);
				goExpand = false;
			}
			else if (goHint == true){
				hintLayer4->setVisible(false);
				goHint = false;
			}
			goMix = true;
			mixLayer4->setPosition(Point(Point(512, 498)));
			mixLayer4->setVisible(true);
			mixLayer4->MixLayerOnOff = true;
			hintLayer4->HintLayerOnOff = false;
			expandLayer4->ExpandLayerOnOff = false;
			Director::getInstance()->pause();
		}
		else if (Go_Menu == false && goMix == true){
			mixLayer4->setVisible(false);
			goMix = false;
			mixLayer4->MixLayerOnOff = false;
			if (Go_Menu == false && goExpand == false && goMix == false && Go_Event == false && goHint == false){
				Director::getInstance()->resume();
			}
		}
		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_H:{
		if (Go_Menu == false && goHint == false && Go_Event == false){
			if (goMix == true){
				mixLayer4->setVisible(false);
				goMix = false;
			}
			else if (goExpand == true){
				expandLayer4->setVisible(false);
				goExpand = false;
			}
			goHint = true;
			hintLayer4->setPosition(Point(Point(512, 384) + Point(0, 114)));
			hintLayer4->setVisible(true);
			mixLayer4->MixLayerOnOff = false;
			hintLayer4->HintLayerOnOff = true;
			expandLayer4->ExpandLayerOnOff = false;
			Director::getInstance()->pause();
		}
		else if (Go_Menu == false && goHint == true){
			hintLayer4->setVisible(false);
			goHint = false;
			hintLayer4->HintLayerOnOff = false;
			if (Go_Menu == false && goExpand == false && goMix == false && Go_Event == false && goHint == false){
				Director::getInstance()->resume();
			}
		}
		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:{
		if (goExpand == false && goMix == false && Go_Menu == false && Go_Event == false && goHint == false){
			if (curtain == true){
				Go_Event = true;
				if (openCurtain == false){
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Map4/Curtain.mp3");
					GameScene4::CallCommunicationWindow(UTF8("Ŀư�� ������."));
					openCurtain = true;
				}
				else if (openCurtain == true){
					curtainCutIn->setPosition(Point(playerSprite->getPosition() + Point(0, ITEM_WINDOW_Y)));
					curtainCutIn->setVisible(true);
				}
				Director::getInstance()->pause();
			}
			else if (carrier == true){
				Go_Event = true;
				if (carrierItem == false){
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Map2/USB_Laptop.mp3");
					carrierLayer->setPosition(Point(playerSprite->getPosition() - Director::getInstance()->getWinSize() * 0.5));
					carrierLayer->setVisible(true);
					GameScene4::CallCommunicationWindow(UTF8("ĳ��� ����� �ִ�."));
				}
				else if (carrierItem == true){
					GameScene4::CallCommunicationWindow(UTF8("������ ������ �ǰ�?"));
				}
				Director::getInstance()->pause();
			}
			else if (jar == true){
				Go_Event = true;
				if (jarItem == false){
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Item_get.wav");
					GameScene4::CallCommunicationWindow(UTF8("�׾Ƹ� �ȿ� ���𰡰� ���δ�.\n\n\n������ ȹ���ߴ�."));
					mixLayer4->MapItemEvents(1);
					expandLayer4->MapItemEvents(4, 1);
					jarItem = true;
				}
				else if (jarItem == true){
					GameScene4::CallCommunicationWindow(UTF8("�����⸦ ������ ���̿���."));
				}
				Director::getInstance()->pause();
			}
			else if (drawer == true){
				Go_Event = true;
				if (chairItem == false){
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Map2/USB_Laptop.mp3");
					GameScene4::CallCommunicationWindow(UTF8("����� �ִ�. ���谡 �ʿ��� �� �ϴ�."));
				}
				else if (chairItem == true && drawerItem == false){
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Item_get.wav");
					GameScene4::CallCommunicationWindow(UTF8("���踦 ����Ͽ� ����� Ǯ����.\n\n\n�����ȿ��� õ�� �߰��ߴ�."));
					mixLayer4->MapItemEvents(21);
					expandLayer4->MapItemEvents(4, 21);
					mixLayer4->MapItemEvents(4);
					expandLayer4->MapItemEvents(4, 4);
					drawerItem = true;
				}
				else if (chairItem == true && drawerItem == true){
					GameScene4::CallCommunicationWindow(UTF8("�� �������� �ܶ� ����ִ�."));
				}
				Director::getInstance()->pause();
			}
			else if (chair == true){
				Go_Event = true;
				if (chairItem == false){
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Item_get.wav");
					GameScene4::CallCommunicationWindow(UTF8("���� �ؿ��� ���踦 �ֿ���."));
					mixLayer4->MapItemEvents(2);
					expandLayer4->MapItemEvents(4, 2);
					chairItem = true;
				}
				else if (chairItem == true){
					GameScene4::CallCommunicationWindow(UTF8("���� ���� �ؿ��� �ƹ��͵� ����."));
				}
				Director::getInstance()->pause();
			}
			else if (desk == true){
				Go_Event = true;
				if (deskItem == false){
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Item_get.wav");
					GameScene4::CallCommunicationWindow(UTF8("å�� ������ �ٴ��� �߰��Ͽ���."));
					mixLayer4->MapItemEvents(3);
					expandLayer4->MapItemEvents(4, 3);
					deskItem = true;
				}
				else if (deskItem == true){
					GameScene4::CallCommunicationWindow(UTF8("å�� ���� �����ϴ�."));
				}
				Director::getInstance()->pause();
			}
			else if (teddyBear == true){
				Go_Event = true;
				if (makeHead == false){
					GameScene4::CallCommunicationWindow(UTF8("�� ���� ����?"));
				}
				else if (makeHead == true && makeTeddyBear == false){
					GameScene4::CallCommunicationWindow(UTF8("�� �������� �Ӹ��� �޾��־���."));
					makeTeddyBear = true;
					mixLayer4->MapItemEvents(71);
					expandLayer4->MapItemEvents(4, 71);
					teddyMake->setVisible(true);
				}
				else if (makeHead == true && makeTeddyBear == true && clockGear4 == false){
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Item_get.wav");
					GameScene4::CallCommunicationWindow(UTF8("����... �̰� �� �Կ��� ��°���?\n\n\n��Ϲ����� ȹ���ߴ�."));
					clockGear4 = true;
					hintLayer4->findHint(4);
				}
				else if (makeHead == true && makeTeddyBear == true && clockGear4 == true){
					GameScene4::CallCommunicationWindow(UTF8("���� �������� �Ӹ��� �����."));
				}
				Director::getInstance()->pause();
			}
			else if (closet == true){
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Map2/USB_Laptop.mp3");
				Go_Event = true;
				GameScene4::CallCommunicationWindow(UTF8("���� ���� ��� �ִ�. ���� ������ ���� �ʴ´�."));
				Director::getInstance()->pause();
			}
			else if (vanity == true){
				Go_Event = true;
				GameScene4::CallCommunicationWindow(UTF8("ȭ��ǰ�� ��û����."));
				Director::getInstance()->pause();
			}
			else if (floor == true){
				Go_Event = true;
				GameScene4::CallCommunicationWindow(UTF8("�̰� ����? �������ΰ�?"));
				Director::getInstance()->pause();
			}
			else if (door == true){
				Go_Event = true;
				if (clockGear4 == false){
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Map5/Door_Spigot_Put.mp3");
					GameScene4::CallCommunicationWindow(UTF8("������ �ܼ��� ã�� �������� ���� �� ����."));
				}
				else if (clockGear4 == true){
					GameScene4::CallCommunicationWindow(UTF8("���� ���� ���� �ʾҾ�. � ����"));
				}
				Director::getInstance()->pause();
			}
		}
		else if (Go_Menu == false && Go_Event == true){
			if (closet == true || vanity == true || floor == true || jar == true || drawer == true ||
				chair == true || desk == true || teddyBear == true){
				Go_Event = false;
				GameScene4::BackCommunicationWindow();
				Director::getInstance()->resume();
			}
			else if (curtain == true){
				Go_Event = false;
				GameScene4::BackCommunicationWindow();
				curtainCutIn->setVisible(false);
				Director::getInstance()->resume();
			}
			else if (carrier == true){
				Go_Event = false;
				if (carrierItem == false){
					GameScene4::BackCommunicationWindow();
					carrierLayer->setVisible(false);
				}
				else if (carrierItem == true){
					GameScene4::BackCommunicationWindow();
				}
				Director::getInstance()->resume();
			}
			else if (door == true){
				Go_Event = false;
				if (clockGear4 == false){
					GameScene4::BackCommunicationWindow();
				}
				else if (clockGear4 == true){
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/door_open.mp3");
					GameScene4::changeGameScene5_R(this);
				}
				Director::getInstance()->resume();
			}
		}
		break;
	}
	}
}

void GameScene4::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event){

	auto sprPlayer = (Sprite*)this->getChildByTag(11);//PLAYER_SPRITE_TAG

	switch (keyCode){
	case cocos2d::EventKeyboard::KeyCode::KEY_A:{
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
	case cocos2d::EventKeyboard::KeyCode::KEY_D:{
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
	case cocos2d::EventKeyboard::KeyCode::KEY_W:{
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
	case cocos2d::EventKeyboard::KeyCode::KEY_S:{
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
void GameScene4::CallEveryFrame(float f){

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

		String propertyValue1 = map1["Collidable"].asString();
		String propertyValue2 = map2["Collidable"].asString();
		String jar1 = map1["Jar"].asString();
		String jar2 = map2["Jar"].asString();
		String carrier1 = map1["Carrier"].asString();
		String carrier2 = map2["Carrier"].asString();
		String floor1 = map1["Floor"].asString();
		String floor2 = map2["Floor"].asString();
		String chair1 = map1["Chair"].asString();
		String chair2 = map2["Chair"].asString();

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
		if (jar1.compare("True") == 0 && jar2.compare("True") == 0){
			jar = true;
		}
		if (carrier1.compare("True") == 0 && carrier2.compare("True") == 0){
			carrier = true;
		}
		if (floor1.compare("True") == 0 && floor2.compare("True") == 0){
			floor = true;
		}
		if (chair1.compare("True") == 0 && chair2.compare("True") == 0){
			chair = true;
		}
	}

	if (checkRight){
		CCPoint playerPos1 = sprPlayer->getPosition();
		CCPoint playerPos2 = sprPlayer->getPosition();

		CCPoint tileCoord1 = this->tileCoordForPosition(playerPos1 + Point(BREAK_TOO_X, BREAK_ZERO_Y));
		CCPoint tileCoord2 = this->tileCoordForPosition(playerPos2 + Point(BREAK_TOO_X, -BREAK_DOWN_Y));

		unsigned int tileGid1 = _background->tileGIDAt(tileCoord1);
		unsigned int tileGid2 = _background->tileGIDAt(tileCoord2);

		auto properties1 = _tileMap->propertiesForGID(tileGid1);
		auto properties2 = _tileMap->propertiesForGID(tileGid2);

		ValueMap map1 = properties1.asValueMap();
		ValueMap map2 = properties2.asValueMap();

		String propertyValue1 = map1["Collidable"].asString();
		String propertyValue2 = map2["Collidable"].asString();
		String chair1 = map1["Chair"].asString();
		String chair2 = map2["Chair"].asString();
		String vanity1 = map1["Vanity"].asString();
		String vanity2 = map2["Vanity"].asString();
		String floor1 = map1["Floor"].asString();
		String floor2 = map2["Floor"].asString();

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
		if (chair1.compare("True") == 0 && chair2.compare("True") == 0){
			chair = true;
		}
		if (vanity1.compare("True") == 0 && vanity2.compare("True") == 0){
			vanity = true;
		}
		if (floor1.compare("True") == 0 && floor2.compare("True") == 0){
			floor = true;
		}
	}
	if (checkUp){
		CCPoint playerPos1 = sprPlayer->getPosition();
		CCPoint playerPos2 = sprPlayer->getPosition();

		CCPoint tileCoord1 = this->tileCoordForPosition(playerPos1 + Point(BREAK_X, BREAK_UP_Y));
		CCPoint tileCoord2 = this->tileCoordForPosition(playerPos2 + Point(-BREAK_X, BREAK_UP_Y));

		unsigned int tileGid1 = _background->tileGIDAt(tileCoord1);
		unsigned int tileGid2 = _background->tileGIDAt(tileCoord2);

		auto properties1 = _tileMap->propertiesForGID(tileGid1);
		auto properties2 = _tileMap->propertiesForGID(tileGid2);

		ValueMap map1 = properties1.asValueMap();
		ValueMap map2 = properties2.asValueMap();

		String propertyValue1 = map1["Collidable"].asString();
		String propertyValue2 = map2["Collidable"].asString();
		String teddyBear1 = map1["TeddyBear"].asString();
		String teddyBear2 = map2["TeddyBear"].asString();
		String carrier1 = map1["Carrier"].asString();
		String carrier2 = map2["Carrier"].asString();
		String floor1 = map1["Floor"].asString();
		String floor2 = map2["Floor"].asString();
		String curtain1 = map1["Curtain"].asString();
		String curtain2 = map2["Curtain"].asString();
		String closet1 = map1["Closet"].asString();
		String closet2 = map2["Closet"].asString();
		String drawer1 = map1["Drawer"].asString();
		String drawer2 = map2["Drawer"].asString();

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
		if (teddyBear1.compare("True") == 0 && teddyBear2.compare("True") == 0){
			teddyBear = true;
		}
		if (carrier1.compare("True") == 0 && carrier2.compare("True") == 0){
			carrier = true;
		}
		if (floor1.compare("True") == 0 && floor2.compare("True") == 0){
			floor = true;
		}
		if (curtain1.compare("True") == 0 && curtain2.compare("True") == 0){
			curtain = true;
		}
		if (closet1.compare("True") == 0 && closet2.compare("True") == 0){
			closet = true;
		}
		if (drawer1.compare("True") == 0 && drawer2.compare("True") == 0){
			drawer = true;
		}
	}
	if (checkDown){
		CCPoint playerPos1 = sprPlayer->getPosition();
		CCPoint playerPos2 = sprPlayer->getPosition();

		CCPoint tileCoord1 = this->tileCoordForPosition(playerPos1 + Point(BREAK_X, -BREAK_TOO_DOWN_Y));
		CCPoint tileCoord2 = this->tileCoordForPosition(playerPos2 + Point(-BREAK_X, -BREAK_TOO_DOWN_Y));

		unsigned int tileGid1 = _background->tileGIDAt(tileCoord1);
		unsigned int tileGid2 = _background->tileGIDAt(tileCoord2);

		auto properties1 = _tileMap->propertiesForGID(tileGid1);
		auto properties2 = _tileMap->propertiesForGID(tileGid2);

		ValueMap map1 = properties1.asValueMap();
		ValueMap map2 = properties2.asValueMap();

		String propertyValue1 = map1["Collidable"].asString();
		String propertyValue2 = map2["Collidable"].asString();
		String jar1 = map1["Jar"].asString();
		String jar2 = map2["Jar"].asString();
		String floor1 = map1["Floor"].asString();
		String floor2 = map2["Floor"].asString();
		String door1 = map1["Door"].asString();
		String door2 = map2["Door"].asString();
		String chair1 = map1["Chair"].asString();
		String chair2 = map2["Chair"].asString();
		String desk1 = map1["Desk"].asString();
		String desk2 = map2["Desk"].asString();

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
		if (jar1.compare("True") == 0 && jar2.compare("True") == 0){
			jar = true;
		}
		if (floor1.compare("True") == 0 && floor2.compare("True") == 0){
			floor = true;
		}
		if (door1.compare("True") == 0 && door2.compare("True") == 0){
			door = true;
		}
		if (chair1.compare("True") == 0 && chair2.compare("True") == 0){
			chair = true;
		}
		if (desk1.compare("True") == 0 && desk2.compare("True") == 0){
			desk = true;
		}
	}
}
//���콺 ���뵵 -> ������
void GameScene4::onMouseDown(cocos2d::Event* event){
	EventMouse* e = (EventMouse*)event;

	Point result = Point(e->getCursorX(), e->getCursorY()); //���콺 Ŀ�� ��ǥ

	//ĳ���� ��ư ��ǥ
	Rect carrierButton1 = Rect(CARRIER_BUTTON_X1, CARRIER_BUTTON_Y1, CARRIER_BUTTON_SIZE_X, CARRIER_BUTTON_SIZE_Y);
	Rect carrierButton2 = Rect(CARRIER_BUTTON_X1, CARRIER_BUTTON_Y2, CARRIER_BUTTON_SIZE_X, CARRIER_BUTTON_SIZE_Y);
	Rect carrierButton3 = Rect(CARRIER_BUTTON_X1, CARRIER_BUTTON_Y3, CARRIER_BUTTON_SIZE_X, CARRIER_BUTTON_SIZE_Y);
	Rect carrierButton4 = Rect(CARRIER_BUTTON_X1, CARRIER_BUTTON_Y4, CARRIER_BUTTON_SIZE_X, CARRIER_BUTTON_SIZE_Y);

	if (Go_Event == true && carrier == true && carrierItem == false){
		if (carrierButton1.containsPoint(result)){
			if (carrierPassWord1 < 9){
				carrierPassWord1++;
			}
			else{
				carrierPassWord1 = 0;
			}
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/password.mp3");
			carrierNumber1->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("C%d.png", carrierPassWord1)));
		}
		else if (carrierButton2.containsPoint(result)){
			if (carrierPassWord2 < 9){
				carrierPassWord2++;
			}
			else{
				carrierPassWord2 = 0;
			}
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/password.mp3");
			carrierNumber2->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("C%d.png", carrierPassWord2)));
		}
		else if (carrierButton3.containsPoint(result)){
			if (carrierPassWord3 < 9){
				carrierPassWord3++;
			}
			else{
				carrierPassWord3 = 0;
			}
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/password.mp3");
			carrierNumber3->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("C%d.png", carrierPassWord3)));
		}
		else if (carrierButton4.containsPoint(result)){
			if (carrierPassWord4 < 9){
				carrierPassWord4++;
			}
			else{
				carrierPassWord4 = 0;
			}
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/password.mp3");
			carrierNumber4->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("C%d.png", carrierPassWord4)));
		}
		if (carrierPassWord1 == 3 && carrierPassWord2 == 2 && carrierPassWord3 == 4 && carrierPassWord4 == 6){
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Item_get.wav");
			carrierItem = true;
			carrierLayer->setVisible(false);
			GameScene4::BackCommunicationWindow();
			GameScene4::CallCommunicationWindow(UTF8("ĳ������ ����� Ǯ�ȴ�.\n\n\n���� ȹ���ߴ�."));
			mixLayer4->MapItemEvents(5);
			expandLayer4->MapItemEvents(4, 5);
		}
	}
}