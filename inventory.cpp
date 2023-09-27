/** 
 * Name: Dallon Jarman
 * Student ID: dmj296
 * Class: CYB136
 * Assignment #: 2
 * Project Name: Inventory Management
 * Purpose: This purpose of this project is to create a 
 * inventory management system using everything I've learned so far
*/

/**
 * RECOMMEND WAY TO COMPILE
 * g++ -Wall -Wextra -std=c++11 inventory.cpp -o Inventory
 * ./Inventory
 */

// header files
#include <iostream>
#include <string>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <iomanip>
#include <functional>

// removes the need of using "std::"
using namespace std;


// Define the InventoryItem class to hold information about each item in the inventory
class InventoryItem 
{

public:
    InventoryItem(const string& name, int quantity, double price) :
        m_name(name), m_quantity(quantity), m_price(price) {}

    // getters
        // this will get and return the name of the item
    const string& getName() const 
    {
        return m_name;
    }

    // this will get and return the quantity of the item
    int getQuantity() const 
    {
        return m_quantity;
    }

    // this will get and return the price of the item
    double getPrice() const 
    {
        return m_price;
    }

    // this is how you will set the quantity of an item
    void setQuantity(int quantity) 
    {
        m_quantity = quantity;
    }

    // this is how you set the price of an item
    void setPrice(double price) 
    {
        m_price = price;
    }

    // operator
    bool operator==(const InventoryItem& other) const 
    {
        return m_name == other.m_name && m_quantity == other.m_quantity && m_price == other.m_price;
    }

// Initalizes private variables
private:
    string m_name;
    int m_quantity;
    double m_price;
};

// Define the InventoryManager class to manage the inventory
class InventoryManager 
{

public:
    InventoryManager() {}

    // Adds an item to the inventory
    void addInventoryItem(const InventoryItem& item) 
    {
        m_inventorySet.insert(item);
    }

    // Removes an item from the inventory
    void removeInventoryItem(const string& itemName) 
    {
        for (auto it = m_inventorySet.begin(); it != m_inventorySet.end(); it++) 
        {
            if (it->getName() == itemName) {
                m_inventorySet.erase(it);
                break;
            }
        }
    }

    // Finds a certain item in the inventory
    const InventoryItem* findInventoryItem(const string& itemName) const 
    {
        for (auto it = m_inventorySet.cbegin(); it != m_inventorySet.cend(); it++) 
        {
            cout << it->getName();
            if (it->getName() == itemName) 
            {
                cout << "a";
                return &(*it);
            }
        }
        cout << "b";
        return nullptr;
    }

    // Display the current inventory
    void displayInventory() const 
    {
        cout << "Current Inventory: " << endl;
        for (auto it = m_inventorySet.begin(); it != m_inventorySet.end(); it++) 
        {
            cout << it->getName() << " | Quantity: " << it->getQuantity() << " | Price: " << it->getPrice() << endl;
        }
    }

// Initalizes private variables
private:
    // Define a hash function for the InventoryManager class
    struct InventoryItemHash 
    {
        size_t operator()(const InventoryItem& item) const 
        {
            return hash<string>()(item.getName()) ^ hash<double>()(item.getPrice());
        }
    };

    unordered_set<InventoryItem, InventoryItemHash> m_inventorySet;
};

/*
Name: printInventoryTable
Process: Prints the Inventory in a nice fancy table
Function Input/Parameters: inventory
Function Output/Parameters: none
Function Output/Returned: area
Device Input/Keyboard: none
Device Output/Monitor: none
Dependencies: none
*/
void printInventoryTable(const unordered_map<string, InventoryItem>& inventory) 
{
    // Print the table header
    cout << left << setw(20) << "Product Name" << setw(10) << "Quantity" << setw(10) << "Price" << endl;
    cout << setfill('-') << setw(40) << "" << setfill(' ') << endl;

    // Print each item in the inventory
    for (const auto& item : inventory) 
    {
        cout << left << setw(20) << item.second.getName() << setw(10) << item.second.getQuantity()
                             << setw(10) << item.second.getPrice() << endl;
    }
}

