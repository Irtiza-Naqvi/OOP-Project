#include "Recipe.h"
#include <iostream>
using namespace std;

Recipe::Recipe() {
    name = "";
    ingredientCount = 0;
    instructions = "";
}

Recipe::Recipe(string n, string ing[], int count, string ins) {
    name = n;
    ingredientCount = count;
    for (int i = 0; i < count; i++) {
        ingredients[i] = ing[i];
    }
    instructions = ins;
}

void Recipe::inputRecipe() {
    cout << "Enter the name of your recipe: ";
    cin.ignore();
    getline(cin, name);

    cout << "How many ingredients are in your recipe? (Maximum allowed ingredients are 10): ";
    cin >> ingredientCount;
    cin.ignore();

    for (int i = 0; i < ingredientCount; i++) {
        cout << "Ingredient " << i + 1 << ": ";
        getline(cin, ingredients[i]);
    }

    cout << "Enter instructions: ";
    getline(cin, instructions);
}

void Recipe::displayRecipe() {
    cout << "--------------The Given Recipe--------------" << endl;
    cout << "Recipe: " << name << endl;
    cout << "Ingredients:" << endl;
    for (int i = 0; i < ingredientCount; i++) {
        cout << "- " << ingredients[i] << endl;
    }
    cout << "Instructions: " << instructions << endl;
}

string Recipe::getName() {
    return name;
}
