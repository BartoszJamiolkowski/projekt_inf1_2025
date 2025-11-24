#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Game.h"

enum class GameState { Menu, Playing, Scores, Exiting };

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Arkanoid");
    window.setFramerateLimit(60);

    Menu menu(window.getSize().x, window.getSize().y);
    Game game;

    GameState currentState = GameState::Menu;

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                switch (currentState)
                {
                case GameState::Menu:
                    if (event.key.code == sf::Keyboard::Up)
                        menu.przesunG();
                    if (event.key.code == sf::Keyboard::Down)
                        menu.przesunD();

                    // ENTER = wybór
                    if (event.key.code == sf::Keyboard::Enter)
                    {
                        int sel = menu.getSelectedItem();
                        if (sel == 0)
                        {
                            game.loadLevel();   // restartowanie gry
                            currentState = GameState::Playing;
                        }
                        else if (sel == 1)
                        {
                            currentState = GameState::Scores; // jeśli będziesz używać
                        }
                        else if (sel == 2)
                        {
                            currentState = GameState::Exiting;
                            window.close();
                        }
                    }
                    break;

                case GameState::Playing:
                    // ESC → powrót do menu
                    if (event.key.code == sf::Keyboard::Escape)
                    {
                        currentState = GameState::Menu;
                    }
                    break;

                case GameState::Exiting:
                    window.close();
                    break;

                default:
                    break;
                }
            }
        }

        // UPDATE
        sf::Time dt = clock.restart();

        if (currentState == GameState::Playing)
            game.update(dt);

        // RENDER
        window.clear();

        if (currentState == GameState::Menu)
            menu.draw(window);
        else if (currentState == GameState::Playing)
            game.render(window);

        window.display();
    }

    return 0;
}
