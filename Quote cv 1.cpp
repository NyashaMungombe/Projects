
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

// Quote class to represent a quote object.
class Quote
{
private:
    // Constants for cost calculations
    const double CARPET_COST_PER_M2 = 5;
    const double WOOD_COST_PER_M2 = 10;
    const double TILED_COST_PER_M2 = 15;

    const double CARPET_INSTALLATION_COST_PER_5_M2 = 50;
    const double WOOD_INSTALLATION_COST_PER_5_M2 = 75;
    const double TILED_INSTALLATION_COST_PER_5_M2 = 100;

    // Quote details
    double price;
    string material;
    double length;
    double width;

public:
    // Function to add details for a quote from user input
    void addquote()
    {
        cout << "Enter details for the chosen customer" << endl;

        cout << "Enter the length: ";
        cin >> length;

        cout << "Enter the width: ";
        cin >> width;

        cout << "Please enter the material, Carpet,wood or tile: ";
        cin >> material;
    }

    // Function to calculate the quote price
    void caluclateQuote()
    {
        addquote();

        if (material == "Carpet" || material == "carpet")
        {
            price = CARPET_COST_PER_M2 * length * width + CARPET_INSTALLATION_COST_PER_5_M2 * (length * width / 5.0);
        }
        else if (material == "Wood" || material == "wood")
        {
            price = WOOD_COST_PER_M2 * length * width + WOOD_INSTALLATION_COST_PER_5_M2 * (length * width / 5.0);
        }
        else if (material == "Tile" || material == "tile")
        {
            price = TILED_COST_PER_M2 * length * width + TILED_INSTALLATION_COST_PER_5_M2 * (length * width / 5.0);
        }
        else
        {
            cout << "Error: Invalid material type." << endl;
        }

        // Display total cost
        cout << "Total cost for " << material << " is: " << price << endl;
    }

    // Getter methods for quote details
    string getMaterial() // this method is allowing me acces to the variable material
    {
        return material;
    }

    double getLength()
    {
        return length;
    }

    double getWidth()
    {
        return width;
    }

    double getPrice()
    {
        return price;
    }

    // Display quote details
    void display()
    {
        cout << "Material: " << material << endl;
        cout << "Length: " << length << endl;
        cout << "Width: " << width << endl;
        cout << "Price: " << price << endl;
    }

    // Function to get data formatted for file storage
    string getDataForFile()
    {
        return material + " " + to_string(length) + " " + to_string(width) + " " + to_string(price);
    }

    // Function to load quote data from a file
    void loadDataFromFile(ifstream& file)
    {
        getline(file, material);
        cin.ignore(1000, '\n');

        file >> length;
        cin.ignore(1000, '\n'); //cin ignore used to remove unwanted characaters from input
        file >> width;
        cin.ignore(1000, '\n');
        file >> price;
        cin.ignore(1000, '\n');
    }
};

// Customer class representing a customer with multiple quotes
class Customer
{
private:
    string name;
    int phone;
    string address;
    vector<Quote> quotes; // Vector to store quotes, this sequentially stores data/quotes , more dynamic 

public:
    // Function to add customer details from user input
    void addCustomer()
    {
        cout << "Type in customer name: " << endl;
        cin >> name;


        cout << "Type in customer phone number: " << endl;
        cin >> phone;

        cout << "Type in customer address: " << endl;
        cin.ignore(1000, '\n');
        cin.clear(); //It allows the program to continue executing after an input error.
        getline(cin, address);

        cout << "After entering details, please proceed to option 2 to choose your desired material, and your price will be calculated." << endl;
    }

    // Function to add a quote for the customer
    void addQuote()
    {
        Quote quote;
        quote.caluclateQuote();
        quotes.push_back(quote);  //pushes elements to the back of vector, if new quote is entered it goes to the back
    }

    // Getter methods for customer details
    string getName()
    {
        return name;
    }

    int getphone()
    {
        return phone;
    }

    string getaddress()
    {
        return address;
    }

    vector<Quote> getQuotes()
    {
        return quotes;
    }

    // Display customer details and quotes
    void printquotes()
    {
        cout << "Customer Name: " << name << endl;
        cout << "Phone Number: " << phone << endl;
        cout << "Address: " << address << endl;

        int i = 1; //index
        for (auto& quote : quotes) // telling the program how many times(no of quotes ) it should run/iterate through
        {
            cout << "Quote " << i++ << endl; //iteration
            quote.display(); //calliing display function from qoute class
        }
    }

