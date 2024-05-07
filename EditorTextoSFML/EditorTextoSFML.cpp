// EditorTextoSFML.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

#include <SFML/Graphics.hpp>
#include "TextBox.h"

int main() {
    sf::RenderWindow window;
    sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width / 2) - 445, (sf::VideoMode::getDesktopMode().height / 2) - 480);
    window.create(sf::VideoMode(900, 900), "SFML works!", sf::Style::Titlebar | sf::Style::Close);
    window.setPosition(centerWindow);
    window.setKeyRepeatEnabled(true);
    sf::Font arial;
    arial.loadFromFile("ARIAL.ttf");
    TextBox textbox1(15, sf::Color::Magenta, true, { 100,100 });
    textbox1.setFont(arial);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::TextEntered:
                textbox1.typedOn(event);
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right) {
                    int direction = event.key.code;
                    textbox1.moveCursor(direction);
                }
                break;
            default:
                break;
            }
        }
        window.clear();
        textbox1.drawTo(window);
        window.display();
    }
    return 0;
}
