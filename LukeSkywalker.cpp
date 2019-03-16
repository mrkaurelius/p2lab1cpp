#include <SFML/Graphics.hpp>
#include "LukeSkywalker.hpp"
#include "Character.hpp"
#include <iostream>

LukeSkywalker::LukeSkywalker(const char* name,int x,int y){
    this->healt = 3;
    this->name = name;
    this->logicX = x-1;
    this->logicY = y+1;
    this->initialX = x-1;
    this->initialY = y+1;
    sf::Texture character_texture;
    //character_texture.loadFromFile("/home/mrk1debian/gelistirme/cpptut/media/sheet1.png");
    character_texture.loadFromFile("/home/mrk0debian/gelistirme/p2lab1cpp/media/sheet1.png");

    sf::Vector2u character_textureSize = character_texture.getSize();
    character_textureSize.x /= 8;
    character_textureSize.y /= 8;
   
    sf::RectangleShape tmpSpirit(sf::Vector2f(50.0f,50.0f));
    tmpSpirit.setPosition(x * 50, y * 50);
    tmpSpirit.setTextureRect(sf::IntRect(character_textureSize.x * 5,character_textureSize.y * 4,character_textureSize.x,character_textureSize.y));
    
    this->spirit = tmpSpirit;
    std::cout << "LUKE merhaba zalım dunya eved adım "<< this->name << std::endl;
}
void LukeSkywalker::setName(const char *name){
    this->name = name;
}

const char* LukeSkywalker::getName(){
    return this->name;
}

LukeSkywalker::LukeSkywalker()
{

}

LukeSkywalker::~LukeSkywalker()
{
    std::cout << "LUKE dunya meger sende bir hayalden ibaretmissin... " << this->name << std::endl;
}