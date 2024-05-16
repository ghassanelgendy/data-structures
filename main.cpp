#include<iostream>
#include<queue>
#include<cassert>
#include<algorithm>
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
    bool operator<(const Item& other) const {
        return price < other.price;
    }

    bool operator>(const Item& other) const {
        return price > other.price;
    }

    bool operator==(const Item& other) const {
        return price == other.price&&itemName==other.itemName&&category==other.category;
    }


    friend ostream& operator<<(ostream& os, const Item& item) {
        os << " Name: " << item.itemName << ", Category: " << item.category << ", Price: " << item.price<<'\n';
        return os;
    }
};




//// akhoya ghassan
//template<typename T>
//class BST {
//
//};

// akhoya atef
template<class T>
class AVLTree {
private:
    T data;
    int height;
    AVLTree* left{};
    AVLTree* right{};

    int getHeight(AVLTree* node) {
        if (node == nullptr)
            return -1;
        return node->height;
    }

    int getBalanceFactor() {
        return getHeight(left) - getHeight(right);
    }

    AVLTree* rightRotate(AVLTree* Q) {
        AVLTree* P = Q->left;
        Q->left = P->right;
        P->right = Q;
        Q->updateHeight();
        P->updateHeight();
        return P;
    }

    AVLTree* leftRotate(AVLTree* P) {
        AVLTree* Q = P->right;
        P->right = Q->left;
        Q->left = P;
        P->updateHeight();
        Q->updateHeight();
        return Q;
    }

    int updateHeight() {
        return height = 1 + max(getHeight(left), getHeight(right));
    }
    void special_delete(AVLTree* child) {
        data = child->data;
        left = child->left;
        right = child->right;
        delete child;
    }

    AVLTree* minValueNode() {
        AVLTree* current = this;
        while (current && current->left)
            current = current->left;
        return current;
    }
    AVLTree* delete_node(T target, AVLTree* node) {
        if (!node)
            return nullptr;

        if (target < node->data)
            node->left = delete_node(target, node->left);
        else if (target > node->data)
            node->right = delete_node(target, node->right);
        else {
            if (!node->left && !node->right) {
                delete node;
                node = nullptr;
            }
            else if (!node->right) 	// case 2: has left only
                node->special_delete(node->left);		// connect with child
            else if (!node->left)	// case 2: has right only
                node->special_delete(node->right);
            else {
                AVLTree* mn = node->right->minValueNode();
                node->data = mn->data;
                node->right = delete_node(node->data, node->right);
            }
        }
        if (node) {
            node->updateHeight();
            node = balance(node);
        }
        return node;
    }



    AVLTree* balance(AVLTree* node) {
        if (node->getBalanceFactor() == 2) { 			// Left
            if (node->left->getBalanceFactor() == -1)	// Left Right?
                node->left = leftRotate(node->left);	// To Left Left

            node = rightRotate(node);	// Balance Left Left
        } else if (node->getBalanceFactor() == -2) {
            if (node->right->getBalanceFactor() == 1)
                node->right = rightRotate(node->right);

            node = leftRotate(node);
        }
        return node;
    }
    void reroot(AVLTree* node) {
        if (node == this)
            return;

        swap(this->data, node->data);
        swap(this->height, node->height);

        if (this == node->left) {

            swap(node->right, this->right);
            node->left = this->left;
            this->left = node;
        } else if (this == node->right) {
            swap(node->left, this->left);
            node->right = this->right;
            this->right = node;
        }
    }

public:
    AVLTree(T data) : data(data), height(0), left(nullptr), right(nullptr) {}

    void insert(T target) {
        if (target < data) {
            if (!left)
                left = new AVLTree(target);
            else
                left->insert(target);
        } else if (target > data) {
            if (!right)
                right = new AVLTree(target);
            else
                right->insert(target);
        }
        else {
            if (!right)
                right = new AVLTree(target);
            else
                right->insert(target);
        }
        updateHeight();

        reroot(balance(this));
    }

    void delete_value(T target) {
        if (target == data && !left && !right)
            return;
        reroot(delete_node(target, this));
    }



    void displaySortedByPriceAscending() {
        if (left)
            left->displaySortedByPriceAscending();
        cout << data << " ";
        if (right)
            right->displaySortedByPriceAscending();
    }

    void displaySortedByPriceDescending() {
        if (right)
            right->displaySortedByPriceDescending();
        cout << data << " ";
        if (left)
            left->displaySortedByPriceDescending();
    }
};

class AVLTreeSortedByName {
private:
    Item data;
    int height;
    AVLTreeSortedByName* left{};
    AVLTreeSortedByName* right{};

    int getHeight(AVLTreeSortedByName* node) {
        if (node == nullptr)
            return -1;
        return node->height;
    }

    int getBalanceFactor() {
        return getHeight(left) - getHeight(right);
    }

    AVLTreeSortedByName* rightRotate(AVLTreeSortedByName* Q) {
        AVLTreeSortedByName* P = Q->left;
        Q->left = P->right;
        P->right = Q;
        Q->updateHeight();
        P->updateHeight();
        return P;
    }

