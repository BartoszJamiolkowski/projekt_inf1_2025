#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Menu.hpp"
#include <iostream>

enum class GameState { Menu, Playing, Scores, Exiting };

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Arkanoid");
    window.setFramerateLimit(60);

    Menu menu(window.getSize().x, window.getSize().y);
    Game game;

    GameState currentState = GameState::Menu;
    sf::Clock deltaClock;

    // Font do wyświetlania wyników
    sf::Font font;
    if (!font.loadFromFile("E:/Windows/Fonts/arial.ttf")) {
        std::cerr << "Nie mozna zaladowac czcionki Arial!" << std::endl;
    }

    while (window.isOpen()) {
        sf::Time dt = deltaClock.restart();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // OBSŁUGA MENU
            if (currentState == GameState::Menu && event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) menu.przesunG();
                if (event.key.code == sf::Keyboard::Down) menu.przesunD();
                if (event.key.code == sf::Keyboard::Enter) {
                    int sel = menu.getSelectedItem();
                    if (sel == 0) currentState = GameState::Playing;
                    else if (sel == 1) currentState = GameState::Scores;
                    else if (sel == 2) { window.close(); }
                }
            }

            // OBSŁUGA GRY
            if (currentState == GameState::Playing && event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape)
                    currentState = GameState::Menu;
            }

            // OBSŁUGA WYNIKÓW
            if (currentState == GameState::Scores && event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape)
                    currentState = GameState::Menu;
            }
        }

        // AKTUALIZACJA GRY
        if (currentState == GameState::Playing) {
            game.update(dt);

            // SPRAWDZENIE KONCA GRY
            if (game.isGameOver()) {
                std::cout << "Koniec gry! Wracamy do menu.\n";
                game.reset();           // reset stanu gry
                currentState = GameState::Menu;
            }
        }

        // CZARNE TŁO
        window.clear(sf::Color::Black);

        // RYSOWANIE
        if (currentState == GameState::Menu)
            menu.draw(window);
        else if (currentState == GameState::Playing)
            game.render(window);
        else if (currentState == GameState::Scores) {
            sf::Text scoresText;
            scoresText.setFont(font);
            scoresText.setString("Ostatnie wyniki:\nBrak danych");
            scoresText.setCharacterSize(30);
            scoresText.setFillColor(sf::Color::White);
            scoresText.setPosition(50.f, 50.f);
            window.draw(scoresText);
        }
        window.display();
    }

    return 0;
}
