#include "Menu.hpp"

Menu::Menu(float width, float height) {
    if (!font.loadFromFile("E:/Windows/Fonts/arial.ttf")) return; // upewnienie się, że czcionka istnieje

    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::Cyan);  // pierwszy element podświetlony
    menu[0].setString("Nowa gra");
    menu[0].setPosition(width / 3.f, height / (MAX_LICZBA_POZIOMOW + 1) * 1);

    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("Ostatnie wyniki");
    menu[1].setPosition(width / 3.f, height / (MAX_LICZBA_POZIOMOW + 1) * 2);

    menu[2].setFont(font);
    menu[2].setFillColor(sf::Color::White);
    menu[2].setString("Wyjscie");
    menu[2].setPosition(width / 3.f, height / (MAX_LICZBA_POZIOMOW + 1) * 3);
}

void Menu::przesunG() {
    menu[selectedItem].setFillColor(sf::Color::White);
    menu[selectedItem].setStyle(sf::Text::Regular);
    selectedItem--;
    if (selectedItem < 0) selectedItem = MAX_LICZBA_POZIOMOW - 1;
    menu[selectedItem].setFillColor(sf::Color::Cyan);
    menu[selectedItem].setStyle(sf::Text::Bold);
}

void Menu::przesunD() {
    menu[selectedItem].setFillColor(sf::Color::White);
    menu[selectedItem].setStyle(sf::Text::Regular);
    selectedItem++;
    if (selectedItem >= MAX_LICZBA_POZIOMOW) selectedItem = 0;
    menu[selectedItem].setFillColor(sf::Color::Cyan);
    menu[selectedItem].setStyle(sf::Text::Bold);
}

void Menu::draw(sf::RenderWindow& window) const {
    for (int i = 0; i < MAX_LICZBA_POZIOMOW; i++)
        window.draw(menu[i]);
}