    AVLTreeSortedByName* leftRotate(AVLTreeSortedByName* P) {
        AVLTreeSortedByName* Q = P->right;
        P->right = Q->left;
        Q->left = P;
        P->updateHeight();
        Q->updateHeight();
        return Q;
    }

    int updateHeight() {
        return height = 1 + max(getHeight(left), getHeight(right));
    }
    void special_delete(AVLTreeSortedByName* child) {
        data = child->data;
        left = child->left;
        right = child->right;
        delete child;
    }

    AVLTreeSortedByName* minValueNode() {
        AVLTreeSortedByName* current = this;
        while (current && current->left)
            current = current->left;
        return current;
    }
    AVLTreeSortedByName* delete_node(Item target, AVLTreeSortedByName* node) {
        if (!node)
            return nullptr;

        if (target.getName() < node->data.getName())
            node->left = delete_node(target, node->left);
        else if (target.getName() > node->data.getName())
            node->right = delete_node(target, node->right);
        else {
            if (!node->left && !node->right) {
                delete node;
                node = nullptr;
            }
            else if (!node->right) 	// case 2: has left only
                node->special_delete(node->left);		// connect with child
            else if (!node->left)	// case 2: has right only
                node->special_delete(node->right);
            else {
                AVLTreeSortedByName* mn = node->right->minValueNode();
                node->data = mn->data;
                node->right = delete_node(node->data, node->right);
            }
        }
        if (node) {
            node->updateHeight();
            node = balance(node);
        }
        return node;
    }



    AVLTreeSortedByName* balance(AVLTreeSortedByName* node) {
        if (node->getBalanceFactor() == 2) { 			// Left
            if (node->left->getBalanceFactor() == -1)	// Left Right?
                node->left = leftRotate(node->left);	// To Left Left

            node = rightRotate(node);	// Balance Left Left
        } else if (node->getBalanceFactor() == -2) {
            if (node->right->getBalanceFactor() == 1)
                node->right = rightRotate(node->right);

            node = leftRotate(node);
        }
        return node;
    }
    void reroot(AVLTreeSortedByName* node) {
        if (node == this)
            return;

        swap(this->data, node->data);
        swap(this->height, node->height);

        if (this == node->left) {

            swap(node->right, this->right);
            node->left = this->left;
            this->left = node;
        } else if (this == node->right) {
            swap(node->left, this->left);
            node->right = this->right;
            this->right = node;
        }
    }

public:
    AVLTreeSortedByName(Item data) : data(data), height(0), left(nullptr), right(nullptr) {}

    void insert(Item target) {
        if (target.getName() < data.getName()) {
            if (!left)
                left = new AVLTreeSortedByName(target);
            else
                left->insert(target);
        } else if (target > data) {
            if (!right)
                right = new AVLTreeSortedByName(target);
            else
                right->insert(target);
        }
        else {
            if(!right) right= new AVLTreeSortedByName(target);
            else right->insert(target);
        }
        updateHeight();

        reroot(balance(this));
    }

    void delete_value(Item target) {
        if (target == data && !left && !right)
            return;
        reroot(delete_node(target, this));
    }



    void displaySortedByNameAscending() {
        if (left)
            left->displaySortedByNameAscending();
        cout << data << " ";
        if (right)
            right->displaySortedByNameAscending();
    }

    void displaySortedByNameDescending() {
        if (right)
            right->displaySortedByNameDescending();
        cout << data << " ";
        if (left)
            left->displaySortedByNameDescending();
    }
};

template<class T>
void readItemsAVL(istream& input, AVLTree<T>& avl,string filename) {
    ifstream fin(filename);

    if (!fin) {
        cerr << "Error opening file." << endl;
        return;
    }
    int numObjects;
    fin >> numObjects;
    for (int i = 0; i < numObjects; ++i) {
        string name, category;
        double price;
        fin.ignore();
        getline(fin, name);
        getline(fin, category);
        fin >> price;
        Item item(name, category, price);
        avl.insert(item);
    }
}
void readItemsNAVL(istream& input, AVLTreeSortedByName &Navl,string filename) {
    ifstream fin(filename);

    if (!fin) {
        cerr << "Error opening file." << endl;
        return;
    }
    int numObjects;
    fin >> numObjects;
    for (int i = 0; i < numObjects; ++i) {
        string name, category;
        double price;
        fin.ignore();
        getline(fin, name);
        getline(fin, category);
        fin >> price;
        Item item(name, category, price);
        Navl.insert(item);
    }
}

