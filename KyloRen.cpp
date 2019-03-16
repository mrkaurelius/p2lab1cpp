#include <SFML/Graphics.hpp>
#include "KyloRen.hpp"
#include "Character.hpp"
#include <iostream>

using namespace std;

KyloRen::KyloRen(const char* name,int x,int y){
    this->name = name;
    this->logicX = x;
    this->logicY = y-1;
    this->initialX = x;
    this->initialY = y-1;
    
    sf::Texture character_texture;
    //character_texture.loadFromFile("/home/mrk1debian/gelistirme/cpptut/media/sheet1.png");
    character_texture.loadFromFile("/home/mrk0debian/gelistirme/p2lab1cpp/media/sheet1.png");
    sf::Vector2u character_textureSize = character_texture.getSize();
    character_textureSize.x /= 8;
    character_textureSize.y /= 8;
   
    sf::RectangleShape tmpSpirit(sf::Vector2f(50.0f,50.0f));
    tmpSpirit.setPosition((y-1) * 50, x * 50);
    tmpSpirit.setTextureRect(sf::IntRect(character_textureSize.x * 4,character_textureSize.y * 4,character_textureSize.x,character_textureSize.y));
    
    this->spirit = tmpSpirit;
    std::cout << "KYLO merhaba zalım dunya eved adım "<< this->name << std::endl;
}

