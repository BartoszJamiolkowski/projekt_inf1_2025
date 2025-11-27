#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Paletka.hpp"
#include "Pilka.hpp"
#include "Stone.hpp"

int main() {
    // Tworzenie okna
    const float WIDTH = 640.f;
    const float HEIGHT = 480.f;
    sf::RenderWindow window({ (unsigned)WIDTH, (unsigned)HEIGHT }, "Arkanoid test");
    window.setFramerateLimit(60);
    sf::Clock deltaClock;
    sf::Event event;

    // Tworzenie obiektów gry
    Paletka pal(320.f, 440.f, 100.f, 20.f, 8.f);  // x, y, szer, wys, predkosc
    Pilka pilka(320.f, 200.f, 4.f, 3.f, 8.f);      // x, y, vx, vy, radius

    // ------------------ Tworzenie bloków ------------------
    std::vector<Stone> bloki;
    const int ILOSC_KOLUMN = 6;
    const int ILOSC_WIERSZY = 7;
    const float ROZMIAR_BLOKU_Y = 25.f;
    const float PRZERWA = 2.f;
    const float OFFSET_Y = 50.f;
    const float ROZMIAR_BLOKU_X = (WIDTH - (ILOSC_KOLUMN - 1) * PRZERWA) / ILOSC_KOLUMN;

    for (int y = 0; y < ILOSC_WIERSZY; ++y) {
        for (int x = 0; x < ILOSC_KOLUMN; ++x) {
            float posX = x * (ROZMIAR_BLOKU_X + PRZERWA);
            float posY = OFFSET_Y + y * (ROZMIAR_BLOKU_Y + PRZERWA);
            int L = (y < 1) ? 3 : (y < 3) ? 2 : 1;  // Życia bloku zależnie od wiersza
            bloki.emplace_back(sf::Vector2f(posX, posY),
                sf::Vector2f(ROZMIAR_BLOKU_X, ROZMIAR_BLOKU_Y),
                L);
        }
    }

    // ------------------ Pętla główna ------------------
    while (window.isOpen()) {
        // Obsługa zdarzeń
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Sterowanie paletką
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            pal.moveLeft();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            pal.moveRight();
        }
        pal.clampToBounds(WIDTH);

        // Aktualizacja piłki
        pilka.move();
        pilka.collideWalls(WIDTH, HEIGHT);
        if (pilka.collidePaddle(pal)) {
            std::cout << "HIT PADDLE\n";
        }

        // ------------------ Kolizja piłki z blokami ------------------
        for (auto& blok : bloki) {
            if (!blok.isDestroyed()) {
                // proste sprawdzenie kolizji piłki z blokiem (od góry/dol/ boków)
                sf::FloatRect blokRect = blok.getGlobalBounds();
                sf::FloatRect pilkaRect(pilka.getX() - pilka.getRadius(),
                    pilka.getY() - pilka.getRadius(),
                    pilka.getRadius() * 2.f,
                    pilka.getRadius() * 2.f);
                if (pilkaRect.intersects(blokRect)) {
                    blok.trafienie();
                    pilka.bounceY();
                }
            }
        }

        // Sprawdzanie przegranej
        if (pilka.getY() - pilka.getRadius() > HEIGHT) {
            std::cout << "MISS! KONIEC GRY\n";
            window.close();
        }

        // Debug info co 0.5s
        if (deltaClock.getElapsedTime().asSeconds() >= 0.5f) {
            std::cout << "x=" << pilka.getX() << " y=" << pilka.getY()
                << " vx=" << pilka.getVx() << " vy=" << pilka.getVy() << std::endl;
            deltaClock.restart();
        }

        // ------------------ Rysowanie ------------------
        window.clear(sf::Color(20, 20, 30));
        pal.draw(window);
        pilka.draw(window);
        for (const auto& blok : bloki) {
            blok.draw(window);
        }
        window.display();
    }

    return 0;
}
