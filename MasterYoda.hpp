#pragma once
#include <bits/stdc++.h> 
#include <iostream> 
#include <SFML/Graphics.hpp>
#include "Character.hpp"

class MasterYoda : public Character
{
private:
    /* data */
public:
    float healt;
public:
    MasterYoda(/* args */);
    MasterYoda(const char* name,int x,int y);
    ~MasterYoda();
};

