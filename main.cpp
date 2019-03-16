#include <SFML/Graphics.hpp>
#include <bits/stdc++.h> 
#include <string>
#include "Character.hpp"
#include "Stormtrooper.hpp"
#include "KyloRen.hpp"
#include "DarthVader.hpp"
#include "LukeSkywalker.hpp"
#include "MasterYoda.hpp"

using namespace std;

vector<vector<sf::RectangleShape>> initTilemap(int rows,int cols);
int** initBoardLogic(int row,int col);
bool checkMove(int x, int y,int** gameBoardLogic);
void printLogicMap(int x, int y,int** gameBoardLogic);
vector<Stormtrooper*> initStormtrooper();
vector<KyloRen*> initKyloRen();
vector<DarthVader*> initDarthVader();

void resetRound(Character *c,vector<DarthVader*> DarthV,vector<KyloRen*> KyloV,vector<Stormtrooper*> StormV ){
    for(int i = 0; i < DarthV.size(); i++)
    {
        DarthVader *td = DarthV[i];
        td->logicX = td->initialX;
        td->logicY = td->initialY;
        td->spirit.setPosition(td->initialY * 50,td->initialX * 50);
    }
    for(int i = 0; i < KyloV.size(); i++)
    {
        KyloRen *td = KyloV[i];
        td->logicX = td->initialX;
        td->logicY = td->initialY;
        td->spirit.setPosition(td->initialY * 50,td->initialX * 50);
    }
    for(int i = 0; i < StormV.size(); i++)
    {
        Stormtrooper *td = StormV[i];
        td->logicX = td->initialX;
        td->logicY = td->initialY;
        td->spirit.setPosition(td->initialY * 50,td->initialX * 50);
    }
    c->logicX = c->initialX;
    c->logicY = c->initialY;
    c->spirit.setPosition(c->initialY * 50,c->initialX * 50);    
}
    // !!! logic konumlar ili ilgili sıkıntı var atlatma yapıldı    
    // !!! logic grafik farkı yeniden baslatmayı etliler
    // !!! harita dısına cikinca segfault oluyor 
    //kylorenin hızlı olması metodu 2 kere cagırmasından oturu
        //hareketin yarısından yanma kontrolu yapmalı mıyım
    //karakterlerin logic debugunu yap
    //farklı karakterler icin farklı restartlar olabilir 
    // constructorların isleyisini kavra 
