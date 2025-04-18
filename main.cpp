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
    cout << "\n====== RecipeHub - Main Menu ======\n";
    cout << "1. Add Recipe\n";
    cout << "2. View All Recipes\n";
    cout << "3. Delete Recipe\n";
    cout << "4. Search Recipes\n";
    cout << "5. Edit Recipe\n";
    cout << "6. Exit\n";
    cout << "Choose an option: ";
}

void viewRecipes() {
    ifstream file("recipes.txt");
    string line;
    int lineCount = 0;

    if (file.is_open()) {
        cout << "\n📖 Saved Recipes:\n";
        while (getline(file, line)) {
            if (line == "---") {
                cout << "----------------------------\n";
                lineCount = 0;
                continue;
            }

            if (lineCount == 0)
                cout << "Title: " << line << "\n";
            else if (lineCount == 1)
                cout << "Ingredients: " << line << "\n";
            else if (lineCount == 2)
                cout << "Instructions: " << line << "\n";

            lineCount++;
        }
        file.close();
    } else {
        cout << "No recipes found.\n";
    }
}

void deleteRecipe(const string& titleToDelete) {
    ifstream inFile("recipes.txt");
    ofstream tempFile("temp.txt");

    string title, ingredients, instructions, separator;
    bool deleted = false;

    while (getline(inFile, title)) {
        getline(inFile, ingredients);
        getline(inFile, instructions);
        getline(inFile, separator);

        if (title != titleToDelete) {
            tempFile << title << "\n" << ingredients << "\n" << instructions << "\n" << separator << "\n";
        } else {
            deleted = true;
        }
    }

    inFile.close();
    tempFile.close();

    remove("recipes.txt");
    rename("temp.txt", "recipes.txt");

    if (deleted) {
        cout << "Recipe \"" << titleToDelete << "\" deleted successfully.\n";
    } else {
        cout << "Recipe not found.\n";
    }
}

void searchRecipes(const string& keyword) {
    ifstream file("recipes.txt");
    string title, ingredients, instructions, separator;
    bool found = false;

    while (getline(file, title)) {
        getline(file, ingredients);
        getline(file, instructions);
        getline(file, separator);

        if (title.find(keyword) != string::npos ||
            ingredients.find(keyword) != string::npos ||
            instructions.find(keyword) != string::npos) {

            Recipe r(title, ingredients, instructions);
            r.displayRecipe();
            found = true;
        }
    }
    
    if (!found)
        cout << "No recipes found with that keyword.\n";

    file.close();
}

void editRecipe(const string& titleToEdit) {
    ifstream inFile("recipes.txt");
    ofstream tempFile("temp.txt");

    string title, ingredients, instructions, separator;
    bool edited = false;

    while (getline(inFile, title)) {
        getline(inFile, ingredients);
        getline(inFile, instructions);
        getline(inFile, separator);

        if (title == titleToEdit) {
            cout << "Editing Recipe: " << title << endl;
            cout << "Enter new title (or press Enter to keep the same): ";
            string newTitle;
            getline(cin, newTitle);
            if (!newTitle.empty()) title = newTitle;

            cout << "Enter new ingredients (or press Enter to keep the same): ";
            string newIngredients;
            getline(cin, newIngredients);
            if (!newIngredients.empty()) ingredients = newIngredients;

            cout << "Enter new instructions (or press Enter to keep the same): ";
            string newInstructions;
            getline(cin, newInstructions);
            if (!newInstructions.empty()) instructions = newInstructions;

            edited = true;
        }

        tempFile << title << "\n" << ingredients << "\n" << instructions << "\n" << separator << "\n";
    }

    inFile.close();
    tempFile.close();

    remove("recipes.txt");
    rename("temp.txt", "recipes.txt");

    if (edited) {
        cout << "Recipe \"" << titleToEdit << "\" has been edited successfully.\n";
    } else {
        cout << "Recipe not found.\n";
    }
}

void backupRecipes() {
    ifstream inFile("recipes.txt");
    ofstream backupFile("recipes_backup.txt");

    if (!inFile || !backupFile) {
        cout << "Error: Unable to perform backup.\n";
        return;
    }

    string line;
    while (getline(inFile, line)) {
        backupFile << line << endl;
    }

    cout << "Recipes backed up successfully.\n";
    inFile.close();
    backupFile.close();
}

void restoreRecipes() {
    ifstream backupFile("recipes_backup.txt");
    ofstream inFile("recipes.txt");

    if (!backupFile || !inFile) {
        cout << "Error: Unable to restore from backup.\n";
        return;
    }

    string line;
    while (getline(backupFile, line)) {
        inFile << line << endl;
    }

    cout << "Recipes restored successfully.\n";
    backupFile.close();
    inFile.close();
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
        else if (choice == 3) {
            string titleToDelete;
            cout << "Enter the title of the recipe to delete: ";
            getline(cin, titleToDelete);
            deleteRecipe(titleToDelete);
        }
        else if (choice == 4) {
            string keyword;
            cout << "Enter keyword to search: ";
            getline(cin, keyword);
            searchRecipes(keyword);
        }
        else if (choice == 5) {
            string titleToEdit;
            cout << "Enter the title of the recipe to edit: ";
            getline(cin, titleToEdit);
            editRecipe(titleToEdit);
        }
        else if (choice != 6) {
            cout << "\n*** Invalid choice. Please try again. ***\n";
        }
    } while (choice != 6);

    cout << "Exiting RecipeHub. Goodbye!\n";
    return 0;
}
