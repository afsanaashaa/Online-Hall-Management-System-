#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

int main();

// Base class for payment
// Use of multifile
#include"payment.cpp"


// Derived class for bKash payment
class BkashPayment : public Payment
{
public:
    void processPayment(float amount) override
    {
        cout << "Processing bKash payment of " << amount << " taka." << endl;
    }
};


// Derived class for Cash on Delivery payment
class CashOnDeliveryPayment : public Payment
{
public:
    void processPayment(float amount) override
    {
        cout << "Processing Cash on Delivery payment of " << amount << " taka." << endl;
    }
};


// Derived class for Bank payment
class BankPayment : public Payment
{
public:
    void processPayment(float amount) override
    {
        cout << "Processing Bank payment of " << amount << " taka." << endl;
    }
};


// Base class for services
class Service
{
public:
    virtual void showMenu() = 0;
    virtual void placeOrder() = 0;
    virtual ~Service() {}
};


class user
{
private:
    string full_name;
    string username;
    string department;
    string class_id;
    string password;

public:
    user() {}

    void createNewAccount();
    bool isLoggedIn();
    void login();
};


class canteen : public Service
{
private:
    vector<int> product_num;
    vector<string> product_name;
    vector<float> prod_price;

public:
    void showMenu() override;
    void placeOrder() override;
    void getProductDetails();
};
canteen can;


class StoreService : public Service
{
private:
    vector<int> prod_num;
    vector<string> prod_name;
    vector<float> prodt_price;

public:
    void showMenu() override;
    void placeOrder() override;
    void productInfo();
};
StoreService store;


class VendingMachine : public Service
{
private:
    vector<int> product_vnum;
    vector<string> product_vname;
    vector<float> prodv_price;

public:
    void showMenu() override;
    void placeOrder() override;
    void vanProduct();
};

VendingMachine venMan;


class WashingMachine
{
private:
    int machineID;
    bool available;

public:
    WashingMachine(int id) : machineID(id), available(true) {}

    int getMachineID() const
    {
        return machineID;
    }

    bool isAvailable() const
    {
        return available;
    }

    void startWash()
    {
        if (available)
        {
            available = false;
            cout << "\nMachine " << machineID << " started washing." << endl;
        }
        else
        {
            cout << "\nMachine " << machineID << " is currently in use." << endl;
        }
    }

    void stopWash()
    {
        available = true;
        cout << "\nMachine " << machineID << " stopped washing." << endl;
    }
};


class WashingMachineManager
{
private:
    vector<WashingMachine> washingMachines;

public:
    WashingMachineManager(int numMachines)
    {
        for (int i = 1; i <= numMachines; ++i)
        {
            washingMachines.push_back(i);
        }
    }

    void displayAvailableMachines() const
    {
        cout << "Available Washing Machines:\n" << endl;
        for (const WashingMachine& machine : washingMachines) //range based loop
        {
            cout << "Machine ID: " << machine.getMachineID() << " - "
                 << (machine.isAvailable() ? "Available" : "In Use") << endl;
        }
    }

    void startWash(int machineID)
    {
        for (WashingMachine& machine : washingMachines)
            {
            if (machine.getMachineID() == machineID)
            {
                machine.startWash();
                writeToFile(); // Update machine status in the file
                return;
            }
        }
        cout << "\nInvalid machine ID. Please enter a valid ID." << endl;
    }

    void stopWash(int machineID)
    {
        for (WashingMachine& machine : washingMachines)
        {
            if (machine.getMachineID() == machineID)
            {
                machine.stopWash();
                writeToFile(); // Update machine status in the file
                return;
            }
        }
        cout << "\nInvalid machine ID. Please enter a valid ID." << endl;
    }

    void writeToFile() const
    {
        ofstream file("machine_status.txt");
        for (const WashingMachine& machine : washingMachines)
        {
            file << machine.getMachineID() << " " << machine.isAvailable() << endl;
        }
        file.close();
    }

    void readFromFile()
    {
        ifstream file("machine_status.txt");
        int id;
        bool status;

        while (file >> id >> status)
        {
            for (WashingMachine& machine : washingMachines)
            {
                if (machine.getMachineID() == id)
                {
                    if (!status)
                    {
                        machine.startWash(); // If the machine was in use, start washing
                    }
                    break;
                }
            }
        }
        file.close();
    }
};


