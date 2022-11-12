#include "MixLayer.h"
#include "ExpandLayer.h"
#include "SimpleAudioEngine.h"
#include "GAME_SCENE_3.h"
#include "GAME_SCENE_4.h"
#include "GAME_SCENE_5.h"

GameScene3* gameScene3;
GameScene4* gameScene4;

bool MixMenuLayer::init(){
	if (!Layer::init()){
		return false;
	}
	//이펙트 사운드 불러오기
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Mouse_click.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Correct_Answer.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Wrong_Answer.mp3");

	//마우스 리스너
	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseDown = CC_CALLBACK_1(MixMenuLayer::onMouseDown, this);
	mouseListener->onMouseUp = CC_CALLBACK_1(MixMenuLayer::onMouseUp, this);

	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

	//아이템 큰창, 작은 창, 조합 버튼(플러스버튼)
	mixWindow = Sprite::create("./Layers/UI_E.png");
	this->addChild(mixWindow);

	return true;
}

bool MixMenuLayer::KnowMapLevel(int MapLevel){
	if (MapLevel == 1){
		return Map1 = true;
	}
	else if (MapLevel == 2){
		Map1 = false;
		return Map2 = true;
	}
	else if (MapLevel == 3){
		Map2 = false;
		return Map3 = true;
	}
	else if (MapLevel == 4){
		Map3 = false;
		return Map4 = true;
	}
	else if (MapLevel == 5){
		Map4 = false;
		return Map5 = true;
	}
	else if (MapLevel == 51){
		Map5 = false;
		return Map5_1 = true;
	}
	else if (MapLevel == 6){
		Map5_1 = false;
		return Map6 = true;
	}
}

