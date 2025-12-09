#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Menu.hpp"
#include <iostream>
#include <vector>

enum class GameState { Menu, Playing, Scores, Exiting };

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Arkanoid");
    window.setFramerateLimit(60);

    Menu menu(window.getSize().x, window.getSize().y);
    Game game;
    GameState currentState = GameState::Menu;
    sf::Clock deltaClock;

    sf::Font font;
    if (!font.loadFromFile("E:/Windows/Fonts/arial.ttf"))
        std::cerr << "Nie mozna zaladowac czcionki Arial!" << std::endl;

    std::vector<int> lastScores; // ostatnie 5 wyników, najnowszy pierwszy

    while (window.isOpen()) {
        sf::Time dt = deltaClock.restart();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            // MENU
            if (currentState == GameState::Menu && event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) menu.przesunG();
                if (event.key.code == sf::Keyboard::Down) menu.przesunD();
                if (event.key.code == sf::Keyboard::Enter) {
                    int sel = menu.getSelectedItem();
                    if (sel == 0) currentState = GameState::Playing;
                    else if (sel == 1) currentState = GameState::Scores;
                    else if (sel == 2) window.close();
                }
            }

            // OBSŁUGA GRY
            if (currentState == GameState::Playing && event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) currentState = GameState::Menu;
            }

            // OBSŁUGA WYNIKÓW
            if (currentState == GameState::Scores && event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) currentState = GameState::Menu;
            }
        }

        if (currentState == GameState::Playing) {
            game.update(dt);

            if (game.isGameOver()) {
                std::cout << "Koniec gry! Wracamy do menu.\n";

                // najnowszy wynik na początku
                lastScores.insert(lastScores.begin(), game.getScore());
                if (lastScores.size() > 5) lastScores.pop_back();

                game.reset();
                currentState = GameState::Menu;
            }
        }

        window.clear(sf::Color::Black);

        if (currentState == GameState::Menu) menu.draw(window);
        else if (currentState == GameState::Playing) game.render(window);
        else if (currentState == GameState::Scores) {
            sf::Text scoresText;
            scoresText.setFont(font);
            scoresText.setCharacterSize(30);
            scoresText.setFillColor(sf::Color::White);
            scoresText.setPosition(50.f, 50.f);

            std::string str = "Ostatnie wyniki:\n";
            if (lastScores.empty()) str += "Brak danych\n";
            else {
                for (size_t i = 0; i < lastScores.size(); ++i)
                    str += std::to_string(i + 1) + ". " + std::to_string(lastScores[i]) + "\n";
            }
            scoresText.setString(str);
            window.draw(scoresText);
        }

        window.display();
    }

    return 0;
}
