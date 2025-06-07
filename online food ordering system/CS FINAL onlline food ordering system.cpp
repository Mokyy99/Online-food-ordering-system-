#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class Item {
public:
    string name;
    int quantity;
    double price;

    Item() {}

    Item(string itemName, int itemQuantity, double itemPrice) {
        name = itemName;
        quantity = itemQuantity;
        price = itemPrice;
    }
};

Item cart[100];
int numberOfItemsInCart = 0;

void menuDisplay() {
    ifstream file("menu.txt");
    if (!file.is_open()) {
        cout << " There is no data to show!" << endl;
    }
    else {
        cout << "1. Drinks" << endl << "2. Desert" << endl << "3. Food" << endl << "4. All" << endl;
        int choice;
        cin >> choice;

        string choiceName;
        if (choice == 1)
            choiceName = "Drinks";
        else if (choice == 2)
            choiceName = "Desert";
        else if (choice == 3)
            choiceName = "Food";
        else
            choiceName = "All";

        cout << endl << endl << "*************************************************" << endl;
        cout << left << setw(20) << "Item Name " << setw(20) << "Price" << setw(20) << "Category" << endl;
        cout << "*************************************************" << endl;

        while (!file.eof()) {
            string itemName, itemPrice, itemCategory;
            file >> itemName >> itemPrice >> itemCategory;
            if (itemCategory == choiceName || choiceName == "All")
                cout << left << setw(20) << itemName << setw(20) << itemPrice << setw(20) << itemCategory << endl;
        }

        file.close();
    }

}

void addToCart() {
    ifstream file("menu.txt");
    if (!file.is_open()) {
        cout << " There is no data to show! " << endl;
        return;
    }
    else {
        cout << endl << endl << "********************************************************************" << endl;
        cout << left << setw(20) << "Item Number " << setw(20) << "Item Name " << setw(20) << "Price" << setw(20) << "Category" << endl;
        cout << "********************************************************************" << endl;
        int number = 1;
        string itemName, itemCategory;
        double itemPrice;
        while (file >> itemName >> itemPrice >> itemCategory) {
            cout << left << setw(20) << number++ << setw(20) << itemName << setw(20) << itemPrice << setw(20) << itemCategory << endl;
        }
        file.close();
    }

    while (true) {
        cout << "Enter the number of the item you want to add to your cart: ";
        int num;
        cin >> num;
        cout << "Enter the quantity of items you want to add to your cart: ";
        int quantity;
        cin >> quantity;

        ifstream f("menu.txt");

        int number = 1;
        bool itemFound = false;
        string itemName, itemCategory;
        double itemPrice;
        while (!f.eof()) {
            f >> itemName >> itemPrice >> itemCategory;
            if (number == num) {
                Item t(itemName, quantity, itemPrice);
                cart[numberOfItemsInCart++] = t;
                cout << "Item added successfully" << endl;
                itemFound = true;
                break;
            }
            number++;
        }
        f.close();

        if (itemFound == false) {
            cout << " We do not have this item. Please try again! " << endl;
        }

        cout << "Do you want to continue? yes/no: ";
        string answer;
        cin >> answer;
        if (answer != "yes")
            break;
    }
}

void ViewCart() {
    if (numberOfItemsInCart == 0) {
        cout << "Your cart is empty! " << endl;
    }
    else {
        cout << endl << endl << "********************************************************************" << endl;
        cout << left << setw(20) << "Item Name " << setw(20) << "Price" << setw(20) << "quantity" << endl;
        cout << "********************************************************************" << endl;
        for (int i = 0; i < numberOfItemsInCart; i++)
        {
            cout << left << setw(20) << cart[i].name << setw(20) << cart[i].price << setw(20) << cart[i].quantity << endl;
        }
    }
}

void removeItem() {
    if (numberOfItemsInCart == 0) {
        cout << "There is no items in your cart!" << endl;
    }
    else {
        cout << endl << endl << "**************************************************************************" << endl;
        cout << left << setw(20) << "Item Number " << setw(20) << "Item Name " << setw(20) << "Price" << setw(20) << "Quantity" << endl;
        cout << "**************************************************************************" << endl;
        for (int i = 0; i < numberOfItemsInCart; i++) {
            cout << left << setw(20) << i + 1 << setw(20) << cart[i].name << setw(20) << cart[i].price << setw(20) << cart[i].quantity << endl;
        }
        cout << "**************************************************************************" << endl;
        cout << "Enter the number of the item you want to remove: ";
        int index;
        cin >> index;

        if (index > 0 && index <= numberOfItemsInCart) {
            // Adjust index for 0-based array
            index--;

            // Shift items in the array to the left
            for (int i = index; i < numberOfItemsInCart - 1; i++) {
                cart[i] = cart[i + 1];
            }

            // Decrement the number of items in the cart
            numberOfItemsInCart--;

            cout << "Item removed successfully." << endl;
        }
        else {
            cout << "Invalid item number." << endl;
        }

        // Display the updated cart
        cout << endl << endl << "**************************************************************************" << endl;
        cout << left << setw(20) << "Item Number " << setw(20) << "Item Name " << setw(20) << "Price" << setw(20) << "Quantity" << endl;
        cout << "=**********************************************************************=" << endl;
        for (int i = 0; i < numberOfItemsInCart; i++) {
            cout << left << setw(20) << i + 1 << setw(20) << cart[i].name << setw(20) << cart[i].price << setw(20) << cart[i].quantity << endl;
        }
        cout << "**************************************************************************" << endl;
    }
}

void checkout() {
    int total = 0;

    if (numberOfItemsInCart == 0) {
        cout << "There is no items in cart!" << endl;
    }
    else {
        cout << endl << endl << "**************************************************************************" << endl;
        cout << left << setw(20) << "Item Number " << setw(20) << "Item Name " << setw(20) << "Price" << endl;
        cout << "**************************************************************************" << endl;
        for (int i = 0; i < numberOfItemsInCart; i++) {
            cout << left << setw(20) << i + 1 << setw(20) << cart[i].name << cart[i].price << " x " << cart[i].quantity << endl;
            total += (cart[i].price * cart[i].quantity);
        }
        cout << endl << "                                   Delivery :   " << 40 << endl;
        cout << "                                   Tax :   " << total * 12 / 100 << endl;
        total += 40;
        total += (total * 12 / 100);

        cout << "                                   Total :   " << total << endl;
        cout << "**************************************************************************" << endl;
    }
}

void exitProgram()
{
    cout << "*******************************" << endl;
    cout << "*    Thank you for ordering!  *" << endl;
    cout << "*******************************" << endl;
    exit(0);
}

void mainMenu() {
    cout << "+-----------------------------------------+" << endl;
    cout << "|                                         |" << endl;
    cout << "|                Main Menu                |" << endl;
    cout << "|                ---------                |" << endl;
    cout << "|                                         |" << endl;
    cout << "|            1. View Menu                 |" << endl;
    cout << "|            2. My cart                   |" << endl;
    cout << "|            3. add to cart               |" << endl;
    cout << "|            4. remove from cart          |" << endl;
    cout << "|            5. checkout                  |" << endl;
    cout << "|            6. Exit                      |" << endl;
    cout << "|                                         |" << endl;
    cout << "+-----------------------------------------+" << endl;
    int x;
    cin >> x;
    switch (x)
    {
    case 1:
        menuDisplay();
        break;
    case 2:
        ViewCart();
        break;
    case 3:
        addToCart();
        break;
    case 4:
        removeItem();
        break;
    case 5:
        checkout();
        break;
    default:
        exitProgram();
        break;
    }
    mainMenu();
}

int main()
{
    mainMenu();
}

