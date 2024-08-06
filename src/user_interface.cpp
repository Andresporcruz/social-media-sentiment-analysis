#include <iostream>
#include <SFML/Graphics.hpp> // Included to create the UI
#include <vector>
#include <fstream>
#include <cstdio> // Included to pass text to a python script and capture the script's output
#include <memory>
#include <stdexcept>
#include <array>

void set_input_text(sf::Text& text, std::string& text_string) {
    text.setString(text_string + "|");
    if (text.getGlobalBounds().width > 950) { // Repositions the user's input string when indents are needed
        text_string += "\n";
        text.setString(text_string + "|");
    }
    if (text.getGlobalBounds().height > 110) { // Rejects input when the phrase is too long
        text_string = text_string.substr(0, text_string.size() - 2);
        text.setString(text_string);
    }
}

void initialize_text(const int& window_width, const int& window_height, const sf::RectangleShape& text_entry, const sf::RectangleShape& text_entered, sf::Font& font, sf::Text& instructions_text, sf::Text& input_text, sf::Text& score_notification, sf::Text& previous_phrase, sf::Text& sentiment_score_text, sf::Text& simple_algorithm, sf::Text& naive_bayes_algorithm, sf::Text& visualization_text, sf::Text& positive_text, sf::Text& negative_text, sf::Text& wordcloud_text) {
    font.loadFromFile("font.ttf"); // Loads default font

    instructions_text.setFont(font); // Creates a text object to request input from the user
    instructions_text.setString("Enter a phrase to be sentiment checked:");
    instructions_text.setCharacterSize(24);
    instructions_text.setFillColor(sf::Color::White);
    instructions_text.setStyle(sf::Text::Bold);
    instructions_text.setOrigin(instructions_text.getLocalBounds().left + instructions_text.getLocalBounds().width / 2.0f, instructions_text.getLocalBounds().top + instructions_text.getLocalBounds().height / 2.0f);
    instructions_text.setPosition(sf::Vector2f((window_width - instructions_text.getPosition().x) / 2, window_height / 8 - instructions_text.getPosition().y + 100));

    input_text.setFont(font); // Creates a text object to display the user's input
    input_text.setString("|");
    input_text.setCharacterSize(18);
    input_text.setFillColor(sf::Color::Black);
    input_text.setPosition(sf::Vector2f(text_entry.getPosition().x + 20, text_entry.getPosition().y + 20));

    score_notification.setFont(font); // Creates a text object to explain what the program does
    score_notification.setString("\t\tThe phrase\n\n\n\n\n\n\n\n\nhas a sentiment score of:");
    score_notification.setCharacterSize(24);
    score_notification.setFillColor(sf::Color::White);
    score_notification.setStyle(sf::Text::Bold);
    score_notification.setOrigin(score_notification.getLocalBounds().left + score_notification.getLocalBounds().width / 2.0f, score_notification.getLocalBounds().top + score_notification.getLocalBounds().height / 2.0f);
    score_notification.setPosition(sf::Vector2f((window_width - score_notification.getPosition().x) / 2, 3 * window_height / 5 + score_notification.getPosition().y + 100));

    previous_phrase.setFont(font); // Creates a text object to display which input's sentiment is being displayed
    previous_phrase.setString("");
    previous_phrase.setCharacterSize(18);
    previous_phrase.setFillColor(sf::Color::Black);
    previous_phrase.setPosition(sf::Vector2f(text_entry.getPosition().x + 20, text_entered.getPosition().y + 20));

    sentiment_score_text.setFont(font); // Creates a text object to display sentiment score
    sentiment_score_text.setString("N/A");
    sentiment_score_text.setCharacterSize(50);
    sentiment_score_text.setFillColor(sf::Color::White);
    sentiment_score_text.setStyle(sf::Text::Bold);
    sentiment_score_text.setOrigin(sentiment_score_text.getLocalBounds().left + sentiment_score_text.getLocalBounds().width / 2.0f, sentiment_score_text.getLocalBounds().top + sentiment_score_text.getLocalBounds().height / 2.0f);
    sentiment_score_text.setPosition(sf::Vector2f((window_width - sentiment_score_text.getPosition().x) / 2, 6 * window_height / 7 + sentiment_score_text.getPosition().y + 70));

    simple_algorithm.setFont(font); // Creates a text object to allow user to select our simple algorithm
    simple_algorithm.setString("Simple\nAlgorithm");
    simple_algorithm.setCharacterSize(30);
    simple_algorithm.setFillColor(sf::Color::White);
    simple_algorithm.setStyle(sf::Text::Bold);
    simple_algorithm.setOrigin(simple_algorithm.getLocalBounds().left + simple_algorithm.getLocalBounds().width / 2.0f, simple_algorithm.getLocalBounds().top + simple_algorithm.getLocalBounds().height / 2.0f);
    simple_algorithm.setPosition(sf::Vector2f(window_width / 5, 100));

    naive_bayes_algorithm.setFont(font); // Creates a text object to allow user to select the custom naive bayes algorithm
    naive_bayes_algorithm.setString("Naive Bayes\nAlgorithm");
    naive_bayes_algorithm.setCharacterSize(30);
    naive_bayes_algorithm.setFillColor(sf::Color::White);
    naive_bayes_algorithm.setStyle(sf::Text::Bold);
    naive_bayes_algorithm.setOrigin(naive_bayes_algorithm.getLocalBounds().left + naive_bayes_algorithm.getLocalBounds().width / 2.0f, naive_bayes_algorithm.getLocalBounds().top + naive_bayes_algorithm.getLocalBounds().height / 2.0f);
    naive_bayes_algorithm.setPosition(sf::Vector2f(window_width / 2, 100));

    visualization_text.setFont(font); // Creates a text object to allow user to change to the visualization screen
    visualization_text.setString("Visualize");
    visualization_text.setCharacterSize(30);
    visualization_text.setFillColor(sf::Color::White);
    visualization_text.setStyle(sf::Text::Bold);
    visualization_text.setOrigin(visualization_text.getLocalBounds().left + visualization_text.getLocalBounds().width / 2.0f, visualization_text.getLocalBounds().top + visualization_text.getLocalBounds().height / 2.0f);
    visualization_text.setPosition(sf::Vector2f(4 * window_width / 5, 100));

    positive_text.setFont(font); // Creates a text object to allow user to select postive sentiment words
    positive_text.setString("Positive\nSentiment");
    positive_text.setCharacterSize(30);
    positive_text.setFillColor(sf::Color::White);
    positive_text.setStyle(sf::Text::Bold);
    positive_text.setOrigin(positive_text.getLocalBounds().left + positive_text.getLocalBounds().width / 2.0f, positive_text.getLocalBounds().top + positive_text.getLocalBounds().height / 2.0f);
    positive_text.setPosition(sf::Vector2f(window_width / 5, window_height / 2));

    negative_text.setFont(font); // Creates a text object to allow user to select negative sentiment words
    negative_text.setString("Negative\nSentiment");
    negative_text.setCharacterSize(30);
    negative_text.setFillColor(sf::Color::White);
    negative_text.setStyle(sf::Text::Bold);
    negative_text.setOrigin(negative_text.getLocalBounds().left + negative_text.getLocalBounds().width / 2.0f, negative_text.getLocalBounds().top + negative_text.getLocalBounds().height / 2.0f);
    negative_text.setPosition(sf::Vector2f(4 * window_width / 5, window_height / 2));

    wordcloud_text.setFont(font); // Creates a text object to allow user to change to the visualization screen
    wordcloud_text.setString("Press \"Enter\" to generate a wordcloud");
    wordcloud_text.setCharacterSize(30);
    wordcloud_text.setFillColor(sf::Color::White);
    wordcloud_text.setStyle(sf::Text::Bold);
    wordcloud_text.setOrigin(wordcloud_text.getLocalBounds().left + wordcloud_text.getLocalBounds().width / 2.0f, wordcloud_text.getLocalBounds().top + wordcloud_text.getLocalBounds().height / 2.0f);
    wordcloud_text.setPosition(sf::Vector2f(window_width / 2, 3 * window_height / 4));
}