std::vector <node_t> KyloRen::calcPath(int tx,int ty,int **gameBoardLogic){
    int x = this->logicX;
    int y = this->logicY;
    std::cout << "/////////////////////KYLOR CALC//////////////////////////" << std::endl;

    for(int i = 0; i < 11; i++) //rows
    {
        for(int j = 0; j < 14; j++) //cos
        {
            if(i == tx && j == ty){
                std::cout << "XP" << "  ";
            }
            else if(i == x && j == y){
                std::cout << "XS" << "  ";
            } else 
            std::cout << gameBoardLogic[i][j] << "   ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    node_t start;
    start.x = tx;
    start.y = ty;
    start.counter = 0;

    node_t end;
    end.x = x;
    end.y = y;
    end.counter = INF;

    cout << "s_x: " << x << " s_y: " << y << " tx: " << tx << " ty: "<< ty << endl;

    deque <node_t> mainlist; 
    mainlist.push_back(start);
    //cout << mainlist[0].x << "," << mainlist[0].y << "," << mainlist[0].counter << endl;
    //!!! KOORDINATLARI

    for(int i = 0; i < mainlist.size(); i++)
    {
           
        bool endsearch = false;
        int xi = mainlist[i].x;
        int yi = mainlist[i].y;
        int counteri = mainlist[i].counter + 1;

        vector <node_t> tmpnodes;

        if (xi+1 < 11) {
            node_t tmpnode;
            tmpnode.x = xi+1;
            tmpnode.y = yi;
            tmpnode.counter = counteri; 
            if (!endsearch) {
                if (gameBoardLogic[xi+1][yi] == 1) {
                    tmpnodes.push_back(tmpnode);
                }
                if (tmpnode.x == end.x && tmpnode.y == end.y) {
                    cout << "aranan kan bulundu x:" << x << " y: "<< y << endl;

                    endsearch = true;
                }
            }
        }

        if (xi-1 >= 0) {
            node_t tmpnode;
            tmpnode.x = xi-1;
            tmpnode.y = yi;
            tmpnode.counter = counteri; 
            if (!endsearch) {
                if (gameBoardLogic[xi-1][yi] == 1) {
                    tmpnodes.push_back(tmpnode);
                }
                if (tmpnode.x == end.x && tmpnode.y == end.y) {
                    cout << "aranan kan bulundu x:" << x << " y: "<< y << endl;

                    endsearch = true;
                }          
            }

        }
        if (yi+1 < 14) {
            node_t tmpnode;
            tmpnode.y = yi+1;
            tmpnode.x = xi;
            tmpnode.counter = counteri;
            if (!endsearch) {
                if (gameBoardLogic[xi][yi+1] == 1) {
                    tmpnodes.push_back(tmpnode);
                }
                if (tmpnode.x == end.x && tmpnode.y == end.y) {
                    cout << "aranan kan bulundu x:" << x << " y: "<< y << endl;
                    endsearch = true;
                }
            }
        }
        if (yi-1 >= 0) {
            node_t tmpnode;
            tmpnode.y = yi-1;
            tmpnode.x = xi;
            tmpnode.counter = counteri;
            if (!endsearch) {
                if (gameBoardLogic[xi][yi-1] == 1) {
                    tmpnodes.push_back(tmpnode);
                }
                if (tmpnode.x == end.x && tmpnode.y == end.y) {
                    cout << "aranan kan bulundu x:" << x << " y: "<< y << endl;
                    endsearch = true;
                }            
            }
        }
        //duvar kontrolu yapıldı simdi analisteyi kontol et

        for(int i = 0; i < tmpnodes.size(); i++)
        {
            for(int j = 0; j < mainlist.size(); j++)
            {
                if ((tmpnodes[i].x ==  mainlist[j].x && tmpnodes[i].y ==  mainlist[j].y) && mainlist[j].counter <= tmpnodes[i].counter ) {
                    tmpnodes.erase(tmpnodes.begin()+i); //bunu test et
                    //cout << tmpnodes[i].y << "," << tmpnodes[i].x  <<" silindi "<<endl;
                    break;
                }
            }
        }
        
        if(tmpnodes.size() != 0 ){
            for(int i = 0; i < tmpnodes.size(); i++)
            {
                mainlist.push_back(tmpnodes[i]);
            }
        }

        
        if (endsearch) {
            break;
        }
    }
    
    for(int i = 0; i < mainlist.size(); i++)
    {
        //cout << i << ". x:" <<  mainlist[i].x << ", y:" << mainlist[i].y << " counter:" << mainlist[i].counter << endl; 
    }
    //en kısa yolu bulma 

    cout << "///////////////////////////////////////" << endl;

    //backtraci yap
    //start 6 6 counter 0 
    //end 3 2  counter 7
    
    node_t iter_node = mainlist[mainlist.size()-1]; 
    cout << iter_node.x << "," << iter_node.y << endl;
    vector <node_t> shortestPath;
    int ix = iter_node.x;
    int iy = iter_node.y; 

    for(int i = mainlist[mainlist.size()-1].counter-1; i > 0 ; i--)
    {
        
        int iter_level = i;
        vector <node_t> level_nodes;
        //cout << "!"<<iter_level << endl;
        for(int j = 0; j < mainlist.size(); j++)
        {
            if (mainlist[j].counter == iter_level) {
                level_nodes.push_back(mainlist[j]);
            }
        }

        node_t tmp_path;
        for(int i = 0; i < level_nodes.size(); i++)
        {
            if (level_nodes[i].x == (ix + 1) && level_nodes[i].y == iy ) {
                tmp_path = level_nodes[i];
                break;
            }
            if (level_nodes[i].x == (ix - 1) && level_nodes[i].y == iy ) {
                tmp_path = level_nodes[i];            
                break;    
            }            
            if (level_nodes[i].y == (iy + 1) && level_nodes[i].x == ix ) {
                tmp_path = level_nodes[i];
                break;
            }
            if (level_nodes[i].y == (iy - 1) && level_nodes[i].x == ix ) {
                tmp_path = level_nodes[i];
                break;
            }                          
        }
        
        shortestPath.push_back(tmp_path);
        ix = tmp_path.x;
        iy = tmp_path.y;

        //shortestPath.push_back() ? 
        for(int i = 0; i < level_nodes.size(); i++)
        {
            //cout << level_nodes[i].x  << "," << level_nodes[i].y << endl;
        }

    }

    for(int i = 0; i < shortestPath.size(); i++)
    {
        cout << i << ". x:" <<  shortestPath[i].x << ", y:" << shortestPath[i].y << " counter:" << shortestPath[i].counter << endl; 
    }
    

    for(int i = 0; i < mainlist.size(); i++)
    {
        //cout << boardlogic[mainlist[i].y][mainlist[i].x] << endl;
    }

    return shortestPath;
}



void KyloRen::moveRandom(int **gameBoardLogic){
    srand(time(NULL));
    int x = this->logicX;
    int y = this->logicY;
   std::cout << "////////////////////////KYLOREN//////////////////////////" << std::endl;

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

   std::cout << "////////////////////////KYLOREN//////////////////////////" << std::endl;
}
void KyloRen::setName(const char *name){
    this->name = name;
}

const char* KyloRen::getName(){
    return this->name;
}


KyloRen::KyloRen()
{

}

KyloRen::~KyloRen()
{
    std::cout << "KYLO dunya meger sende bir hayalden ibaretmissin... " << this->name << std::endl;
}