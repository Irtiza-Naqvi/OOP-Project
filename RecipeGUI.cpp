#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace std;

struct Recipe {
    string name;
    int ingredientCount = 0;
    string ingredients[10];
    string instructions;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 700), "Recipe Organizer");

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        cout << "Failed to load font.\n";
        return 1;
    }

    sf::Text title("Recipe Organizer", font, 36);
    title.setPosition(300, 20);
    title.setFillColor(sf::Color::Black);

    string labels[6] = {"Add Recipe", "View Recipes", "Search Recipe", "Edit Recipe", "Delete Recipe", "Exit"};
    sf::RectangleShape buttons[6];
    sf::Text buttonTexts[6];

    for (int i = 0; i < 6; i++) {
        buttons[i].setSize(sf::Vector2f(300, 50));
        buttons[i].setPosition(350, 100 + i * 70);
        buttons[i].setFillColor(sf::Color(100, 100, 255));

        buttonTexts[i].setFont(font);
        buttonTexts[i].setString(labels[i]);
        buttonTexts[i].setCharacterSize(24);
        buttonTexts[i].setFillColor(sf::Color::White);
        buttonTexts[i].setPosition(370, 110 + i * 70);
    }

    Recipe recipes[100];
    int recipeCount = 0;
    bool recipeAdded = false;
    bool inputMode = false;
    bool viewMode = false;
    bool searchMode = false;
    bool editMode = false;
    bool deleteMode = false;

    Recipe newRecipe;
    int inputStep = 0;
    string currentInput = "";

    sf::Text prompt("", font, 24);
    prompt.setPosition(50, 550);
    prompt.setFillColor(sf::Color::Black);

    sf::Text inputField("", font, 24);
    inputField.setPosition(50, 590);
    inputField.setFillColor(sf::Color::Blue);

    sf::Text status("", font, 20);
    status.setPosition(50, 650);
    status.setFillColor(sf::Color::Red);

    string searchQuery = "";
    int editIndex = -1;
    int deleteIndex = -1;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if ((inputMode || searchMode || editMode || deleteMode) && event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b') {
                    if (!currentInput.empty())
                        currentInput.pop_back();
                } else if (event.text.unicode == '\r') {
                    if (inputMode) {
                        if (inputStep == 0) {
                            newRecipe.name = currentInput;
                            inputStep++;
                        } else if (inputStep == 1) {
                            try {
                                newRecipe.ingredientCount = stoi(currentInput);
                            } catch (...) {
                                status.setString("Invalid number!");
                                currentInput.clear();
                                continue;
                            }
                            if (newRecipe.ingredientCount < 1 || newRecipe.ingredientCount > 10) {
                                status.setString("Enter 1-10 ingredients.");
                                currentInput.clear();
                                continue;
                            }
                            inputStep++;
                        } else if (inputStep >= 2 && inputStep < 2 + newRecipe.ingredientCount) {
                            newRecipe.ingredients[inputStep - 2] = currentInput;
                            inputStep++;
                        } else {
                            newRecipe.instructions = currentInput;
                            recipes[recipeCount++] = newRecipe;
                            recipeAdded = true;
                            status.setString("Recipe added!");
                            inputMode = false;
                            inputStep = 0;
                            newRecipe = Recipe();
                        }
                        currentInput.clear();
                    } else if (searchMode) {
                        bool found = false;
                        for (int i = 0; i < recipeCount; i++) {
                            if (recipes[i].name == currentInput) {
                                status.setString("Found: " + recipes[i].name);
                                found = true;
                                break;
                            }
                        }
                        if (!found)
                            status.setString("Recipe not found.");
                        searchMode = false;
                        currentInput.clear();
                    } else if (editMode) {
                        try {
                            editIndex = stoi(currentInput) - 1;
                            if (editIndex < 0 || editIndex >= recipeCount) {
                                status.setString("Invalid index.");
                            } else {
                                newRecipe = recipes[editIndex];
                                inputMode = true;
                                inputStep = 0;
                                status.setString("Editing recipe...");
                            }
                        } catch (...) {
                            status.setString("Enter a valid number.");
                        }
                        editMode = false;
                        currentInput.clear();
                    } else if (deleteMode) {
                        try {
                            deleteIndex = stoi(currentInput) - 1;
                            if (deleteIndex < 0 || deleteIndex >= recipeCount) {
                                status.setString("Invalid index.");
                            } else {
                                for (int i = deleteIndex; i < recipeCount - 1; i++) {
                                    recipes[i] = recipes[i + 1];
                                }
                                recipeCount--;
                                status.setString("Recipe deleted.");
                            }
                        } catch (...) {
                            status.setString("Enter a valid number.");
                        }
                        deleteMode = false;
                        currentInput.clear();
                    }
                } else if (event.text.unicode < 128) {
                    currentInput += static_cast<char>(event.text.unicode);
                }
            }

            if (!inputMode && event.type == sf::Event::MouseButtonPressed) {
                auto mouse = sf::Mouse::getPosition(window);
                for (int i = 0; i < 6; i++) {
                    if (buttons[i].getGlobalBounds().contains((float)mouse.x, (float)mouse.y)) {
                        switch (i) {
                            case 0: // Add
                                inputMode = true;
                                inputStep = 0;
                                currentInput = "";
                                newRecipe = Recipe();
                                break;
                            case 1: // View
                                if (recipeAdded) viewMode = true;
                                else status.setString("Add a recipe first.");
                                break;
                            case 2: // Search
                                if (recipeAdded) {
                                    searchMode = true;
                                    currentInput = "";
                                    status.setString("Enter recipe name to search:");
                                } else status.setString("Add a recipe first.");
                                break;
                            case 3: // Edit
                                if (recipeAdded) {
                                    editMode = true;
                                    currentInput = "";
                                    status.setString("Enter recipe number to edit:");
                                } else status.setString("Add a recipe first.");
                                break;
                            case 4: // Delete
                                if (recipeAdded) {
                                    deleteMode = true;
                                    currentInput = "";
                                    status.setString("Enter recipe number to delete:");
                                } else status.setString("Add a recipe first.");
                                break;
                            case 5: // Exit
                                window.close();
                                break;
                        }
                    }
                }
            }

            if (viewMode && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                viewMode = false;
        }

        window.clear(sf::Color::White);

        if (viewMode) {
            sf::Text heading("Saved Recipes", font, 28);
            heading.setPosition(50, 30);
            heading.setFillColor(sf::Color::Black);
            window.draw(heading);

            for (int i = 0; i < recipeCount && i < 5; i++) {
                sf::Text recipeText;
                recipeText.setFont(font);
                recipeText.setCharacterSize(20);
                recipeText.setFillColor(sf::Color::Black);
                string info = to_string(i + 1) + ". " + recipes[i].name + "\nIngredients:\n";
                for (int j = 0; j < recipes[i].ingredientCount; j++) {
                    info += "- " + recipes[i].ingredients[j] + "\n";
                }
                info += "Instructions: " + recipes[i].instructions + "\n";
                recipeText.setString(info);
                recipeText.setPosition(50, 80 + i * 110);
                window.draw(recipeText);
            }

            sf::Text back("Press ESC to go back", font, 20);
            back.setPosition(50, 640);
            back.setFillColor(sf::Color::Red);
            window.draw(back);
        } else {
            window.draw(title);
            for (int i = 0; i < 6; i++) {
                window.draw(buttons[i]);
                window.draw(buttonTexts[i]);
            }

            if (inputMode || searchMode || editMode || deleteMode) {
                if (inputMode) {
                    if (inputStep == 0) prompt.setString("Enter recipe name:");
                    else if (inputStep == 1) prompt.setString("Enter number of ingredients:");
                    else if (inputStep < 2 + newRecipe.ingredientCount)
                        prompt.setString("Ingredient " + to_string(inputStep - 1) + ":");
                    else prompt.setString("Enter instructions:");
                }
                window.draw(prompt);
                inputField.setString(currentInput);
                window.draw(inputField);
            }

            window.draw(status);
        }

        window.display();
    }

    return 0;
}
