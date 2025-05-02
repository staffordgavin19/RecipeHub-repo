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
    bool insideRecipe = false;
    string title, ingredients, instructions;

    if (file.is_open()) {
        cout << "\nSaved Recipes:\n";
        while (getline(file, line)) {
            if (line == "### RECIPE START ###") {
                insideRecipe = true;
                title = ingredients = instructions = "";
            }

            else if (line.find("Title: ") == 0) {
                title = line.substr(7);
            }
            else if (line.find("Ingredients: ") == 0) {
                ingredients = line.substr(13);
            }
            else if (line.find("Instructions: ") == 0) {
                instructions = line.substr(14);
            }
            else if (line == "### RECIPE END ###" && insideRecipe) {
                Recipe r(title, ingredients, instructions);
                r.displayRecipe();
                insideRecipe = false;
            }

        }
        file.close();
    } else {
        cout << "No recipes found.\n";
    }
}

void deleteRecipe(const string& titleToDelete) {
    ifstream inFile("recipes.txt");
    ofstream tempFile("temp.txt");

    string line;
    bool insideRecipe = false;
    bool recipeFound = false;
    string currentRecipeBlock = "";
    string currentTitle = "";

    while (getline(inFile, line)) {
        if (line == "### RECIPE START ###") {
            insideRecipe = true;
            currentRecipeBlock = line + "\n";
            currentTitle = "";
        }
        else if (insideRecipe && line.find("Title: ") == 0) {
            currentTitle = line.substr(7);
            currentRecipeBlock += line + "\n";
        }
        else if (insideRecipe) {
            currentRecipeBlock += line + "\n";
            if (line == "### RECIPE END ###") {
                insideRecipe = false;
                if (currentTitle == titleToDelete) {
                    recipeFound = true;
                } else {
                    tempFile << currentRecipeBlock;
                }
                currentRecipeBlock = "";
            }
        }
        else {
            tempFile << line << "\n";
        }
    }

    inFile.close();
    tempFile.close();

    remove("recipes.txt");
    rename("temp.txt", "recipes.txt");
    if (recipeFound) {
        cout << "Recipe \"" << titleToDelete << "\" deleted successfully.\n";
    } else {
        cout << "Recipe not found.\n";
    }
}

void searchRecipes(const string& keyword) {
    ifstream file("recipes.txt");
    string line;
    string title, ingredients, instructions;
    bool insideRecipe = false;
    bool found = false;

    while (getline(file, line)) {
        if (line == "### RECIPE START ###") {
            insideRecipe = true;
            title = ingredients = instructions = "";
        }
        else if (insideRecipe && line.find("Title: ") == 0) {
            title = line.substr(7);
        }
        else if (insideRecipe && line.find("Ingredients: ") == 0) {
            ingredients = line.substr(13);
        }
        else if (insideRecipe && line.find("Instructions: ") == 0) {
            instructions = line.substr(13);
        }
        else if (line == "### RECIPE END ###") {
            insideRecipe = false;

            if (title.find(keyword) != string::npos ||
                ingredients.find(keyword) != string::npos ||
                instructions.find(keyword) != string::npos) {
                
                Recipe recipe(title, ingredients, instructions);
                recipe.displayRecipe();
                found = true;
            }
        }
    }

    if (!found)
        cout << "No recipes found with that keyword.\n";

    file.close();
}

void editRecipe(const string& titleToEdit) {
    ifstream inFile("recipes.txt");
    ofstream tempFile("temp.txt");

    string line;
    string title, ingredients, instructions;
    bool insideRecipe = false;
    bool edited = false;

    while (getline(inFile, line)) {
        if (line == "### RECIPE START ###") {
            insideRecipe = true;
            tempFile << line << "\n";
        }
        else if (insideRecipe && line.find("Title: ") == 0) {
            title = line.substr(7);
            if (title == titleToEdit) {
                cout << "Enter new ingredients: ";
                getline(cin, ingredients);
                cout << "Enter new instructions: ";
                getline(cin, instructions);

                tempFile << "Title: " << title << "\n";
                tempFile << "Ingredients: " << ingredients << "\n";
                tempFile << "Instructions: " << instructions << "\n";
                edited = true;

                getline(inFile, line);
                getline(inFile, line);
            } else {
                tempFile << line << "\n";
            }
        }
        else {
            tempFile << line << "\n";
            if (line == "### RECIPE END ###") {
                insideRecipe = false;
            }
        }
    }

    inFile.close();
    tempFile.close();

    remove("recipes.txt");
    rename("temp.txt", "recipes.txt");

    if (edited)
        cout << "Recipe \"" << titleToEdit << "\" updated successfully.\n";
    else
        cout << "Recipe not found.\n";
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