int main()
{   
    sf::RenderWindow window(sf::VideoMode(750, 750), "SFML works!");
    int **gameBoardLogic;
    gameBoardLogic = initBoardLogic(11,14);
    vector<vector<sf::RectangleShape>> tileMap = initTilemap(11,14);

    vector<Stormtrooper*> StormV = initStormtrooper(); 
    vector<KyloRen*> KyloV = initKyloRen(); 
    vector<DarthVader*> DarthV = initDarthVader(); 

    //iyi karakterleri mainde init et

    //road texture
    sf::Texture road;
    //road.loadFromFile("/home/mrk1debian/gelistirme/cpptut/media/sheet1.png");
    road.loadFromFile("/home/mrk0debian/gelistirme/p2lab1cpp/media/sheet1.png");

    sf::Vector2u road_textureSize = road.getSize();
    road_textureSize.x /= 8;
    road_textureSize.y /= 8;
    
    //wall texture
    sf::Texture wall;
    //wall.loadFromFile("/home/mrk1debian/gelistirme/cpptut/media/sheet1.png");
    wall.loadFromFile("/home/mrk0debian/gelistirme/p2lab1cpp/media/sheet1.png");

    sf::Vector2u wall_textureSize = wall.getSize();
    wall_textureSize.x /= 8;
    wall_textureSize.y /= 8;

    //player texture
    sf::Texture player_texture;
    //player_texture.loadFromFile("/home/mrk1debian/gelistirme/cpptut/media/sheet1.png");
    player_texture.loadFromFile("/home/mrk0debian/gelistirme/p2lab1cpp/media/sheet1.png");


    // texture ref
    sf::Texture texture_ref;
    //texture_ref.loadFromFile("/home/mrk1debian/gelistirme/cpptut/media/sheet1.png");
    texture_ref.loadFromFile("/home/mrk0debian/gelistirme/p2lab1cpp/media/sheet1.png");


    cout << "KARAKTERNI SEC !! YODA:1 LUKE:2" << endl;
    int chc;
    cin >> chc;
    int kx = 9;
    int ky = 13;
    if (chc == 1){
        
        MasterYoda c = MasterYoda("MasterYoda",6,5);
        c.spirit.setTexture(&player_texture);    
        for(int i = 0; i < KyloV.size(); i++)
        {
            KyloRen *tp = KyloV[i]; 
            tp->spirit.setTexture(&texture_ref);
        }
        
        for(int i = 0; i < StormV.size(); i++)
        {
            Stormtrooper *tp = StormV[i]; 
            tp->spirit.setTexture(&texture_ref);
        }

        for(int i = 0; i < DarthV.size(); i++)
        {
            DarthVader *tp = DarthV[i]; 
            tp->spirit.setTexture(&texture_ref);
        }


        //texturede sıkıntı oluyor
        //classa yazacagım move komutu ikisinide beraber götürsun grafik ve logic 

        cout << "debug" << endl;
        bool ENDROUND = false;


        while (window.isOpen())
        {   
            //bağımsız hareket etdemyi dusun 
            sf::Event event;
            if(c.logicX == kx && c.logicY == ky ){
                cout << "KAZANDIN BENDEN BU KADAR !!" << endl;
                exit(0);
            }
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
                //std::cout << elapsed1.asSeconds() << std::endl;
                while(elapsed1.asSeconds() < 0.29){
                    elapsed1 = clock.getElapsedTime();
                }
                if (checkMove(c.logicX,c.logicY-1,gameBoardLogic)) {
                    c.moveLeft();
                    cout << endl;
                }
                printLogicMap(c.logicX,c.logicY,gameBoardLogic);

                for(int i = 0; i < StormV.size(); i++)
                {
                    Stormtrooper *tp = StormV[i]; 
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;
                        //exit(0);
                    }
                    tp->moveRandom(gameBoardLogic);
                    tp->shortest_path =  tp->calcPath(c.logicX,c.logicY,gameBoardLogic);
                    //burada hesapla 
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;
                        //exit(0);
                    }
                }
                
                for(int i = 0; i < KyloV.size(); i++)
                {
                    KyloRen *tp = KyloV[i]; 
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;
                        //exit(0);
                    }
                    tp->moveRandom(gameBoardLogic);
                    tp->shortest_path =  tp->calcPath(c.logicX,c.logicY,gameBoardLogic);
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;
                        //exit(0);
                    }
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;
                        //exit(0);
                    }
                    tp->moveRandom(gameBoardLogic);
                    tp->shortest_path =  tp->calcPath(c.logicX,c.logicY,gameBoardLogic);
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;
                        //exit(0);
                    }
                    
                }
                
                for(int i = 0; i < DarthV.size(); i++)
                {
                    DarthVader *tp = DarthV[i]; 
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;
                        //exit(0);
                    }
                    tp->moveRandom(gameBoardLogic);
                    tp->shortest_path =  tp->calcPath(c.logicX,c.logicY);
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;
                        //exit(0);
                    }
                }
                clock.restart();
                
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
            {
                sf::Time elapsed1 = clock.getElapsedTime();
                //std::cout << elapsed1.asSeconds() << std::endl;
                while(elapsed1.asSeconds() < 0.29){
                    elapsed1 = clock.getElapsedTime();
                }         
                if (checkMove(c.logicX,c.logicY+1,gameBoardLogic)) {
                    c.moveRight();
                    cout << endl;
                }

                printLogicMap(c.logicX,c.logicY,gameBoardLogic);
                for(int i = 0; i < StormV.size(); i++)
                {
                    
                    Stormtrooper *tp = StormV[i];
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;
                        //exit(0);
                    }                 
                    tp->moveRandom(gameBoardLogic);
                    tp->shortest_path =  tp->calcPath(c.logicX,c.logicY,gameBoardLogic);
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;
                        //exit(0);
                    }
                }

                for(int i = 0; i < KyloV.size(); i++)
                {
                    KyloRen *tp = KyloV[i]; 
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;
                        //exit(0);
                    }
                    tp->moveRandom(gameBoardLogic);
                    tp->shortest_path =  tp->calcPath(c.logicX,c.logicY,gameBoardLogic);
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;
                        //exit(0);
                    }
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;
                        //exit(0);
                    }
                    tp->moveRandom(gameBoardLogic);
                    tp->shortest_path =  tp->calcPath(c.logicX,c.logicY,gameBoardLogic);
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;
                        //exit(0);
                    }                
                }

                for(int i = 0; i < DarthV.size(); i++)
                {
                    DarthVader *tp = DarthV[i]; 
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;
                        //exit(0);
                    }
                    tp->moveRandom(gameBoardLogic);
                    tp->shortest_path =  tp->calcPath(c.logicX,c.logicY);
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;
                        //exit(0);
                    }
                }
                clock.restart();
            }      

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
            {
                sf::Time elapsed1 = clock.getElapsedTime();
                //std::cout << elapsed1.asSeconds() << std::endl;
                while(elapsed1.asSeconds() < 0.29){
                    elapsed1 = clock.getElapsedTime();
                }
                if (checkMove(c.logicX-1,c.logicY,gameBoardLogic)) {
                    c.moveUp();
                    cout << endl;                
                }
            
                printLogicMap(c.logicX,c.logicY,gameBoardLogic);
                for(int i = 0; i < StormV.size(); i++)
                {
                    Stormtrooper *tp = StormV[i]; 
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;

                        //exit(0);
                    }                
                    tp->moveRandom(gameBoardLogic);
                    tp->shortest_path =  tp->calcPath(c.logicX,c.logicY,gameBoardLogic);
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;
                        
                        //exit(0);
                    }                
                }
                for(int i = 0; i < KyloV.size(); i++)
                {
                    KyloRen *tp = KyloV[i]; 
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;
                        
                        //exit(0);
                    }
                    tp->moveRandom(gameBoardLogic);
                    tp->shortest_path =  tp->calcPath(c.logicX,c.logicY,gameBoardLogic);
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;
                        
                        //exit(0);
                    }
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;
                        
                        //exit(0);
                    }
                    tp->moveRandom(gameBoardLogic);
                    tp->shortest_path =  tp->calcPath(c.logicX,c.logicY,gameBoardLogic);
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;
                        
                        //exit(0);
                    }                
                }

                for(int i = 0; i < DarthV.size(); i++)
                {
                    DarthVader *tp = DarthV[i]; 
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;
                        
                        //exit(0);
                    }
                    tp->moveRandom(gameBoardLogic);
                    tp->shortest_path =  tp->calcPath(c.logicX,c.logicY);
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;
                        
                        //exit(0);
                    }
                }

                clock.restart();

            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
            {
                sf::Time elapsed1 = clock.getElapsedTime();
                //std::cout << elapsed1.asSeconds() << std::endl;
                while(elapsed1.asSeconds() < 0.29){
                    elapsed1 = clock.getElapsedTime();
                }
                if(checkMove(c.logicX+1,c.logicY,gameBoardLogic)) {
                    c.moveDown();
                    cout << endl;                
                }        
                printLogicMap(c.logicX,c.logicY,gameBoardLogic);
                for(int i = 0; i < StormV.size(); i++)
                {
                    Stormtrooper *tp = StormV[i]; 
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;

                        //exit(0);
                    }                
                    tp->moveRandom(gameBoardLogic);
                    tp->shortest_path =  tp->calcPath(c.logicX,c.logicY,gameBoardLogic);
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;
                        
                        //exit(0);
                    }                
                }

                for(int i = 0; i < KyloV.size(); i++)
                {
                    KyloRen *tp = KyloV[i]; 
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;
                        
                        //exit(0);
                    }
                    tp->moveRandom(gameBoardLogic);
                    tp->shortest_path =  tp->calcPath(c.logicX,c.logicY,gameBoardLogic);
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;
                        
                        //exit(0);
                    }
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;
                        
                        //exit(0);
                    }
                    tp->moveRandom(gameBoardLogic);
                    tp->shortest_path =  tp->calcPath(c.logicX,c.logicY,gameBoardLogic);
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;
                        
                        //exit(0);
                    }                
                }

                for(int i = 0; i < DarthV.size(); i++)
                {
                    DarthVader *tp = DarthV[i]; 
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;
                        
                        //exit(0);
                    }
                    tp->moveRandom(gameBoardLogic);
                    tp->shortest_path =  tp->calcPath(c.logicX,c.logicY);
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;
                        
                        //exit(0);
                    }
                }

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
            window.draw(c.spirit);
            //  canları çiz
            for(int i = 0; i < c.healt; i++)
            {
                sf::RectangleShape tmp(sf::Vector2f(25.0f,25.0f));
                tmp.setPosition(50 * i ,600);
                tmp.setFillColor(sf::Color::Red);
                window.draw(tmp);
            }
            

            for(int i = 0; i < StormV.size(); i++)
            {
                Stormtrooper *tp = StormV[i]; 

                vector <sf::RectangleShape> path_graph;
                for(int k = 0; k < tp->shortest_path.size(); k++)
                {
                    node_t tmp_r = tp->shortest_path[k];
                    sf::RectangleShape tmp(sf::Vector2f(25.0f,25.0f));
                    tmp.setPosition(50 * (tmp_r.y) ,50 * tmp_r.x);
                    tmp.setFillColor(sf::Color::Red);
                    path_graph.push_back(tmp);
                }

                for(int ii = 0; ii < path_graph.size(); ii++)
                {
                    window.draw(path_graph[ii]);
                }
                

                window.draw(tp->spirit);
            }

            for(int i = 0; i < KyloV.size(); i++)
            {
                KyloRen *tp = KyloV[i]; 
                vector <sf::RectangleShape> path_graph;
                for(int k = 0; k < tp->shortest_path.size(); k++)
                {
                    node_t tmp_r = tp->shortest_path[k];
                    sf::RectangleShape tmp(sf::Vector2f(25.0f,25.0f));
                    tmp.setPosition(50 * (tmp_r.y) + 25 ,50 * tmp_r.x);
                    tmp.setFillColor(sf::Color::Yellow);
                    path_graph.push_back(tmp);
                }

                for(int ii = 0; ii < path_graph.size(); ii++)
                {
                    window.draw(path_graph[ii]);
                }

                window.draw(tp->spirit);
            }

            for(int i = 0; i < DarthV.size(); i++)
            {
                DarthVader *tp = DarthV[i]; 
                vector <sf::RectangleShape> path_graph;
                for(int k = 0; k < tp->shortest_path.size(); k++)
                {
                    node_t tmp_r = tp->shortest_path[k];
                    sf::RectangleShape tmp(sf::Vector2f(25.0f,25.0f));
                    tmp.setPosition(50 * (tmp_r.y) ,50 * tmp_r.x + 25);
                    tmp.setFillColor(sf::Color::Black);
                    path_graph.push_back(tmp);
                }

                for(int ii = 0; ii < path_graph.size(); ii++)
                {
                    window.draw(path_graph[ii]);
                }            
                window.draw(tp->spirit);
            }        
            
            
            window.display();
            ////////////////////////////////////////////////////////////////////////
            if (ENDROUND) {
                window.clear();

                window.draw(c.spirit);
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
                for(int i = 0; i < StormV.size(); i++)
                {
                    Stormtrooper *tp = StormV[i]; 
                    window.draw(tp->spirit);
                }

                for(int i = 0; i < KyloV.size(); i++)
                {
                    KyloRen *tp = KyloV[i]; 
                    window.draw(tp->spirit);
                }

                for(int i = 0; i < DarthV.size(); i++)
                {
                    DarthVader *tp = DarthV[i]; 
                    window.draw(tp->spirit);
                }              

                window.display();

                clock.restart();
                sf::Time elapsed1 = clock.getElapsedTime();
                //std::cout << elapsed1.asSeconds() << std::endl;
                while(elapsed1.asSeconds() < 2){
                    elapsed1 = clock.getElapsedTime();
                }
                //levele reset at
                resetRound(&c,DarthV,KyloV,StormV);
                ENDROUND = false;
                c.healt--;
                // burayı daha sofistike yap 
                if(c.healt == 0){
                    cout << "GAMEOVER" << endl;
                    exit(0);             
                } 
            }
        }
    }
    if(chc == 2){
        LukeSkywalker c = LukeSkywalker("MasterYoda",6,5);
        c.spirit.setTexture(&player_texture);    
        for(int i = 0; i < KyloV.size(); i++)
        {
            KyloRen *tp = KyloV[i]; 
            tp->spirit.setTexture(&texture_ref);
        }
        
        for(int i = 0; i < StormV.size(); i++)
        {
            Stormtrooper *tp = StormV[i]; 
            tp->spirit.setTexture(&texture_ref);
        }

        for(int i = 0; i < DarthV.size(); i++)
        {
            DarthVader *tp = DarthV[i]; 
            tp->spirit.setTexture(&texture_ref);
        }


        //texturede sıkıntı oluyor
        //classa yazacagım move komutu ikisinide beraber götürsun grafik ve logic 

        cout << "debug" << endl;
        bool ENDROUND = false;

        while (window.isOpen())
        {   
            if(c.logicX == kx && c.logicY == ky ){
                cout << "KAZANDIN BENDEN BU KADAR !!" << endl;
                exit(0);
            }
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
                //std::cout << elapsed1.asSeconds() << std::endl;
                while(elapsed1.asSeconds() < 0.29){
                    elapsed1 = clock.getElapsedTime();
                }
                if (checkMove(c.logicX,c.logicY-1,gameBoardLogic)) {
                    c.moveLeft();
                    cout << endl;
                }
                printLogicMap(c.logicX,c.logicY,gameBoardLogic);

                for(int i = 0; i < StormV.size(); i++)
                {
                    Stormtrooper *tp = StormV[i]; 
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;
                        //exit(0);
                    }
                    tp->moveRandom(gameBoardLogic);
                    tp->shortest_path =  tp->calcPath(c.logicX,c.logicY,gameBoardLogic);
                    //burada hesapla 
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;
                        //exit(0);
                    }
                }
                
                for(int i = 0; i < KyloV.size(); i++)
                {
                    KyloRen *tp = KyloV[i]; 
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;
                        //exit(0);
                    }
                    tp->moveRandom(gameBoardLogic);
                    tp->shortest_path =  tp->calcPath(c.logicX,c.logicY,gameBoardLogic);
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;
                        //exit(0);
                    }
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;
                        //exit(0);
                    }
                    tp->moveRandom(gameBoardLogic);
                    tp->shortest_path =  tp->calcPath(c.logicX,c.logicY,gameBoardLogic);
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;
                        //exit(0);
                    }
                    
                }
                
                for(int i = 0; i < DarthV.size(); i++)
                {
                    DarthVader *tp = DarthV[i]; 
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;
                        //exit(0);
                    }
                    tp->moveRandom(gameBoardLogic);
                    tp->shortest_path =  tp->calcPath(c.logicX,c.logicY);
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;
                        //exit(0);
                    }
                }
                clock.restart();
                
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
            {
                sf::Time elapsed1 = clock.getElapsedTime();
                //std::cout << elapsed1.asSeconds() << std::endl;
                while(elapsed1.asSeconds() < 0.29){
                    elapsed1 = clock.getElapsedTime();
                }         
                if (checkMove(c.logicX,c.logicY+1,gameBoardLogic)) {
                    c.moveRight();
                    cout << endl;
                }

                printLogicMap(c.logicX,c.logicY,gameBoardLogic);
                for(int i = 0; i < StormV.size(); i++)
                {
                    
                    Stormtrooper *tp = StormV[i];
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;
                        //exit(0);
                    }                 
                    tp->moveRandom(gameBoardLogic);
                    tp->shortest_path =  tp->calcPath(c.logicX,c.logicY,gameBoardLogic);
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;
                        //exit(0);
                    }
                }

                for(int i = 0; i < KyloV.size(); i++)
                {
                    KyloRen *tp = KyloV[i]; 
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;
                        //exit(0);
                    }
                    tp->moveRandom(gameBoardLogic);
                    tp->shortest_path =  tp->calcPath(c.logicX,c.logicY,gameBoardLogic);
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;
                        //exit(0);
                    }
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;
                        //exit(0);
                    }
                    tp->moveRandom(gameBoardLogic);
                    tp->shortest_path =  tp->calcPath(c.logicX,c.logicY,gameBoardLogic);
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;
                        //exit(0);
                    }                
                }

                for(int i = 0; i < DarthV.size(); i++)
                {
                    DarthVader *tp = DarthV[i]; 
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;
                        //exit(0);
                    }
                    tp->moveRandom(gameBoardLogic);
                    tp->shortest_path =  tp->calcPath(c.logicX,c.logicY);
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;
                        //exit(0);
                    }
                }
                clock.restart();
            }      

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
            {
                sf::Time elapsed1 = clock.getElapsedTime();
                //std::cout << elapsed1.asSeconds() << std::endl;
                while(elapsed1.asSeconds() < 0.29){
                    elapsed1 = clock.getElapsedTime();
                }
                if (checkMove(c.logicX-1,c.logicY,gameBoardLogic)) {
                    c.moveUp();
                    cout << endl;                
                }
            
                printLogicMap(c.logicX,c.logicY,gameBoardLogic);
                for(int i = 0; i < StormV.size(); i++)
                {
                    Stormtrooper *tp = StormV[i]; 
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;

                        //exit(0);
                    }                
                    tp->moveRandom(gameBoardLogic);
                    tp->shortest_path =  tp->calcPath(c.logicX,c.logicY,gameBoardLogic);
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;
                        
                        //exit(0);
                    }                
                }
                for(int i = 0; i < KyloV.size(); i++)
                {
                    KyloRen *tp = KyloV[i]; 
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;
                        
                        //exit(0);
                    }
                    tp->moveRandom(gameBoardLogic);
                    tp->shortest_path =  tp->calcPath(c.logicX,c.logicY,gameBoardLogic);
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;
                        
                        //exit(0);
                    }
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;
                        
                        //exit(0);
                    }
                    tp->moveRandom(gameBoardLogic);
                    tp->shortest_path =  tp->calcPath(c.logicX,c.logicY,gameBoardLogic);
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;
                        
                        //exit(0);
                    }                
                }

                for(int i = 0; i < DarthV.size(); i++)
                {
                    DarthVader *tp = DarthV[i]; 
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;
                        
                        //exit(0);
                    }
                    tp->moveRandom(gameBoardLogic);
                    tp->shortest_path =  tp->calcPath(c.logicX,c.logicY);
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;
                        
                        //exit(0);
                    }
                }

                clock.restart();

            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
            {
                sf::Time elapsed1 = clock.getElapsedTime();
                //std::cout << elapsed1.asSeconds() << std::endl;
                while(elapsed1.asSeconds() < 0.29){
                    elapsed1 = clock.getElapsedTime();
                }
                if(checkMove(c.logicX+1,c.logicY,gameBoardLogic)) {
                    c.moveDown();
                    cout << endl;                
                }        
                printLogicMap(c.logicX,c.logicY,gameBoardLogic);
                for(int i = 0; i < StormV.size(); i++)
                {
                    Stormtrooper *tp = StormV[i]; 
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;

                        //exit(0);
                    }                
                    tp->moveRandom(gameBoardLogic);
                    tp->shortest_path =  tp->calcPath(c.logicX,c.logicY,gameBoardLogic);
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;
                        
                        //exit(0);
                    }                
                }

                for(int i = 0; i < KyloV.size(); i++)
                {
                    KyloRen *tp = KyloV[i]; 
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;
                        
                        //exit(0);
                    }
                    tp->moveRandom(gameBoardLogic);
                    tp->shortest_path =  tp->calcPath(c.logicX,c.logicY,gameBoardLogic);
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;
                        
                        //exit(0);
                    }
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;
                        
                        //exit(0);
                    }
                    tp->moveRandom(gameBoardLogic);
                    tp->shortest_path =  tp->calcPath(c.logicX,c.logicY,gameBoardLogic);
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;
                        
                        //exit(0);
                    }                
                }

                for(int i = 0; i < DarthV.size(); i++)
                {
                    DarthVader *tp = DarthV[i]; 
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;
                        
                        //exit(0);
                    }
                    tp->moveRandom(gameBoardLogic);
                    tp->shortest_path =  tp->calcPath(c.logicX,c.logicY);
                    if(tp->logicX == c.logicX && tp->logicY == c.logicY){
                        cout << "yandın " << endl;
                        ENDROUND = true;
                        break;
                        
                        //exit(0);
                    }
                }

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
            window.draw(c.spirit);
            
            for(int i = 0; i < c.healt; i++)
            {
                sf::RectangleShape tmp(sf::Vector2f(25.0f,25.0f));
                tmp.setPosition(50 * i ,600);
                tmp.setFillColor(sf::Color::Red);
                window.draw(tmp);
            }

            for(int i = 0; i < StormV.size(); i++)
            {
                Stormtrooper *tp = StormV[i]; 

                vector <sf::RectangleShape> path_graph;
                for(int k = 0; k < tp->shortest_path.size(); k++)
                {
                    node_t tmp_r = tp->shortest_path[k];
                    sf::RectangleShape tmp(sf::Vector2f(25.0f,25.0f));
                    tmp.setPosition(50 * (tmp_r.y) ,50 * tmp_r.x);
                    tmp.setFillColor(sf::Color::Red);
                    path_graph.push_back(tmp);
                }

                for(int ii = 0; ii < path_graph.size(); ii++)
                {
                    window.draw(path_graph[ii]);
                }
                

                window.draw(tp->spirit);
            }

            for(int i = 0; i < KyloV.size(); i++)
            {
                KyloRen *tp = KyloV[i]; 
                vector <sf::RectangleShape> path_graph;
                for(int k = 0; k < tp->shortest_path.size(); k++)
                {
                    node_t tmp_r = tp->shortest_path[k];
                    sf::RectangleShape tmp(sf::Vector2f(25.0f,25.0f));
                    tmp.setPosition(50 * (tmp_r.y) + 25 ,50 * tmp_r.x);
                    tmp.setFillColor(sf::Color::Yellow);
                    path_graph.push_back(tmp);
                }

                for(int ii = 0; ii < path_graph.size(); ii++)
                {
                    window.draw(path_graph[ii]);
                }

                window.draw(tp->spirit);
            }

            for(int i = 0; i < DarthV.size(); i++)
            {
                DarthVader *tp = DarthV[i]; 
                vector <sf::RectangleShape> path_graph;
                for(int k = 0; k < tp->shortest_path.size(); k++)
                {
                    node_t tmp_r = tp->shortest_path[k];
                    sf::RectangleShape tmp(sf::Vector2f(25.0f,25.0f));
                    tmp.setPosition(50 * (tmp_r.y) ,50 * tmp_r.x + 25);
                    tmp.setFillColor(sf::Color::Black);
                    path_graph.push_back(tmp);
                }

                for(int ii = 0; ii < path_graph.size(); ii++)
                {
                    window.draw(path_graph[ii]);
                }            
                window.draw(tp->spirit);
            }        
            
            
            window.display();
            ////////////////////////////////////////////////////////////////////////
            if (ENDROUND) {
                window.clear();

                window.draw(c.spirit);
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
                for(int i = 0; i < StormV.size(); i++)
                {
                    Stormtrooper *tp = StormV[i]; 
                    window.draw(tp->spirit);
                }

                for(int i = 0; i < KyloV.size(); i++)
                {
                    KyloRen *tp = KyloV[i]; 
                    window.draw(tp->spirit);
                }

                for(int i = 0; i < DarthV.size(); i++)
                {
                    DarthVader *tp = DarthV[i]; 
                    window.draw(tp->spirit);
                }              

                window.display();

                clock.restart();
                sf::Time elapsed1 = clock.getElapsedTime();
                //std::cout << elapsed1.asSeconds() << std::endl;
                while(elapsed1.asSeconds() < 2){
                    elapsed1 = clock.getElapsedTime();
                }
                //levele reset at
                resetRound(&c,DarthV,KyloV,StormV);
                ENDROUND = false;
                c.healt--;
                // burayı daha sofistike yap 
                if(c.healt == 0){
                    cout << "GAMEOVER" << endl;
                    exit(0);             
                } 
            }
        }    
    
    
    
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
        //cout << "true" << endl;
    } else
    {
        //cout << "oraya oynamaz" << endl;
    }
    return move;
}