bool MixMenuLayer::MapItemEvents(int itemNumber){
	if (Map1 == true){
		if (itemNumber == 1){
			bedLetter = Sprite::create("./Items/Map1/message1.png");
			bedLetter->setPosition(Point(mixWindow->getPosition() + Point(-POINT_LONG_X_LEFT, POINT_Y_UP)));
			this->addChild(bedLetter, 3);
			return bedItem = true;
		}
		else if (itemNumber == 2){
			leftCarpetLetter = Sprite::create("./Items/Map1/message3.png");
			leftCarpetLetter->setPosition(Point(mixWindow->getPosition() + Point(-POINT_X_LEFT, POINT_Y_UP)));
			this->addChild(leftCarpetLetter, 3);
			return leftCarpetItem = true;
		}
	}
	else if (Map2 == true){
		if (itemNumber == 1){
			USB = Sprite::create("./Items/Map2/USB.png");
			USB->setPosition(Point(mixWindow->getPosition() + Point(-POINT_LONG_X_LEFT, POINT_Y_UP)));
			this->addChild(USB, 3);
			return USBItem = true;
		}
		else if (itemNumber == 2){
			coin = Sprite::create("./Items/Map2/coin.png");
			coin->setPosition(Point(mixWindow->getPosition() + Point(-POINT_X_LEFT, POINT_Y_UP)));
			this->addChild(coin, 3);
			return coinItem = true;
		}
		else if (itemNumber == 11){
			USB->setVisible(false);
			this->removeChild(USB, true);
			return USBItem = false;
		}
		else if (itemNumber == 21){
			coin->setVisible(false);
			this->removeChild(coin, true);
			return coinItem = false;
		}
	}
	else if (Map3 == true){
		if (itemNumber == 1){
			stick = Sprite::create("./Items/Map3/hammer2.png");
			stick->setPosition(Point(mixWindow->getPosition() + Point(-POINT_LONG_X_LEFT, POINT_Y_UP)));
			this->addChild(stick, 3);
			stickNum = 1;
			return stickItem = true;
		}
		else if (itemNumber == 2){
			rubber = Sprite::create("./Items/Map3/hammer1.png");
			rubber->setPosition(Point(mixWindow->getPosition() + Point(-POINT_X_LEFT, POINT_Y_UP)));
			this->addChild(rubber, 3);
			rubberNum = 2;
			return rubberItem = true;
		}
		else if (itemNumber == 3){
			cellphone = Sprite::create("./Items/Map3/phone.png");
			cellphone->setPosition(Point(mixWindow->getPosition() + Point(POINT_X_RIGHT, POINT_Y_UP)));
			this->addChild(cellphone, 3);
			return cellphoneItem = true;
		}
		else if (itemNumber == 4){
			puzzlePiece = Sprite::create("./Items/Map3/puzzle.png");
			puzzlePiece->setPosition(Point(mixWindow->getPosition() + Point(POINT_LONG_X_RIGHT, POINT_Y_UP)));
			this->addChild(puzzlePiece, 3);
			return puzzlePieceItem = true;
		}
		else if (itemNumber == 5){
			memo = Sprite::create("./Items/Map3/message4.png");
			memo->setPosition(Point(mixWindow->getPosition() + Point(-POINT_LONG_X_LEFT, POINT_Y_MIDDLE)));
			this->addChild(memo, 3);
			return memoItem = true;
		}
		else if (itemNumber == 6){
			hammer = Sprite::create("./Items/Map3/hammer.png");
			hammer->setPosition(Point(mixWindow->getPosition() + Point(-POINT_X_LEFT, POINT_Y_MIDDLE)));
			this->addChild(hammer, 3);
			return hammerItem = true;
		}
		else if (itemNumber == 11){
			stick->setVisible(false);
			stick->removeChild(stick, true);
			return stickItem = false;
		}
		else if (itemNumber == 21){
			rubber->setVisible(false);
			rubber->removeChild(rubber, true);
			return rubberItem = false;
		}
	}
	else if (Map4 == true){
		if (itemNumber == 1){
			jarMessage = Sprite::create("./Items/Map4/message2.png");
			jarMessage->setPosition(Point(mixWindow->getPosition() + Point(-POINT_LONG_X_LEFT, POINT_Y_UP)));
			this->addChild(jarMessage, 3);
			return jarMessageItem = true;
		}
		else if (itemNumber == 2){
			key = Sprite::create("./Items/Map4/key1.png");
			key->setPosition(Point(mixWindow->getPosition() + Point(-POINT_X_LEFT, POINT_Y_UP)));
			this->addChild(key, 3);
			return keyItem = true;
		}
		else if (itemNumber == 3){
			needle = Sprite::create("./Items/Map4/needle.png");
			needle->setPosition(Point(mixWindow->getPosition() + Point(POINT_X_RIGHT, POINT_Y_UP)));
			this->addChild(needle, 3);
			needleNum = 1;
			return needleItem = true;
		}
		else if (itemNumber == 4){
			cloth = Sprite::create("./Items/Map4/cloth.png");
			cloth->setPosition(Point(mixWindow->getPosition() + Point(POINT_LONG_X_RIGHT, POINT_Y_UP)));
			this->addChild(cloth, 3);
			clothNum = 2;
			return clothItem = true;
		}
		else if (itemNumber == 5){
			cotton = Sprite::create("./Items/Map4/cotton.png");
			cotton->setPosition(Point(mixWindow->getPosition() + Point(-POINT_LONG_X_LEFT, POINT_Y_MIDDLE)));
			this->addChild(cotton, 3);
			cottonNum = 4;
			return cottonItem = true;
		}
		else if (itemNumber == 6){
			cloth_2 = Sprite::create("./Items/Map4/cloth2.png");
			cloth_2->setPosition(Point(mixWindow->getPosition() + Point(-POINT_X_LEFT, POINT_Y_MIDDLE)));
			this->addChild(cloth_2, 3);
			cloth_2Num = 7;
			return cloth_2Item = true;
		}
		else if (itemNumber == 7){
			teddyHead = Sprite::create("./Items/Map4/teddy_bear.png");
			teddyHead->setPosition(Point(mixWindow->getPosition() + Point(POINT_X_RIGHT, POINT_Y_MIDDLE)));
			this->addChild(teddyHead, 3);
			return teddyHeadItem = true;
		}
		else if (itemNumber == 21){
			key->setVisible(false);
			key->removeChild(key, true);
			return keyItem = false;
		}
		else if (itemNumber == 71){
			teddyHead->setVisible(false);
			teddyHead->removeChild(teddyHead, true);
			return teddyHeadItem = false;
		}
	}
	else if (Map5 == true){
		if (itemNumber == 1){
			knife = Sprite::create("./Items/Map5/utilityKnife.png");
			knife->setPosition(Point(mixWindow->getPosition() + Point(-POINT_LONG_X_LEFT, POINT_Y_UP)));
			this->addChild(knife, 3);
			return knifeItem = true;
		}
		else if (itemNumber == 2){
			shovelHead = Sprite::create("./Items/Map5/shovel1.png");
			shovelHead->setPosition(Point(mixWindow->getPosition() + Point(-POINT_X_LEFT, POINT_Y_UP)));
			this->addChild(shovelHead, 3);
			shovelHeadNum = 1;
			return shovelHeadItem = true;
		}
		else if (itemNumber == 3){
			shovelTail = Sprite::create("./Items/Map5/shovel2.png");
			shovelTail->setPosition(Point(mixWindow->getPosition() + Point(POINT_X_RIGHT, POINT_Y_UP)));
			this->addChild(shovelTail, 3);
			shovelTailNum = 2;
			return shovelTailItem = true;
		}
		else if (itemNumber == 4){
			drawerKey = Sprite::create("./Items/Map5/key2.png");
			drawerKey->setPosition(Point(mixWindow->getPosition() + Point(POINT_LONG_X_RIGHT, POINT_Y_UP)));
			this->addChild(drawerKey, 3);
			return drawerKeyItem = true;
		}
		else if (itemNumber == 5){
			doorHandle = Sprite::create("./Items/Map5/doorknob.png");
			doorHandle->setPosition(Point(mixWindow->getPosition() + Point(-POINT_LONG_X_LEFT, POINT_Y_MIDDLE)));
			this->addChild(doorHandle, 3);
			return doorHandleItem = true;
		}
		else if (itemNumber == 6){
			shovel = Sprite::create("./Items/Map5/shovel.png");
			shovel->setPosition(Point(mixWindow->getPosition() + Point(-POINT_X_LEFT, POINT_Y_MIDDLE)));
			this->addChild(shovel, 3);
			return shovelItem = true;
		}
		else if (itemNumber == 41){
			drawerKey->setVisible(false);
			drawerKey->removeChild(drawerKey, true);
			return drawerKeyItem = false;
		}
		else if (itemNumber == 51){
			doorHandle->setVisible(false);
			doorHandle->removeChild(doorHandle, true);
			return doorHandleItem = false;
		}
	}
	else if (Map5_1 == true){
		if (itemNumber == 1){
			drainCleaner = Sprite::create("./Items/Map5-1/drain_cleaner.png");
			drainCleaner->setPosition(Point(mixWindow->getPosition() + Point(-POINT_LONG_X_LEFT, POINT_Y_UP)));
			this->addChild(drainCleaner, 3);
			return drainCleanerItem = true;
		}
		else if (itemNumber == 2){
			message = Sprite::create("./Items/Map5-1/message1.png");
			message->setPosition(Point(mixWindow->getPosition() + Point(-POINT_X_LEFT, POINT_Y_UP)));
			this->addChild(message, 3);
			return messageItem = true;
		}
		else if (itemNumber == 3){
			rag = Sprite::create("./Items/Map5-1/rag.png");
			rag->setPosition(Point(mixWindow->getPosition() + Point(POINT_X_RIGHT, POINT_Y_UP)));
			this->addChild(rag, 3);
			return ragItem = true;
		}
		else if (itemNumber == 4){
			dice = Sprite::create("./Items/Map5-1/dice.png");
			dice->setPosition(Point(mixWindow->getPosition() + Point(POINT_LONG_X_RIGHT, POINT_Y_UP)));
			this->addChild(dice, 3);
			return diceItem = true;
		}
		else if (itemNumber == 5){
			faucet = Sprite::create("./Items/Map5-1/faucet.png");
			faucet->setPosition(Point(mixWindow->getPosition() + Point(-POINT_LONG_X_LEFT, POINT_Y_MIDDLE)));
			this->addChild(faucet, 3);
			return faucetItem = true;
		}
		else if (itemNumber == 6){
			key3 = Sprite::create("./Items/Map5-1/key3.png");
			key3->setPosition(Point(mixWindow->getPosition() + Point(-POINT_X_LEFT, POINT_Y_MIDDLE)));
			this->addChild(key3, 3);
			return keyItem = true;
		}
		else if (itemNumber == 51){
			faucet->setVisible(false);
			faucet->removeChild(faucet, true);
			return faucetItem = false;
		}
		else if (itemNumber == 61){
			key3->setVisible(false);
			key3->removeChild(key3, true);
			return key3Item = false;
		}
	}
	else if (Map6 == true){
		if (itemNumber == 1){
			pianoMessage = Sprite::create("./Items/Map6/message3.png");
			pianoMessage->setPosition(Point(mixWindow->getPosition() + Point(-POINT_LONG_X_LEFT, POINT_Y_UP)));
			this->addChild(pianoMessage, 3);
			return pianoMessageItem = true;
		}
		else if (itemNumber == 2){
			frameMessage = Sprite::create("./Items/Map6/message4.png");
			frameMessage->setPosition(Point(mixWindow->getPosition() + Point(-POINT_X_LEFT, POINT_Y_UP)));
			this->addChild(frameMessage, 3);
			return frameMessageItem = true;
		}
		else if (itemNumber == 3){
			pianoKey = Sprite::create("./Items/Map6/Key4.png");
			pianoKey->setPosition(Point(mixWindow->getPosition() + Point(POINT_X_RIGHT, POINT_Y_UP)));
			this->addChild(pianoKey, 3);
			return pianoKeyItem = true;
		}
		else if (itemNumber == 4){
			map = Sprite::create("./Items/Map6/map.png");
			map->setPosition(Point(mixWindow->getPosition() + Point(POINT_LONG_X_RIGHT, POINT_Y_UP)));
			this->addChild(map, 3);
			return mapItem = true;
		}
		else if (itemNumber == 31){
			pianoKey->setVisible(false);
			pianoKey->removeChild(pianoKey, true);
			return pianoKeyItem = false;
		}
	}
	return 0;
}

