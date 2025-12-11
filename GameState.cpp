#include "GameState.hpp"
#include <fstream>
#include <string>

void GameState::capture(const Paletka& p, const Pilka& b, const std::vector<Stone>& stones)
{   //zapis aktualnej pozycji paletki i piłki
    paddlePosition = sf::Vector2f(p.getX(), p.getY());
    ballPosition = sf::Vector2f(b.getX(), b.getY());
    ballVelocity = sf::Vector2f(b.getVx(), b.getVy());

    blocks.clear();
    blocks.reserve(stones.size());

    for (const auto& s : stones) {
        if (!s.isDestroyed()) {
            BlockData bd;
            bd.x = s.getPosition().x;
            bd.y = s.getPosition().y;
            bd.hp = s.getHP();
            blocks.push_back(bd);
        }
    }
}

bool GameState::saveToFile(const std::string& filename)
{   //proba otwarcia pliku do zapisu
    std::ofstream file(filename);
    if (!file.is_open()) return false;

    //zapsis pozycji paletki, pilki i blokow do pliku 
    file << "PADDLE " << paddlePosition.x << " " << paddlePosition.y << "\n";
    file << "BALL " << ballPosition.x << " " << ballPosition.y << " "
        << ballVelocity.x << " " << ballVelocity.y << "\n";
    //liczba blokow
    file << "BLOCKS_COUNT " << blocks.size() << "\n";

    for (const auto& b : blocks)
        file << b.x << " " << b.y << " " << b.hp << "\n";

    return true;
}

bool GameState::loadFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    std::string label;
    file >> label >> paddlePosition.x >> paddlePosition.y;
    file >> label >> ballPosition.x >> ballPosition.y >> ballVelocity.x >> ballVelocity.y;

    int count;
    file >> label >> count;

    blocks.clear();
    blocks.reserve(count);

    for (int i = 0; i < count; i++) {
        BlockData bd;
        file >> bd.x >> bd.y >> bd.hp;
        blocks.push_back(bd);
    }

    return true;
}

void GameState::apply(Paletka& p, Pilka& b, std::vector<Stone>& stones)
{   
    // przywrocenie pozycji paletki i piłki
    p.setPosition(paddlePosition);
    b.reset(ballPosition, ballVelocity);

    stones.clear();

    // rozmiary blokow i rozmieszczenie
    const int ILOSC_KOLUMN = 6;
    const float PRZERWA = 2.f;
    const float ROZMIAR_BLOKU_Y = 25.f;
    const float ROZMIAR_BLOKU_X = (800.f - (ILOSC_KOLUMN - 1) * PRZERWA) / ILOSC_KOLUMN; // stała szerokość

    sf::Vector2f blockSize(ROZMIAR_BLOKU_X, ROZMIAR_BLOKU_Y);
    
    //odtwarzanie każdego bloku na podstawie danych z pliku
    for (const auto& bd : blocks) {
        stones.emplace_back(sf::Vector2f(bd.x, bd.y), blockSize, bd.hp);
    }
}