int main() {
    Item item("item1", "CS", 10);
    //BST<Item> bst;
    AVLTree<Item> avl(item);
    AVLTreeSortedByName Navl(item);
    //Heap<Item> heap;

    bool mainFlag = true;
    while (mainFlag) {
        int choice;
        cout << "Choose a data structure to use:\n"
                "1. Binary Search Tree (BST)\n"
                "2. AVL Tree\n"
                "3. AVL Sort By Name\n"
                "4. Heap\n"
                "5. Exit\n"
                "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                bool bstFlag = true;
                while (bstFlag) {
                    int bstChoice;
                    cout << "Binary Search Tree (BST) Operations:\n"
                         << "1. Add item data\n"
                         << "2. Remove item data\n"
                         << "3. Display item data normally\n"
                         << "4. Display all items sorted by name ascending\n"
                         << "5. Display all items sorted by name descending\n"
                         << "6. Display all items sorted by prices ascending\n"
                         << "7. Display all items sorted by prices descending\n"
                         << "8. Exit\n"
                         << "Enter choice: ";
                    cin >> bstChoice;

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
                        case 8:
                            bstFlag = false;
                            break;
                        default:
                            cout << "Invalid choice.";
                    }
                }
                break;
            }
            case 2: {
                bool avlFlag = true;
                while (avlFlag) {
                    int avlChoice;
                    cout << "AVL Tree Operations:\n"
                         << "1. Add item data\n"
                         << "2. Remove item data\n"
                         << "3. Read Data From File\n"
                         << "4. Display all items sorted by Prices ascending\n"
                         << "5. Display all items sorted by Prices descending\n"
                         << "6. Exit\n"
                         << "Enter choice: ";
                    cin >> avlChoice;

                    switch (avlChoice) {
                        case 1: {
                            string name, category;
                            double price;
                            cout << "Enter Name of item: "; cin >> name;
                            cout << "\nEnter Category: "; cin >> category;
                            cout << "\nEnter Price: "; cin >> price;
                            avl.insert(Item(name, category, price));
                            break;
                        }
                        case 2: {
                            string name, category;
                            double price;
                            cout << "Enter Name of item: "; cin >> name;
                            cout << "\nEnter Category: "; cin >> category;
                            cout << "\nEnter Price: "; cin >> price;
                            avl.delete_value(Item(name, category, price));
                            break;
                        }
                        case 3: {
                            cout << "\nEnter File Name(with .txt): ";
                            string filename; cin >> filename;
                            readItemsAVL(cin, avl, filename);
                            break;
                        }
                        case 4:
                            avl.displaySortedByPriceAscending();
                            break;
                        case 5:
                            avl.displaySortedByPriceDescending();
                            break;
                        case 6:
                            avlFlag = false;
                            break;
                        default:
                            cout << "Invalid choice.";
                            break;
                    }
                }
                break;
            }
            case 3: {
                bool nameAvlFlag = true;
                while (nameAvlFlag) {
                    int avlChoice;
                    cout << "AVL Tree Sorted By Name Operations:\n"
                         << "1. Add item data\n"
                         << "2. Remove item data\n"
                         << "3. Read Data From File\n"
                         << "4. Display all items sorted by Name ascending\n"
                         << "5. Display all items sorted by Name descending\n"
                         << "6. Exit\n"
                         << "Enter choice: ";
                    cin >> avlChoice;

                    switch (avlChoice) {
                        case 1: {
                            string name, category;
                            double price;
                            cout << "Enter Name of item: "; cin >> name;
                            cout << "\nEnter Category: "; cin >> category;
                            cout << "\nEnter Price: "; cin >> price;
                            Navl.insert(Item(name, category, price));
                            break;
                        }
                        case 2: {
                            string name, category;
                            double price;
                            cout << "Enter Name of item: "; cin >> name;
                            cout << "\nEnter Category: "; cin >> category;
                            cout << "\nEnter Price: "; cin >> price;
                            Navl.delete_value(Item(name, category, price));
                            break;
                        }
                        case 3: {
                            cout << "\nEnter File Name(with .txt): ";
                            string filename; cin >> filename;
                            readItemsNAVL(cin, Navl, filename);
                            break;
                        }
                        case 4:
                            Navl.displaySortedByNameAscending();
                            break;
                        case 5:
                            Navl.displaySortedByNameDescending();
                            break;
                        case 6:
                            nameAvlFlag = false;
                            break;
                        default:
                            cout << "Invalid choice.";
                    }
                }
                break;
            }
            case 4: {
                bool heapFlag = true;
                while (heapFlag) {
                    int heapChoice;
                    cout << "Heap Operations:\n"
                         << "1. Add item data\n"
                         << "2. Remove item data\n"
                         << "3. Display item data normally\n"
                         << "4. Display all items sorted by name ascending\n"
                         << "5. Display all items sorted by name descending\n"
                         << "6. Display all items sorted by prices ascending\n"
                         << "7. Display all items sorted by prices descending\n"
                         << "8. Exit\n"
                         << "Enter choice: ";
                    cin >> heapChoice;

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
                        case 8:
                            heapFlag = false;
                            break;
                        default:
                            cout << "Invalid choice.";
                    }
                }
                break;
            }
            case 5:
                mainFlag = false;
                break;
            default:
                cout << "Invalid choice.";
        }
    }
    return 0;
}
