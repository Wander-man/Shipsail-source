#pragma once

#include <unordered_map>
#include <iostream>
#include <fstream>
#include "w_awindow.h"

using udatamap = std::unordered_map <std::string, std::string>;
using uit = udatamap::iterator;

class Logwindow : public Awindow
{
    private:

        std::string m_name;
        std::string m_password;

        udatamap m_udata;

        //write a usr record to the map
        void writerec(std::string& name, std::string& password);

        //find a usr record, rets m_udata.end() on failure
        uit findrec(std::string& name);

        //saves the map, (cstrings) to a binary file
        int savedata();

        //load user data from a binary file
        int loaddata();

    public:

        //base window class constructor
        using Awindow::Awindow;

        //default destructor
        ~Logwindow() = default;

        //run window
        std::string launch() override final;
};