#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>

void set_text_position(sf::Text& text, std::string& text_string) {
    text.setString(text_string + "|");
    if (text.getGlobalBounds().width > 950) {
        text_string += "\n";
        text.setString(text_string + "|");
    }
    if (text.getGlobalBounds().height > 110) {
        text_string = text_string.substr(0, text_string.size() - 2);
        text.setString(text_string);
    }
}

void initialize_text(const int& window_width, const int& window_height, const sf::RectangleShape& text_entry, sf::Font& font, sf::Text& instructions_text, sf::Text& input_text, sf::Text& score_notification, sf::Text& sentiment_score_text) {
    font.loadFromFile("font.ttf");

    instructions_text.setFont(font);
    instructions_text.setString("Enter a phrase to be sentiment checked:");
    instructions_text.setCharacterSize(24);
    instructions_text.setFillColor(sf::Color::White);
    instructions_text.setStyle(sf::Text::Bold);
    instructions_text.setOrigin(instructions_text.getLocalBounds().left + instructions_text.getLocalBounds().width / 2.0f, instructions_text.getLocalBounds().top + instructions_text.getLocalBounds().height / 2.0f);
    instructions_text.setPosition(sf::Vector2f((window_width - instructions_text.getPosition().x) / 2, window_height / 6 - instructions_text.getPosition().y));

    input_text.setFont(font);
    input_text.setString("|");
    input_text.setCharacterSize(18);
    input_text.setFillColor(sf::Color::Black);
    input_text.setPosition(sf::Vector2f(text_entry.getPosition().x + 20, text_entry.getPosition().y + 20));

    score_notification.setFont(font);
    score_notification.setString("This phrase has a sentiment score of:");
    score_notification.setCharacterSize(24);
    score_notification.setFillColor(sf::Color::White);
    score_notification.setStyle(sf::Text::Bold);
    score_notification.setOrigin(score_notification.getLocalBounds().left + score_notification.getLocalBounds().width / 2.0f, score_notification.getLocalBounds().top + score_notification.getLocalBounds().height / 2.0f);
    score_notification.setPosition(sf::Vector2f((window_width - score_notification.getPosition().x) / 2, 4 * window_height / 7 + score_notification.getPosition().y));

    sentiment_score_text.setFont(font);
    sentiment_score_text.setString("N/A");
    sentiment_score_text.setCharacterSize(50);
    sentiment_score_text.setFillColor(sf::Color::White);
    sentiment_score_text.setStyle(sf::Text::Bold);
    sentiment_score_text.setOrigin(sentiment_score_text.getLocalBounds().left + sentiment_score_text.getLocalBounds().width / 2.0f, sentiment_score_text.getLocalBounds().top + sentiment_score_text.getLocalBounds().height / 2.0f);
    sentiment_score_text.setPosition(sf::Vector2f((window_width - sentiment_score_text.getPosition().x) / 2, 5 * window_height / 7 + sentiment_score_text.getPosition().y));

}

int main() {
    int window_width = 1200;
    int window_height = 800;

    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Sentiment Analysis");
    sf::Vector2f text_entry_dimensions(1000, 150);
    sf::RectangleShape text_entry(text_entry_dimensions);
    text_entry.setFillColor(sf::Color::White);
    text_entry.setPosition(sf::Vector2f((window_width - text_entry_dimensions.x) / 2, window_height / 4));

    sf::Font font;
    sf::Text instructions_text;
    sf::Text input_text;
    std::string input_string = "";
    sf::Text score_notification;
    sf::Text sentiment_score_text;
    std::string sentiment_score_string = "N/A";

    initialize_text(window_width, window_height, text_entry, font, instructions_text, input_text, score_notification, sentiment_score_text);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b') {
                    if (input_string[input_string.size() - 1] == '\n') {
                        input_string = input_string.substr(0, input_string.size() - 2);
                    }
                    else {
                        input_string = input_string.substr(0, input_string.size() - 1);
                    }
                }
                else if (event.text.unicode < 128) {
                    input_string += static_cast<char>(event.text.unicode);
                }
                set_text_position(input_text, input_string);
            }
        }

        window.clear();
        window.draw(text_entry);
        window.draw(instructions_text);
        window.draw(input_text);
        window.draw(score_notification);
        window.draw(sentiment_score_text);
        window.display();
    }
    return 0;
}