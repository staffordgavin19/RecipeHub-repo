#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Recipe {
    public:
        string title;
        string ingredients;
        string instructions;

        Recipe(string t, string i, string instr) : title(t), ingredients(i), instructions(instr) {}

        void displayRecipe() {
            cout << "\nRecipe: " << title << "\n";
            cout << "Ingredients: " << ingredients << "\n";
            cout << "Instructions: " << instructions << "\n";
        }
};

void saveRecipe(const Recipe& recipe) {
    ofstream file("recipes.txt", ios::app);
    if (file.is_open()) {
        file << "### RECIPE START ###\n";
        file << "Title: " << recipe.title << "\n";
        file << "Ingredients: " << recipe.ingredients << "\n";
        file << "Instructions: " << recipe.instructions << "\n";
        file << "### RECIPE END ###\n\n";
        file.close();
        cout << "Recipe saved successfully!\n";
    } else {
        cout << "Error saving recipe.\n";
    }
}

void showMenu() {
    cout << "\nRecipeHub - Main Menu\n";
    cout << "1. Add Recipe\n";
    cout << "2. View Recipes\n";
    cout << "3. Exit\n";
    cout << "Enter your choice: ";
}

void viewRecipes() {
    ifstream file("recipes.txt");
    string line;
    if (file.is_open()) {
        cout << "\nSaved Recipes:\n";
        while (getline(file, line)) {
            if (line.find("### RECIPE START ###") != string::npos) {
                cout << "\n------------------------\n";
            }
            cout << line << endl;
        }
        file.close();
    } else {
        cout << "No recipes found.\n";
    }
}

int main() {
    int choice;
    do {
        showMenu();
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string title, ingredients, instructions;
            cout << "Enter recipe title: ";
            getline(cin, title);
            cout << "Enter ingredients: ";
            getline(cin, ingredients);
            cout << "Enter instructions: ";
            getline(cin, instructions);

            Recipe newRecipe(title, ingredients, instructions);
            saveRecipe(newRecipe);
        }
        else if (choice == 2) {
            viewRecipes();
        }
    } while (choice != 3);

    cout << "Exiting RecipeHub. Goodbye!\n";
    return 0;
}