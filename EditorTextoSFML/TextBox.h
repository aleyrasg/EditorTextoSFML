#pragma once
#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

class TextBox {
public:
    TextBox();
    TextBox(int size, sf::Color color, bool sel, sf::Vector2f pos);

    void setFont(sf::Font& font);
    void setPosition(sf::Vector2f pos);
    void setLimit(bool ToF, int lim);
    void moveCursor(int direction);
    void setSelected(bool sel);
    std::string getText();
    void drawTo(sf::RenderWindow& window);
    void typedOn(sf::Event input);

private:
    sf::Text textbox;
    std::ostringstream text;
    int limit;
    bool hasLimit;
    bool isSelected;

    void inputLogic(int charTyped);
    void deleteLastChar();
};

#endif


