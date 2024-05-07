#include "TextBox.h"
#include <SFML/Graphics.hpp>

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

TextBox::TextBox() {}

TextBox::TextBox(int size, sf::Color color, bool sel, sf::Vector2f pos) {
    textbox.setCharacterSize(size);
    textbox.setFillColor(color);
    isSelected = sel;
    this->setPosition(pos);
    if (sel) {
        textbox.setString("_");
    }
    else {
        textbox.setString("");
    }
}

void TextBox::setFont(sf::Font& font) {
    textbox.setFont(font);
}

void TextBox::setPosition(sf::Vector2f pos) {
    textbox.setPosition(pos);
}

void TextBox::setLimit(bool ToF, int lim) {
    hasLimit = ToF;
    limit = lim;
}

void TextBox::moveCursor(int direction) {
    int cursorPosition = text.tellp();

    if (direction == sf::Keyboard::Left && cursorPosition > 0) {
        cursorPosition--;
    }
    else if (direction == sf::Keyboard::Right && cursorPosition < text.str().length()) {
        cursorPosition++;
    }

    text.seekp(cursorPosition);

    std::string displayedText = text.str();
    displayedText.insert(cursorPosition, "_");
    textbox.setString(displayedText);
}

void TextBox::setSelected(bool sel) {
    isSelected = sel;
    if (!sel) {
        std::string t = text.str();
        std::string newT = "";
        for (int i = 0; i < t.length() - 1; i++) {
            newT += t[i];
        }
        textbox.setString(newT);
    }
}

std::string TextBox::getText() {
    return text.str();
}

void TextBox::drawTo(sf::RenderWindow& window) {
    window.draw(textbox);
}

void TextBox::typedOn(sf::Event input) {
    if (isSelected) {
        int charTyped = input.text.unicode;
        if (charTyped < 128) {
            if (hasLimit) {
                if (text.str().length() <= limit) {
                    inputLogic(charTyped);
                }
                else if (text.str().length() > limit && charTyped == DELETE_KEY) {
                    deleteLastChar();
                }
            }
            else {
                inputLogic(charTyped);
            }
        }
    }
}

void TextBox::inputLogic(int charTyped) {
    if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY) {
        text << static_cast<char>(charTyped);
    }
    else if (charTyped == DELETE_KEY) {
        if (text.str().length() > 0) {
            deleteLastChar();
        }
        textbox.setString(text.str() + "_");
    }
    textbox.setString(text.str() + "_");
}

void TextBox::deleteLastChar() {
    std::string t = text.str();
    std::string newT = "";
    for (int i = 0; i < t.length() - 1; i++) {
        newT += t[i];
    }
    text.str("");
    text << newT;
    textbox.setString(text.str());
}
