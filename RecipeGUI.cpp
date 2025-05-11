#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Recipe Organizer");
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cout << "Failed to load font\n";
        return 1;
    }

    sf::Text title("Recipe Organizer", font, 36);
    title.setPosition(200, 30);
    title.setFillColor(sf::Color::Black);

    std::string labels[6] = {
        "Add Recipe",
        "View Recipes",
        "Search Recipe",
        "Edit Recipe",
        "Delete Recipe",
        "Exit"
    };

    sf::RectangleShape buttons[6];
    sf::Text buttonTexts[6];

    for (int i = 0; i < 6; i++) {
        buttons[i].setSize(sf::Vector2f(300, 50));
        buttons[i].setPosition(250, 100 + i * 70);
        buttons[i].setFillColor(sf::Color(100, 100, 255));

        buttonTexts[i].setFont(font);
        buttonTexts[i].setString(labels[i]);
        buttonTexts[i].setCharacterSize(24);
        buttonTexts[i].setFillColor(sf::Color::White);
        buttonTexts[i].setPosition(270, 110 + i * 70);
    }

    bool recipeAdded = false;
    sf::Text statusText("", font, 20);
    statusText.setPosition(200, 530);
    statusText.setFillColor(sf::Color::Red);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mouse = sf::Mouse::getPosition(window);
                for (int i = 0; i < 6; i++) {
                    if (buttons[i].getGlobalBounds().contains((float)mouse.x, (float)mouse.y)) {
                        if (i == 0) {
                            std::cout << "Add Recipe clicked!\n";
                            recipeAdded = true;
                            statusText.setString("Recipe added! Options unlocked.");
                        }
                        else if (i == 5) {
                            window.close();
                        }
                        else if (!recipeAdded) {
                            statusText.setString("Please add a recipe first.");
                        } else {
                            std::cout << labels[i] << " clicked!\n";
                            statusText.setString(labels[i] + std::string(" is selected."));
                        }
                    }
                }
            }
        }

        window.clear(sf::Color::White);
        window.draw(title);
        for (int i = 0; i < 6; i++) {
            window.draw(buttons[i]);
            window.draw(buttonTexts[i]);
        }
        window.draw(statusText);
        window.display();
    }

    return 0;
}