#include <SFML/Graphics.hpp>
#include <bits/stdc++.h> 
#include <string>
#include "Character.hpp"
#include "Stormtrooper.hpp"

using namespace std;

vector<vector<sf::RectangleShape>> initTilemap(int rows,int cols);
int** initBoardLogic(int row,int col);
bool checkMove(int x, int y,int** gameBoardLogic);
void printLogicMap(int x, int y,int** gameBoardLogic);

vector<Character*> initCharacters(){
    vector<Character*> sv;
    //kapılar hardcoded
    //Karakter:Stormtrooper,Kapi:A
    string line;
    ifstream map("harita.txt");
    if ( map.is_open() ) {
        //int ax=0;int ay=5;int bx=4;int by=0;int cx=12;int cy=0;int dx=13;int dy=5;int ex=4;int ey=10;
        while( getline(map,line) ){
            char tn[64];
            char td;
            if (line[0] == 'K') {
                string tn;
                char td;
                string s = line;
                string delimiter = ",";
                string token = s.substr(0, s.find(delimiter));
                string s1 = token;
                string delimiter1 = ":";
                string token1 = s1.substr(s1.find(delimiter1)+1,s1[s1.size()-1]);
                tn = token1;
                td = line[line.size()-1];
                //cout << td << " " << tn << endl;
                int ix;int iy;
                if (td == 'A') {
                    ix = 0;iy=5;
                }
                if (td == 'B') {
                    ix = 4;iy=0;
                }
                if (td == 'C') {
                    ix = 12;iy=0;
                }
                if (td == 'D') {
                    ix = 13;iy=5;
                }
                if (td == 'E') {
                    ix = 4;iy=10;
                }
                if(!tn.compare("Stormtrooper") ){
                    Character *p =new Stormtrooper("Stormtrooper",ix,iy);
                    sv.push_back(p);
                }
            }
        }
    }

    else cout << "dosya acılamadı " << endl;
    return sv;
}