    // Function to edit customer details or update existing quotes
    void edit()
    {
        cout << "Type in new name: " << endl;
        cin.ignore(1000, '\n');
        cin.clear();
        getline(cin, name); //allows you to enter a full name

        cout << "Type in new phone number: " << endl;
        cin >> phone;

        cout << "Type in new address: " << endl;
        cin.ignore(1000, '\n');
        getline(cin, address);

        // Ask if the user wants to update or create a new quote
        cout << "Do you want to update the existing quote (Y/N)? ";
        char choice;
        cin >> choice;

        if (toupper(choice) == 'Y') // toupper converts a character to uppercase
        {
            // Update existing quote
            cout << "Choose a quote to update:" << endl;
            printquotes();

            int quoteIndex;
            cin >> quoteIndex;

            if (quoteIndex >= 1 && quoteIndex <= quotes.size())
            {
                // Call calculateQuote for the selected quote
                quotes[quoteIndex - 1].caluclateQuote();
            }
            else
            {
                cout << "Invalid quote index." << endl;
            }
        }
        else
        {
            // Create a new quote
            addQuote();
        }
    }

    // Function to load customer data from a file
    void loadDataFromFile(ifstream& file)
    {


        getline(file, name);
        cin.ignore(1000, '\n');
        file >> phone;
        cin.ignore(1000, '\n');
        file >> address;
        cin.ignore(1000, '\n');

        Quote quote;
        bool getquotes = true;

        while (getquotes)
        {
            quote.loadDataFromFile(file);
            quotes.push_back(quote);

            streampos oldpos = file.tellg();  // telg is used to get the current position of the file pointer in the file . This position is stored in a variable of type streampos.
            string checkEndOfRecord;
            getline(file, checkEndOfRecord);

            if (checkEndOfRecord == " ") //if file is empty
            {
                getquotes = false; //return false
            }
            else
            {
                file.seekg(oldpos);
            }
        }
    }
};

// Menu class controls the program running and holds a vector of customers
class Menu
{
private:
    vector<Customer> customers; // Vector to hold all the customers
    bool keepMenuGoing = true;

    // Function to print customer records
    void printcustomerVector()
    {
        for (int i = 0; i < customers.size(); i++)
        {
            cout << (i + 1) << " " << customers[i].getName() << endl;
        }
    }

    // Function to add a new customer
    void addNewcustomer()
    {
        Customer customer;
        customer.addCustomer();
        customers.push_back(customer);
    }

    // Function to add a new quote for a customer
    void addNewmaterial()
    {
        cout << "Add material for which customer?" << endl;
        printcustomerVector();

        int input;
        cin >> input;

        customers[input - 1].addQuote();
    }

    // Function to show customer details and quotes
    void showcustomer()
    {
        cout << "Pick customer to show details?" << endl;
        printcustomerVector(); //function called to print list of customers

        int input;
        cin >> input;

        customers[input - 1].printquotes();
    }

    // Function to edit customer details or update quotes
    void editcustomer()
    {
        cout << "Pick customer to edit details?" << endl;
        printcustomerVector();

        int input;
        cin >> input;

        customers[input - 1].edit();
    }

    // Function to write all the information to a file
    void writeToFile()
    {
        ofstream outPutFile;
        outPutFile.open("Quote Calculator for flooring company");

        for (int i = 0; i < customers.size(); i++)
        {
            outPutFile << customers[i].getName() << endl;
            outPutFile << customers[i].getphone() << endl;
            outPutFile << customers[i].getaddress() << endl;

            for (auto y : customers[i].getQuotes())
            {
                outPutFile << y.getDataForFile() << endl;
            }

            outPutFile << " ";

            if (i != (customers.size() - 1))
            {
                outPutFile << endl;
            }
        }
    }

    // Function to load data from a file
    void loadFromFile()
    {
        ifstream file;
        file.open("Quote Calculator for flooring company");

        if (file)
        {
            while (!file.eof())
            {
                Customer customer;
                customer.loadDataFromFile(file);
                customers.push_back(customer);
            }
        }
    }

    // Function to save and quit the program
    void saveAndQuit()
    {
        writeToFile();
        keepMenuGoing = false;
        cout << "Thank you for your time, and I look forward to helping you again" << endl;
    }

public:
    // Function to display the start menu
    void start()
    {
        loadFromFile();

        while (keepMenuGoing)
        {
            cout << "The flooring company quote calculator is here to assist you. Please choose an option:" << endl;
            cout << "1. Enter customer details" << endl;
            cout << "2. Choose material" << endl;
            cout << "3. Show customer" << endl;
            cout << "4. Edit customer details" << endl;
            cout << "5. Write to File" << endl;
            cout << "6. Load from file" << endl;
            cout << "7. Save and Quit" << endl;

            int input;
            cin >> input;

            switch (input)
            {
            case 1:
                addNewcustomer();
                break;
            case 2:
                addNewmaterial();
                break;
            case 3:
                showcustomer();
                break;
            case 4:
                editcustomer();
                break;
            case 5:
                writeToFile();
                break;
            case 6:
                loadFromFile();
                break;
            case 7:
                saveAndQuit();
                break;
            }
        }
    }
};

int main()
{
    // Initialize menu class
    Menu m;
    m.start(); // Start the menu
}
