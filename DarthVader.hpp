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
    std::vector <node_t> shortest_path;
public:
    void moveRandom(int **gameBoardLogic);
    std::vector <node_t> calcPath(int tx,int ty);

public:
    DarthVader(const char* name,int x,int y);
    DarthVader(/* args */);
    ~DarthVader();
};