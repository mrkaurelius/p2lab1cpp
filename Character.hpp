#pragma once 
#ifndef CHARACTER_H
#define CHARACTER_H
#include <iostream>
#include <bits/stdc++.h> 
#include <SFML/Graphics.hpp>
#include <deque> 

//empty constructorda redefinition alıyorum  aceba legalmi 
//empy constructor conksyon imzası ile ilgilimi ? 
#define INF 2147483647

struct node_t
{
    int x;
    int y;
    int counter;
};

class Character
{
private:
public:

    int logicX;
    int logicY;
    int initialX;
    int initialY;
    //bool good;
    sf::RectangleShape spirit;
public:
    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();
    //void moveX(Character *c,int deltaX);
    //void moveY(Character *c,int deltaY);

public:
    Character(const char* name,int x,int y);
    Character();
    ~Character();

    const char *name;
    void sayHello();
};

#endif