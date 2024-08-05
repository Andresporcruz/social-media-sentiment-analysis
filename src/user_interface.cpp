#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>

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

void initialize_text(const int& window_width, const int& window_height, const sf::RectangleShape& text_entry, const sf::RectangleShape& text_entered, sf::Font& font, sf::Text& instructions_text, sf::Text& input_text, sf::Text& score_notification, sf::Text& previous_phrase, sf::Text& sentiment_score_text, sf::Text& simple_algorithm, sf::Text& multinomial_algorithm) {
    font.loadFromFile("font.ttf");

    instructions_text.setFont(font);
    instructions_text.setString("Enter a phrase to be sentiment checked:");
    instructions_text.setCharacterSize(24);
    instructions_text.setFillColor(sf::Color::White);
    instructions_text.setStyle(sf::Text::Bold);
    instructions_text.setOrigin(instructions_text.getLocalBounds().left + instructions_text.getLocalBounds().width / 2.0f, instructions_text.getLocalBounds().top + instructions_text.getLocalBounds().height / 2.0f);
    instructions_text.setPosition(sf::Vector2f((window_width - instructions_text.getPosition().x) / 2, window_height / 8 - instructions_text.getPosition().y + 100));

    input_text.setFont(font);
    input_text.setString("|");
    input_text.setCharacterSize(18);
    input_text.setFillColor(sf::Color::Black);
    input_text.setPosition(sf::Vector2f(text_entry.getPosition().x + 20, text_entry.getPosition().y + 20));

    score_notification.setFont(font);
    score_notification.setString("\t\tThe phrase\n\n\n\n\n\n\n\n\nhas a sentiment score of:");
    score_notification.setCharacterSize(24);
    score_notification.setFillColor(sf::Color::White);
    score_notification.setStyle(sf::Text::Bold);
    score_notification.setOrigin(score_notification.getLocalBounds().left + score_notification.getLocalBounds().width / 2.0f, score_notification.getLocalBounds().top + score_notification.getLocalBounds().height / 2.0f);
    score_notification.setPosition(sf::Vector2f((window_width - score_notification.getPosition().x) / 2, 3 * window_height / 5 + score_notification.getPosition().y + 100));

    previous_phrase.setFont(font);
    previous_phrase.setString("");
    previous_phrase.setCharacterSize(18);
    previous_phrase.setFillColor(sf::Color::Black);
    previous_phrase.setPosition(sf::Vector2f(text_entry.getPosition().x + 20, text_entered.getPosition().y + 20));

    sentiment_score_text.setFont(font);
    sentiment_score_text.setString("N/A");
    sentiment_score_text.setCharacterSize(50);
    sentiment_score_text.setFillColor(sf::Color::White);
    sentiment_score_text.setStyle(sf::Text::Bold);
    sentiment_score_text.setOrigin(sentiment_score_text.getLocalBounds().left + sentiment_score_text.getLocalBounds().width / 2.0f, sentiment_score_text.getLocalBounds().top + sentiment_score_text.getLocalBounds().height / 2.0f);
    sentiment_score_text.setPosition(sf::Vector2f((window_width - sentiment_score_text.getPosition().x) / 2, 6 * window_height / 7 + sentiment_score_text.getPosition().y + 70));

    simple_algorithm.setFont(font);
    simple_algorithm.setString("Simple\nAlgorithm");
    simple_algorithm.setCharacterSize(30);
    simple_algorithm.setFillColor(sf::Color::White);
    simple_algorithm.setStyle(sf::Text::Bold);
    simple_algorithm.setOrigin(simple_algorithm.getLocalBounds().left + simple_algorithm.getLocalBounds().width / 2.0f, simple_algorithm.getLocalBounds().top + simple_algorithm.getLocalBounds().height / 2.0f);
    simple_algorithm.setPosition(sf::Vector2f(window_width / 5, 100));

    multinomial_algorithm.setFont(font);
    multinomial_algorithm.setString("Naive Bayes\nAlgorithm");
    multinomial_algorithm.setCharacterSize(30);
    multinomial_algorithm.setFillColor(sf::Color::White);
    multinomial_algorithm.setStyle(sf::Text::Bold);
    multinomial_algorithm.setOrigin(multinomial_algorithm.getLocalBounds().left + multinomial_algorithm.getLocalBounds().width / 2.0f, multinomial_algorithm.getLocalBounds().top + multinomial_algorithm.getLocalBounds().height / 2.0f);
    multinomial_algorithm.setPosition(sf::Vector2f(4 * window_width / 5, 100));

}

