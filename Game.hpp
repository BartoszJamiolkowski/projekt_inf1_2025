#pragma once
#include <SFML/Graphics.hpp>
#include "Paletka.hpp"
#include "Pilka.hpp"
#include "Stone1.h"
#include <vector>

class Game {
private:
    sf::RenderWindow m_window;
    sf::Clock m_deltaClock;

    Paletka m_paletka;
    Pilka m_pilka;
    std::vector<Stone> m_bloki;

    // wymiary okna
    const float WIDTH = 640.f;
    const float HEIGHT = 480.f;

private:
    void processEvents();
    void update(sf::Time dt);
    void render();
    void loadLevel(); // generowanie bloków, przeniesione z main

public:
    Game();
    void run();
};
