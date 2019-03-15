#pragma once
#include <bits/stdc++.h> 
#include <iostream> 
#include <SFML/Graphics.hpp>
#include "Character.hpp"
#include <deque> 

class KyloRen : public Character
{
private:
    /* data */
public:
    std::vector <node_t> shortest_path;
public:
    void moveRandom(int **gameBoardLogic);
    std::vector <node_t> calcPath(int tx,int ty,int **gameBoardLogic);
    void setName(const char *name);
    const char* getName();
public:
    KyloRen(const char* name,int x,int y);
    KyloRen(/* args */);
    ~KyloRen();
};