int main() {
    int window_width = 1200;
    int window_height = 800;

    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Sentiment Analysis");
    sf::Vector2f text_entry_dimensions(1000, 150);
    sf::RectangleShape text_entry(text_entry_dimensions);
    text_entry.setFillColor(sf::Color::White);
    text_entry.setPosition(sf::Vector2f((window_width - text_entry_dimensions.x) / 2, window_height / 6 + 100));

    sf::RectangleShape text_entered(text_entry_dimensions);
    text_entered.setFillColor(sf::Color::White);
    text_entered.setPosition(sf::Vector2f((window_width - text_entry_dimensions.x) / 2, window_height / 2 + 100));

    sf::Vector2f button_dimensions(250, 100);
    sf::RectangleShape button(button_dimensions);
    button.setFillColor(sf::Color::Transparent);
    button.setPosition(sf::Vector2f((window_width - button_dimensions.x) / 8, window_height / 16));
    button.setOutlineColor(sf::Color::White);
    button.setOutlineThickness(5.f);

    sf::Font font;
    sf::Text instructions_text;
    sf::Text input_text;
    std::string input_string = "";
    sf::Text score_notification;
    sf::Text previous_phrase;
    sf::Text sentiment_score_text;
    std::string sentiment_score_string = "N/A";
    sf::Text simple_algorithm;
    sf::Text multinomial_algorithm;
    std::string algorithm_path = "src/predict.py";
    std::string algorithm_selected = "simple";

    initialize_text(window_width, window_height, text_entry, text_entered, font, instructions_text, input_text, score_notification, previous_phrase, sentiment_score_text, simple_algorithm, multinomial_algorithm);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (simple_algorithm.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))) {
                        button.setPosition(sf::Vector2f((window_width - button_dimensions.x) / 8, window_height / 16));
                        algorithm_selected = "simple";
                    }
                    if (multinomial_algorithm.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))) {
                        button.setPosition(sf::Vector2f(7 * (window_width - button_dimensions.x) / 8, window_height / 16));
                        algorithm_selected = "nb";
                    }
                }
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
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Return) {
                std::string command = "python " + algorithm_path + " " + algorithm_selected + " " + input_string;
                std::array<char, 128> buffer;
                std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(command.c_str(), "r"), _pclose);
                while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
                    sentiment_score_string = buffer.data();
                }
                sentiment_score_text.setString(sentiment_score_string);
                sentiment_score_text.setOrigin(sentiment_score_text.getLocalBounds().left + sentiment_score_text.getLocalBounds().width / 2.0f, sentiment_score_text.getLocalBounds().top + sentiment_score_text.getLocalBounds().height / 2.0f);
                std::cout << sentiment_score_string << std::endl;

                previous_phrase.setString(input_string);
                input_string = "";
                set_text_position(input_text, input_string);
            }
        }

        window.clear();
        window.draw(text_entry);
        window.draw(instructions_text);
        window.draw(input_text);
        window.draw(score_notification);
        window.draw(text_entered);
        window.draw(previous_phrase);
        window.draw(sentiment_score_text);
        window.draw(button);
        window.draw(simple_algorithm);
        window.draw(multinomial_algorithm);
        window.display();
    }
    return 0;
}