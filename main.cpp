#include <iostream>
#include <fstream>

using namespace std;

class Item {
private:
    string itemName;
    string category;
    double price;
public:
    Item(string name, string category, double p) : itemName(name), category(category), price(p) {}

    string getName() const {
        return itemName;
    }

    string getCategory() const {
        return category;
    }

    double getPrice() const {
        return price;
    }

    void setName(string name){
        itemName = name;
    }

    void setCategory(string category){
        category = category;
    }

    void setPrice(double price){
        price = price;
    }

    bool operator<(const Item& other) const {
        return price < other.price;
    }

    bool operator>(const Item& other) const {
        return price > other.price;
    }

    bool operator==(const Item& other) const {
        return price == other.price;
    }

    void print() const {
        cout << "Name: " << itemName << ", Category: " << category << ", Price: " << price << endl;
    }
};


// akhoya ghassan
template<typename T>
class BST {

};

// akhoya atef
template<typename T>
class AVL {

};

// ekhwaty osama w rew
template<typename T>
class Heap {

};



//void readItems(istream& in, BST& tree) {
//
//}
//
//void readItems(istream& in, AVL& tree) {
//
//}
//
//void readItems(istream& in, Heap& tree) {
//
//}






int main() {

    BST<Item> bst;
    AVL<Item> avl;
    Heap<Item> heap;



    int choice;
    cout << "Choose a data structure to use:\n"
            "1.Binary Search Tree (BST)\n"
            "2.AVL Tree\n"
            "3.Heap\n"
            "Enter choice: ";
    cin >> choice;

    ifstream inputFile("items.txt");

    if (!inputFile) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    switch (choice) {
        case 1: {
            int bstChoice;
            cout << "Binary Search Tree (BST) Operations:\n"
                 << "1. Add item data\n"
                 << "2. Remove item data\n"
                 << "3. Display item data normally\n"
                 << "4. Display all items sorted by name ascending\n"
                 << "5. Display all items sorted by name descending\n"
                 << "6. Display all items sorted by prices ascending\n"
                 << "7. Display all items sorted by prices descending\n"
                 << "Enter choice: ";
            cin >> bstChoice;

            // switch case lel BST
            switch (bstChoice) {
                case 1: {
                    // Add item data.
                    break;
                }
                case 2:
                    // Remove item data.
                    break;
                case 3:
                    // Display the item data normally.
                    break;
                case 4:
                    // Display all the items sorted by their name ascending.
                    break;
                case 5:
                    // Display all the items sorted by their name descending.
                    break;
                case 6:
                    // Display all the items sorted by their prices ascending.
                    break;
                case 7:
                    // Display all the items sorted by their prices descending.
                    break;
                default:
                    cout << "Invalid choice.";
            }
            break;
        }
        case 2: {
            int avlChoice;
            cout<< "AVL Tree Operations:\n"
                   "1. Add item data\n"
                   "2. Remove item data\n"
                   "3. Display item data normally\n"
                   "4. Display all items sorted by name ascending\n"
                   "5. Display all items sorted by name descending\n"
                   "6. Display all items sorted by prices ascending\n"
                   "7. Display all items sorted by prices descending\n"
                   "Enter choice: ";
            cin >> avlChoice;

            // switch case lel AVL
            switch (avlChoice) {
                case 1: {
                    // Add item data.
                    break;
                }
                case 2:
                    // Remove item data.
                    break;
                case 3:
                    // Displaying item data normally.
                    break;
                case 4:
                    // Display all items sorted by name ascending.
                    break;
                case 5:
                    // Display all items sorted by name descending.
                    break;
                case 6:
                    // Display all items sorted by prices ascending
                    break;
                case 7:
                    // Display all items sorted by prices descending.
                    break;
                default:
                    cout << "Invalid choice.";
            }
            break;
        }
        case 3: {
            int heapChoice;
            cout<< "Heap Operations:\n"
                   "1. Add item data\n"
                   "2. Remove item data\n"
                   "3. Display item data normally\n"
                   "4. Display all items sorted by name ascending\n"
                   "5. Display all items sorted by name descending\n"
                   "6. Display all items sorted by prices ascending\n"
                   "7. Display all items sorted by prices descending\n"
                   "Enter choice: ";
            cin >> heapChoice;

            // switch case lel heap
            switch (heapChoice) {
                case 1: {
                    // Add item data.
                    break;
                }
                case 2:
                    // Remove item data.
                    break;
                case 3:
                    // Displaying item data normally.
                    break;
                case 4:
                    // Display all items sorted by name ascending.
                    break;
                case 5:
                    // Display all items sorted by name descending.
                    break;
                case 6:
                    // Display all items sorted by prices ascending
                    break;
                case 7:
                    // Display all items sorted by prices descending.
                    break;
                default:
                    cout << "Invalid choice.";
            }
            break;
        }
        default:
            cout << "Invalid choice.";
    }


    //readItems(inputFile, bst);  yetnayel call el function be esm el file w bst
    //readItems(inputFile, avl);  yetnayel call el function be esm el file w avl
    //readItems(inputFile, heap);  yetnayel call el function be esm el file w heap


    inputFile.close();

    return 0;
}