void wash()
{
    WashingMachineManager machineManager(4);

    // Read machine status from file at the beginning
    machineManager.readFromFile();

    int choice;
    do
        {
        cout << endl << "Options: " << endl;
        cout << "1. Start Wash" << endl;
        cout << "2. Stop Wash" << endl;
        cout << "3. Check Washing Machine Availability" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {

            case 1:
                int machineID;
                cout << "\nEnter the machine ID to start washing: ";
                cin >> machineID;
                machineManager.startWash(machineID);
                break;
            case 2:
            {
                int machineID;
                cout << "\nEnter the machine ID to stop washing: ";
                cin >> machineID;
                machineManager.stopWash(machineID);
                break;
            }
            case 3:
            {
                machineManager.displayAvailableMachines();
                break;
            }
            case 4:
                cout << "\nBack to service page." << endl;
                break;
            default:
                cout << "\nInvalid choice. Please try again." << endl;
                break;
        }
    } while (choice != 4);

    // Write machine status to file before exiting
    machineManager.writeToFile();

}


//service class for different types of service
class service
{
private:
    string service_name;

public:
    void show_service_menu()
    {
        cout << endl << endl;
        cout << "----------------WELCOME TO HALL SERVICE PAGE---------------------" << endl;
        cout << "|   1) CANTEEN SERVICE                                           |" << endl;
        cout << "|   2) STORE SERVICE                                             |" << endl;
        cout << "|   3) WASHING MACHINE SERVICE                                   |" << endl;
        cout << "|   4) VENDING MACHINE SERVICE                                   |" << endl;
        cout << "|   5) BACK TO THE MAIN MENU                                     |" << endl;
        cout << "|----------------------------------------------------------------|" << endl;
        cout << "ENTER YOUR CHOICE(1-5): ";
        int choice;
        cin >> choice;
        switch (choice)
        {
            case 1:
                //canteen
                //canteen can;
                can.getProductDetails();
                can.showMenu();
                break;
            case 2:
                //store
                //StoreService store;
                store.productInfo();
                store.showMenu();
                break;
            case 3:
                wash();
                break;

            case 4:
                //vending machine
                venMan.vanProduct();
                venMan.showMenu();
                break;

            case 5:
                main();
                break;

            default:
                cout << "PLEASE ENTER RIGHT KEY!" << endl;
        }
    }

    // Payment method selection
    Payment* selectPaymentMethod()
    {
        cout << "Select Payment Method:" << endl;
        cout << "1. bKash" << endl;
        cout << "2. Cash on Delivery" << endl;
        cout << "3. Bank Transfer" << endl;

        int choice;
        cin >> choice;

        switch (choice)
        {
            case 1:
                return new BkashPayment();
            case 2:
                return new CashOnDeliveryPayment();
            case 3:
                return new BankPayment();
            default:
                cout << "Invalid choice. Defaulting to Cash on Delivery." << endl;
                return new CashOnDeliveryPayment();
        }
    }
};

service ser;

void canteen::getProductDetails()
{
    int n = 10;

    // Using push_back to store product numbers
    for (int i = 0; i < n; i++)
    {
        product_num.push_back(i + 1);
    }

    // storing product names
    product_name.push_back("Full Rice");
    product_name.push_back("Half Rice");
    product_name.push_back("Biriyani");
    product_name.push_back("Smashed Potato");
    product_name.push_back("Hilsha Fish");
    product_name.push_back("Rohu Fish");
    product_name.push_back("Lentil Curry");
    product_name.push_back("Egg Curry");
    product_name.push_back("Chicken Curry");
    product_name.push_back("Egg Fry");

    //storing product price
    prod_price.push_back(10);
    prod_price.push_back(5);
    prod_price.push_back(60);
    prod_price.push_back(5);
    prod_price.push_back(40);
    prod_price.push_back(30);
    prod_price.push_back(10);
    prod_price.push_back(20);
    prod_price.push_back(40);
    prod_price.push_back(20);
}


void canteen::showMenu()
{
    cout << "======================= CANTEEN MENU ==========================" << endl;
    cout << setw(8) << "PRODUCT" << setw(20) << "NAME OF" << setw(20) << "PRICE" << endl;
    cout << setw(8) << "NUMBER " << setw(20) << "PRODUCT" << endl;
    cout << "_______________________________________________________________" << endl;

    for (int i = 0; i < 10; i++)
    {
        cout << setw(8) << product_num[i] << setw(20) << product_name[i] << setw(20) << prod_price[i] << endl;
    }

    cout << endl << "1. PLACE AN ORDER" << endl;
    cout << "2. BACK TO THE SERVICE PAGE" << endl;

    int choice;
    cin >> choice;

    if (choice == 1)
    {
        placeOrder();
       // ser.selectPaymentMethod();
        ser.show_service_menu();
    }
    else if (choice == 2)
        ser.show_service_menu();
}

