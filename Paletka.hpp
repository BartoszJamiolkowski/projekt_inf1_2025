#pragma once
#include <SFML/Graphics.hpp>

class Paletka {
private:
	float x, y;// wspolrzedne srodka x,y
	float szerokosc, wysokosc;//rozmiar paletki
	float predkosc;//predkosc paletki
	sf::RectangleShape shape;// rysowanie paletki
public:
	//parametry startowe paletki 
	Paletka(float x_, float y_, float s, float w, float p)
		: x(x_), y(y_), szerokosc(s), wysokosc(w), predkosc(p)
	{
		shape.setSize({ szerokosc, wysokosc });
		shape.setOrigin(szerokosc / 2.f, wysokosc / 2.f);
		shape.setPosition(x, y);
		shape.setFillColor(sf::Color::White);
	}
	
	//ruch paletki w lewo
	void moveLeft() {
		x = x-predkosc;
		shape.setPosition(x, y);
	}

	//ruch paletki w prawo
	void moveRight() {
		x = x+predkosc;
		shape.setPosition(x, y);
	}

	//ograniczenie paletki w grancicach okna 
	void clampToBounds(float width) {
		float polowa= szerokosc / 2.f;
		if (x - polowa < 0.f) x = polowa;
		if (x + polowa > width) x = width - polowa;
		shape.setPosition(x, y);
	}

	void draw(sf::RenderTarget& target) {
		target.draw(shape);
	}
	// gettery do kolizji z pilka
	float getX() const { return x; }
	float getY() const { return y; }
	float getSzerokosc() const { return szerokosc; }
	float getWysokosc() const { return wysokosc; }
};
