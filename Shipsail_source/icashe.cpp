#include "icashe.h"

Icashe::Icashe(fns filenames)
{   
    init(filenames);
}

void Icashe::init(fns filenames)
{
    char sFullFileName[255];
    for(auto i : filenames)
    {
        sf::Image ibuf;
        strncpy(sFullFileName,sProgramRoot,255);
        strcat(sFullFileName,i);
        if(!ibuf.loadFromFile(sFullFileName))
        {
            std::cout << "\nfailed to load image" << std::endl;
        }
        std::string sbuf = i;

        m_cashemap.insert(std::make_pair(sbuf,ibuf));
    }
}

const sf::Image& Icashe::getimg(const char* fname)
{
    std::string buf(fname);
    const sf::Image& ret = m_cashemap.at(buf);
    return ret;
}