int main()
{   
    sf::RenderWindow window(sf::VideoMode(750, 750), "SFML works!");
    int **gameBoardLogic;
    gameBoardLogic = initBoardLogic(11,14);
    vector<vector<sf::RectangleShape>> tileMap = initTilemap(11,14);

    vector<Character*> charList = initCharacters(); 

    cout << charList.size() << endl;

    // !!! logic konumlar ili ilgili sıkıntı var atlatma yapıldı    
    // !!! logic grafik farkı yeniden baslatmayı etliler
    // !!! harita dısına cikinca segfault oluyor 
    // texturlerin kaybolmasının sebebi pointer kullanmamam olabilir 
    // constructorların isleyisini kavra 
    //road texture
    sf::Texture road;
    road.loadFromFile("/home/mrk1debian/gelistirme/cpptut/media/sheet1.png");
    sf::Vector2u road_textureSize = road.getSize();
    road_textureSize.x /= 8;
    road_textureSize.y /= 8;
    
    //wall texture
    sf::Texture wall;
    wall.loadFromFile("/home/mrk1debian/gelistirme/cpptut/media/sheet1.png");
    sf::Vector2u wall_textureSize = wall.getSize();
    wall_textureSize.x /= 8;
    wall_textureSize.y /= 8;

    //player texture
    sf::Texture player_texture;
    player_texture.loadFromFile("/home/mrk1debian/gelistirme/cpptut/media/sheet1.png");

    //stormtrooper texture
    sf::Texture stormtrooper_texture;
    stormtrooper_texture.loadFromFile("/home/mrk1debian/gelistirme/cpptut/media/sheet1.png");

    Character c("rezzak",6,5);
    c.spirit.setTexture(&player_texture);
    
        for(int i = 0; i < charList.size(); i++)
        {
            Character *tp = charList[i]; 
            tp->spirit.setTexture(&stormtrooper_texture);
        }
        

    //texturede sıkıntı oluyor
    //classa yazacagım move komutu ikisinide beraber götürsun grafik ve logic 
    while (window.isOpen())
    {   
        //bağımsız hareket etdemyi dusun 
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        sf::Clock clock; // starts the clock
        // clock cok sağlıklı calısmıyor

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {
            sf::Time elapsed1 = clock.getElapsedTime();
            std::cout << elapsed1.asSeconds() << std::endl;
            while(elapsed1.asSeconds() < 0.29){
                elapsed1 = clock.getElapsedTime();
            }
            if (checkMove(c.logicX,c.logicY-1,gameBoardLogic)) {
                c.moveLeft();
                cout << endl;
            }
            printLogicMap(c.logicX,c.logicY,gameBoardLogic);
            clock.restart();

        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
            sf::Time elapsed1 = clock.getElapsedTime();
            std::cout << elapsed1.asSeconds() << std::endl;
            while(elapsed1.asSeconds() < 0.29){
                elapsed1 = clock.getElapsedTime();
            }         
            if (checkMove(c.logicX,c.logicY+1,gameBoardLogic)) {
                c.moveRight();
                cout << endl;
            }
            printLogicMap(c.logicX,c.logicY,gameBoardLogic);
            clock.restart();


        }      
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        {
            sf::Time elapsed1 = clock.getElapsedTime();
            std::cout << elapsed1.asSeconds() << std::endl;
            while(elapsed1.asSeconds() < 0.29){
                elapsed1 = clock.getElapsedTime();
            }
            if (checkMove(c.logicX-1,c.logicY,gameBoardLogic)) {
                c.moveUp();
                cout << endl;                
            }
            printLogicMap(c.logicX,c.logicY,gameBoardLogic);
            clock.restart();

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        {
            sf::Time elapsed1 = clock.getElapsedTime();
            std::cout << elapsed1.asSeconds() << std::endl;
            while(elapsed1.asSeconds() < 0.29){
                elapsed1 = clock.getElapsedTime();
            }
            if(checkMove(c.logicX+1,c.logicY,gameBoardLogic)) {
                c.moveDown();
                cout << endl;                
            }        
            printLogicMap(c.logicX,c.logicY,gameBoardLogic);
            clock.restart();
        }

        window.clear();
        for(int i = 0; i < tileMap.size(); i++)
        {
            vector<sf::RectangleShape> tilemapRow = tileMap[i];
            for(int j = 0; j < tilemapRow.size(); j++)
            {

                //duvarlara texture girdir 
                if (gameBoardLogic[i][j] == 0) {

                    tilemapRow[j].setTexture(&wall);
                    tilemapRow[j].setTextureRect(sf::IntRect(wall_textureSize.x * 1,wall_textureSize.y * 3,wall_textureSize.x,wall_textureSize.y));
                    window.draw(tilemapRow[j]);
                    
                } else {
                    tilemapRow[j].setTexture(&road);
                    tilemapRow[j].setTextureRect(sf::IntRect(road_textureSize.x * 2,road_textureSize.y * 1,road_textureSize.x,road_textureSize.y));
                    window.draw(tilemapRow[j]);
                }

            }
        }
        //npc ve oyuncular buraya gelebilir 
        // clear draw ve display olayını ogren 
        window.draw(c.spirit);
       
        for(int i = 0; i < charList.size(); i++)
        {
            Character *tp = charList[i]; 
            window.draw(tp->spirit);
        }
        
        //render ve logic sırası cnasıl olmalı, aradaki zaman nasıl ayarlanamalı
        window.display();
    }

    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////

vector<vector<sf::RectangleShape>> initTilemap(int rows,int cols){
    vector<vector<sf::RectangleShape>> tileMap;
   
    for(int y = 0; y < rows; y++)
    {
        vector<sf::RectangleShape> tmpvect;
        for(int x = 0; x < cols; x++)
        {
            sf::RectangleShape rectangle;
            rectangle.setSize(sf::Vector2f(50, 50));
            rectangle.setPosition(x * 50, y * 50);
            tmpvect.push_back(rectangle);
        }
        tileMap.push_back(tmpvect);
        tmpvect.clear();

    }
    return tileMap;
}

int** initBoardLogic(int row,int col){
    //dosyayı oku ve dondur
    int **logicArr;
    string line;
    string logic;
    logicArr = new int*[row];

    ifstream map("harita.txt");
    if ( map.is_open() ) {
        while( getline(map,line) ){
            if (line[0] == '1' || line[0] == '0') {
                //handle logic 
                //cout << line << endl;
                for(int i = 0; i < line.size(); i++)
                {
                    if ( line[i] == '1' || line[i] == '0' ) {
                        logic.push_back(line[i]);
                    }
                }
            }
        }
        map.close();
    }
    else cout << "dosya acılamadı " << endl;
    
    //cout << logic << endl;

    for(int i = 0; i < row; i++)
    {
        logicArr[i] = new int[col];
        for(int j = 0; j < col; j++)
        {
            logicArr[i][j] = logic[i * 14 + j] - 48; //ascii magic
        }
    }
    
    /*
    cout << "harita start" << endl;
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            cout << logicArr[i][j] << " ";
        }
        cout << endl;
    }
    cout << "harita end" << endl;
    */

    return logicArr;
}

bool checkMove(int x, int y,int** gameBoardLogic){
    bool move = false;
    if (gameBoardLogic[x][y] == 1) {
        move = true;
        cout << "true" << endl;
    } else
    {
        cout << "oraya oynamaz" << endl;
    }
    return move;
}

void printLogicMap(int x, int y,int** gameBoardLogic){
    for(int i = 0; i < 11; i++) //rows
    {
        for(int j = 0; j < 14; j++) //cos
        {
            if(i == x && j == y){
                cout << "X" << "   ";
            } else 
            cout << gameBoardLogic[i][j] << "   ";
        }
        cout << endl;
    }
}

/*
    for(int i = 0; i < 11; i++) //rows
    {
        for(int j = 0; j < 14; j++) //cos
        {
            //cout << gameBoardLogic[i][j] << "\t";
        }
        //cout << endl;
    }
*/