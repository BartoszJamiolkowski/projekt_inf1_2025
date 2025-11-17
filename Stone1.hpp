#pragma once
#include <SFML/Graphics.hpp>
#include <array>

class Stone : public sf::RectangleShape {
private:
    int m_punktyZycia;
    bool m_jestZniszczony;
    static const std::array<sf::Color, 4> m_colorLUT;

public:
    // Konstruktor
    Stone(sf::Vector2f startPos, sf::Vector2f rozmiar, int L)
        : m_punktyZycia(L), m_jestZniszczony(false)
    {
        this->setPosition(startPos);
        this->setSize(rozmiar);
        this->setOutlineThickness(2.f);
        aktualizujKolor();
    }

    // Trafienie blokiem
    void trafienie() {
        if (m_jestZniszczony)
            return;
        m_punktyZycia--;
        aktualizujKolor();
        if (m_punktyZycia <= 0)
            m_jestZniszczony = true;
    }

    // Aktualizacja koloru na podstawie punktów życia
    void aktualizujKolor() {
        if (m_punktyZycia >= 0 && m_punktyZycia < (int)m_colorLUT.size()) {
            this->setFillColor(m_colorLUT[m_punktyZycia]);
        }
    }

    bool isDestroyed() const {
        return m_jestZniszczony;
    }

    void draw(sf::RenderTarget& target) const {
        if (!m_jestZniszczony) {
            target.draw(*this);
        }
    }
};

// Definicja statycznej tablicy kolorów
const std::array<sf::Color, 4> Stone::m_colorLUT = {
    sf::Color::Transparent, // L = 0
    sf::Color::Red,         // L = 1
    sf::Color::Yellow,      // L = 2
    sf::Color::Blue         // L = 3
};
