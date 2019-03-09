#pragma once
#include <bits/stdc++.h> 
#include <iostream> 
#include <SFML/Graphics.hpp>
#include "Character.hpp"

class DarthVader : public Character
{
private:
    /* data */
public:
    void moveRandom(int **gameBoardLogic);

public:
    DarthVader(const char* name,int x,int y);
    DarthVader(/* args */);
    ~DarthVader();
};