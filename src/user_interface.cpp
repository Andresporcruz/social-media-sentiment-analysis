#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>

int main() {
    int window_width = 1200;
    int window_height = 800;

    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Sentiment Analysis");
    sf::Vector2f text_entry_dimensions(1000, 150);
    sf::RectangleShape text_entry(text_entry_dimensions);
    text_entry.setFillColor(sf::Color::White);
    text_entry.setPosition(sf::Vector2f((window_width - text_entry_dimensions.x) / 2, (window_height + text_entry_dimensions.y) / 2));

    sf::Font font;
    font.loadFromFile("font.ttf");

    sf::Text instructions_text;
    instructions_text.setFont(font);
    instructions_text.setString("Enter a phrase to be sentiment checked:");
    instructions_text.setCharacterSize(24);
    instructions_text.setFillColor(sf::Color::White);
    instructions_text.setStyle(sf::Text::Bold);
    instructions_text.setOrigin(instructions_text.getLocalBounds().left + instructions_text.getLocalBounds().width / 2.0f, instructions_text.getLocalBounds().top + instructions_text.getLocalBounds().height / 2.0f);
    instructions_text.setPosition(sf::Vector2f((window_width - instructions_text.getPosition().x) / 2, (window_height - instructions_text.getPosition().y) / 2));

    sf::Text input_text;
    input_text.setFont(font);
    std::string inputString = "";
    input_text.setString(inputString + "|");
    input_text.setCharacterSize(18);
    input_text.setFillColor(sf::Color::Black);
    //inputText.setOrigin(inputText.getLocalBounds().left + inputText.getLocalBounds().width / 2.0f, inputText.getLocalBounds().top + inputText.getLocalBounds().height / 2.0f);
    input_text.setPosition(sf::Vector2f(text_entry.getPosition().x + 20, text_entry.getPosition(). y + 20));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        window.draw(text_entry);
        window.draw(instructions_text);
        window.draw(input_text);
        window.display();
    }
    return 0;
}