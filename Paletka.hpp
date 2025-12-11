#pragma once
#include <SFML/Graphics.hpp>

class Paletka {
private:
    float x, y;
    float szerokosc, wysokosc;
    float predkosc;
    sf::RectangleShape shape;

public:
    Paletka(float x_, float y_, float s, float w, float p)
        : x(x_), y(y_), szerokosc(s), wysokosc(w), predkosc(p)
    {
        shape.setSize({ szerokosc, wysokosc });
        shape.setOrigin(szerokosc / 2.f, wysokosc / 2.f);
        shape.setPosition(x, y);
        shape.setFillColor(sf::Color::White);
    }

    void moveLeft() {
        x -= predkosc;
        shape.setPosition(x, y);
    }

    void moveRight() {
        x += predkosc;
        shape.setPosition(x, y);
    }

    void clampToBounds(float width) {
        float polowa = szerokosc / 2.f;
        if (x - polowa < 0.f) x = polowa;
        if (x + polowa > width) x = width - polowa;
        shape.setPosition(x, y);
    }

    void setPosition(float nx, float ny) {
        x = nx;
        y = ny;
        shape.setPosition(x, y);
    }

    void setPosition(const sf::Vector2f& pos) {  
        x = pos.x;
        y = pos.y;
        shape.setPosition(x, y);
    }

    void draw(sf::RenderTarget& target) const {
        target.draw(shape);
    }

    float getX() const { 
        return x; 
    }
    float getY() const { 
        return y; 
    }
    float getSzerokosc() const { 
        return szerokosc; 
    }
    float getWysokosc() const { 
        return wysokosc; 
    }
};