/*
Name: findProduct
Process: Allows the user to find a product when their inventory starts to get large
Function Input/Parameters: product, inventoryMap
Function Output/Parameters: none
Function Output/Returned: area
Device Input/Keyboard: none
Device Output/Monitor: none
Dependencies: none
*/
void findProduct ( string product, const unordered_map<string, InventoryItem>& inventoryMap) 
{

    // Finds if the product does exist within the map
    const auto it = inventoryMap.find(product);

    // Gets the product and prints the quantity and price of the product
    if (it != inventoryMap.end()) 
    {
        // Get the associated InventoryItem object
        const InventoryItem& item = it->second;

        // Prints the quantity and price of the object
        cout << "The quantity is " << item.getQuantity() << "\n";
        cout << "This price is $" << item.getPrice() << "\n\n";
    } 
    else 
    {
        // Prints a message if the product could not be found
        cout << "Item not found.\n\n";
    }
}

/*
Name: changeValues
Process: allows the user to change values of their inventory
Function Input/Parameters: raproduct, quantity, price, InventoryMap
Function Output/Parameters: none
Function Output/Returned: area
Device Input/Keyboard: none
Device Output/Monitor: none
Dependencies: none
*/

void changeValues ( const string product, int quantity, double price, unordered_map<string, InventoryItem>& inventoryMap ) 
{
    
    auto it = inventoryMap.find(product);
    if (it != inventoryMap.end()) 
    {
        inventoryMap.erase(it);
        inventoryMap.insert({product, InventoryItem(product, quantity, price)});
        cout << product << " has been changed.\n\n";
    }
    else 
    {
       cout << product << " is not in the inventory.\n\n"; 
    }
    
    
}

