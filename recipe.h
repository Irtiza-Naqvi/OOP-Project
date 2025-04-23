#pragma once
#include <string>
using namespace std;

class Recipe {
private:
    string name;
    string ingredients[10]; //max ingredients 10
    int ingredientCount;
    string instructions;

public:
    Recipe();

    Recipe(string n, string ing[], int count, string ins);

    virtual void inputRecipe();
    virtual void displayRecipe();
    string getName();
};
