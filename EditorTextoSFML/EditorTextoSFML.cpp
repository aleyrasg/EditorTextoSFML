// EditorTextoSFML.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class TextBox {
public:
    TextBox() {}
    TextBox(int size, sf::Color color, bool sel, sf::Vector2f pos) {
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

    void setFont(sf::Font& font) {
        textbox.setFont(font);
    }

    void setPosition(sf::Vector2f pos) {
        textbox.setPosition(pos);
    }

    void setLimit(bool ToF, int lim) {
        hasLimit = ToF;
        limit = lim;
    }
    void moveCursor(int direction) {
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

    void setSelected(bool sel) {
        isSelected = sel;
        if (!sel)
        {
            std::string t = text.str();
            std::string newT = "";
            for (int i = 0; i < t.length() - 1; i++)
            {
                newT += t[i];
            }
            textbox.setString(newT);
        }
    }

    std::string getText() {
        return text.str();
    }

    void drawTo(sf::RenderWindow& window) {
        window.draw(textbox);
    }


    void typedOn(sf::Event input) {
        if (isSelected)
        {
            int charTyped = input.text.unicode;
            if (charTyped < 128)
            {
                if (hasLimit)
                {
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

private:
    sf::Text textbox;
    std::ostringstream text;
    int limit;
    bool hasLimit;
    bool isSelected = false;

    void inputLogic(int charTyped) {
        if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY) {
            text << static_cast<char>(charTyped);
        }
        else if (charTyped == DELETE_KEY) {
            if (text.str().length() > 0)
            {
                deleteLastChar();
            }
            textbox.setString(text.str() + "_");
        }
        textbox.setString(text.str() + "_");
    }

    void deleteLastChar() {
        std::string t = text.str();
        std::string newT = "";
        for (int i = 0; i < t.length() - 1; i++)
        {
            newT += t[i];
        }
        text.str("");
        text << newT;
        textbox.setString(text.str());
    }

};


int main() {
    sf::RenderWindow window;
    sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width / 2) - 445, (sf::VideoMode::getDesktopMode().height / 2) - 480);
    window.create(sf::VideoMode(900, 900), "SFML works!", sf::Style::Titlebar | sf::Style::Close);
    window.setPosition(centerWindow);
    window.setKeyRepeatEnabled(true);
    sf::Font arial;
    arial.loadFromFile("ARIAL.ttf");
    TextBox textbox1(15, sf::Color::White, true, { 100,100 });
    textbox1.setFont(arial);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
            case sf::Event::TextEntered:
                textbox1.typedOn(event);

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
// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
