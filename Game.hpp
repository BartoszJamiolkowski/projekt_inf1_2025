#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Paletka.hpp"
#include "Pilka.hpp"
#include "Stone.hpp"

class Game {
private:
    // Okno i zegar
    sf::RenderWindow m_window;
    sf::Clock m_deltaClock;

    // Obiekty gry
    Paletka m_paletka;
    Pilka m_pilka;
    std::vector<Stone> m_bloki;

    // Stałe rozmiary okna
    const float WIDTH = 640.f;
    const float HEIGHT = 480.f;

    // Metody prywatne
    void processEvents();
    void update(sf::Time dt);
    void render();

public:
    Game();
    void run();
};
