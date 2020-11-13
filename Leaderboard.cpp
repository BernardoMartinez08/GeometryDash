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

#include "Leaderboard.h"
#include <fstream>
#include <iostream>
#include "HelloWorldScene.h"
#include <string>

using namespace std;

USING_NS_CC;

Scene* Leaderboard::createScene()
{
    return Leaderboard::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Leaderboard::init()
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
                                            CC_CALLBACK_1(Leaderboard::menuCloseCallback, this));

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

    auto spriteFondo = Sprite::create("Fondos/board.jpg");
    if (spriteFondo == nullptr)
    {
        problemLoading("'Fondos/board.jpg'");
    }
    else
    {
        spriteFondo->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        this->addChild(spriteFondo, 0);
    }

    UltimasJugadas();
    return true;
}

void Leaderboard::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->replaceScene(TransitionFlipX::create(1, HelloWorld::createScene()));

}

void Leaderboard::UltimasJugadas() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    string cadena = "";
    string aux = "";

    ifstream fe("C:/Repositorio/ProyectoGeometryDash/Resources/Puntajes.txt", ios::in);
    int cont = 1;
    string Last10[10];
    if (fe.is_open()) {

        while (getline(fe, aux)) {
            cont++;
        }
    }

    ifstream fe2("C:/Repositorio/ProyectoGeometryDash/Resources/Puntajes.txt", ios::in);
    int Lines = 0;
    int top = 0;
    if (fe2.is_open()) {

        while (getline(fe2, aux)) {
            if (Lines >= cont - 10) {
                Last10[top] = aux;
                top++;
            }
            Lines++;
        }
    }

    string txt = "LEADERBOARD";
    auto labelRankTitulo = Label::createWithTTF(txt, "fonts/Demoness.otf", 18);
    if (labelRankTitulo == nullptr)
    {
        problemLoading("'fonts/Demoness.otf'");
    }
    else
    {
        // position the label on the center of the screen
        labelRankTitulo->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - labelRankTitulo->getContentSize().height - 30));

        // add the label as a child to this layer
        this->addChild(labelRankTitulo, 1);
    }

    int position = 60;
    for (int i = 9; i > -1; i--) {
        if (Last10[i] != "") {
            auto labelRank = Label::createWithTTF(Last10[i], "fonts/arial.ttf", 10);
            if (labelRank == nullptr)
            {
                problemLoading("'fonts/arial.ttf'");
            }
            else
            {
                labelRank->setPosition(Vec2(origin.x + visibleSize.width / 2,
                                            origin.y + visibleSize.height - labelRank->getContentSize().height - position));
                labelRank->setColor(Color3B::BLUE);
                this->addChild(labelRank, 1);
                position += 20;
            }
        }   
    }

    fe.close();
    fe2.close();
}