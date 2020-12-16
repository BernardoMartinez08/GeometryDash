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
#include "CambioSkin.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "string"
#include <vector>


//#include "C:\Users\hecto\Desktop\Intento\cocos2d\cocos\editor-support\cocostudio\SimpleAudioEngine.h"  

using namespace std;
USING_NS_CC;

typedef cocos2d::Rect Pua;
typedef cocos2d::Rect Bloque;
typedef cocos2d::Rect Meta;
Camera* camara;
int i = 0;
bool jump = false,pausa=false,fall=false;
auto tamano=cocos2d::Size(0.0,0.0);
//Rect playerColision;
//Cajas de las puas
//Rect puas,pua2,pua3;
//Cajas de las plataformas
//Rect suelo,
//suelo2;

Meta meta;
vector<Pua> puas;
vector<Bloque> bloques;

PhysicsBody* physicsPlayer;


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
    //Soundtrack
    //auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    //audio->preloadBackgroundMusic("C:/Users/hecto/source/repos/G/Resources/Crystals.mp3");
    //audio->playBackgroundMusic("C:/Users/hecto/source/repos/G/Resources/Crystals.mp3");
    if (!Scene::initWithPhysics())
    {
        return false;
    }
    //camara
    camara = Camera::create();
    camara->setCameraFlag(CameraFlag::DEFAULT);
    camara->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    //camara->setContentSize(Director::getInstance()->getVisibleSize());
    this->addChild(camara);
    camara->setPosition(Vec2(0, 0));

    //CCFOllow
    

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
    tamano = director->getWinSize();

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
    keyboardListener1->onKeyPressed = CC_CALLBACK_2(Level1::keyPressed, this);

    //Cuadro de movimiento 
    physicsPlayer = PhysicsBody::createBox(Size(65.0f, 81.0f), PhysicsMaterial(0.1f, 1.0f, 0.0f));
    physicsPlayer->setGravityEnable(false);
    physicsPlayer->setVelocity(Vec2(200, 0));
    physicsPlayer->setVelocityLimit(500.0f);

    //Crear SpritePlayer
    CambioSkin Cambio;
    std::string skin = "";
    skin = Cambio.getSprite();

    if(skin == "")
        skin = "Players/Player1.png";

    SpritePlayer = Sprite::create(skin);
    SpritePlayer->setPosition(tamano.width / 6, tamano.height * 0.20);
    SpritePlayer->setScale(0.55, 0.55);
    addChild(SpritePlayer);
    //Colisiones del player
    //playerColision=SpritePlayer->getBoundingBox();
    //Sprites y colisiones de obstaculos y plataformas
    initObstaculos();
    //Aplicar physicsBody al sprite
    SpritePlayer->addComponent(physicsPlayer);

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener1, SpritePlayer);

   schedule(CC_SCHEDULE_SELECTOR(Level1::movimientoCamara));
   schedule(CC_SCHEDULE_SELECTOR(Level1::saltar));
   schedule(CC_SCHEDULE_SELECTOR(Level1::colision));
   schedule(CC_SCHEDULE_SELECTOR(Level1::gravedad));
    return true;
}

void Level1::initObstaculos() {
    
 //Puas
    int y = tamano.height * 0.20 - 20;
    crearPua(700, y);

    crearPua(900, y);

    crearPua(1100, y);
    //
    //crearBloque(tamano.width + 700, y - 20);

    //crearBloque(puas[1].getMaxX(), puas[1].getMinY());

    crearMeta(1300, y);
}

void Level1::keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    Vec2 loc = event->getCurrentTarget()->getPosition();

    switch (keyCode) {
    case EventKeyboard::KeyCode::KEY_SPACE:
        jump = true;
        break;

    case EventKeyboard::KeyCode::KEY_P:
        pausa = !pausa;
        if (pausa) {
            //CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
            physicsPlayer->setVelocity(cocos2d::Vec2(0, 0));
            labelPause->setVisible(true);

            this->pause();
        }
        if (!pausa) {
            //CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
            physicsPlayer->setVelocity(cocos2d::Vec2(200, 0));
            labelPause->setVisible(false);
           
            this->resume();
        }
        break;

    case EventKeyboard::KeyCode::KEY_R:
        labelPause->setVisible(false);
        this->resume();
        break;

    case EventKeyboard::KeyCode::KEY_ESCAPE:
        guardarPuntos();
        Director::getInstance()->replaceScene(TransitionFadeBL::create(1, HelloWorld::createScene()));
        break;
    }

}

void Level1::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application

    Director::getInstance()->replaceScene(TransitionFlipX::create(1, HelloWorld::createScene()));

}

void Level1::movimientoPlayer(float dt) {

   /* Vec2 loc = SpritePlayer->getPosition();
    SpritePlayer->setPosition(loc.x + 0.4, loc.y);*/
}

void Level1::updateScore() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    string puntos;
    puntos = "SCORE: " + std::to_string(puntosLevel);

    labelScore = Label::createWithTTF(puntos, "fonts/Demoness.otf", 10);
    if (labelScore == nullptr)
    {
        problemLoading("'fonts/Demoness.otf'");
    }
    else
    {
        // position the label on the center of the screen
        labelScore->setPosition(Vec2((origin.x + visibleSize.width / 2) - 90,
            (origin.y + visibleSize.height - labelScore->getContentSize().height)));

        // add the label as a child to this layer
        this->addChild(labelScore, 1);
    }
}

