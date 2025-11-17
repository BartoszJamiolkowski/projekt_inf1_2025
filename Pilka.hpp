#pragma once
#include <SFML/Graphics.hpp>
#include "Paletka.hpp"
#include <cmath>

class Pilka {
private:
	float x, y;
	float vx, vy;
	float radius;
	sf::CircleShape shape;

public:
	Pilka(float x_, float y_, float vx_, float vy_, float r)
		: x(x_), y(y_), vx(vx_), vy(vy_), radius(r)
	{
		shape.setRadius(radius);
		shape.setOrigin(radius, radius);
		shape.setPosition(x, y);
		shape.setFillColor(sf::Color::White);
	}

	void move() {
		x += vx;
		y += vy;
		shape.setPosition(x, y);
	}

	//odbicie pilki X
	void bounceX() { 
		vx = -vx; 
	}

	//odbicie pilki Y
	void bounceY() { 
		vy = -vy; 
	}
	
	void collideWalls(float width, float height) {
		// lewa sciana
		if (x - radius <= 0.f) {
			x = radius;
			bounceX();
			shape.setPosition(x, y);
		}
		// prawa sciana
		if (x + radius >= width) {
			x = width - radius;
			bounceX();
			shape.setPosition(x, y);
		}
		// gora
		if (y - radius <= 0.f) {
			y = radius;
			bounceY();
			shape.setPosition(x, y);
		}
	}


	bool collidePaddle(const Paletka& p) {
		float palLeft = p.getX() - p.getSzerokosc() / 2.f;
		float palRight = p.getX() + p.getSzerokosc() / 2.f;
		float palTop = p.getY() - p.getWysokosc() / 2.f;


		// Sprawdzenie kolizji od góry
		if (x >= palLeft && x <= palRight) {
			if ((y + radius) >= palTop && (y - radius) < palTop && vy > 0.f) {
				vy = -std::abs(vy);        // piłka leci w górę
				y = palTop - radius;      // ustaw tuż nad paletką
				shape.setPosition(x, y);
				return true;
			}
		}
		return false;
	}
	void draw(sf::RenderTarget& target) {
		target.draw(shape);
	}


	
	float getX() const { return x; }
	float getY() const { return y; }
	float getVx() const { return vx; }
	float getVy() const { return vy; }
	float getRadius() const { return radius; }
};
