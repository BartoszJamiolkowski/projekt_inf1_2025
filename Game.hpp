#pragma once
#include <SFML/Graphics.hpp>
#include "Paletka.hpp"
#include "Pilka.hpp"
#include "Stone1.h"
#include <vector>

class Game {
private:
    Paletka m_paletka;
    Pilka m_pilka;
    std::vector<Stone> m_bloki;

    const float WIDTH = 640.f;
    const float HEIGHT = 480.f;

public:
    Game();

    void loadLevel();                     // generowanie bloków
    void update(sf::Time dt);             // logika gry (bez wejścia)
    void render(sf::RenderTarget& target); // rysowanie na podanym oknie
};
