#pragma once
#include <bits/stdc++.h> 
#include <iostream> 
#include <SFML/Graphics.hpp>
#include "Character.hpp"
#include <deque> 

class Stormtrooper : public Character
{
private:
    /* data */
public: 
    std::vector <node_t> shortest_path;
public:
    void moveRandom(int **gameBoardLogic);
    void setName(const char *name);
    const char* getName();
    std::vector <node_t> calcPath(int tx,int ty,int **gameBoardLogic);
public:
    Stormtrooper(const char* name,int x,int y);
    Stormtrooper(/* args */);
    ~Stormtrooper();
};