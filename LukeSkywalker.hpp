#pragma once
#include <bits/stdc++.h> 
#include <iostream> 
#include <SFML/Graphics.hpp>
#include "Character.hpp"

class LukeSkywalker : public Character
{
private:
    /* data */
public:
    float healt;
public:
    LukeSkywalker(/* args */);
    LukeSkywalker(const char* name,int x,int y);
    ~LukeSkywalker();
};