void canteen::placeOrder()
{
    int x;
    float total_price = 0;
    char choice2;

    do
    {
        cout << "ENTER THE PRODUCT NUMBER YOU WANT TO ORDER: ";
        cin >> x;
        cout << product_num[x - 1] << ":" << product_name[x - 1] << " has been added to your cart" << endl << endl;
        total_price = total_price + prod_price[x - 1];
        cout << "DO YOU WANT TO ADD MORE ITEM(y/n): ";
        cin >> choice2;
    }
    while (choice2 == 'y' || choice2 == 'Y');

    cout << "Your order has been placed!" << endl << endl;
    cout << "Total cost: " << total_price << " taka" << endl << endl;

    BkashPayment bp;
    CashOnDeliveryPayment CoP;
    BankPayment bankp;

    Payment* p = ser.selectPaymentMethod();
    p->processPayment(total_price);
    //delete paymentMethod; // Don't forget to free the allocated memory
}

void StoreService::productInfo()
{
    int n = 10;

    // Using push_back to store product numbers
    for (int i = 0; i < n; i++)
    {
        prod_num.push_back(i + 1);
    }

    // storing product names
    prod_name.push_back("Lays chips");
    prod_name.push_back("Sun chips");
    prod_name.push_back("Shampoo");
    prod_name.push_back("Soap");
    prod_name.push_back("Dan cake");
    prod_name.push_back("Detergent");
    prod_name.push_back("Fit biscuits");
    prod_name.push_back("Coca-Cola");
    prod_name.push_back("Juice");
    prod_name.push_back("Breads");

    // storing product prices
    prodt_price.push_back(25);
    prodt_price.push_back(15);
    prodt_price.push_back(5);
    prodt_price.push_back(65);
    prodt_price.push_back(45);
    prodt_price.push_back(10);
    prodt_price.push_back(20);
    prodt_price.push_back(35);
    prodt_price.push_back(25);
    prodt_price.push_back(10);
}


void StoreService::showMenu()
{
    cout << "======================= STORE MENU ==========================" << endl;
    cout << setw(8) << "PRODUCT" << setw(20) << "NAME OF" << setw(20) << "PRICE" << endl;
    cout << setw(8) << "NUMBER " << setw(20) << "PRODUCT" << endl;
    cout << "_______________________________________________________________" << endl;
    for (int i = 0; i < 10; i++)
    {
        cout << setw(8) << prod_num[i] << setw(20) << prod_name[i] << setw(20) << prodt_price[i] << endl;
    }

    cout << endl <<  "1. PLACE AN ORDER" << endl;
    cout << "2. BACK TO THE SERVICE PAGE" << endl;

    int ch;
    cin >> ch;

    if (ch == 1)
    {
        placeOrder();
    } else if (ch == 2) {
        ser.show_service_menu();
    }
}


void StoreService::placeOrder()
{
    int s;
    float total_cost = 0;
    char choice3;
    do
    {
        cout << "ENTER THE PRODUCT NUMBER YOU WANT TO ORDER: ";
        cin >> s;
        cout << prod_num[s - 1] << ":" << prod_name[s - 1] << " has been added to your cart" << endl << endl;
        total_cost += prodt_price[s - 1];
        cout << "DO YOU WANT TO ADD MORE ITEM(y/n): ";
        cin >> choice3;
    } while (choice3 == 'y' || choice3 == 'Y');

    cout << "Your order has been placed!" << endl << endl;
    cout << "Total cost: " << total_cost << " taka" << endl;
    Payment* p = ser.selectPaymentMethod();
    p->processPayment(total_cost);
    //delete paymentMethod;
}

void VendingMachine::vanProduct()
{
    int n = 10;
    for (int i = 0; i < n; i++)
    {
        product_vnum.push_back(i + 1);
    }
        product_vname.push_back("speed");
        product_vname.push_back("Drinko");
        product_vname.push_back("SMC-Plus");
        product_vname.push_back("Dan cake");
        product_vname.push_back("Pepsi");
        product_vname.push_back("Fit biscuits");
        product_vname.push_back("Nutty biscuits");
        product_vname.push_back("Potata biscuits");
        product_vname.push_back("7-UP");
        product_vname.push_back("Mojo");

        // Using push_back for prodv_price
        prodv_price.push_back(35);
        prodv_price.push_back(15);
        prodv_price.push_back(30);
        prodv_price.push_back(20);
        prodv_price.push_back(25);
        prodv_price.push_back(20);
        prodv_price.push_back(20);
        prodv_price.push_back(20);
        prodv_price.push_back(25);
        prodv_price.push_back(25);

}