void update_program(sf::RenderWindow& window, bool visualizing, const sf::RectangleShape& text_entry, const sf::RectangleShape& text_entered, const sf::RectangleShape& button, const sf::RectangleShape& visuals_button, const sf::RectangleShape& sentiment_button, sf::Text& instructions_text, sf::Text& input_text, sf::Text& score_notification, sf::Text& previous_phrase, sf::Text& sentiment_score_text, sf::Text& simple_algorithm, sf::Text& naive_bayes_algorithm, sf::Text& visualization_text, sf::Text& positive_text, sf::Text& negative_text, sf::Text& wordcloud_text) {
    window.clear(); // Clears the screen to prepare for the update
    if (!visualizing) {
        window.draw(text_entry); // Draws the text entry box
        window.draw(instructions_text); // Draws the instructions
        window.draw(input_text); // Draws the current phrase text box
        window.draw(score_notification); // Draws the clarification text
        window.draw(text_entered); // Draws the user's input
        window.draw(previous_phrase); // Draws the current phrase being evaluated
        window.draw(sentiment_score_text); // Draws the sentiment score
    }
    if (visualizing) {
        window.draw(visuals_button); // Draws the button outline to indicate if visuals mode is active
        window.draw(positive_text); // Draws positive sentiment text 
        window.draw(negative_text); // Draws negative sentiment text
        window.draw(sentiment_button); // Draws button outline to indicate which sentiment has been selected
        window.draw(wordcloud_text); // Draws instrcutions for generating wordclouds
    }
    window.draw(button); // Draws the button outline to indicate the algorithm being used
    window.draw(simple_algorithm); // Draws the simple algorithm button
    window.draw(naive_bayes_algorithm); // Draws the naive bayes algorithm button
    window.draw(visualization_text); // Draws visualize button
    window.display(); // Displays the screen for the user to see the updates
}

