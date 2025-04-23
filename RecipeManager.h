#include "recipe.h"
#include "DerivedRecipies.h"
#include <iostream>
using namespace std;

class RecipeManager {
private:
    Recipe* recipes[100];
    int count;

public:
    RecipeManager() {
        count = 0;
    }

    ~RecipeManager() {
        for (int i = 0; i < count; i++) {
            delete recipes[i];
        }
    }

    void addRecipe() {
        if (count >= 100) {
            cout << "The recipe list is full." << endl;
            return;
        }

        int type;
        cout << "Choose type of recipe:" << endl;
        cout << "1. Starter\n2. Main Course\n3. Dessert" << endl;
        cout << "Enter your choice: ";
        cin >> type;
        cin.ignore();

        Recipe* newRecipe = nullptr;

        if (type == 1) {
            newRecipe = new StarterRecipe();
        } else if (type == 2) {
            newRecipe = new MainCourseRecipe();
        } else if (type == 3) {
            newRecipe = new DessertRecipe();
        } else {
            cout << "Invalid choice." << endl;
            return;
        }

        newRecipe->inputRecipe();
        recipes[count] = newRecipe;
        count++;
        cout << "Recipe added successfully!" << endl;
    }

    void displayAllRecipes() {
        if (count == 0) {
            cout << "No recipes to display." << endl;
            return;
        }

        for (int i = 0; i < count; i++) {
            cout << "----- Recipe " << (i + 1) << " -----" << endl;
            recipes[i]->displayRecipe();
        }
    }

    void deleteRecipe() {
        if (count == 0) {
            cout << "No recipes to delete." << endl;
            return;
        }

        int index;
        cout << "Enter recipe number to delete (1 to " << count << "): ";
        cin >> index;

        if (index < 1 || index > count) {
            cout << "Invalid number entered." << endl;
            return;
        }

        delete recipes[index - 1];

        for (int i = index - 1; i < count - 1; i++) {
            recipes[i] = recipes[i + 1];
        }

        count--;
        cout << "Recipe deleted successfully." << endl;
    }

    void searchRecipeByName() {
        if (count == 0) {
            cout << "No recipes available to search." << endl;
            return;
        }

        string searchName;
        cout << "Enter the name of the recipe to search: ";
        cin >> searchName;
        cin.ignore();

        bool found = false;
        for (int i = 0; i < count; i++) {
            if (recipes[i]->getName() == searchName) {
                cout << "------ Found Recipe " << (i + 1) << " ------" << endl;
                recipes[i]->displayRecipe();
                found = true;
            }
        }

        if (!found) {
            cout << "Recipe with the name '" << searchName << "' not found." << endl;
        }
    }

    void editRecipe(){
        if (count == 0)
        {
            cout << "No recipies available to edit" << endl;
            return;
        }

        int index;
        cout << "Enter the recipe number to edit (1 to " << count << "): ";
        cin >> index;
        cin.ignore();
    
        if (index < 1 || index > count) {
            cout << "Invalid recipe number." << endl;
            return;
        }
    
        cout << "Editing Recipe " << index << ":" << endl;
        recipes[index - 1]->inputRecipe();
        cout << "Recipe updated successfully!" << endl;
    }
};
