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

#include "Level1.h"
#include "HelloWorldScene.h"

USING_NS_CC;

Scene* Level1::createScene()
{
    return Level1::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Level1::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::initWithPhysics())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // add "HelloWorld" splash screen"
    auto spriteFondo = Sprite::create("Fondos/Inicio.jpg");
    if (spriteFondo == nullptr)
    {
        problemLoading("'Fondos/Inicio.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        spriteFondo->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(spriteFondo, 0);
    }

    auto director = Director::getInstance();
    auto tamano = director->getWinSize();

    labelPause = Label::createWithTTF("GAME PAUSED", "fonts/Demoness.otf", 15);
    if (labelPause == nullptr)
    {
        problemLoading("'fonts/Demoness.otf'");
    }
    else
    {
        // position the label on the center of the screen
        labelPause->setPosition(tamano.width / 2, tamano.height * 0.50);

        // add the label as a child to this layer
        this->addChild(labelPause, 1);
        labelPause->setVisible(false);
    }


    auto keyboardListener1 = EventListenerKeyboard::create();
    keyboardListener1->onKeyPressed = CC_CALLBACK_2(Level1::keyPressedPlayer, this);

    //Cuadro de movimiento 
    auto physicsBody = PhysicsBody::createBox(Size(65.0f, 81.0f), PhysicsMaterial(0.1f, 1.0f, 0.0f));
    physicsBody->setGravityEnable(false);
    physicsBody->setVelocity(Vec2(200, 0));
    physicsBody->setVelocityLimit(500.0f);


    //Crear SpritePlayer
    auto SpritePlayer = Sprite::create("PC_Sprite.png");
    SpritePlayer->setPosition(tamano.width / 6, tamano.height * 0.20);
    addChild(SpritePlayer);

    //Aplicar physicsBody al sprite
    SpritePlayer->addComponent(physicsBody);

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener1, SpritePlayer);

    /*schedule(CC_SCHEDULE_SELECTOR(Level1::movimientoPlayer));*/

    return true;
}

void Level1::keyPressedPlayer(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    Vec2 loc = event->getCurrentTarget()->getPosition();

    switch (keyCode) {
    case EventKeyboard::KeyCode::KEY_SPACE:
        
        break;

    case EventKeyboard::KeyCode::KEY_P:
        labelPause->setVisible(true);
        this->pause();
        break;

    case EventKeyboard::KeyCode::KEY_R:
        labelPause->setVisible(false);
        this->resume();
        break;
    }

}

void Level1::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application

    Director::getInstance()->replaceScene(TransitionFlipX::create(1, HelloWorld::createScene()));

}

void Level1::movimientoPlayer(float dt) {

    Vec2 loc = SpritePlayer->getPosition();
    SpritePlayer->setPosition(loc.x + 0.4, loc.y);
}
    
