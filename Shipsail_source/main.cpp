#include "game.h"

const fns files({MAPTILES_PNG, SSHIP_PNG, ARMSHIP_PNG, PROJECTILE_PNG, TOWERS_PNG});
Icashe cashe;

char sProgramRoot[255];

void getRootPath(char *argv)
{
    unsigned int  Size = 255;
    strncpy(sProgramRoot,argv,255);
    Size = strlen(sProgramRoot);
    while (Size > 0) 
    {
        if ( sProgramRoot[Size]=='\\') break;
        Size--;
    }
    sProgramRoot[Size+1] = 0;  
    printf(sProgramRoot);
}

int main(int argc, char *argv[])
{
    getRootPath(argv[0]);
    cashe.init(files);
    
    sf::Font font{};
    std::string root = sProgramRoot;
    if (!font.loadFromFile((root + "font/OpenSans.ttf").c_str()))
    {
        return 1;
    }
    //setting textures from cashe
    Sship::settexture(SSHIP_PNG);
    Armship::settexture(ARMSHIP_PNG);
    Atower::settexture(TOWERS_PNG);
    Projectile::settexture(PROJECTILE_PNG);

    Gamemap map1{};
    map1.load_tiles((root + "maps/map1s.bin").c_str());
    ivect tow1 = map1.gettow();
    Gamemap map2{};
    map2.load_tiles((root + "maps/map2s.bin").c_str());
    ivect tow2 = map2.gettow();
    Gamemap map3{};
    map3.load_tiles((root + "maps/map3s.bin").c_str());
    ivect tow3 = map3.gettow();

    Astar path1(map1.getbases(), map1.getdim(), map1.getbmap());
    path1.astarfind();
    crdvect p1 = path1.getpath();
    Astar path2(map2.getbases(), map2.getdim(), map2.getbmap());
    path2.astarfind();
    crdvect p2 = path2.getpath();
    Astar path3(map3.getbases(), map3.getdim(), map3.getbmap());
    path3.astarfind();
    crdvect p3 = path3.getpath();

    Gamemaptext maptext1(map1.getmap(), path1.getpath(), map1.gettow(), map1.getdim());
    Gamemaptext maptext2(map2.getmap(), path2.getpath(), map2.gettow(), map2.getdim());
    Gamemaptext maptext3(map3.getmap(), path3.getpath(), map3.gettow(), map3.getdim());

    if (!maptext1.load(MAPTILES_PNG, sf::Vector2u(TSIZE, TSIZE)) ||
        !maptext2.load(MAPTILES_PNG, sf::Vector2u(TSIZE, TSIZE)) ||
        !maptext3.load(MAPTILES_PNG, sf::Vector2u(TSIZE, TSIZE)))
    {
        return 1;
    } 

    std::string level = "hello there";
    Logwindow auwind(sf::VideoMode(300, 200), "login", font, sf::Vector2i(500, 300));
    Menuwindow mmenu(sf::VideoMode(750, 750), "Shipsail", font, sf::Vector2i(0, 0), auwind.launch());
    
    while(level != "")
    {
        level = mmenu.launch();
        if(level == "") return 1;

        if(level == "level1")
        {
            Game lvl1(sf::VideoMode(750, 750), "Shipsail", font, sf::Vector2i(500, 200), tow1, p1, maptext1, mmenu.getstats(), 30, 20);
            lvl1.launch();
        }
        if(level == "level2")
        {
            Game lvl2(sf::VideoMode(750, 750), "Shipsail", font, sf::Vector2i(500, 200), tow2, p2, maptext2, mmenu.getstats(), 30, 15);
            lvl2.launch();
        }
        if(level == "level3")
        {
            Game lvl3(sf::VideoMode(750, 750), "Shipsail", font, sf::Vector2i(500, 200), tow3, p3, maptext3, mmenu.getstats(), 5000, 1000);
            lvl3.launch();
        }
    }
    

    return 0;
}