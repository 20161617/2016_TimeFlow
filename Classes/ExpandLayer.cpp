#include "ExpandLayer.h"
#include "GAME_SCENE_1.h"
#include "SimpleAudioEngine.h"
#include "MixLayer.h"

bool ExpandMenuLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//효과음 로드
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Mouse_click.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Wrong_Answer.mp3");

	//마우스 리스너
	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseDown = CC_CALLBACK_1(ExpandMenuLayer::onMouseDown, this);
	mouseListener->onMouseUp = CC_CALLBACK_1(ExpandMenuLayer::onMouseUp, this);

	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

	//확대 큰창
	itemWindow = Sprite::create("./Layers/UI_Q.png");
	this->addChild(itemWindow);

	//나가기 버튼
	exit = Sprite::create("./Mainmenu/exit.png");
	exit->setPosition(Point(itemWindow->getPosition() + Point(EXIT_X, -EXIT_Y)));
	exit->setAnchorPoint(Point::ZERO);
	exit->setScale(2);
	exit->setVisible(false);
	this->addChild(exit, 5);

	return true;
}

//맵 레벨(단계) 구별
bool ExpandMenuLayer::KnowMapLevel(int MapLevel){
	if (MapLevel == 1){
		bedLetterExpand = Sprite::create("./Items/Map1/memo1.png");
		bedLetterExpand->setPosition(Point(itemWindow->getPosition()) - Point(0, ITEM_WINDOW_Y));
		bedLetterExpand->setVisible(false);
		this->addChild(bedLetterExpand, 4);

		leftCatpetLetterExpand = Sprite::create("./Items/Map1/memo2.png");
		leftCatpetLetterExpand->setPosition(Point(itemWindow->getPosition()) - Point(0, ITEM_WINDOW_Y));
		leftCatpetLetterExpand->setVisible(false);
		this->addChild(leftCatpetLetterExpand, 4);

		return Map1 = true;
	}
	else if (MapLevel == 2){
		Map1 = false;
		return Map2 = true;
	}
	else if (MapLevel == 3){
		cellphoneExpand = Sprite::create("./Items/Map3/phone2.png");
		cellphoneExpand->setPosition(Point(itemWindow->getPosition()) - Point(0, ITEM_WINDOW_Y));
		cellphoneExpand->setVisible(false);
		this->addChild(cellphoneExpand, 4);

		puzzlePieceExpand = Sprite::create("./Items/Map3/puzzle_piece.png");
		puzzlePieceExpand->setPosition(Point(itemWindow->getPosition()) - Point(0, ITEM_WINDOW_Y));
		puzzlePieceExpand->setVisible(false);
		this->addChild(puzzlePieceExpand, 4);

		memoExpand = Sprite::create("./Items/Map3/MEMO.png");
		memoExpand->setPosition(Point(itemWindow->getPosition()) - Point(0, ITEM_WINDOW_Y));
		memoExpand->setVisible(false);
		this->addChild(memoExpand, 4);

		Map2 = false;
		return Map3 = true;
	}
	else if (MapLevel == 4){
		jarMessageExpand = Sprite::create("./Items/Map4/memo.png");
		jarMessageExpand->setPosition(Point(itemWindow->getPosition() - Point(0, ITEM_WINDOW_Y)));
		jarMessageExpand->setVisible(false);
		this->addChild(jarMessageExpand, 4);

		Map3 = false;
		return Map4 = true;
	}
	else if (MapLevel == 5){
		Map4 = false;
		return Map5 = true;
	}
	else if (MapLevel == 51){
		messageExpand = Sprite::create("./Items/Map5-1/memo.png");
		messageExpand->setPosition(Point(itemWindow->getPosition() - Point(0, ITEM_WINDOW_Y)));
		messageExpand->setVisible(false);
		this->addChild(messageExpand, 4);

		diceExpand = Sprite::create("./Items/Map5-1/dice2.png");
		diceExpand->setPosition(Point(itemWindow->getPosition() - Point(0, ITEM_WINDOW_Y)));
		diceExpand->setVisible(false);
		this->addChild(diceExpand, 4);

		Map5 = false;
		return Map5_1 = true;
	}
	else if (MapLevel == 6){
		pianoMessageExpand = Sprite::create("./Items/Map6/Piano_memo.png");
		pianoMessageExpand->setPosition(Point(itemWindow->getPosition() - Point(0, ITEM_WINDOW_Y)));
		pianoMessageExpand->setVisible(false);
		this->addChild(pianoMessageExpand, 4);

		frameMessageExpand = Sprite::create("./Items/Map6/Frame_memo.png");
		frameMessageExpand->setPosition(Point(itemWindow->getPosition() - Point(0, ITEM_WINDOW_Y)));
		frameMessageExpand->setVisible(false);
		this->addChild(frameMessageExpand, 4);

		mapExpand = Sprite::create("./Items/Map6/mapExpand.png");
		mapExpand->setPosition(Point(itemWindow->getPosition() - Point(0, ITEM_WINDOW_Y)));
		mapExpand->setVisible(false);
		this->addChild(mapExpand, 4);

		Map5_1 = false;
		return Map6 = true;
	}
}

