#include "w_logwindow.h"

void Logwindow::writerec(std::string &name, std::string &password)
{
    m_udata[m_name] = m_password;
}

uit Logwindow::findrec(std::string &name)
{
    return m_udata.find(name);
}

int Logwindow::savedata()
{
    std::ofstream file;
    file.open("usrdata.bin", std::ios::binary | std::ios::trunc);

    if (!file.is_open())
    {
        std::cout << "\nUnable to open file" << std::endl;
        return 1;
    }

    for (auto &i : m_udata)
    {
        std::string buf = i.first + ';' + i.second + ';';
        file.write(buf.c_str(), buf.size());
    }
    file.close();
}

int Logwindow::loaddata()
{
    std::ifstream file;
    file.open("usrdata.bin", std::ios::binary);

    if (!file.is_open())
    {
        std::ofstream file2;
        file2.open("usrdata.bin", std::ios::binary);
        file2.close();
        file.open("usrdata.bin", std::ios::binary);
    }

    file.seekg(0, std::ios::end);
    if (file.tellg() == 0)
        return 1;
    else
        file.seekg(0, std::ios::beg);

    std::string buf;
    m_udata.clear();

    while (!file.eof())
    {
        getline(file, m_name, ';');
        getline(file, m_password, ';');

        m_udata[m_name] = m_password;
    }
    file.close();
}

std::string Logwindow::launch()
{
    sf::RenderWindow window(m_vmode, m_name, sf::Style::Titlebar);
    window.setPosition(m_pos);  

    loaddata();
    Button login("login", m_font, sf::Vector2f(117.5f, 142.0f), sf::Vector2f(65.0f, 33.0f), 15);
    Button exit("exit", m_font, sf::Vector2f(207.5f, 142.0f), sf::Vector2f(65.0f, 33.0f), 15);
    Button newusr("create", m_font, sf::Vector2f(27.5f, 142.0f), sf::Vector2f(65.0f, 33.0f), 15);

    Tlabel message("", m_font, sf::Vector2f(50.0f, 15.0f), 15);

    Textbar name("username:", m_font, sf::Vector2f(100.0f, 35.0f), 18.0f, 15);
    Textbar password("password:", m_font, sf::Vector2f(100.0f, 85.0f), 18.0f, 15);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return "";
            }
            if (exit.manage(event, window))
            {
                window.close();
                return "";
            }
            if (login.manage(event, window))
            {
                message.setstr("");

                uit i = findrec(m_name);
                if (i != m_udata.end() && m_name.size() != 0)
                {
                    if (m_password == i->second)
                    {
                        message.setstr("Login success");
                        savedata();
                        window.close();
                        return m_name;
                    }
                    else
                    {
                        message.setstr("Wrong password");
                    }
                }
                else
                {
                    message.setstr("Wrong username");
                }
            }
            if (newusr.manage(event, window))
            {
                message.setstr("");

                uit i = findrec(m_name);
                if (i == m_udata.end())
                {
                    m_udata[m_name] = m_password;
                    message.setstr("User created, login");
                    savedata();
                }
                else
                {
                    message.setstr("Username occupied");
                }
            }
            m_name = name.manage(event, window);
            m_password = password.manage(event, window);
        }

        window.display();
        window.clear(sf::Color(120, 100, 100));

        login.draw(window);
        newusr.draw(window);
        exit.draw(window);

        name.draw(window);
        password.draw(window);

        message.draw(window);

    } //!main loop------
}