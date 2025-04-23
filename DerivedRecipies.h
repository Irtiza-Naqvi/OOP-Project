#pragma once
#include "recipe.h"
#include <iostream>
using namespace std;

class StarterRecipe : public Recipe{
    private:
    string temperature;

    public:
    void inputRecipe() override {
        Recipe::inputRecipe();
        cout << "Enter serving temperature (Hot/Cold): ";
        cin >> temperature;
    }

    void displayRecipe() override {
        Recipe::displayRecipe();
        cout << "Serving Temperature: " << temperature << endl;
    }
};

class MainCourseRecipe : public Recipe {
    private:
        string spiceLevel;
    
    public:
        void inputRecipe() override {
            Recipe::inputRecipe();
            cout << "Enter spice level (Mild/Medium/Spicy): ";
            getline(cin, spiceLevel);
        }
    
        void displayRecipe() override {
            Recipe::displayRecipe();
            cout << "Spice Level: " << spiceLevel << endl;
        }
};

class DessertRecipe : public Recipe {
    private:
        string sweetnessLevel;
    
    public:
        void inputRecipe() override {
            Recipe::inputRecipe();
            cout << "Enter sweetness level (Low/Medium/High): ";
            getline(cin, sweetnessLevel);
        }
    
        void displayRecipe() override {
            Recipe::displayRecipe();
            cout << "Sweetness Level: " << sweetnessLevel << endl;
        }
};