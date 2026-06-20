#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <cctype>

using namespace std;

class GroceryTracker {
private:
    map<string, int> itemFrequency;
    map<string, string> displayNames;

    string ToLower(string text) const {
        for (int i = 0; i < text.length(); ++i) {
            text[i] = static_cast<char>(tolower(text[i]));
        }
        return text;
    }

    bool IsValidMenuChoice(string input) const {
        if (input.length() != 1) {
            return false;
        }

        return input[0] >= '1' && input[0] <= '4';
    }

public:
    bool LoadInputFile(string fileName) {
        ifstream inputFile(fileName);
        string item;

        if (!inputFile.is_open()) {
            cout << "Error: Could not open " << fileName << endl;
            cout << "Make sure the input file is inside the project folder." << endl;
            return false;
        }

        while (inputFile >> item) {
            string key = ToLower(item);

            if (displayNames.find(key) == displayNames.end()) {
                displayNames[key] = item;
            }

            itemFrequency[key]++;
        }

        inputFile.close();
        return true;
    }

    void CreateBackupFile(string fileName) const {
        ofstream outputFile(fileName);

        if (!outputFile.is_open()) {
            cout << "Error: Could not create " << fileName << endl;
            return;
        }

        for (map<string, int>::const_iterator it = itemFrequency.begin(); it != itemFrequency.end(); ++it) {
            string key = it->first;
            int count = it->second;

            outputFile << displayNames.at(key) << " " << count << endl;
        }

        outputFile.close();
    }

    void SearchItem() const {
        string item;

        cout << "Enter the item you wish to search for: ";
        getline(cin, item);

        string key = ToLower(item);

        if (itemFrequency.find(key) != itemFrequency.end()) {
            cout << displayNames.at(key) << " appears " << itemFrequency.at(key) << " time(s)." << endl;
        }
        else {
            cout << item << " was not found in the grocery records." << endl;
        }
    }

    void PrintFrequencyList() const {
        cout << endl;
        cout << "Item Frequency List" << endl;
        cout << "-------------------" << endl;

        for (map<string, int>::const_iterator it = itemFrequency.begin(); it != itemFrequency.end(); ++it) {
            string key = it->first;
            int count = it->second;

            cout << displayNames.at(key) << " " << count << endl;
        }
    }

    void PrintHistogram() const {
        cout << endl;
        cout << "Item Frequency Histogram" << endl;
        cout << "------------------------" << endl;

        for (map<string, int>::const_iterator it = itemFrequency.begin(); it != itemFrequency.end(); ++it) {
            string key = it->first;
            int count = it->second;

            cout << displayNames.at(key) << " ";

            for (int i = 0; i < count; ++i) {
                cout << "*";
            }

            cout << endl;
        }
    }

    void DisplayMenu() {
        string userInput;
        int choice = 0;

        do {
            cout << endl;
            cout << "Corner Grocer Item Tracking Menu" << endl;
            cout << "--------------------------------" << endl;
            cout << "1. Search for an item" << endl;
            cout << "2. Display all item frequencies" << endl;
            cout << "3. Display item histogram" << endl;
            cout << "4. Exit" << endl;
            cout << "Enter your choice: ";

            getline(cin, userInput);

            if (!IsValidMenuChoice(userInput)) {
                cout << "Invalid option. Please enter a number from 1 to 4." << endl;
                continue;
            }

            choice = userInput[0] - '0';

            switch (choice) {
            case 1:
                SearchItem();
                break;

            case 2:
                PrintFrequencyList();
                break;

            case 3:
                PrintHistogram();
                break;

            case 4:
                cout << "Thank you for using the Corner Grocer tracking program." << endl;
                break;

            default:
                cout << "Invalid option. Please enter a number from 1 to 4." << endl;
                break;
            }

        } while (choice != 4);
    }
};

int main() {
    GroceryTracker tracker;

    if (tracker.LoadInputFile("CS210_Project_Three_Input_File.txt")) {
        tracker.CreateBackupFile("frequency.dat");
        tracker.DisplayMenu();
    }

    return 0;
}