void printLogicMap(int x, int y,int** gameBoardLogic){
    for(int i = 0; i < 11; i++) //rows
    {
        for(int j = 0; j < 14; j++) //cos
        {
            if(i == x && j == y){
                cout << "W" << "   ";
            } else 
            cout << gameBoardLogic[i][j] << "   ";
        }
        cout << endl;
    }
    std::cout << "////////////////////////////////////////////////////////" << std::endl;

}

vector<Stormtrooper*> initStormtrooper(){
    vector<Stormtrooper*> sv;
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
                    ix = 5;iy=1;
                }
                if (td == 'C') {
                    ix = 0;iy=13;
                }
                if (td == 'D') {
                    ix = 5;iy=14;
                }
                if (td == 'E') {
                    ix = 10;iy=5;
                }
                if(!tn.compare("Stormtrooper") ){
                    Stormtrooper *p =new Stormtrooper("Stormtrooper",ix,iy);
                    sv.push_back(p);
                }
            }
        }
    }

    else cout << "dosya acılamadı " << endl;
    return sv;
}

vector<KyloRen*> initKyloRen(){
    vector<KyloRen*> sv;
    //kapılar hardcoded
    //Karakter:KyloRen,Kapi:A
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
                    ix = 5;iy=1;
                }
                if (td == 'C') {
                    ix = 0;iy=13;
                }
                if (td == 'D') {
                    ix = 5;iy=14;
                }
                if (td == 'E') {
                    ix = 10;iy=5;
                }
                if(!tn.compare("KyloRen") ){
                    cout << "kyloren debug" << endl;
                    KyloRen *p =new KyloRen("KyloRen",ix,iy);
                    sv.push_back(p);
                }
            }
        }
    }

    else cout << "dosya acılamadı " << endl;
    return sv;
}

vector<DarthVader*> initDarthVader(){
    vector<DarthVader*> sv;
    //kapılar hardcoded
    //Karakter:DarthVader,Kapi:A
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
                    ix = 5;iy=1;
                }
                if (td == 'C') {
                    ix = 0;iy=13;
                }
                if (td == 'D') {
                    ix = 5;iy=14;
                }
                if (td == 'E') {
                    ix = 10;iy=5;
                }
                if(!tn.compare("DarthVader") ){
                    DarthVader *p =new DarthVader("DarthVader",ix,iy);
                    sv.push_back(p);
                }
            }
        }
    }

    else cout << "dosya acılamadı " << endl;
    return sv;
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