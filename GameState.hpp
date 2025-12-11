#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Paletka.hpp"
#include "Pilka.hpp"
#include "Stone.hpp"

//struktura do przechowywania danych o klockach
struct BlockData {
    float x, y;
    int hp;
};

class GameState {
private:
    sf::Vector2f paddlePosition;
    sf::Vector2f ballPosition;
    sf::Vector2f ballVelocity;
    std::vector<BlockData> blocks;

public:
    GameState() = default;

    void capture(const Paletka& p, const Pilka& b, const std::vector<Stone>& stones);//zapis stanu gry
    bool saveToFile(const std::string& filename);//zapis do pliku
    bool loadFromFile(const std::string& filename);//odczyt z pliku
    void apply(Paletka& p, Pilka& b, std::vector<Stone>& stones);//przywrocenie stanu gry
};