void MixMenuLayer::MixItems(int itemNum1, int itemNum2){
	if (Map1 == true){
		if (selectItem1 + selectItem2 != 0){
			if (bedItem == true){
				bedLetter->setPosition(Point(mixWindow->getPosition() + Point(-POINT_LONG_X_LEFT, POINT_Y_UP)));
			}
			if (leftCarpetItem == true){
				leftCarpetLetter->setPosition(Point(mixWindow->getPosition() + Point(-POINT_X_LEFT, POINT_Y_UP)));
			}
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Wrong_Answer.mp3");
		}
	}
	else if (Map2 == true){
		if (selectItem1 + selectItem2 != 0){
			if (USBItem == true){
				USB->setPosition(Point(mixWindow->getPosition() + Point(-POINT_LONG_X_LEFT, POINT_Y_UP)));
			}
			if (coinItem == true){
				coin->setPosition(Point(mixWindow->getPosition() + Point(-POINT_X_LEFT, POINT_Y_UP)));
			}
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Wrong_Answer.mp3");
		}
	}
	else if (Map3 == true){
		if (selectItem1 + selectItem2 == 3){
			stick->setVisible(false);
			rubber->setVisible(false);
			stick->removeChild(stick, true);
			rubber->removeChild(rubber, true);
			stickItem = false;
			rubberItem = false;
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Correct_Answer.wav");
			MapItemEvents(6);
			expandLayer->MapItemEvents(3, 6);
			expandLayer->MapItemEvents(3, 11);
			expandLayer->MapItemEvents(3, 21);
			gameScene3->knowEvent(3, 1);
		}
		else{
			if (stickItem == true){
				stick->setPosition(Point(mixWindow->getPosition() + Point(-POINT_LONG_X_LEFT, POINT_Y_UP)));
			}
			if (rubberItem == true){
				rubber->setPosition(Point(mixWindow->getPosition() + Point(-POINT_X_LEFT, POINT_Y_UP)));
			}
			if (cellphoneItem == true){
				cellphone->setPosition(Point(mixWindow->getPosition() + Point(POINT_X_RIGHT, POINT_Y_UP)));
			}
			if (puzzlePieceItem == true){
				puzzlePiece->setPosition(Point(mixWindow->getPosition() + Point(POINT_LONG_X_RIGHT, POINT_Y_UP)));
			}
			if (memoItem == true){
				memo->setPosition(Point(mixWindow->getPosition() + Point(-POINT_LONG_X_LEFT, POINT_Y_MIDDLE)));
			}
			if (hammerItem == true){
				hammer->setPosition(Point(mixWindow->getPosition() + Point(-POINT_X_LEFT, POINT_Y_MIDDLE)));
			}
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Wrong_Answer.mp3");
		}
	}
	else if (Map4 == true){
		if (selectItem1 + selectItem2 == 3){
			needle->setVisible(false);
			cloth->setVisible(false);
			needle->removeChild(needle, true);
			cloth->removeChild(cloth, true);
			needleItem = false;
			clothItem = false;
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Correct_Answer.wav");
			MapItemEvents(6);
			expandLayer->MapItemEvents(4, 6);
			expandLayer->MapItemEvents(4, 31);
			expandLayer->MapItemEvents(4, 41);
			gameScene4->knowEvent(4, 1);
		}
		else if (selectItem1 + selectItem2 == 11){
			cloth_2->setVisible(false);
			cotton->setVisible(false);
			cloth_2->removeChild(cloth_2, true);
			cotton->removeChild(cotton, true);
			cloth_2Item = false;
			cottonItem = false;
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Correct_Answer.wav");
			MapItemEvents(7);
			expandLayer->MapItemEvents(4, 7);
			expandLayer->MapItemEvents(4, 51);
			expandLayer->MapItemEvents(4, 61);
			gameScene4->knowEvent(4, 2);
		}
		else{
			if (jarMessageItem == true){
				jarMessage->setPosition(Point(mixWindow->getPosition() + Point(-POINT_LONG_X_LEFT, POINT_Y_UP)));
			}
			if (keyItem == true){
				key->setPosition(Point(mixWindow->getPosition() + Point(-POINT_X_LEFT, POINT_Y_UP)));
			}
			if (needleItem == true){
				needle->setPosition(Point(mixWindow->getPosition() + Point(POINT_X_RIGHT, POINT_Y_UP)));
			}
			if (clothItem == true){
				cloth->setPosition(Point(mixWindow->getPosition() + Point(POINT_LONG_X_RIGHT, POINT_Y_UP)));
			}
			if (cottonItem == true){
				cotton->setPosition(Point(mixWindow->getPosition() + Point(-POINT_LONG_X_LEFT, POINT_Y_MIDDLE)));
			}
			if (cloth_2Item == true){
				cloth_2->setPosition(Point(mixWindow->getPosition() + Point(-POINT_X_LEFT, POINT_Y_MIDDLE)));
			}
			if (teddyHeadItem == true){
				teddyHead->setPosition(Point(mixWindow->getPosition() + Point(POINT_X_RIGHT, POINT_Y_MIDDLE)));
			}
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Wrong_Answer.mp3");
		}
	}
	else if (Map5 == true){
		if (selectItem1 + selectItem2 == 3){
			shovelHead->setVisible(false);
			shovelTail->setVisible(false);
			shovelHead->removeChild(shovelHead, true);
			shovelTail->removeChild(shovelTail, true);
			shovelHeadItem = false;
			shovelTailItem = false;
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Correct_Answer.wav");
			MapItemEvents(6);
			expandLayer->MapItemEvents(5, 6);
			expandLayer->MapItemEvents(5, 21);
			expandLayer->MapItemEvents(5, 31);
			gameScene5->knowEvent(5, 1);
		}
		else{
			if (knifeItem == true){
				knife->setPosition(Point(mixWindow->getPosition() + Point(-POINT_LONG_X_LEFT, POINT_Y_UP)));
			}
			if (shovelHeadItem == true){
				shovelHead->setPosition(Point(mixWindow->getPosition() + Point(-POINT_X_LEFT, POINT_Y_UP)));
			}
			if (shovelTailItem == true){
				shovelTail->setPosition(Point(mixWindow->getPosition() + Point(POINT_X_RIGHT, POINT_Y_UP)));
			}
			if (drawerKeyItem == true){
				drawerKey->setPosition(Point(mixWindow->getPosition() + Point(POINT_LONG_X_RIGHT, POINT_Y_UP)));
			}
			if (doorHandleItem == true){
				doorHandle->setPosition(Point(mixWindow->getPosition() + Point(-POINT_LONG_X_LEFT, POINT_Y_MIDDLE)));
			}
			if (shovelItem == true){
				shovel->setPosition(Point(mixWindow->getPosition() + Point(-POINT_X_LEFT, POINT_Y_MIDDLE)));
			}
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Wrong_Answer.mp3");
		}
	}
	else if (Map5_1 == true){
		if (selectItem1 + selectItem2 != 0){
			if (drainCleanerItem == true){
				drainCleaner->setPosition(Point(mixWindow->getPosition() + Point(-POINT_LONG_X_LEFT, POINT_Y_UP)));
			}
			if (messageItem == true){
				message->setPosition(Point(mixWindow->getPosition() + Point(-POINT_X_LEFT, POINT_Y_UP)));
			}
			if (ragItem == true){
				rag->setPosition(Point(mixWindow->getPosition() + Point(POINT_X_RIGHT, POINT_Y_UP)));
			}
			if (diceItem == true){
				dice->setPosition(Point(mixWindow->getPosition() + Point(POINT_LONG_X_RIGHT, POINT_Y_UP)));
			}
			if (faucetItem == true){
				faucet->setPosition(Point(mixWindow->getPosition() + Point(-POINT_LONG_X_LEFT, POINT_Y_MIDDLE)));
			}
			if (key3Item == true){
				key3->setPosition(Point(mixWindow->getPosition() + Point(-POINT_X_LEFT, POINT_Y_MIDDLE)));
			}
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Wrong_Answer.mp3");
		}
	}
	else if (Map6 == true){
		if (selectItem1 + selectItem2 != 0){
			if (pianoMessageItem == true){
				pianoMessage->setPosition(Point(mixWindow->getPosition() + Point(-POINT_LONG_X_LEFT, POINT_Y_UP)));
			}
			if (frameMessageItem == true){
				frameMessage->setPosition(Point(mixWindow->getPosition() + Point(-POINT_X_LEFT, POINT_Y_UP)));
			}
			if (pianoKeyItem == true){
				pianoKey->setPosition(Point(mixWindow->getPosition() + Point(POINT_X_RIGHT, POINT_Y_UP)));
			}
			if (mapItem == true){
				map->setPosition(Point(mixWindow->getPosition() + Point(POINT_LONG_X_RIGHT, POINT_Y_UP)));
			}
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Wrong_Answer.mp3");
		}
	}
}


