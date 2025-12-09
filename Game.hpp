#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Paletka.hpp"
#include "Pilka.hpp"
#include "Stone.hpp"

class Game {
private:
    Paletka m_paletka;
    Pilka m_pilka;
    std::vector<Stone> m_bloki;
    float m_windowWidth;
    float m_windowHeight;
    bool m_gameOver = false;

    int m_score = 0; // aktualny wynik

public:
    Game(float windowWidth = 800.f, float windowHeight = 600.f);
    void update(sf::Time dt);
    void render(sf::RenderTarget& target) const;
    bool isGameOver() const { return m_gameOver; }
    void reset(); // reset stanu gry
    int getScore() const { return m_score; }
    void addScore(int pts) { m_score += pts; }
};
