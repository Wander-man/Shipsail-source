#include "g_stats.h"

Stats::Stats(std::string user)
    : m_user(user), m_count{}
{
    loadstats();
}

bool Stats::loadstats()
{
    std::ifstream file;
    std::string name = "usrstats/stats-" + m_user + ".bin";
    file.open(name , std::ios::binary);

    if (!file.is_open())
    {
        std::ofstream file2;
        file2.open(name , std::ios::binary);
        file2.close();
        file.open(name , std::ios::binary);
    }


    file.seekg(0, std::ios::end);
    if (file.tellg() == 0)
    {
        m_count[skilled] = 0;
        m_count[armkilled] = 0;
        m_count[tbuilt] = 0;
        m_count[tplayed] = 0;
        m_count[vict] = 0;
        m_count[loss] = 0;
        savestats();
    }    
    else
    {
        file.seekg(0, std::ios::beg);
        while(!file.eof())
        {
            std::string buf;
            
            getline(file, buf, ',');
            if(file.eof()) break;            
            int stat = std::stoi(buf);

            getline(file, buf, ';');
            m_count[stat] = std::stoi(buf);

        }
    }    
    file.close();
    return true;
}

bool Stats::savestats()
{
    std::ofstream file;
    file.open("usrstats/stats-" + m_user + ".bin", std::ios::binary | std::ios::trunc);

    if (!file.is_open())
    {
        std::cout << "\nUnable to open file" << std::endl;
        return false;
    }

    for (auto &i : m_count)
    {
        std::string buf = std::to_string(i.first) + ',' + std::to_string(i.second) + ';';
        file.write(buf.c_str(), buf.size());
    }
    file.close();
    return true;
}

int Stats::getcount(int stat)
{
    return m_count.at(stat);
}

void Stats::upcount(int stat, int amount)
{
    m_count.at(stat) += amount;
}

void Stats::changeuser(std::string newuser)
{
    savestats();
    m_user = newuser;
    loadstats();
}