/*
Name: addProducts
Process: adds products to the inventory
Function Input/Parameters: num, inventoryMap
Function Output/Parameters: none
Function Output/Returned: area
Device Input/Keyboard: none
Device Output/Monitor: none
Dependencies: none
*/
void addProducts( int num, unordered_map<string, InventoryItem>& inventoryMap ) 
{
    // initalize variables
    string products;
    int quantity;
    double price;
    string addAnother = "yes";

    for ( auto i = 0; i < num; i++) 
    {
    // Allows user to add a product to inventory
        cout << "Name of the product would you like to add: ";
        cin >> ws;
        getline(cin, products);

        // checks to see if the product already exists in the inventory
        auto it = inventoryMap.find(products);
        if (it != inventoryMap.end()) 
        {
            cout << endl;
            cout << products << " is already in the inventory." << endl;
            cout << endl;
            break;
        }

        // Allows user to add the quantity of the product
        cout << "How many " << products << "'s do you have?: ";

        cin.clear();

        while (!(cin >> quantity) || cin.peek() != '\n') 
        {
            cout << "Invalid input. Please enter a valid number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }


        // Allows the user to add a price to the product
        cout << "How much do these " << products << "'s cost: $";
        
        cin.clear();

        while (!(cin >> price)) 
        {
        cout << "Invalid input. Please enter a valid number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }


        cout << endl;

        // Adds the product to the map
        inventoryMap.insert(
            {
                products, InventoryItem(products, quantity, price)
            });

        auto item = inventoryMap.begin();

        cout << item->second.getQuantity() << " " << item->second.getName() << "'s" << " with a price of $" << 
                                item->second.getPrice() << " was added to inventory" << endl;
        cout << endl;

    }
}

/*
Name: removeProduct
Process: removed a product from the inventory
Function Input/Parameters: productName, inventoryMap
Function Output/Parameters: none
Function Output/Returned: area
Device Input/Keyboard: none
Device Output/Monitor: none
Dependencies: none
*/

void removeProduct(const string& productName, unordered_map<string, InventoryItem>& inventoryMap) 
{
    auto it = inventoryMap.find(productName);
    if (it != inventoryMap.end()) 
    {
        inventoryMap.erase(it);
        cout << productName << " has been removed from the inventory.\n\n";
    }
    else 
    {
        cout << productName << " is not in the inventory.\n\n";
    }
}

// Prints the program title
void title() 
{
    cout << endl << "Welcome to Dallon's Inventory Management System" << endl;
    cout << "This mangement system allows users to keep track of items inside their store" << endl;
    cout << "You may add or remove products, change the quantity, and change the price of any time" << endl;
    cout << endl;
}

int main() 
{

    // initalize variables
    int productNum, quantity, nextStep = 0;
    double price;
    string product, printStatement;

    // Prints title
    title();

    // Creates an InventoryManager object
    InventoryManager manager;

    // Create an unordered map of InventoryItem objects
    unordered_map<string, InventoryItem> inventoryMap;

    // Ask the user for their next steps
    do 
    {
        
        // Lists of all the next steps the user can take
        cout << "Please type the following number for your next steps" << endl;
        cout << endl;
        cout << "1. Add more products" << endl;
        cout << "2. Remove a product" << endl;
        cout << "3. Change a value in a product" << endl;
        cout << "4. Print out the product list" << endl;
        cout << "5. Find a product" << endl;
        cout << "6. End program" << endl;

        // Allows the user to select their next step
        cout << "Type a number above: ";


        // Starts while loop to keep program running until user types in correct input       
        while (true) 
        {

            
            // This will ask the user for a int input until an integer input is given
            if (!(cin >> nextStep) || cin.peek() != '\n') 
            {
                cout << "Invalid input. Please enter a valid number (1-6): ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            // Checks to see if the number the user inputs is possible
            if (nextStep < 1 || nextStep > 6) 
            {
                cout << "Number out of range. ";
                cout << "Please enter a number between 1 and 6: ";
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }


        // Prints endline
        cout << endl;

        if ( nextStep == 1) 
        {
            // Asks the user how many items they would like to add 
            cout << "How many items would you like to add: ";


            // Failsafe if user inserts a word instead of a number
            while (!(cin >> productNum) || cin.peek() != '\n') 
            {
                cout << "Invalid input. Please enter a valid number: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            // calls the function addProducts to allow the user to add products
            addProducts(productNum, inventoryMap);
            

            
        }

        // Allows users to remove products
        else if ( nextStep == 2 ) 
        {

            // checks to see if there is product currently in the map
            bool noProduct = inventoryMap.empty();

            // If no product exists then it will print the users next step and leave the if statement
            if ( noProduct ) 
            {
                cout << "Please add a product before removing a product" << endl;
                cout << endl;
                continue;
            }

            // Allows the user to remove a product
            cout << "What product would you like to remove: ";
            cin >> ws;
            getline(cin, product);
            removeProduct( product, inventoryMap );
        }

        // Allows user to change the values of a product
        else if ( nextStep == 3 ) 
        {

            // checks to see if there is product currently in the map
            bool noProduct = inventoryMap.empty();

            // If no product exists then it will print the users next step and leave the if statement
            if ( noProduct ) 
            {
                cout << "Please add a product before changing the values of a product" << endl;
                cout << endl;
                continue;
            }

            // Allows the user to change parts of a product
            cout << "What product would you like to change: ";

            // Clears cin
            cin.clear();

            // If user enters in a invalid input it will nag the user till correct input is entered
            while (!(cin >> product)) 
            {
                cout << "Invalid input. Please enter a valid number: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            // Asks user for a new quantity
            cout << "What is the new quantity" << endl;

            // Clears cin
            cin.clear();

            // Nags user until valid input is given
            while (!(cin >> quantity)) 
            {
                cout << "Invalid input. Please enter a valid number: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            // Asks user for a new price
            cout << "What is the new price" << endl;

            // Clears cin
            cin.clear();

            // Nags user until correct input is given
            while (!(cin >> price)) 
            {
                cout << "Invalid input. Please enter a valid number: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            // Changes the value of the product
            changeValues(product, quantity, price, inventoryMap);
        }

        // Allows the user to print out a table of all the existing products
        else if ( nextStep == 4 ) 
        {
            // Prints the table of all your products
            printInventoryTable(inventoryMap);
            cout << endl;
        }

        // Allows the user to find a specific product
        else if ( nextStep == 5 ) 
        {

            // checks to see if there is product currently in the map
            bool noProduct = inventoryMap.empty();

            // If no product exists then it will print the users next step and leave the if statement
            if ( noProduct ) 
            {
                cout << "Please add a product before finding a product" << endl;
                cout << endl;
                continue;
            }

            // Asks the user for what product they would like to find
            cout << "What product would you like to find: ";
            cin >> ws;
            getline(cin, product);

            // calls the function and finds their product
            findProduct( product, inventoryMap );

        }

    // Ends whille loop when 6 is inserted
    } while ( nextStep != 6);


    // Return SUCCESS
    return 0;
}
