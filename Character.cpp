#include "Character.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>


Character::Character(const char* name,int x,int y){
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
    tmpSpirit.setTextureRect(sf::IntRect(character_textureSize.x * 7,character_textureSize.y * 2,character_textureSize.x,character_textureSize.y));
    
    this->spirit = tmpSpirit;
    std::cout << "CHAR merhaba zalım dunya eved adım "<< this->name << std::endl;
}

void Character::moveRight(){
    this->logicY += 1;
    this->spirit.move(50 * 1,0);
}
void Character::moveLeft(){
    this->logicY -= 1;
    this->spirit.move(50 * -1,0);
}

void Character::moveUp(){
    this->logicX -= 1;
    this->spirit.move(0,50 * -1);
}

void Character::moveDown(){
    this->logicX += 1;
    this->spirit.move(0,50 * 1);
}

std::vector<sf::Vector2f> Character::shortestPath(){
    std::cout << "merhaba zalım class " << std::endl;
    std::vector<sf::Vector2f> rVect;
    return rVect;
    //buradan return alamayınca neden seg fault yiyorum

};

Character::Character()
{

}


Character::~Character(){
    std::cout << "CHAR dunya meger sende bir hayalden ibaretmissin... " << this->name << std::endl;
}

/*
    sf::RectangleShape character(sf::Vector2f(50.0f,50.0f)); //bunları classa tasısam 
    
    character.setTexture(&character_texture);
    character.setTextureRect(sf::IntRect(character_textureSize.x * 3,character_textureSize.y * 4,character_textureSize.x,character_textureSize.y));
    //character x = 6 y = %
*/