#include "Game.hpp"
#include <iostream>

Game::Game()
    : 
      m_paletka(320.f, 440.f, 100.f, 20.f, 8.f),
      m_pilka(320.f, 250.f, 4.f, 3.f, 8.f)
{
    loadLevel();
}

void Game::loadLevel()
{
    m_bloki.clear();

    const int ILOSC_KOLUMN = 6;
    const int ILOSC_WIERSZY = 7;
    const float ROZMIAR_BLOKU_Y = 25.f;
    const float PRZERWA = 2.f;
    const float OFFSET_Y = 50.f;

    const float ROZMIAR_BLOKU_X =
        (WIDTH - (ILOSC_KOLUMN - 1) * PRZERWA) / ILOSC_KOLUMN;

    for (int y = 0; y < ILOSC_WIERSZY; ++y)
    {
        for (int x = 0; x < ILOSC_KOLUMN; ++x)
        {
            float posX = x * (ROZMIAR_BLOKU_X + PRZERWA);
            float posY = OFFSET_Y + y * (ROZMIAR_BLOKU_Y + PRZERWA);
            int L = (y < 1) ? 3 : (y < 3) ? 2 : 1;

            m_bloki.emplace_back(
                sf::Vector2f(posX, posY),
                sf::Vector2f(ROZMIAR_BLOKU_X, ROZMIAR_BLOKU_Y),
                L
            );
        }
    }
}

void Game::update(sf::Time)
{
    // Ruch piłki
    m_pilka.move();
    m_pilka.collideWalls(WIDTH, HEIGHT);

    // Kolizja paletki
    m_pilka.collidePaddle(m_paletka);

    // Kolizje z blokami
    for (auto& blok : m_bloki)
    {
        if (!blok.isDestroyed())
        {
            sf::FloatRect blokRect = blok.getGlobalBounds();
            sf::FloatRect pilkaRect(
                m_pilka.getX() - m_pilka.getRadius(),
                m_pilka.getY() - m_pilka.getRadius(),
                m_pilka.getRadius() * 2.f,
                m_pilka.getRadius() * 2.f
            );

            if (pilkaRect.intersects(blokRect))
            {
                blok.trafienie();
                m_pilka.bounceY();
            }
        }
    }

    // Jeżeli piłka spadnie pod ekran
    if (m_pilka.getY() - m_pilka.getRadius() > HEIGHT)
    {
        std::cout << "MISS! KONIEC GRY\n";
        // W tym miejscu możesz zaimplementować reset lub powrót do menu
    }
}

void Game::render(sf::RenderTarget& target)
{
    // Rysowanie obiektów
    m_paletka.draw(target);
    m_pilka.draw(target);

    for (auto& blok : m_bloki)
        blok.draw(target);
}

