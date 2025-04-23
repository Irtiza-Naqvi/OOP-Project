#include<iostream>
#include "RecipeManager.h"
using namespace std;

int main (){
    RecipeManager rm1;
    int choice;

    do
    {
        cout << "---------------Recipe Organizer & Meal Planner---------------" << endl;
        cout << "1. Add Recipe" << endl;
        cout << "2. View all Recipes" << endl;
        cout << "3. Search a Recipe by name" << endl;
        cout << "4. Delete a Recipe" << endl;
        cout << "5. Edit a Recipe" << endl;
        cout << "6. Exit Program" << endl;
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                rm1.addRecipe();
                break;
            case 2:
                rm1.displayAllRecipes();
                break;
            
            case 3:
                rm1.deleteRecipe();
                break;
            case 4:
                rm1.searchRecipeByName();
                break;
            case 5:
                rm1.editRecipe();
                break;
            case 6:
                cout << "Exiting Program..." << endl;
                break;
            default:
                cout << "Invaid Choice." << endl;
        }
    } while (choice != 6);
    

    return 0;
}