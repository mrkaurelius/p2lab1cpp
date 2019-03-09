#pragma once
#include <bits/stdc++.h> 
#include <iostream> 
#include <SFML/Graphics.hpp>
#include "Character.hpp"

class KyloRen : public Character
{
private:
    /* data */
public:
    void moveRandom(int **gameBoardLogic);

public:
    KyloRen(const char* name,int x,int y);
    KyloRen(/* args */);
    ~KyloRen();
};