int main() {
    int window_width = 1200; // Initializes the display window's dimensions to static values
    int window_height = 800;

    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Sentiment Analysis"); // Creates display window
    sf::Vector2f text_entry_dimensions(1000, 150);
    sf::RectangleShape text_entry(text_entry_dimensions); // Creates a text entry box for the user
    text_entry.setFillColor(sf::Color::White);
    text_entry.setPosition(sf::Vector2f((window_width - text_entry_dimensions.x) / 2, window_height / 6 + 100));

    sf::RectangleShape text_entered(text_entry_dimensions); // Creates a text box to display user input
    text_entered.setFillColor(sf::Color::White);
    text_entered.setPosition(sf::Vector2f((window_width - text_entry_dimensions.x) / 2, window_height / 2 + 100));

    sf::Vector2f button_dimensions(250, 100); // Creates an outline to indicate which algorithm is running
    sf::RectangleShape button(button_dimensions);
    button.setFillColor(sf::Color::Transparent);
    button.setPosition(sf::Vector2f((window_width - button_dimensions.x) / 8, window_height / 16));
    button.setOutlineColor(sf::Color::White);
    button.setOutlineThickness(5.f);

    sf::RectangleShape visuals_button(button_dimensions); // Creates an outline to indicate if visualizing mode is on
    visuals_button.setFillColor(sf::Color::Transparent);
    visuals_button.setPosition(sf::Vector2f(7 * (window_width - button_dimensions.x) / 8, window_height / 16));
    visuals_button.setOutlineColor(sf::Color::White);
    visuals_button.setOutlineThickness(5.f);

    sf::RectangleShape sentiment_button(button_dimensions); // Creates an outline to indicate which sentiment to generate a wordcloud for
    sentiment_button.setFillColor(sf::Color::Transparent);
    sentiment_button.setPosition(sf::Vector2f((window_width - button_dimensions.x) / 8, 7 * window_height / 16));
    sentiment_button.setOutlineColor(sf::Color::White);
    sentiment_button.setOutlineThickness(5.f);

    sf::Font font; // Initializing text objects to have their parameters set in the initialize_text() function
    sf::Text instructions_text;
    sf::Text input_text;
    std::string input_string = "";
    sf::Text score_notification;
    sf::Text previous_phrase;
    sf::Text sentiment_score_text;
    std::string sentiment_score_string = "N/A";
    sf::Text simple_algorithm;
    sf::Text naive_bayes_algorithm;
    sf::Text visualization_text;
    sf::Text positive_text;
    sf::Text negative_text;
    sf::Text wordcloud_text;
    std::string algorithm_path = "src/predict.py";
    std::string algorithm_selected = "simple";
    std::string sentiment_selected = "positive";

    bool visualizing = false; // Sets mode to computing sentiments and not visualizing data

    // Set the parameters for all of the program's text objects
    initialize_text(window_width, window_height, text_entry, text_entered, font, instructions_text, input_text, score_notification, previous_phrase, sentiment_score_text, simple_algorithm, naive_bayes_algorithm, visualization_text, positive_text, negative_text, wordcloud_text);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) { // Detects user input
            if (event.type == sf::Event::Closed) { // Detects if user has closed the program
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) { // Detects for mouse clicks
                if (event.mouseButton.button == sf::Mouse::Left) { // Switches algorithm in use depending on option the user clicks
                    if (simple_algorithm.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))) {
                        button.setPosition(sf::Vector2f((window_width - button_dimensions.x) / 8, window_height / 16));
                        algorithm_selected = "simple";
                    }
                    if (naive_bayes_algorithm.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))) {
                        button.setPosition(sf::Vector2f((window_width - button_dimensions.x) / 2, window_height / 16));
                        algorithm_selected = "nb";
                    }
                    if (visualization_text.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))) {
                        visualizing = !visualizing;
                    }
                }
            }
            if (!visualizing) {
                if (event.type == sf::Event::TextEntered) { // Detects for alphanumeric input
                    if (event.text.unicode == '\b') { // If user presses backspace the last character is deleted
                        if (input_string[input_string.size() - 1] == '\n') {
                            input_string = input_string.substr(0, input_string.size() - 2);
                        }
                        else {
                            input_string = input_string.substr(0, input_string.size() - 1);
                        }
                    }
                    else if (event.text.unicode < 128) { // If user enters alphanumeric characters or symbols they are appended to the input string
                        input_string += static_cast<char>(event.text.unicode);
                    }
                    set_input_text(input_text, input_string); // User input text position is updated on the screen
                }
                if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Return) { // Detects if user presse "Return" or "Enter"
                    std::string command = "python " + algorithm_path + " " + algorithm_selected + " " + input_string; // Sets the command which is about to be run
                    std::array<char, 128> buffer; // Creates a buffer to capture program output
                    std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(command.c_str(), "r"), _pclose); // Runs python script to evaluate the input text and captures program output
                    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
                        sentiment_score_string = buffer.data(); // Sets the sentiment score to the program's output
                    }
                    sentiment_score_text.setString(sentiment_score_string); // Updates sentiment score
                    sentiment_score_text.setOrigin(sentiment_score_text.getLocalBounds().left + sentiment_score_text.getLocalBounds().width / 2.0f, sentiment_score_text.getLocalBounds().top + sentiment_score_text.getLocalBounds().height / 2.0f);

                    previous_phrase.setString(input_string); // Updates current phrase being scored
                    input_string = "";
                    set_input_text(input_text, input_string); // Updates the input text to be an empty string again
                }
            }
            else {
                if (event.type == sf::Event::MouseButtonPressed) { // Detects for mouse clicks
                    if (event.mouseButton.button == sf::Mouse::Left) { // Switches sentiment selection depending on option the user clicks
                        if (positive_text.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))) {
                            sentiment_button.setPosition(sf::Vector2f((window_width - button_dimensions.x) / 8, 7 * window_height / 16));
                            sentiment_selected = "positive";
                        }
                        if (negative_text.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))) {
                            sentiment_button.setPosition(sf::Vector2f(7 * (window_width - button_dimensions.x) / 8, 7 * window_height / 16));
                            sentiment_selected = "negative";
                        }
                    }
                }
                if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Return) { // Detects if user presse "Return" or "Enter"
                    if (algorithm_selected == "nb") { // Generates word cloud for the user based on the options selected
                        if (sentiment_selected == "positive") {
                            system("python visuals/visualize_positive_nb.py");
                        }
                        else {
                            system("python visuals/visualize_negative_nb.py");
                        }
                    }
                    else {
                        if (sentiment_selected == "positive") {
                            system("python visuals/visualize_positive_simple.py");
                        }
                        else {
                            system("python visuals/visualize_negative_simple.py");
                        }
                    }
                    
                }
            }
        }

        // Draws all of the text elements onto the screen
        update_program(window, visualizing, text_entry, text_entered, button, visuals_button, sentiment_button, instructions_text, input_text, score_notification, previous_phrase, sentiment_score_text, simple_algorithm, naive_bayes_algorithm, visualization_text, positive_text, negative_text, wordcloud_text);
    }
    return 0;
}