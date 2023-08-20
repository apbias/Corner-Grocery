/**************************************/
/*Student: Aaron Bias                 */
/*Class: CS 210 Programming Languages */
/*Date: 08/17/2023                    */
/**************************************/

#include <iostream>
#include <fstream>
#include <map>
#include <iomanip>
using namespace std;

//Class handles item frequencies (reading and writing to a file) and interactions with the user.
class GroceryManager {
private:
    map<string, int> itemFrequency;  // This container is the back bone of the Corner Grocery, defines a container that associates (or maps) keys to values.  

public:
    //Function to read input data from a file and populate a map
    void readDataFromFile(const string& filename, map<string, int>& itemFrequency) {
        ifstream inputFile(filename);

        //Error checking for opening input file
        if (!inputFile) {
            cerr << "Error opening file: " << filename << endl;
            exit(1);
        }

        string itemName;  //String variable to store item list in input file to help populate the map frequency

        while (inputFile >> itemName) { // >> extracts whitespace seperated words from the input stream
            itemFrequency[itemName]++; //Increments the frequency of the item 
        }

        inputFile.close();
    }

    //Prints the frequency of items, works with itemFrequency with a reference (&) so we dont create a copy 
    void printItemFrequency(const map<string, int>& itemFrequency) {
        for (const auto& pair : itemFrequency) {
            cout << pair.first << " " << pair.second << endl;
        }
    }

    //Prints the histogram of ItemFrequence with a reference (&), working with the original map and not creating a copy
    void printHistogram(const map<string, int>& itemFrequency) {

    //pair.first is the itenName while pair.second is the frequency, for loop will loop for each frequency of the item
        for (const auto& pair : itemFrequency) {
            cout << pair.first << " ";
            for (int i = 0; i < pair.second; ++i) {
                cout << "*";
            }
            cout << endl;
        }
    }

    //Writes item frequencies to a backup file, referencing the original filename and map container (itemFrequency)
    void writeBackupFile(const string& filename, const map<string, int>& itemFrequency) {
        ofstream backupFile(filename);

        //Error Checking
        if (!backupFile) {
            cerr << "Error opening file: " << filename << endl;
            exit(1);
        }
        //pair.first from map container (itemFrequency) is the name while pair.second is the frequency
        for (const auto& pair : itemFrequency) {
            backupFile << pair.first << " " << pair.second << endl;
        }

        backupFile.close();
    }
};

int main() {

    //Variable declarations
    const string inputFilename = "CS210_Project_Three_Input_File.txt"; //Test file with grocery items
    const string backupFilename = "frequency.dat";  //backup file, will write to file before exit from user input
    map<string, int> itemFrequency; //map container that maps keys to values
    int choice; //user input for Menu
    GroceryManager manager; //Creates a instance of GroceryManager to manage grocery item frequency

    //Reading data from the input file to populate the map
    manager.readDataFromFile(inputFilename, itemFrequency);  //itemFrequency is the map container that map keys to values

    //Do while loop for Main menu, will exit if user selects 4
    do {
        cout << "Corner Grocer Item Tracking Menu:" << endl;
        cout << "1. Search item" << endl;
        cout << "2. Print list with the item's frequencies" << endl;
        cout << "3. Print frequency information histogram" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your selection: ";
        cin >> choice;

        //Switch case to capture user input and execute function based on selection
        //Class file is GroceryManager
        switch (choice) {
        case 1: {
            string item;
            cout << "Enter item to find the frequency: ";
            cin >> item;
            cout << "Frequency of " << item << ": " << itemFrequency[item] << endl; //When we access an item name (string) in itemFrequency, it returns a reference to the integer associated with that item
            break;
        }
        case 2: {
            manager.printItemFrequency(itemFrequency);  //Calls printItemFrequency in GroceryManager Class
            break;
        }
        case 3: {
            manager.printHistogram(itemFrequency);   //Calls printHistogram in GroceryManager Class
            break;
        }
        case 4: {
            //Write data to backup file before exiting
            manager.writeBackupFile(backupFilename, itemFrequency);   //Calls writeBackupFile in GroceryManager Class
            cout << "Writing to backup file." << endl;
            break;
        }
        default: {
            cout << "Invalid choice. Try again" << endl;
            break;
        }
        }
    } while (choice != 4);

    return 0;
}