void MixMenuLayer::onMouseDown(cocos2d::Event* event){

	EventMouse* e = (EventMouse*)event;
	Point cursorXY = Point(e->getCursorX(), e->getCursorY());

	Rect rect1 = Rect(ORIGIN_X1, ORIGIN_Y2, ITEM_WINDOW_SIZE_X, ITEM_WINDOW_SIZE_Y);
	Rect rect2 = Rect(ORIGIN_X2, ORIGIN_Y2, ITEM_WINDOW_SIZE_X, ITEM_WINDOW_SIZE_Y);
	Rect rect3 = Rect(ORIGIN_X3, ORIGIN_Y2, ITEM_WINDOW_SIZE_X, ITEM_WINDOW_SIZE_Y);
	Rect rect4 = Rect(ORIGIN_X4, ORIGIN_Y2, ITEM_WINDOW_SIZE_X, ITEM_WINDOW_SIZE_Y);
	Rect rect5 = Rect(ORIGIN_X1, ORIGIN_Y1, ITEM_WINDOW_SIZE_X, ITEM_WINDOW_SIZE_Y);
	Rect rect6 = Rect(ORIGIN_X2, ORIGIN_Y1, ITEM_WINDOW_SIZE_X, ITEM_WINDOW_SIZE_Y);
	Rect rect7 = Rect(ORIGIN_X3, ORIGIN_Y1, ITEM_WINDOW_SIZE_X, ITEM_WINDOW_SIZE_Y);
	Rect rect8 = Rect(ORIGIN_X4, ORIGIN_Y1, ITEM_WINDOW_SIZE_X, ITEM_WINDOW_SIZE_Y);
	Rect plusR = Rect(ORIGIN_PLUS_X, ORIGIN_PLUS_Y, PLUS_WINDOW_SIZE_X, PLUS_WINDOW_SIZE_Y);

	if (Map1 == true && MixLayerOnOff == true){
		if (fullMixWindow1 == false){
			if (bedItem == true && rect1.containsPoint(cursorXY)){
				bedLetter->setPosition(Point(-POINT_MIX_X_LEFT, -POINT_Y_DOWN));
				selectItem1 = bedLetterNum;
				fullMixWindow1 = true;
			}
			else if (leftCarpetItem == true && rect2.containsPoint(cursorXY)){
				leftCarpetLetter->setPosition(Point(-POINT_MIX_X_LEFT, -POINT_Y_DOWN));
				selectItem1 = leftCarpetNum;
				fullMixWindow1 = true;
			}
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Mouse_click.mp3");
		}
		else if (fullMixWindow1 == true){
			if (bedItem == true && rect1.containsPoint(cursorXY) && selectItem1 != 100){
				bedLetter->setPosition(Point(POINT_MIX_X_RIGHT, -POINT_Y_DOWN));
				selectItem2 = bedLetterNum;
				fullMixWindow2 = true;
			}
			else if (leftCarpetItem == true && rect2.containsPoint(cursorXY) && selectItem1 != 101){
				leftCarpetLetter->setPosition(Point(POINT_MIX_X_RIGHT, -POINT_Y_DOWN));
				selectItem2 = leftCarpetNum;
				fullMixWindow2 = true;
			}
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Mouse_click.mp3");
		}
	}
	else if (Map2 == true && MixLayerOnOff == true){
		if (fullMixWindow1 == false){
			if (USBItem == true && rect1.containsPoint(cursorXY)){
				USB->setPosition(Point(-POINT_MIX_X_LEFT, -POINT_Y_DOWN));
				selectItem1 = USBNum;
				fullMixWindow1 = true;
			}
			else if (coinItem == true && rect2.containsPoint(cursorXY)){
				coin->setPosition(Point(-POINT_MIX_X_LEFT, -POINT_Y_DOWN));
				selectItem1 = true;
				fullMixWindow1 = true;
			}
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Mouse_click.mp3");
		}
		else if (fullMixWindow1 == true){
			if (USBItem == true && rect1.containsPoint(cursorXY) && selectItem1 != 100){
				USB->setPosition(Point(POINT_MIX_X_RIGHT, -POINT_Y_DOWN));
				selectItem2 = USBNum;
				fullMixWindow2 = true;
			}
			else if (coinItem == true && rect2.containsPoint(cursorXY) && selectItem1 != 101){
				coin->setPosition(Point(POINT_MIX_X_RIGHT, -POINT_Y_DOWN));
				selectItem2 = coinNum;
				fullMixWindow2 = true;
			}
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Mouse_click.mp3");
		}
	}
	else if (Map3 == true && MixLayerOnOff == true){
		if (fullMixWindow1 == false){
			if (stickItem == true && rect1.containsPoint(cursorXY)){
				stick->setPosition(Point(-POINT_MIX_X_LEFT, -POINT_Y_DOWN));
				selectItem1 = stickNum;
				fullMixWindow1 = true;
			}
			else if (rubberItem == true && rect2.containsPoint(cursorXY)){
				rubber->setPosition(Point(-POINT_MIX_X_LEFT, -POINT_Y_DOWN));
				selectItem1 = rubberNum;
				fullMixWindow1 = true;
			}
			else if (cellphoneItem == true && rect3.containsPoint(cursorXY)){
				cellphone->setPosition(Point(-POINT_MIX_X_LEFT, -POINT_Y_DOWN));
				selectItem1 = cellphoneNum;
				fullMixWindow1 = true;
			}
			else if (puzzlePieceItem == true && rect4.containsPoint(cursorXY)){
				puzzlePiece->setPosition(Point(-POINT_MIX_X_LEFT, -POINT_Y_DOWN));
				selectItem1 = puzzlePieceNum;
				fullMixWindow1 = true;
			}
			else if (memoItem == true && rect5.containsPoint(cursorXY)){
				memo->setPosition(Point(-POINT_MIX_X_LEFT, -POINT_Y_DOWN));
				selectItem1 = memoNum;
				fullMixWindow1 = true;
			}
			else if (hammerItem == true && rect6.containsPoint(cursorXY)){
				hammer->setPosition(Point(-POINT_MIX_X_LEFT, -POINT_Y_DOWN));
				selectItem1 = hammerNum;
				fullMixWindow1 = true;
			}
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Mouse_click.mp3");
		}
		else if (fullMixWindow1 == true){
			if (stickItem == true && rect1.containsPoint(cursorXY) && selectItem1 != 1){
				stick->setPosition(Point(POINT_MIX_X_RIGHT, -POINT_Y_DOWN));
				selectItem2 = stickNum;
				fullMixWindow2 = true;
			}
			else if (rubberItem == true && rect2.containsPoint(cursorXY) && selectItem1 != 2){
				rubber->setPosition(Point(POINT_MIX_X_RIGHT, -POINT_Y_DOWN));
				selectItem2 = rubberNum;
				fullMixWindow2 = true;
			}
			else if (cellphoneItem == true && rect3.containsPoint(cursorXY) && selectItem1 != 100){
				cellphone->setPosition(Point(POINT_MIX_X_RIGHT, -POINT_Y_DOWN));
				selectItem2 = cellphoneNum;
				fullMixWindow2 = true;
			}
			else if (puzzlePieceItem == true && rect4.containsPoint(cursorXY) && selectItem1 != 101){
				puzzlePiece->setPosition(Point(POINT_MIX_X_RIGHT, -POINT_Y_DOWN));
				selectItem2 = puzzlePieceNum;
				fullMixWindow2 = true;
			}
			else if (memoItem == true && rect5.containsPoint(cursorXY) && selectItem1 != 102){
				memo->setPosition(Point(POINT_MIX_X_RIGHT, -POINT_Y_DOWN));
				selectItem2 = memoNum;
				fullMixWindow2 = true;
			}
			else if (hammerItem == true && rect6.containsPoint(cursorXY) && selectItem1 != 103){
				hammer->setPosition(Point(POINT_MIX_X_RIGHT, -POINT_Y_DOWN));
				selectItem2 = hammerNum;
				fullMixWindow2 = true;
			}
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Mouse_click.mp3");
		}
	}
	else if (Map4 == true && MixLayerOnOff == true){
		if (fullMixWindow1 == false){
			if (jarMessageItem == true && rect1.containsPoint(cursorXY)){
				jarMessage->setPosition(Point(-POINT_MIX_X_LEFT, -POINT_Y_DOWN));
				selectItem1 = jarMessageNum;
				fullMixWindow1 = true;
			}
			else if (keyItem == true && rect2.containsPoint(cursorXY)){
				key->setPosition(Point(-POINT_MIX_X_LEFT, -POINT_Y_DOWN));
				selectItem1 = keyNum;
				fullMixWindow1 = true;
			}
			else if (needleItem == true && rect3.containsPoint(cursorXY)){
				needle->setPosition(Point(-POINT_MIX_X_LEFT, -POINT_Y_DOWN));
				selectItem1 = needleNum;
				fullMixWindow1 = true;
			}
			else if (clothItem == true && rect4.containsPoint(cursorXY)){
				cloth->setPosition(Point(-POINT_MIX_X_LEFT, -POINT_Y_DOWN));
				selectItem1 = clothNum;
				fullMixWindow1 = true;
			}
			else if (cottonItem == true && rect5.containsPoint(cursorXY)){
				cotton->setPosition(Point(-POINT_MIX_X_LEFT, -POINT_Y_DOWN));
				selectItem1 = cottonNum;
				fullMixWindow1 = true;
			}
			else if (cloth_2Item == true && rect6.containsPoint(cursorXY)){
				cloth_2->setPosition(Point(-POINT_MIX_X_LEFT, -POINT_Y_DOWN));
				selectItem1 = cloth_2Num;
				fullMixWindow1 = true;
			}
			else if (teddyHeadItem == true && rect7.containsPoint(cursorXY)){
				teddyHead->setPosition(Point(-POINT_MIX_X_LEFT, -POINT_Y_DOWN));
				selectItem1 = teddyHeadNum;
				fullMixWindow1 = true;
			}
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Mouse_click.mp3");
		}
		else if (fullMixWindow1 == true){
			if (jarMessageItem == true && rect1.containsPoint(cursorXY) && selectItem1 != 100){
				jarMessage->setPosition(Point(POINT_MIX_X_RIGHT, -POINT_Y_DOWN));
				selectItem2 = jarMessageNum;
				fullMixWindow2 = true;
			}
			else if (keyItem == true && rect2.containsPoint(cursorXY) && selectItem1 != 101){
				key->setPosition(Point(POINT_MIX_X_RIGHT, -POINT_Y_DOWN));
				selectItem2 = keyNum;
				fullMixWindow2 = true;
			}
			else if (needleItem == true && rect3.containsPoint(cursorXY) && selectItem1 != 1){
				needle->setPosition(Point(POINT_MIX_X_RIGHT, -POINT_Y_DOWN));
				selectItem2 = needleNum;
				fullMixWindow2 = true;
			}
			else if (clothItem == true && rect4.containsPoint(cursorXY) && selectItem1 != 2){
				cloth->setPosition(Point(POINT_MIX_X_RIGHT, -POINT_Y_DOWN));
				selectItem2 = clothNum;
				fullMixWindow2 = true;
			}
			else if (cottonItem == true && rect5.containsPoint(cursorXY) && selectItem1 != 4){
				cotton->setPosition(Point(POINT_MIX_X_RIGHT, -POINT_Y_DOWN));
				selectItem2 = cottonNum;
				fullMixWindow2 = true;
			}
			else if (cloth_2Item == true && rect6.containsPoint(cursorXY) && selectItem1 != 7){
				cloth_2->setPosition(Point(POINT_MIX_X_RIGHT, -POINT_Y_DOWN));
				selectItem2 = cloth_2Num;
				fullMixWindow2 = true;
			}
			else if (teddyHeadItem == true && rect7.containsPoint(cursorXY) && selectItem1 != 102){
				teddyHead->setPosition(Point(POINT_MIX_X_RIGHT, -POINT_Y_DOWN));
				selectItem2 = teddyHeadNum;
				fullMixWindow2 = true;
			}
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Mouse_click.mp3");
		}
	}
	else if (Map5 == true && MixLayerOnOff == true){
		if (fullMixWindow1 == false){
			if (knifeItem == true && rect1.containsPoint(cursorXY)){
				knife->setPosition(Point(-POINT_MIX_X_LEFT, -POINT_Y_DOWN));
				selectItem1 = knifeNum;
				fullMixWindow1 = true;
			}
			else if (shovelHeadItem == true && rect2.containsPoint(cursorXY)){
				shovelHead->setPosition(Point(-POINT_MIX_X_LEFT, -POINT_Y_DOWN));
				selectItem1 = shovelHeadNum;
				fullMixWindow1 = true;
			}
			else if (shovelTailItem == true && rect3.containsPoint(cursorXY)){
				shovelTail->setPosition(Point(-POINT_MIX_X_LEFT, -POINT_Y_DOWN));
				selectItem1 = shovelTailNum;
				fullMixWindow1 = true;
			}
			else if (drawerKeyItem == true && rect4.containsPoint(cursorXY)){
				drawerKey->setPosition(Point(-POINT_MIX_X_LEFT, -POINT_Y_DOWN));
				selectItem1 = drawerKeyNum;
				fullMixWindow1 = true;
			}
			else if (doorHandleItem == true && rect5.containsPoint(cursorXY)){
				doorHandle->setPosition(Point(-POINT_MIX_X_LEFT, -POINT_Y_DOWN));
				selectItem1 = doorHandleNum;
				fullMixWindow1 = true;
			}
			else if (shovelItem == true && rect6.containsPoint(cursorXY)){
				shovel->setPosition(Point(-POINT_MIX_X_LEFT, -POINT_Y_DOWN));
				selectItem1 = shovelNum;
				fullMixWindow1 = true;
			}
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Mouse_click.mp3");
		}
		else if (fullMixWindow1 == true){
			if (knifeItem == true && rect1.containsPoint(cursorXY) && selectItem1 != 100){
				knife->setPosition(Point(POINT_MIX_X_RIGHT, -POINT_Y_DOWN));
				selectItem2 = knifeNum;
				fullMixWindow2 = true;
			}
			else if (shovelHeadItem == true && rect2.containsPoint(cursorXY) && selectItem1 != 1){
				shovelHead->setPosition(Point(POINT_MIX_X_RIGHT, -POINT_Y_DOWN));
				selectItem2 = shovelHeadNum;
				fullMixWindow2 = true;
			}
			else if (shovelTailItem == true && rect3.containsPoint(cursorXY) && selectItem1 != 2){
				shovelTail->setPosition(Point(POINT_MIX_X_RIGHT, -POINT_Y_DOWN));
				selectItem2 = shovelTailNum;
				fullMixWindow2 = true;
			}
			else if (drawerKeyItem == true && rect4.containsPoint(cursorXY) && selectItem1 != 101){
				drawerKey->setPosition(Point(POINT_MIX_X_RIGHT, -POINT_Y_DOWN));
				selectItem2 = drawerKeyNum;
				fullMixWindow2 = true;
			}
			else if (doorHandleItem == true && rect5.containsPoint(cursorXY) && selectItem1 != 102){
				doorHandle->setPosition(Point(POINT_MIX_X_RIGHT, -POINT_Y_DOWN));
				selectItem2 = doorHandleNum;
				fullMixWindow2 = true;
			}
			else if (shovelItem == true && rect6.containsPoint(cursorXY) && selectItem1 != 103){
				shovel->setPosition(Point(POINT_MIX_X_RIGHT, -POINT_Y_DOWN));
				selectItem2 = shovelNum;
				fullMixWindow2 = true;
			}
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Mouse_click.mp3");
		}
	}
	else if (Map5_1 == true && MixLayerOnOff == true){
		if (fullMixWindow1 == false){
			if (drainCleanerItem == true && rect1.containsPoint(cursorXY)){
				drainCleaner->setPosition(Point(-POINT_MIX_X_LEFT, -POINT_Y_DOWN));
				selectItem1 = drainCleanerNum;
				fullMixWindow1 = true;
			}
			else if (messageItem == true && rect2.containsPoint(cursorXY)){
				message->setPosition(Point(-POINT_MIX_X_LEFT, -POINT_Y_DOWN));
				selectItem1 = messageNum;
				fullMixWindow1 = true;
			}
			else if (ragItem == true && rect3.containsPoint(cursorXY)){
				rag->setPosition(Point(-POINT_MIX_X_LEFT, -POINT_Y_DOWN));
				selectItem1 = ragNum;
				fullMixWindow1 = true;
			}
			else if (diceItem == true && rect4.containsPoint(cursorXY)){
				dice->setPosition(Point(-POINT_MIX_X_LEFT, -POINT_Y_DOWN));
				selectItem1 = diceNum;
				fullMixWindow1 = true;
			}
			else if (faucetItem == true && rect5.containsPoint(cursorXY)){
				faucet->setPosition(Point(-POINT_MIX_X_LEFT, -POINT_Y_DOWN));
				selectItem1 = faucetNum;
				fullMixWindow1 = true;
			}
			else if (key3Item == true && rect6.containsPoint(cursorXY)){
				key3->setPosition(Point(-POINT_MIX_X_LEFT, -POINT_Y_DOWN));
				selectItem1 = key3Num;
				fullMixWindow1 = true;
			}
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Mouse_click.mp3");
		}
		else if (fullMixWindow1 == true){
			if (drainCleanerItem == true && rect1.containsPoint(cursorXY) && selectItem1 != 100){
				drainCleaner->setPosition(Point(POINT_MIX_X_RIGHT, -POINT_Y_DOWN));
				selectItem2 = drainCleanerNum;
				fullMixWindow2 = true;
			}
			else if (messageItem == true && rect2.containsPoint(cursorXY) && selectItem1 != 101){
				message->setPosition(Point(POINT_MIX_X_RIGHT, -POINT_Y_DOWN));
				selectItem2 = messageNum;
				fullMixWindow2 = true;
			}
			else if (ragItem == true && rect3.containsPoint(cursorXY) && selectItem1 != 102){
				rag->setPosition(Point(POINT_MIX_X_RIGHT, -POINT_Y_DOWN));
				selectItem2 = ragNum;
				fullMixWindow2 = true;
			}
			else if (diceItem == true && rect4.containsPoint(cursorXY) && selectItem1 != 103){
				dice->setPosition(Point(POINT_MIX_X_RIGHT, -POINT_Y_DOWN));
				selectItem2 = diceNum;
				fullMixWindow2 = true;
			}
			else if (faucetItem == true && rect5.containsPoint(cursorXY) && selectItem1 != 104){
				faucet->setPosition(Point(POINT_MIX_X_RIGHT, -POINT_Y_DOWN));
				selectItem2 = faucetNum;
				fullMixWindow2 = true;
			}
			else if (key3Item == true && rect6.containsPoint(cursorXY) && selectItem1 != 105){
				key3->setPosition(Point(POINT_MIX_X_RIGHT, -POINT_Y_DOWN));
				selectItem2 = key3Num;
				fullMixWindow2 = true;
			}
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Mouse_click.mp3");
		}
	}
	else if (Map6 == true && MixLayerOnOff == true){
		if (fullMixWindow1 == false){
			if (pianoMessageItem == true && rect1.containsPoint(cursorXY)){
				pianoMessage->setPosition(Point(-POINT_MIX_X_LEFT, -POINT_Y_DOWN));
				selectItem1 = pianoMessageNum;
				fullMixWindow1 = true;
			}
			else if (frameMessageItem == true && rect2.containsPoint(cursorXY)){
				frameMessage->setPosition(Point(-POINT_MIX_X_LEFT, -POINT_Y_DOWN));
				selectItem1 = frameMessageNum;
				fullMixWindow1 = true;
			}
			else if (pianoKeyItem == true && rect3.containsPoint(cursorXY)){
				pianoKey->setPosition(Point(-POINT_MIX_X_LEFT, -POINT_Y_DOWN));
				selectItem1 = pianoKeyNum;
				fullMixWindow1 = true;
			}
			else if (mapItem == true && rect4.containsPoint(cursorXY)){
				map->setPosition(Point(-POINT_MIX_X_LEFT, -POINT_Y_DOWN));
				selectItem1 = mapNum;
				fullMixWindow1 = true;
			}
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Mouse_click.mp3");
		}
		else if (fullMixWindow1 == true){
			if (pianoMessageItem == true && rect1.containsPoint(cursorXY) && selectItem1 != 100){
				pianoMessage->setPosition(Point(POINT_MIX_X_RIGHT, -POINT_Y_DOWN));
				selectItem2 = pianoMessageNum;
				fullMixWindow2 = true;
			}
			else if (frameMessageItem == true && rect2.containsPoint(cursorXY) && selectItem1 != 101){
				frameMessage->setPosition(Point(POINT_MIX_X_RIGHT, -POINT_Y_DOWN));
				selectItem2 = frameMessageNum;
				fullMixWindow2 = true;
			}
			else if (pianoKeyItem == true && rect3.containsPoint(cursorXY) && selectItem1 != 102){
				pianoKey->setPosition(Point(POINT_MIX_X_RIGHT, -POINT_Y_DOWN));
				selectItem2 = pianoKeyNum;
				fullMixWindow2 = true;
			}
			else if (mapItem == true && rect4.containsPoint(cursorXY) && selectItem1 != 103){
				map->setPosition(Point(POINT_MIX_X_RIGHT, -POINT_Y_DOWN));
				selectItem2 = mapNum;
				fullMixWindow2 = true;
			}
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Mouse_click.mp3");
		}
	}
		//조합버튼 클릭시
	if ((fullMixWindow1 == true || fullMixWindow2 == true) && plusR.containsPoint(cursorXY)){
		MixItems(selectItem1, selectItem2);
		fullMixWindow1 = false;
		fullMixWindow2 = false;
	}
}
void MixMenuLayer::onMouseUp(cocos2d::Event* event){
	EventMouse* e = (EventMouse*)event;
}
