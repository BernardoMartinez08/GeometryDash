/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "Level1.h"
#include "Leaderboard.h"
#include "CambioSkin.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                            "Botones/SalirBT2.png",
                                            "Botones/SalirBTSelected.png",
                                            CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'Botones/SalirBT2.png' and 'Botones/SalirBTSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
        float y = origin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    //Boton de Play
    auto PlayItem = MenuItemImage::create(
                                            "Botones/PlayBT2.png",
                                            "Botones/PlayBT2.png",
                                            CC_CALLBACK_1(HelloWorld::Level1Callback, this));

    if (PlayItem == nullptr ||
        PlayItem->getContentSize().width <= 0 ||
        PlayItem->getContentSize().height <= 0)
    {
        problemLoading("'Botones/PlayBT2.png' and 'Botones/PlayBT2.png'");
    }
    else
    {
        float x = origin.x  + visibleSize.width - PlayItem->getContentSize().width / 2;
        float y = origin.y + 60 + PlayItem->getContentSize().height / 2;
        PlayItem->setPosition(Vec2(x, y));
    }

    // create menu, it's an autorelease object
    auto menuPlay = Menu::create(PlayItem, NULL);
    menuPlay->setPosition(Vec2::ZERO);
    this->addChild(menuPlay, 1);


    //Boton de Leaderboard
    auto LeaderItem = MenuItemImage::create(
                                            "Botones/Leaderboard.png",
                                            "Botones/LeaderboardSelected.png",
                                            CC_CALLBACK_1(HelloWorld::LeaderBoardCallback, this));

    if (LeaderItem == nullptr ||
        LeaderItem->getContentSize().width <= 0 ||
        LeaderItem->getContentSize().height <= 0)
    {
        problemLoading("'Botones/Leaderboard.png' and 'Botones/LeaderboardSelected.png'");
    }
    else
    {
        float x = origin.x - 430 + visibleSize.width - LeaderItem->getContentSize().width / 2;
        float y = origin.y + 210 + LeaderItem->getContentSize().height / 2;
        LeaderItem->setPosition(Vec2(x, y));
    }

    // create menu, it's an autorelease object
    auto menuLeader = Menu::create(LeaderItem, NULL);
    menuLeader->setPosition(Vec2::ZERO);
    this->addChild(menuLeader, 1);

    //Boton de CambioSkin
    auto skinItem = MenuItemImage::create(
        "Botones/CambioSkin.png",
        "Botones/CambioSkin.png",
        CC_CALLBACK_1(HelloWorld::CambioSkinCallback, this));

    if (skinItem == nullptr ||
        skinItem->getContentSize().width <= 0 ||
        skinItem->getContentSize().height <= 0)
    {
        problemLoading("'Botones/CambioSkin.png' and 'Botones/CambioSkin.png'");
    }
    else
    {
        float x = (origin.x - 440 + visibleSize.width - skinItem->getContentSize().width / 2) + 30;
        float y = (origin.y + skinItem->getContentSize().height / 2) + 10;
        skinItem->setPosition(Vec2(x, y));
    }

    // create menu, it's an autorelease object
    auto menuSkin = Menu::create(skinItem, NULL);
    menuSkin->setPosition(Vec2::ZERO);
    this->addChild(menuSkin, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("Geometry Dash", "fonts/PUSAB___.otf", 44);
    if (label == nullptr)
    {
        problemLoading("'fonts/PUSAB___.otf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    // add "HelloWorld" splash screen"
    auto spriteFondo = Sprite::create("Fondos/FondoInicio2.png");
    if (spriteFondo == nullptr)
    {
        problemLoading("'Fondos/FondoInicio2.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        spriteFondo->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(spriteFondo, 0);
    }

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}

void HelloWorld::Level1Callback(Ref* pSender)
{
    Director::getInstance()->replaceScene(TransitionFlipX::create(1, Level1::createScene()));
}

void HelloWorld::LeaderBoardCallback(Ref* pSender)
{
    Director::getInstance()->replaceScene(TransitionFlipX::create(1, Leaderboard::createScene()));
}

void HelloWorld::CambioSkinCallback(Ref* pSender)
{
    Director::getInstance()->replaceScene(TransitionFlipX::create(1, CambioSkin::createScene()));
}