bool ExpandMenuLayer::MapItemEvents(int level, int itemNumber){
	if (level == 1){
		if (itemNumber == 1){
			bedLetter = Sprite::create("./Items/Map1/message1.png");
			bedLetter->setPosition(Point(itemWindow->getPosition() + Point(-POINT_LONG_X_LEFT, POINT_Y_UP)));
			this->addChild(bedLetter, 3);
			return bedItem = true;
		}
		else if (itemNumber == 2){
			leftCarpetLetter = Sprite::create("./Items/Map1/message3.png");

			leftCarpetLetter->setPosition(Point(itemWindow->getPosition() + Point(-POINT_X_LEFT, POINT_Y_UP)));
			this->addChild(leftCarpetLetter, 3);
			return leftCarpetItem = true;
		}
	}
	else if (level == 2){
		if (itemNumber == 1){
			USB = Sprite::create("./Items/Map2/USB.png");
			USB->setPosition(Point(itemWindow->getPosition() + Point(-POINT_LONG_X_LEFT, POINT_Y_UP)));
			this->addChild(USB, 3);
			return USBItem = true;
		}
		else if (itemNumber == 2){
			coin = Sprite::create("./Items/Map2/coin.png");
			coin->setPosition(Point(itemWindow->getPosition() + Point(-POINT_X_LEFT, POINT_Y_UP)));
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
	else if (level == 3){
		if (itemNumber == 1){
			stick = Sprite::create("./Items/Map3/hammer2.png");
			stick->setPosition(Point(itemWindow->getPosition() + Point(-POINT_LONG_X_LEFT, POINT_Y_UP)));
			this->addChild(stick, 3);
			return stickItem = true;
		}
		else if (itemNumber == 2){
			rubber = Sprite::create("./Items/Map3/hammer1.png");
			rubber->setPosition(Point(itemWindow->getPosition() + Point(-POINT_X_LEFT, POINT_Y_UP)));
			this->addChild(rubber, 3);
			return rubberItem = true;
		}
		else if (itemNumber == 3){
			cellphone = Sprite::create("./Items/Map3/phone.png");
			cellphone->setPosition(Point(itemWindow->getPosition() + Point(POINT_X_RIGHT, POINT_Y_UP)));
			this->addChild(cellphone, 3);
			return cellphoneItem = true;
		}
		else if (itemNumber == 4){
			puzzlePiece = Sprite::create("./Items/Map3/puzzle.png");
			puzzlePiece->setPosition(Point(itemWindow->getPosition() + Point(POINT_LONG_X_RIGHT, POINT_Y_UP)));
			this->addChild(puzzlePiece, 3);
			return puzzlePieceItem = true;
		}
		else if (itemNumber == 5){
			memo = Sprite::create("./Items/Map3/message4.png");
			memo->setPosition(Point(itemWindow->getPosition() + Point(-POINT_LONG_X_LEFT, -POINT_Y_DOWN)));
			this->addChild(memo, 3);
			return memoItem = true;
		}
		else if (itemNumber == 6){
			hammer = Sprite::create("./Items/Map3/hammer.png");
			hammer->setPosition(Point(itemWindow->getPosition() + Point(-POINT_X_LEFT, -POINT_Y_DOWN)));
			this->addChild(hammer, 3);
			return hammerItem = true;
		}
		else if (itemNumber == 11){ //망치 조합시 삭제
			stick->setVisible(false);
			this->removeChild(stick, true);
		}
		else if (itemNumber == 21){ //망치 조합시 삭제
			rubber->setVisible(false);
			this->removeChild(rubber, true);
		}
	}
	else if (level == 4){
		if (itemNumber == 1){
			jarMessage = Sprite::create("./Items/Map4/message2.png");
			jarMessage->setPosition(Point(itemWindow->getPosition() + Point(-POINT_LONG_X_LEFT, POINT_Y_UP)));
			this->addChild(jarMessage, 3);
			return jarMessageItem = true;
		}
		else if (itemNumber == 2){
			key = Sprite::create("./Items/Map4/key1.png");
			key->setPosition(Point(itemWindow->getPosition() + Point(-POINT_X_LEFT, POINT_Y_UP)));
			this->addChild(key, 3);
			return keyItem = true;
		}
		else if (itemNumber == 3){
			needle = Sprite::create("./Items/Map4/needle.png");
			needle->setPosition(Point(itemWindow->getPosition() + Point(POINT_X_RIGHT, POINT_Y_UP)));
			this->addChild(needle, 3);
			return needleItem = true;
		}
		else if (itemNumber == 4){
			cloth = Sprite::create("./Items/Map4/cloth.png");
			cloth->setPosition(Point(itemWindow->getPosition() + Point(POINT_LONG_X_RIGHT, POINT_Y_UP)));
			this->addChild(cloth, 3);
			return clothItem = true;
		}
		else if (itemNumber == 5){
			cotton = Sprite::create("./Items/Map4/cotton.png");
			cotton->setPosition(Point(itemWindow->getPosition() + Point(-POINT_LONG_X_LEFT, -POINT_Y_DOWN)));
			this->addChild(cotton, 3);
			return cottonItem = true;
		}
		else if (itemNumber == 6){
			cloth_2 = Sprite::create("./Items/Map4/cloth2.png");
			cloth_2->setPosition(Point(itemWindow->getPosition() + Point(-POINT_X_LEFT, -POINT_Y_DOWN)));
			this->addChild(cloth_2, 3);
			return cloth_2Item = true;
		}
		else if (itemNumber == 7){
			teddyHead = Sprite::create("./Items/Map4/teddy_bear.png");
			teddyHead->setPosition(Point(itemWindow->getPosition() + Point(POINT_X_RIGHT, -POINT_Y_DOWN)));
			this->addChild(teddyHead, 3);
			return teddyHeadItem = true;
		}
		else if (itemNumber == 21){
			key->setVisible(false);
			key->removeChild(key, true);
			return keyItem = false;
		}
		else if (itemNumber == 31){
			needle->setVisible(false);
			needle->removeChild(needle, true);
			return needleItem = false;
		}
		else if (itemNumber == 41){
			cloth->setVisible(false);
			cloth->removeChild(cloth, true);
			return clothItem = false;
		}
		else if (itemNumber == 51){
			cotton->setVisible(false);
			cotton->removeChild(cotton, true);
			return cottonItem = false;
		}
		else if (itemNumber == 61){
			cloth_2->setVisible(false);
			cloth->removeChild(cloth_2, true);
			return cloth_2Item = false;
		}
		else if (itemNumber == 71){
			teddyHead->setVisible(false);
			teddyHead->removeChild(teddyHead, true);
			return teddyHeadItem = false;
		}
	}
	else if (level == 5){
		if (itemNumber == 1){
			knife = Sprite::create("./Items/Map5/utilityKnife.png");
			knife->setPosition(Point(itemWindow->getPosition() + Point(-POINT_LONG_X_LEFT, POINT_Y_UP)));
			this->addChild(knife, 3);
			return knifeItem = true;
		}
		else if (itemNumber == 2){
			shovelHead = Sprite::create("./Items/Map5/shovel1.png");
			shovelHead->setPosition(Point(itemWindow->getPosition() + Point(-POINT_X_LEFT, POINT_Y_UP)));
			this->addChild(shovelHead, 3);
			return shovelHeadItem = true;
		}
		else if (itemNumber == 3){
			shovelTail = Sprite::create("./Items/Map5/shovel2.png");
			shovelTail->setPosition(Point(itemWindow->getPosition() + Point(POINT_X_RIGHT, POINT_Y_UP)));
			this->addChild(shovelTail, 3);
			return shovelHeadItem = true;
		}
		else if (itemNumber == 4){
			drawerKey = Sprite::create("./Items/Map5/key2.png");
			drawerKey->setPosition(Point(itemWindow->getPosition() + Point(POINT_LONG_X_RIGHT, POINT_Y_UP)));
			this->addChild(drawerKey, 3);
			return drawerKeyItem = true;
		}
		else if (itemNumber == 5){
			doorHandle = Sprite::create("./Items/Map5/doorknob.png");
			doorHandle->setPosition(Point(itemWindow->getPosition() + Point(-POINT_LONG_X_LEFT, -POINT_Y_DOWN)));
			this->addChild(doorHandle, 3);
			return doorHandleItem = true;
		}
		else if (itemNumber == 6){
			shovel = Sprite::create("./Items/Map5/shovel.png");
			shovel->setPosition(Point(itemWindow->getPosition() + Point(-POINT_X_LEFT, -POINT_Y_DOWN)));
			this->addChild(shovel, 3);
			return shovelItem = true;
		}
		else if (itemNumber == 21){
			shovelHead->setVisible(false);
			shovelHead->removeChild(shovelHead, true);
			return shovelHeadItem = false;
		}
		else if (itemNumber == 31){
			shovelTail->setVisible(false);
			shovelTail->removeChild(shovelTail, true);
			return shovelTailItem = false;
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
	else if (level == 51){
		if (itemNumber == 1){
			drainCleaner = Sprite::create("./Items/Map5-1/drain_cleaner.png");
			drainCleaner->setPosition(Point(itemWindow->getPosition() + Point(-POINT_LONG_X_LEFT, POINT_Y_UP)));
			this->addChild(drainCleaner, 3);
			return drainCleanerItem = true;
		}
		else if (itemNumber == 2){
			message = Sprite::create("./Items/Map5-1/message1.png");
			message->setPosition(Point(itemWindow->getPosition() + Point(-POINT_X_LEFT, POINT_Y_UP)));
			this->addChild(message, 3);
			return messageItem = true;
		}
		else if (itemNumber == 3){
			rag = Sprite::create("./Items/Map5-1/rag.png");
			rag->setPosition(Point(itemWindow->getPosition() + Point(POINT_X_RIGHT, POINT_Y_UP)));
			this->addChild(rag, 3);
			return ragItem = true;
		}
		else if (itemNumber == 4){
			dice = Sprite::create("./Items/Map5-1/dice.png");
			dice->setPosition(Point(itemWindow->getPosition() + Point(POINT_LONG_X_RIGHT, POINT_Y_UP)));
			this->addChild(dice, 3);
			return diceItem = true;
		}
		else if (itemNumber == 5){
			faucet = Sprite::create("./Items/Map5-1/faucet.png");
			faucet->setPosition(Point(itemWindow->getPosition() + Point(-POINT_LONG_X_LEFT, -POINT_Y_DOWN)));
			this->addChild(faucet, 3);
			return faucetItem = true;
		}
		else if (itemNumber == 6){
			key3 = Sprite::create("./Items/Map5-1/key3.png");
			key3->setPosition(Point(itemWindow->getPosition() + Point(-POINT_X_LEFT, -POINT_Y_DOWN)));
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
	else if (level == 6){
		if (itemNumber == 1){
			pianoMessage = Sprite::create("./Items/Map6/message3.png");
			pianoMessage->setPosition(Point(itemWindow->getPosition() + Point(-POINT_LONG_X_LEFT, POINT_Y_UP)));
			this->addChild(pianoMessage, 3);
			return pianoMessageItem = true;
		}
		else if (itemNumber == 2){
			frameMessage = Sprite::create("./Items/Map6/message4.png");
			frameMessage->setPosition(Point(itemWindow->getPosition() + Point(-POINT_X_LEFT, POINT_Y_UP)));
			this->addChild(frameMessage, 3);
			return frameMessageItem = true;
		}
		else if (itemNumber == 3){
			pianoKey = Sprite::create("./Items/Map6/Key4.png");
			pianoKey->setPosition(Point(itemWindow->getPosition() + Point(POINT_X_RIGHT, POINT_Y_UP)));
			this->addChild(pianoKey, 3);
			return pianoKeyItem = true;
		}
		else if (itemNumber == 4){
			map = Sprite::create("./Items/Map6/map.png");
			map->setPosition(Point(itemWindow->getPosition() + Point(POINT_LONG_X_RIGHT, POINT_Y_UP)));
			this->addChild(map, 3);
			return mapItem = true;
		}
		else if (itemNumber == 31){
			pianoKey->setVisible(false);
			pianoKey->removeChild(pianoKey, true);
			return pianoKeyItem = false;
		}
	}
}

// 마우스 사용용도->선택지
void ExpandMenuLayer::onMouseDown(cocos2d::Event* event){
	EventMouse* e = (EventMouse*)event;
	Point cursorXY = Point(e->getCursorX(), e->getCursorY());

	Rect rect1R = Rect(ORIGIN_X1, ORIGIN_Y2, ITEM_WINDOW_SIZE_X, ITEM_WINDOW_SIZE_Y);
	Rect rect2R = Rect(ORIGIN_X2, ORIGIN_Y2, ITEM_WINDOW_SIZE_X, ITEM_WINDOW_SIZE_Y);
	Rect rect3R = Rect(ORIGIN_X3, ORIGIN_Y2, ITEM_WINDOW_SIZE_X, ITEM_WINDOW_SIZE_Y);
	Rect rect4R = Rect(ORIGIN_X4, ORIGIN_Y2, ITEM_WINDOW_SIZE_X, ITEM_WINDOW_SIZE_Y);
	Rect rect5R = Rect(ORIGIN_X1, ORIGIN_Y1, ITEM_WINDOW_SIZE_X, ITEM_WINDOW_SIZE_Y);
	Rect rect6R = Rect(ORIGIN_X2, ORIGIN_Y1, ITEM_WINDOW_SIZE_X, ITEM_WINDOW_SIZE_Y);
	Rect rect7R = Rect(ORIGIN_X3, ORIGIN_Y1, ITEM_WINDOW_SIZE_X, ITEM_WINDOW_SIZE_Y);
	Rect rect8R = Rect(ORIGIN_X4, ORIGIN_Y1, ITEM_WINDOW_SIZE_X, ITEM_WINDOW_SIZE_Y);
	Rect exitR = Rect(EXIT_RECT_X, 0, EXIT_RECT_SIZE_X, EXIT_RECT_SIZE_Y);

	if (Map1 == true && ExpandLayerOnOff == true){
		if (bedItem == true && rect1R.containsPoint(cursorXY) && expandOn == false){
			bedLetterExpand->setVisible(true);
			bedExpandOn = true;
			exit->setVisible(true);
			expandOn = true;
		}
		else if (leftCarpetItem == true && rect2R.containsPoint(cursorXY) && expandOn == false){
			leftCatpetLetterExpand->setVisible(true);
			leftCarpetExpandOn = true;
			exit->setVisible(true);
			expandOn = true;
		}
		else if ((bedItem == true || leftCarpetItem == true) && exitR.containsPoint(cursorXY)){
			if (bedExpandOn == true){
				bedLetterExpand->setVisible(false);
				bedExpandOn = false;
			}
			else if (leftCarpetExpandOn == true){
				leftCatpetLetterExpand->setVisible(false);
				leftCarpetExpandOn = false;
			}
			exit->setVisible(false);
			expandOn = false;
		}
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Mouse_click.mp3");
	}
	else if (Map2 == true && ExpandLayerOnOff == true){
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Mouse_click.mp3");
	}
	else if (Map3 == true && ExpandLayerOnOff == true){
		if (cellphoneItem == true && rect3R.containsPoint(cursorXY) && expandOn == false){
			cellphoneExpand->setVisible(true);
			cellphoneExpandOn = true;
			exit->setVisible(true);
			expandOn = true;
		}
		else if (puzzlePieceItem == true && rect4R.containsPoint(cursorXY) && expandOn == false){
			puzzlePieceExpand->setVisible(true);
			puzzlepieceExpandOn = true;
			exit->setVisible(true);
			expandOn = true;
		}
		else if (memoItem == true && rect5R.containsPoint(cursorXY) && expandOn == false){
			memoExpand->setVisible(true);
			memoExpandOn = true;
			exit->setVisible(true);
			expandOn = true;
		}
		else if ((cellphoneItem == true || puzzlePieceItem == true || memoItem == true) &&
			exitR.containsPoint(cursorXY)){
			if (cellphoneExpandOn == true){
			    cellphoneExpand->setVisible(false);
				cellphoneExpandOn = false;
			}
			else if (puzzlepieceExpandOn == true){
				puzzlePieceExpand->setVisible(false);
				puzzlepieceExpandOn = false;
			}
			else if (memoExpandOn == true){
				memoExpand->setVisible(false);
				memoExpandOn = false;
			}
			exit->setVisible(false);
			expandOn = false;
		}
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Mouse_click.mp3");
	}
	else if (Map4 == true && ExpandLayerOnOff == true){
		if (jarMessageItem == true && rect1R.containsPoint(cursorXY) && expandOn == false){
			jarMessageExpand->setVisible(true);
			jarMessageExpandon = true;
			exit->setVisible(true);
			expandOn = true;
		}
		else if (jarMessageItem == true && exitR.containsPoint(cursorXY)){
			if (jarMessageExpandon == true){
				jarMessageExpand->setVisible(false);
				jarMessageExpandon = false;
			}
			exit->setVisible(false);
			expandOn = false;
		}
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Mouse_click.mp3");
	}
	else if (Map5 == true && ExpandLayerOnOff == true){
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Mouse_click.mp3");
	}
	else if (Map5_1 == true && ExpandLayerOnOff == true){
		if (messageItem == true && rect2R.containsPoint(cursorXY) && expandOn == false){
			messageExpand->setVisible(true);
			messageExpandOn = true;
			exit->setVisible(true);
		expandOn = true;
		}
		else if (diceItem == true && rect4R.containsPoint(cursorXY) && expandOn == false){
			diceExpand->setVisible(true);
			diceExpandOn = true;
			exit->setVisible(true);
			expandOn = true;
		}
		else if ((messageItem == true || diceItem == true) && exitR.containsPoint(cursorXY)){
			if (messageExpandOn == true){
				messageExpand->setVisible(false);
				messageExpandOn = false;
			}
			else if (diceExpandOn == true){
				diceExpand->setVisible(false);
				diceExpandOn = false;
			}
			exit->setVisible(false);
			expandOn = false;
		}
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Mouse_click.mp3");
	}
	else if (Map6 == true && ExpandLayerOnOff == true){
		if (pianoMessageItem == true && rect1R.containsPoint(cursorXY) && expandOn == false){
			pianoMessageExpand->setVisible(true);
			pianoMessageExpandOn = true;
			exit->setVisible(true);
			expandOn = true;
		}
		else if (frameMessageItem == true && rect2R.containsPoint(cursorXY) && expandOn == false){
			frameMessageExpand->setVisible(true);
			frameMessageExpandOn = true;
			exit->setVisible(true);
			expandOn = true;
		}
		else if (mapItem == true && rect4R.containsPoint(cursorXY) && expandOn == false){
			mapExpand->setVisible(true);
			mapExpandOn = true;
			exit->setVisible(true);
			expandOn = true;
		}
		else if ((pianoMessageItem == true || frameMessageItem == true) && exitR.containsPoint(cursorXY)){
			if (pianoMessageExpandOn == true){
				pianoMessageExpand->setVisible(false);
				pianoMessageExpandOn = false;
			}
			else if (frameMessageExpandOn == true){
				frameMessageExpand->setVisible(false);
				frameMessageExpandOn = false;
			}
			else if (mapExpandOn == true){
				mapExpand->setVisible(false);
				mapExpandOn = false;
			}
			exit->setVisible(false);
			expandOn = false;
		}
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Mouse_click.mp3");
	}
}

void ExpandMenuLayer::onMouseUp(cocos2d::Event* event){
	EventMouse* e = (EventMouse*)event;
}
