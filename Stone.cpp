#include "Stone.hpp"

const std::array<sf::Color, 4> Stone::m_colorLUT = {
    sf::Color::Transparent,
    sf::Color::Red,
    sf::Color::Yellow,
    sf::Color::Blue
};


Stone::Stone(sf::Vector2f startPos, sf::Vector2f rozmiar, int L)
    : m_punktyZycia(L), m_jestZniszczony(false)
{
    this->setPosition(startPos);
    this->setSize(rozmiar);
    this->setOutlineThickness(2.f);
    aktualizujKolor();
}

//zmniejszenie HP po trafieniu piłką
void Stone::trafienie() {
    if (m_jestZniszczony) return;
    m_punktyZycia--;
    aktualizujKolor();
    if (m_punktyZycia <= 0) m_jestZniszczony = true;
}

//aktualizacja koloru bloku według aktualnych punktów życia
void Stone::aktualizujKolor() {
    if (m_punktyZycia >= 0 && m_punktyZycia < (int)m_colorLUT.size()) {
        this->setFillColor(m_colorLUT[m_punktyZycia]);
    }
}

//sprawdzenie, czy blok został zniszczony
bool Stone::isDestroyed() const {
    return m_jestZniszczony;
}

//rysowanie bloku tylko jeśli nie został zniszczony
void Stone::draw(sf::RenderTarget& target) const {
    if (!m_jestZniszczony) {
        target.draw(*this);
    }
}