void VendingMachine::showMenu()
{
    cout << "======================= VENDING MACHINE ==========================" << endl;
    cout << setw(8) << "PRODUCT" << setw(20) << "NAME OF" << setw(20) << "PRICE" << endl;
    cout << setw(8) << "NUMBER " << setw(20) << "PRODUCT" << endl;
    cout << "_______________________________________________________________" << endl;
    for (int i = 0; i < 10; i++)
    {
        cout << setw(8) << product_vnum[i] << setw(20) << product_vname[i] << setw(20) << prodv_price[i] << endl;
    }

    cout << endl << "1. PLACE AN ORDER" << endl;
    cout << "2. BACK TO THE SERVICE PAGE" << endl;
    int ch;
    cin >> ch;
    if (ch == 1)
    {
        placeOrder();
    } else if (ch == 2) {
        ser.show_service_menu();
    }
}

void VendingMachine::placeOrder()
{
    int v;
    float total_cost = 0;
    char ch;
    do
    {
        cout << "ENTER THE PRODUCT NUMBER YOU WANT TO ORDER: ";
        cin >> v;
        cout << product_vnum[v - 1] << ":" << product_vname[v - 1] << " has been added to your cart" << endl;
        total_cost += prodv_price[v - 1];
        cout << "DO YOU WANT TO ADD MORE ITEM(y/n): ";
        cin >> ch;
    }
    while (ch == 'y' || ch == 'Y');

    cout << "Your order has been placed!" << endl;
    cout << "Total cost: " << total_cost << " taka" << endl;
    Payment* p = ser.selectPaymentMethod();
    p->processPayment(total_cost);
   // delete paymentMethod;
}


void user::createNewAccount()
{
    cout << "----------------CREATE NEW ACCOUNT-----------------" << endl;
    cout << endl;
    cin.ignore();
    cout << "ENTER YOUR FULL NAME: ";
    getline(cin , full_name);
    cout << "SELECT a USERNAME  : ";
    cin >> username;
    cout << "ENTER YOUR DEPARTMENT: ";
    cin >> department;
    cout << "ENTER YOUR CLASS ID: ";
    cin >> class_id;
    cout << "SELECT A PASSWORD: ";
    cin >> password;

    ofstream file;
    file.open(username + ".txt");
    file << full_name << " " << username << " " << department << " " << class_id << " " << password << endl;
    file.close();
    cout << "Welcome " << full_name << "!" << endl;
}


bool user::isLoggedIn()
{
    string uname, pword;

    cout << "ENTER A USERNAME: ";
    cin >> uname;
    cout << "ENTER A PASSWORD: ";
    cin >> pword;

    ifstream file(uname + ".txt");
    string line;

    if(file.is_open())
    {
        while(getline(file, line))
        {
            istringstream iss(line);
            string f_name, m_name, un, dept, id, pw;

            if(iss >> f_name >> m_name >> un >> dept >> id >> pw)
            {
                if(un == uname && pw == pword)
                {
                    return true;
                }
            }
        }
    }
}


void user::login()
{
    bool status = isLoggedIn();

    if (!status)
    {
        cout << endl;
        cout << "INVALID LOGIN!" << endl;
        return;
    }
    else
    {
        cout << endl << "SUCCESSFULLY LOGGED IN!" << endl;
        cout << endl;

        int choiceTwo;

        cout << "WELCOME BACK!" << endl;
        while(1)
        ser.show_service_menu();

    }
}

int main()
{
    user st;
    char choice2;
    cout << "                     WELCOME TO MAIN MENU                   " << endl;
    cout << "|----------------------------------------------------------|" << endl;
    do {
        cout << "|   1) LOG IN TO YOUR PROFILE                              |" << endl;
        cout << "|   2) CREATE NEW ACCOUNT                                  |" << endl;
        cout << "|   3) TO EXIT                                             |" << endl;
        cout << "|----------------------------------------------------------|" << endl;

        cout << "ENTER YOUR CHOICE: ";
        int choice;
        cin >> choice;

        switch (choice)
        {
            case 1:
                st.login();
                break;

            case 2:
                st.createNewAccount();
                cout << "Now login to your account with username and password: " << endl;
                st.login();
                break;

            case 3:
                exit(0);

            default:
                cout << "INVALID CHOICE " << endl;
        }
        cout << "DO YOU WANT TO CONTINUE(y/n): ";
        cin >> choice2;
    }
    while (choice2 == 'y' || choice2 == 'Y');

    return 0;
}
