#include <SFML/Graphics.hpp>
#include "KyloRen.hpp"
#include "Character.hpp"
#include <iostream>

KyloRen::KyloRen(const char* name,int x,int y){
    this->name = name;
    this->logicX = x;
    this->logicY = y-1;
    this->initialX = x;
    this->initialY = y;
    
    sf::Texture character_texture;
    character_texture.loadFromFile("/home/mrk1debian/gelistirme/cpptut/media/sheet1.png");
    sf::Vector2u character_textureSize = character_texture.getSize();
    character_textureSize.x /= 8;
    character_textureSize.y /= 8;
   
    sf::RectangleShape tmpSpirit(sf::Vector2f(50.0f,50.0f));
    tmpSpirit.setPosition((y-1) * 50, x * 50);
    tmpSpirit.setTextureRect(sf::IntRect(character_textureSize.x * 4,character_textureSize.y * 4,character_textureSize.x,character_textureSize.y));
    
    this->spirit = tmpSpirit;
    std::cout << "KYLO merhaba zalım dunya eved adım "<< this->name << std::endl;
}

void KyloRen::moveRandom(int **gameBoardLogic){
    srand(time(NULL));
    int x = this->logicX;
    int y = this->logicY;

    //this->logicX++;
    //this->spirit.move(0,50 * 1);

    //this->logicY++;
    //this->spirit.move(50 * 1,0);
    
    for(int i = 0; i < 11; i++) //rows
    {
        for(int j = 0; j < 14; j++) //cos
        {
            if(i == x && j == y){
                std::cout << "X" << "   ";
            } else 
            std::cout << gameBoardLogic[i][j] << "   ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    std::vector<std::vector<int>> paths;
    std::vector<char> sr;
    if (this->logicX+1 < 11) {
        if (gameBoardLogic[this->logicX+1][this->logicY]) {
            std::vector <int> tmpv;
            tmpv.push_back(this->logicX+1);
            tmpv.push_back(this->logicY);
            paths.push_back(tmpv);
            sr.push_back('d');
        }
    }

    if (this->logicX-1 > 0) {
        if (gameBoardLogic[this->logicX-1][this->logicY]) {
            std::vector <int> tmpv;
            tmpv.push_back(this->logicX-1);
            tmpv.push_back(this->logicY);
            paths.push_back(tmpv);
            sr.push_back('u');
        }
    }
    
    if (this->logicY+1 < 14) {
    if (gameBoardLogic[this->logicX][this->logicY +1 ]) {
            
            std::vector <int> tmpv;
            tmpv.push_back(this->logicX);
            tmpv.push_back(this->logicY+1);
            paths.push_back(tmpv);
            sr.push_back('r');
        }
    } 

    if (this->logicY-1 >= 0) {
        if (gameBoardLogic[this->logicX][this->logicY-1]) {
            std::vector <int> tmpv;
            tmpv.push_back(this->logicX);
            tmpv.push_back(this->logicY-1);
            paths.push_back(tmpv);
            sr.push_back('l');
        }
    
    }    
    int r = rand() % paths.size();
    //std::cout << r << std::endl;
    this->logicX = paths[r][0];
    this->logicY = paths[r][1];

    if (sr[r] == 'd') {
        this->spirit.move(0,50 * 1);
    }
    if (sr[r] == 'u') {
        this->spirit.move(0,50 * -1);
    }
    if (sr[r] == 'r') {
        this->spirit.move(50 * 1,0);
    }
    if (sr[r] == 'l') {
        this->spirit.move(50 * -1,0);
    }

    x = this->logicX;
    y = this->logicY;



    
    for(int i = 0; i < 11; i++) //rows
    {
        for(int j = 0; j < 14; j++) //cos
        {
            if(i == x && j == y){
                std::cout << "X" << "   ";
            } else 
            std::cout << gameBoardLogic[i][j] << "   ";
        }
        std::cout << std::endl;
    }
    
    std::cout << std::endl;

   std::cout << "////////////////////////////////////////////////////////" << std::endl;
}

KyloRen::KyloRen()
{

}

KyloRen::~KyloRen()
{
    std::cout << "KYLO dunya meger sende bir hayalden ibaretmissin... " << this->name << std::endl;
}