void Level1::guardarPuntos() {
    ofstream file;
    file.open("C:/Repositorio/ProyectoGeometryDash/Resources/Puntajes.txt", ios::app);
    file.seekp(0, ios::end);
    file << "TU NUEVO PORCENTAJE DEL NIVEL ES: " << puntosLevel << "%\n";
    file.close();
}

void Level1::GANASTE() {
    auto director = Director::getInstance();
    auto tamano = director->getWinSize();

    auto labelGanador = Label::createWithTTF("PASASTE El NIVEL", "fonts/Demoness.otf", 13);
    if (labelGanador == nullptr)
    {
        problemLoading("'fonts/Demoness.otf'");
    }
    else
    {
        // position the label on the center of the screen
        labelGanador->setPosition(tamano.width / 2, tamano.height * 0.50);

        // add the label as a child to this layer
        this->addChild(labelGanador, 1);
        labelGanador->setVisible(true);
        
    }

    auto labelSalir = Label::createWithTTF("Presioan  [ESC]  para salir", "fonts/arial.ttf", 7);
    if (labelSalir == nullptr)
    {
        problemLoading("'fonts/arial.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        labelSalir->setPosition(tamano.width / 2, tamano.height * 0.45);

        // add the label as a child to this layer
        this->addChild(labelSalir, 1);
        labelSalir->setVisible(true);
    }

    /*physicsPlayer->setVelocity(cocos2d::Vec2(0, 0));*/
    this->pause();

    auto keyboardListener2 = EventListenerKeyboard::create();
    keyboardListener2->onKeyPressed = CC_CALLBACK_2(Level1::keyPressed, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener2, labelSalir);
}

void Level1::movimientoCamara(float a) {
    camara->setPosition(SpritePlayer->getPosition().x + 150, 160);
}

void Level1::saltar(float h) {
    if (jump) {
        fall = false;
        i++;
        SpritePlayer->setRotation(SpritePlayer->getRotation() + 3);
        if (i < 23) {
            SpritePlayer->setPosition(SpritePlayer->getPosition().x, SpritePlayer->getPosition().y + 3);
        }
       else fall = true;
    } 
    
    if (i >= 30) {
        jump = false;//fall = true;
        i = 0;
    }
}

void Level1::colision(float noImporta) {
    

    for (int i = 0; i < puas.size(); i++)
    {
        if (puas[i].intersectsCircle(SpritePlayer->getPosition(), 15))
        {
            morir();
        }
    }

    bool entro = false;
    for (int i = 0; i < bloques.size(); i++)
    {
        if (bloques[i].intersectsCircle(SpritePlayer->getPosition(), 15))
        {
            if (!jump)
            {
                SpritePlayer->setPosition(SpritePlayer->getPosition().x, bloques[i].getMaxY() + 15);
                //jump = false;
                fall = true;
                entro = true;
            }
        }
    }

    if (meta.intersectsCircle(SpritePlayer->getPosition(), 15))
    {
        GANASTE();
    }
    //else {
    //   /* if (fall) {
    //       // SpritePlayer->setPosition(SpritePlayer->getPosition().x,SpritePlayer->getPosition().y-1.5);
}

void Level1::gravedad(float h) {
    if (SpritePlayer->getPositionY() > tamano.height * 0.20&&fall) {
        physicsPlayer->setVelocity(Vec2(200, -200));
    }
    else {
        physicsPlayer->setVelocity(Vec2(200, 0));
    }
}

void Level1::morir() {
    SpritePlayer->setVisible(false);
    jump = false;i = 0;
    fall = false;
    pausa = true;
    //CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    //CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("C:/Users/hecto/source/repos/G/Resources/hit.mp3");
    //cooldown
    scheduleOnce(CC_SCHEDULE_SELECTOR(Level1::respawn), 0.0f);
}

void Level1::respawn(float g) {
    pausa = false;
    //auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    //audio->preloadBackgroundMusic("C:/Users/hecto/source/repos/G/Resources/Crystals.mp3");
   // audio->playBackgroundMusic("C:/Users/hecto/source/repos/G/Resources/Crystals.mp3");
    SpritePlayer->setVisible(true);
    SpritePlayer->setPosition(tamano.width / 6, tamano.height * 0.20);
    SpritePlayer->setRotation(SpritePlayer->getRotation() - SpritePlayer->getRotation());
}

void Level1::crearPua(int x, int y)
{
    auto Sprite = cocos2d::Sprite::create("pua.png");
    Sprite->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_RIGHT);
    Sprite->setPosition(x, y);
    Sprite->setScale(0.5, 0.5);
    Pua pua = Sprite->getBoundingBox();
    puas.push_back(pua);
    addChild(Sprite);
}

void Level1::crearBloque(int x, int y)
{
    auto spriteSuelo = Sprite::create("C:/Repositorio/ProyectoGeometryDash/Resources/bloque.png");
    spriteSuelo->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);
    spriteSuelo->setPosition(x, y);
    spriteSuelo->setScale(0.4, 0.4);
    Bloque suelo = spriteSuelo->getBoundingBox();
    bloques.push_back(suelo);
    addChild(spriteSuelo);
}

void Level1::crearMeta(int x, int y)
{
    auto sprite = Sprite::create("Meta.png");
    sprite->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);
    sprite->setPosition(x, y);
    meta = sprite->getBoundingBox();
    addChild(sprite);
}