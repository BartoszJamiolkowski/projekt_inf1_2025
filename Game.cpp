#include "Game.h"
#include <iostream>

Game::Game()
    : m_window(sf::VideoMode((unsigned)WIDTH, (unsigned)HEIGHT), "Arkanoid test"),
      m_paletka(320.f, 440.f, 100.f, 20.f, 8.f),
      m_pilka(320.f, 250.f, 4.f, 3.f, 8.f)
{
    m_window.setFramerateLimit(60);
    loadLevel();  // tworzenie bloków
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

    for (int y = 0; y < ILOSC_WIERSZY; ++y) {
        for (int x = 0; x < ILOSC_KOLUMN; ++x) {
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

void Game::run()
{
    while (m_window.isOpen()) {
        processEvents();
        update(m_deltaClock.restart());
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            m_window.close();
    }

    // sterowanie
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        m_paletka.moveLeft();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        m_paletka.moveRight();

    m_paletka.clampToBounds(WIDTH);
}

void Game::update(sf::Time)
{
    m_pilka.move();
    m_pilka.collideWalls(WIDTH, HEIGHT);
    m_pilka.collidePaddle(m_paletka);

    // kolizje piłki z blokami
    for (auto& blok : m_bloki) {
        if (!blok.isDestroyed()) {
            sf::FloatRect blokRect = blok.getGlobalBounds();
            sf::FloatRect pilkaRect(
                m_pilka.getX() - m_pilka.getRadius(),
                m_pilka.getY() - m_pilka.getRadius(),
                m_pilka.getRadius() * 2.f,
                m_pilka.getRadius() * 2.f
            );

            if (pilkaRect.intersects(blokRect)) {
                blok.trafienie();
                m_pilka.bounceY();
            }
        }
    }

    if (m_pilka.getY() - m_pilka.getRadius() > HEIGHT) {
        std::cout << "MISS! KONIEC GRY\n";
        m_window.close();
    }
}

void Game::render()
{
    m_window.clear(sf::Color(20, 20, 30));

    m_paletka.draw(m_window);
    m_pilka.draw(m_window);

    for (auto& b : m_bloki)
        b.draw(m_window);

    m_window.display();
}
