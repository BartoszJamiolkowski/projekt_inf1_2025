#include "Game.hpp"
#include <iostream>

Game::Game(float windowWidth, float windowHeight)
    : m_paletka(windowWidth / 2.f, windowHeight - 60.f, 100.f, 20.f, 8.f),
    m_pilka(windowWidth / 2.f, windowHeight / 2.f, 4.f, 3.f, 8.f),
    m_windowWidth(windowWidth), m_windowHeight(windowHeight) {

    //tworzenie blokow
    const int ILOSC_KOLUMN = 6;
    const int ILOSC_WIERSZY = 7;
    const float ROZMIAR_BLOKU_Y = 25.f;
    const float PRZERWA = 2.f;
    const float OFFSET_Y = 50.f;
    const float ROZMIAR_BLOKU_X = (m_windowWidth - (ILOSC_KOLUMN - 1) * PRZERWA) / ILOSC_KOLUMN;

    for (int y = 0; y < ILOSC_WIERSZY; ++y) {
        for (int x = 0; x < ILOSC_KOLUMN; ++x) {
            float posX = x * (ROZMIAR_BLOKU_X + PRZERWA);
            float posY = OFFSET_Y + y * (ROZMIAR_BLOKU_Y + PRZERWA);
            int L = (y < 1) ? 3 : (y < 3) ? 2 : 1;// punkty zycia blokow
            m_bloki.emplace_back(sf::Vector2f(posX, posY), sf::Vector2f(ROZMIAR_BLOKU_X, ROZMIAR_BLOKU_Y), L);
        }
    }
}

void Game::update(sf::Time dt) {
    //sterowanie paletka
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        m_paletka.moveLeft();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        m_paletka.moveRight();
    m_paletka.clampToBounds(m_windowWidth);

    //ruch pilki i kolizje z paletka, scianami i blokami 
    m_pilka.move();
    m_pilka.collideWalls(m_windowWidth, m_windowHeight);
    m_pilka.collidePaddle(m_paletka);

    //kolizja z blokami
    for (auto& blok : m_bloki) {
        if (!blok.isDestroyed()) {
            sf::FloatRect blokRect = blok.getGlobalBounds();
            sf::FloatRect pilkaRect(m_pilka.getX() - m_pilka.getRadius(),
                m_pilka.getY() - m_pilka.getRadius(),
                m_pilka.getRadius() * 2.f,
                m_pilka.getRadius() * 2.f);
            if (pilkaRect.intersects(blokRect)) {
                int hpBefore = blok.getHP();
                blok.trafienie();
                m_pilka.bounceY();

                // punkty za kolor bloku
                switch (hpBefore) {
                case 3: addScore(15); break;   // niebieksi 
                case 2: addScore(10); break;  // żółty
                case 1: addScore(5); break;  // czerwony
                }
            }
        }
    }
    //sprawdzanie konca gry
    if (m_pilka.getY() - m_pilka.getRadius() > m_windowHeight) {
        std::cout << "MISS! KONIEC GRY\n";
        m_gameOver = true;
    }
}

void Game::render(sf::RenderTarget& target) const {
    m_paletka.draw(target);
    m_pilka.draw(target);
    for (const auto& blok : m_bloki) blok.draw(target);

    // Wyświetlanie punktów
    static sf::Font font;
    static bool fontLoaded = false;
    if (!fontLoaded) {
        font.loadFromFile("E:/Windows/Fonts/arial.ttf");
        fontLoaded = true;
    }
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setString("Punkty: " + std::to_string(m_score));
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(target.getSize().x - 150.f, 10.f);
    target.draw(scoreText);
}

void Game::reset() {
    //restart paletki i pilki 
    m_paletka = Paletka(m_windowWidth / 2.f, m_windowHeight - 60.f, 100.f, 20.f, 8.f);
    m_pilka = Pilka(m_windowWidth / 2.f, m_windowHeight / 2.f, 4.f, 3.f, 8.f);
    m_bloki.clear();

    //ponowne tworzenie blokow po przegranej
    const int ILOSC_KOLUMN = 6;
    const int ILOSC_WIERSZY = 7;
    const float ROZMIAR_BLOKU_Y = 25.f;
    const float PRZERWA = 2.f;
    const float OFFSET_Y = 50.f;
    const float ROZMIAR_BLOKU_X = (m_windowWidth - (ILOSC_KOLUMN - 1) * PRZERWA) / ILOSC_KOLUMN;

    for (int y = 0; y < ILOSC_WIERSZY; ++y) {
        for (int x = 0; x < ILOSC_KOLUMN; ++x) {
            float posX = x * (ROZMIAR_BLOKU_X + PRZERWA);
            float posY = OFFSET_Y + y * (ROZMIAR_BLOKU_Y + PRZERWA);
            int L = (y < 1) ? 3 : (y < 3) ? 2 : 1;
            m_bloki.emplace_back(sf::Vector2f(posX, posY), sf::Vector2f(ROZMIAR_BLOKU_X, ROZMIAR_BLOKU_Y), L);
        }
    }
    m_score = 0;
    m_gameOver = false;
}
