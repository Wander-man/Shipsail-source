#pragma once

#include <unordered_map>
#include <string>
#include <iostream>
#include <fstream>

enum stats
{
    skilled,
    armkilled,
    tbuilt,
    tplayed,
    vict,
    loss    
};

using intmap = std::unordered_map<int, int>;

class Stats
{
    private:

        std::string m_user;
        intmap m_count;

        //load stats from user file
        //if not present, created    
        bool loadstats();

    public:

        //constructor
        Stats(std::string user);

        //default destructor
        ~Stats() = default;        

        //save stats to user file
        //if not present, created    
        bool savestats();

        //returns the count of a stat
        int getcount(int stat);

        //adds 1 to the stat count
        void upcount(int stat, int amount = 1);

        //change current user
        void changeuser(std::string newuser);
};