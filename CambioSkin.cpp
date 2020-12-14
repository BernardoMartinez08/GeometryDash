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

#include "CambioSkin.h"
#include <fstream>
#include <iostream>
#include "HelloWorldScene.h"
#include <string>

using namespace std;

USING_NS_CC;

Scene* CambioSkin::createScene()
{
    return CambioSkin::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool CambioSkin::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto closeItem = MenuItemImage::create(
                                            "Botones/SalirBT2.png",
                                            "Botones/SalirBTSelected.png",
                                            CC_CALLBACK_1(CambioSkin::menuCloseCallback, this));

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


    auto label = Label::createWithTTF("Geometry Dash", "fonts/PUSAB___.otf", 34);
    if (label == nullptr)
    {
        problemLoading("'fonts/PUSAB___.otf'");
    }
    else
    {
        label->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - label->getContentSize().height));

        this->addChild(label, 1);
    }

    auto spriteFondo = Sprite::create("Fondos/Skin.jpg");
    if (spriteFondo == nullptr)
    {
        problemLoading("'Fondos/board.jpg'");
    }
    else
    {
        spriteFondo->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        this->addChild(spriteFondo, 0);
    }

    pauseScreen();
    return true;
}

void CambioSkin::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->replaceScene(TransitionFlipX::create(1, HelloWorld::createScene()));

}



void CambioSkin::pauseScreen() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto director = Director::getInstance();
    auto tamano = director->getWinSize();


    auto Player1 = MenuItemImage::create(
                "Players/Player1.png",
                "Players/Player1.png",
                CC_CALLBACK_1(CambioSkin::cambiarPlayer1, this));

    if (Player1 == nullptr ||
        Player1->getContentSize().width <= 0 ||
        Player1->getContentSize().height <= 0)
    {
        problemLoading("'Players/Player1.png' and 'Players/Player1.png'");
    }
    else
    {
        float x = (origin.x + visibleSize.width - Player1->getContentSize().width / 2) - 300;
        float y = origin.y + 60 + Player1->getContentSize().height / 2;
        Player1->setPosition(Vec2(x, y));
    }

    // create menu, it's an autorelease object
    botonPlayer1 = Menu::create(Player1, NULL);
    botonPlayer1->setPosition(Vec2::ZERO);
    this->addChild(botonPlayer1, 3);

    auto Player2 = MenuItemImage::create(
        "Players/Player2.png",
        "Players/Player2.png",
        CC_CALLBACK_1(CambioSkin::cambiarPlayer2, this));

    if (Player2 == nullptr ||
        Player2->getContentSize().width <= 0 ||
        Player2->getContentSize().height <= 0)
    {
        problemLoading("'Players/Player2.png' and 'Players/Player2.png'");
    }
    else
    {
        float x = (origin.x + visibleSize.width - Player2->getContentSize().width / 2) - 200;
        float y = origin.y + 60 + Player2->getContentSize().height / 2;
        Player2->setPosition(Vec2(x, y));
    }

    // create menu, it's an autorelease object
    botonPlayer2 = Menu::create(Player2, NULL);
    botonPlayer2->setPosition(Vec2::ZERO);
    this->addChild(botonPlayer2, 3);


    auto Player3 = MenuItemImage::create(
        "Players/Player3.png",
        "Players/Player3.png",
        CC_CALLBACK_1(CambioSkin::cambiarPlayer3, this));

    if (Player3 == nullptr ||
        Player3->getContentSize().width <= 0 ||
        Player3->getContentSize().height <= 0)
    {
        problemLoading("'Players/Player3.png' and 'Players/Player3.png'");
    }
    else
    {
        float x = (origin.x + visibleSize.width - Player3->getContentSize().width / 2) - 100;
        float y = origin.y + 60 + Player3->getContentSize().height / 2;
        Player3->setPosition(Vec2(x, y));
    }

    // create menu, it's an autorelease object
    botonPlayer3 = Menu::create(Player3, NULL);
    botonPlayer3->setPosition(Vec2::ZERO);
    this->addChild(botonPlayer3, 3);

    labelPersonaje = Label::createWithTTF("CAMBIA TU SKIN", "fonts/Demoness.otf", 15);
    if (labelPersonaje == nullptr)
    {
        problemLoading("'fonts/Demoness.otf'");
    }
    else
    {
        // position the label on the center of the screen

        labelPersonaje->setPosition(tamano.width / 2, (tamano.height * 0.50) - 80);

        // add the label as a child to this layer
        this->addChild(labelPersonaje, 2);
        labelPersonaje->setVisible(true);
    }
}

void CambioSkin::cambiarPlayer1(Ref* pSender)
{
    spriteFile = "Players/Player1.png";
    ofstream file;
    file.open("C:/Repositorio/ProyectoGeometryDash/Resources/Skin.txt");
    file.seekp(0, ios::beg);
    file << spriteFile;
    file.close();
}

void CambioSkin::cambiarPlayer2(Ref* pSender)
{
    spriteFile = "Players/Player2.png";
    ofstream file;
    file.open("C:/Repositorio/ProyectoGeometryDash/Resources/Skin.txt");
    file.seekp(0, ios::beg);
    file << spriteFile;
    file.close();
}

void CambioSkin::cambiarPlayer3(Ref* pSender)
{
    spriteFile = "Players/Player3.png";
    ofstream file;
    file.open("C:/Repositorio/ProyectoGeometryDash/Resources/Skin.txt");
    file.seekp(0, ios::beg);
    file << spriteFile;
    file.close();
}

std::string CambioSkin::getSprite() {
    ifstream fe2("C:/Repositorio/ProyectoGeometryDash/Resources/Skin.txt", ios::in);
    string aux;
    if (fe2.is_open()) {

        while (getline(fe2, aux)) {
            spriteFile = aux;
        }
    }
    return spriteFile;
}

void CambioSkin::setSprite(std::string player) {
    this->spriteFile = player;
}
