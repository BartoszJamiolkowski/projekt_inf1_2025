#pragma once
#include <SFML/Graphics.hpp>

#define MAX_LICZBA_POZIOMOW 3

class Menu
{
private:
    sf::Font font;
    sf::Text menu[MAX_LICZBA_POZIOMOW]; // elementy menu
    int selectedItem = 0;

public:
    Menu(float width, float height);
    ~Menu() {}

    void przesunG();  // przesuwanie w górę
    void przesunD();  // przesuwanie w dół
    int getSelectedItem() const { return selectedItem; } // zwróć aktualny wybór
    void draw(sf::RenderWindow& window) const;           // rysuj menu
};
