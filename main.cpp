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
            cout << "\n===============================" << endl;
            cout << "        Recipe: " << title << endl;
            cout << "-------------------------------" << endl;
            cout << "Ingredients: " << endl;
            cout << ingredients << endl;
            cout << "-------------------------------" << endl;
            cout << "Instructions: " << endl;
            cout << instructions << endl;
            cout << "===============================" << endl;
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
    cout << "\n===============================" << endl;
    cout << "           RecipeHub Menu       " << endl;
    cout << "===============================" << endl;
    cout << "1. Add Recipe" << endl;
    cout << "2. View Recipes" << endl;
    cout << "3. Exit" << endl;
    cout << "===============================" << endl;
    cout << "Enter your choice: ";
}

void viewRecipes() {
    ifstream file("recipes.txt");
    string line;
    if (file.is_open()) {
        cout << "\n===============================" << endl;
        cout << "        Saved Recipes          " << endl;
        cout << "===============================" << endl;
        while (getline(file, line)) {
            if (line.find("### RECIPE START ###") != string::npos) {
                cout << "\n------------------------\n";
            }
            cout << line << endl;
        }
        cout << "===============================" << endl;
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
        else if (choice != 3) {
            cout << "\n*** Invalid choice. Please try again. ***\n";
        }
    } while (choice != 3);

    cout << "Exiting RecipeHub. Goodbye!\n";
    return 0;
}
