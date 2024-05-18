#include<iostream>
#include<queue>
#include<algorithm>
#include <fstream>

using namespace std;

string to_lower(string s) {
    for (char &c: s)
        c = tolower(c);
    return s;
}

class Item {
private:
    string nameSmall;

    string itemName;
    string category;
    double price;
public:
    Item(string name, string category, double p) : itemName(name), category(category), price(p) {
        nameSmall = to_lower(itemName);
    }

    Item() : itemName("Unnamed"), category("Null"), price(0.0) {
        nameSmall = to_lower(itemName);
    };

    string getName() const {
        return nameSmall;
    }

    bool operator<(const Item &other) const {
        return price < other.price;
    }

    bool operator>(const Item &other) const {
        return price > other.price;
    }

    bool operator==(const Item &other) const {
        return price == other.price && itemName == other.itemName && category == other.category;
    }


    friend ostream &operator<<(ostream &os, const Item &item) {
        if (item.nameSmall != "unnamed")
            os << " Name: " << item.itemName << ", Category: " << item.category << ", Price: " << item.price << '\n';
        return os;
    }
};

class BST {
private:
    BST *left{};
    BST *right{};
    Item data;
public:
    BST() {
        data = Item();
    }

    BST(Item input) : data(input) {};

    void insert(Item item) {
        if (item < data) {
            if (!left) {
                left = new BST(item);
            } else {
                left->insert(item);
            }
        } else {
            if (!right) {
                right = new BST(item);
            } else {
                right->insert(item);
            }
        }
    }

    void displayAsc() {
        if (left) {
            left->displayAsc();
        }
        cout << data << " ";
        if (right) {
            right->displayAsc();
        }
    }

    void displayDisc() {
        if (right) {
            right->displayDisc();
        }
        cout << data << " ";

        if (left) {
            left->displayDisc();
        }
    }

    Item search(BST *Node, const std::string &x) {
        if (!Node) {
            return Item();
        }
        if (Node->data.getName() == x) {
            return Node->data;
        } else if (x < Node->data.getName()) {
            return search(Node->left, x);
        } else {
            return search(Node->right, x);
        }
    }

    Item search(const std::string &x) {
        return search(this, x);
    }

    void remove(Item x) {

    }

    BST *findMin(BST *node) {
        while (node->left) {
            node = node->left;
        }
        return node;
    }

    BST *remove(BST *root, const std::string &key) {
        if (!root) {
            return nullptr;
        }

        if (key < root->data.getName()) {
            root->left = remove(root->left, key);
        } else if (key > root->data.getName()) {
            root->right = remove(root->right, key);
        } else {
            if (!root->left) {
                BST *temp = root->right;
                delete root;
                return temp;
            } else if (!root->right) {
                BST *temp = root->left;
                delete root;
                return temp;
            }
            BST *temp = findMin(root->right);
            root->data = temp->data;

            root->right = remove(root->right, temp->data.getName());
        }
        return root;
    }

};
void readItemsBST(istream &input, BST* avl, string& filename) {
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
        avl->insert(item);
    }
}
class BSTN {
private:
    BSTN *left{};
    BSTN *right{};
    Item data;
public:
    BSTN() {
        data = Item();
    }

    BSTN(Item input) : data(input) {};

    void insert(Item item) {
        if (item.getName() < data.getName()) {
            if (!left) {
                left = new BSTN(item);
            } else {
                left->insert(item);
            }
        } else {
            if (!right) {
                right = new BSTN(item);
            } else {
                right->insert(item);
            }
        }
    }

    void displayAsc() {
        if (left) {
            left->displayAsc();
        }
        cout << data << " ";
        if (right) {
            right->displayAsc();
        }
    }

    void displayDisc() {
        if (right) {
            right->displayDisc();
        }
        cout << data << " ";

        if (left) {
            left->displayDisc();
        }
    }

    Item search(BSTN *Node, const std::string &x) {
        if (!Node) {
            return Item();
        }
        if (Node->data.getName() == x) {
            return Node->data;
        } else if (x < Node->data.getName()) {
            return search(Node->left, x);
        } else {
            return search(Node->right, x);
        }
    }

    Item search(const std::string &x) {
        return search(this, x);
    }

    void remove(Item x) {

    }

    BSTN *findMin(BSTN *node) {
        while (node->left) {
            node = node->left;
        }
        return node;
    }

    BSTN *remove(BSTN *root, const std::string &key) {
        if (!root) {
            return nullptr;
        }

        if (key < root->data.getName()) {
            root->left = remove(root->left, key);
        } else if (key > root->data.getName()) {
            root->right = remove(root->right, key);
        } else {
            if (!root->left) {
                BSTN *temp = root->right;
                delete root;
                return temp;
            } else if (!root->right) {
                BSTN *temp = root->left;
                delete root;
                return temp;
            }
            BSTN *temp = findMin(root->right);
            root->data = temp->data;

            root->right = remove(root->right, temp->data.getName());
        }
        return root;
    }

};
void readItemsBSTN(istream &input, BSTN* avl, string filename) {
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
        avl->insert(item);
    }
}
// akhoya atef
template<class T>
class AVLTree {
private:
    T data;
    int height;
    AVLTree *left{};
    AVLTree *right{};

    int getHeight(AVLTree *node) {
        if (node == nullptr)
            return -1;
        return node->height;
    }

    int getBalanceFactor() {
        return getHeight(left) - getHeight(right);
    }

    AVLTree *rightRotate(AVLTree *Q) {
        AVLTree *P = Q->left;
        Q->left = P->right;
        P->right = Q;
        Q->updateHeight();
        P->updateHeight();
        return P;
    }

    AVLTree *leftRotate(AVLTree *P) {
        AVLTree *Q = P->right;
        P->right = Q->left;
        Q->left = P;
        P->updateHeight();
        Q->updateHeight();
        return Q;
    }

    int updateHeight() {
        return height = 1 + max(getHeight(left), getHeight(right));
    }

    void special_delete(AVLTree *child) {
        data = child->data;
        left = child->left;
        right = child->right;
        delete child;
    }

    AVLTree *minValueNode() {
        AVLTree *current = this;
        while (current && current->left)
            current = current->left;
        return current;
    }

    AVLTree *delete_node(T target, AVLTree *node) {
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
            } else if (!node->right)    // case 2: has left only
                node->special_delete(node->left);        // connect with child
            else if (!node->left)    // case 2: has right only
                node->special_delete(node->right);
            else {
                AVLTree *mn = node->right->minValueNode();
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


    AVLTree *balance(AVLTree *node) {
        if (node->getBalanceFactor() == 2) {            // Left
            if (node->left->getBalanceFactor() == -1)    // Left Right?
                node->left = leftRotate(node->left);    // To Left Left

            node = rightRotate(node);    // Balance Left Left
        } else if (node->getBalanceFactor() == -2) {
            if (node->right->getBalanceFactor() == 1)
                node->right = rightRotate(node->right);

            node = leftRotate(node);
        }
        return node;
    }

    void reroot(AVLTree *node) {
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
        } else {
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
    AVLTreeSortedByName *left{};
    AVLTreeSortedByName *right{};

    int getHeight(AVLTreeSortedByName *node) {
        if (node == nullptr)
            return -1;
        return node->height;
    }

    int getBalanceFactor() {
        return getHeight(left) - getHeight(right);
    }

    AVLTreeSortedByName *rightRotate(AVLTreeSortedByName *Q) {
        AVLTreeSortedByName *P = Q->left;
        Q->left = P->right;
        P->right = Q;
        Q->updateHeight();
        P->updateHeight();
        return P;
    }

    AVLTreeSortedByName *leftRotate(AVLTreeSortedByName *P) {
        AVLTreeSortedByName *Q = P->right;
        P->right = Q->left;
        Q->left = P;
        P->updateHeight();
        Q->updateHeight();
        return Q;
    }

    int updateHeight() {
        return height = 1 + max(getHeight(left), getHeight(right));
    }

    void special_delete(AVLTreeSortedByName *child) {
        data = child->data;
        left = child->left;
        right = child->right;
        delete child;
    }

    AVLTreeSortedByName *minValueNode() {
        AVLTreeSortedByName *current = this;
        while (current && current->left)
            current = current->left;
        return current;
    }

    AVLTreeSortedByName *delete_node(Item target, AVLTreeSortedByName *node) {
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
            } else if (!node->right)    // case 2: has left only
                node->special_delete(node->left);        // connect with child
            else if (!node->left)    // case 2: has right only
                node->special_delete(node->right);
            else {
                AVLTreeSortedByName *mn = node->right->minValueNode();
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


    AVLTreeSortedByName *balance(AVLTreeSortedByName *node) {
        if (node->getBalanceFactor() == 2) {            // Left
            if (node->left->getBalanceFactor() == -1)    // Left Right?
                node->left = leftRotate(node->left);    // To Left Left

            node = rightRotate(node);    // Balance Left Left
        } else if (node->getBalanceFactor() == -2) {
            if (node->right->getBalanceFactor() == 1)
                node->right = rightRotate(node->right);

            node = leftRotate(node);
        }
        return node;
    }

    void reroot(AVLTreeSortedByName *node) {
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
        } else {
            if (!right) right = new AVLTreeSortedByName(target);
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
void readItemsAVL(istream &input, AVLTree<T> &avl, string filename) {
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

void readItemsNAVL(istream &input, AVLTreeSortedByName &Navl, string filename) {
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
// ****************************************************************************************************
// ****************************************************************************************************

// ** MinHeap bybd2 mn hnaa **
template<class T>
class MinHeap {
private:
    vector<T> heap;

    // btkhly el parent node hya asghar node
    void heapifyUp(int index) {
        if (index == 0) return; // howa bybd2 mn el akher ll awal , fa lma ywsl 0 done
        int parent = (index - 1) / 2; // parent rules
        if (heap[index] < heap[parent]) { // index bymosl el min, fa lw el min asgahr mn parent swap them
            // 3shan yb2a el parent howa el index(el soghyr)
            swap(heap[index], heap[parent]);
            heapifyUp(parent);
        }
    }

    void heapifyDown(int index) {
        int leftChild = 2 * index + 1; // by7sb el left w el right children
        int rightChild = 2 * index + 2;
        int smallest = index;

        //law el leftChild lsa fe elements mawslsh ll akher
        // wlw el leftChild asghar mn smallest , swap them , nafs fekrt eli fo2
        if (leftChild < heap.size() && heap[leftChild] < heap[smallest])
            smallest = leftChild;
        // nafs el kalam bas 3la el right
        if (rightChild < heap.size() && heap[rightChild] < heap[smallest])
            smallest = rightChild;
        // lw el smallest msh howa index swapo
        if (smallest != index) {
            swap(heap[index], heap[smallest]);
            heapifyDown(smallest);
        }
    }

public:
    // el insert bt push el item then btst3ml heapifyUp 3shan t sort bl tarteb el sa7
    //(lma b insert item geded el sorting byboz fa lazem asort tany 3shan ybaa kol haga fola)
    void insert(T item) {
        heap.push_back(item);
        heapifyUp(heap.size() - 1);
    }

    // remove bt search 3l item eli 3ayz ams7o
    void remove(T item) {
        auto it = find(heap.begin(), heap.end(), item);
        if (it == heap.end()) return;// lw el it wasal ll akehr w mala2hosh , return

        // law la2eto ems7o then sort el array tany using heapify
        int index = distance(heap.begin(), it);
        heap[index] = heap.back();
        heap.pop_back();
        heapifyDown(index);
        cout << "item etmasa7 benga7 :)))" << endl;
    }

    // m3rofa yaani mthresh m3aya
    void display() const {
        for (const auto &item: heap) {
            cout << item;
        }
    }

    // same as display el 3ady bas bt sort el awl then ttb3
    // // 3shan da minheap by sort assc by default
    void displaySorted() {
        vector<T> tempHeap = heap;
        sort(tempHeap.begin(), tempHeap.end());
        for (const auto &item: tempHeap) {
            cout << item;
        }
    }

    // lamdba function bt sort el names assc
    void displaySortedByNameAscending() {
        vector<T> tempHeap = heap;
        sort(tempHeap.begin(), tempHeap.end(), [](const T &a, const T &b) {
            return a.getName() < b.getName();
        });
        for (const auto &item: tempHeap) {
            cout << item;
        }
    }
};

// *********************************************************************************************************
// *********************************************************************************************************

// ** MaxHeap class **
template<class T>
class MaxHeap {
private:
    vector<T> heap;

    // btkhly el parent node hya akbar node
    void heapifyUp(int index) {
        if (index == 0) return; // howa bybd2 mn el akher ll awal , fa lm ywsl 0 done
        int parent = (index - 1) / 2; // parent rules
        if (heap[index] > heap[parent]) {
            swap(heap[index], heap[parent]);// index byomsl el max, fa lw el max akbar mn parent swap them
            // 3shan yb2a el parent howa el index(el keber)
            heapifyUp(parent);
        }
    }

    // btrtb el heap w t check 3la akbar node 3shan da maxHeap
    void heapifyDown(int index) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int largest = index;
        // nafs el fekra bas el 3aks
        if (leftChild < heap.size() && heap[leftChild] > heap[largest])
            largest = leftChild;
        if (rightChild < heap.size() && heap[rightChild] > heap[largest])
            largest = rightChild;

        if (largest != index) {
            swap(heap[index], heap[largest]);
            heapifyDown(largest);
        }
    }

public:
    // insert mthressh
    // ba2y el functions eli taht mashro7en fo2 (matktrsh ma3aya)
    void insert(T item) {
        heap.push_back(item);
        heapifyUp(heap.size() - 1);
    }

    void remove(T item) {
        auto it = find(heap.begin(), heap.end(), item);
        if (it == heap.end()) return;

        int index = distance(heap.begin(), it);
        heap[index] = heap.back();
        heap.pop_back();
        heapifyDown(index);
        cout << "item etmasa7 benga7 :)))" << endl;
    }

    void display() const {
        for (const auto &item: heap) {
            cout << item;
        }
    }

    void displaySorted() {
        vector<T> tempHeap = heap;
        sort(tempHeap.begin(), tempHeap.end(), greater<T>()); // 3shan da maxheap by sort desc by default
        for (const auto &item: tempHeap) {
            cout << item;
        }
    }


    void displaySortedByNameDescending() {
        vector<T> tempHeap = heap;
        sort(tempHeap.begin(), tempHeap.end(), [](const T &a, const T &b) {
            return a.getName() > b.getName();
        });
        for (const auto &item: tempHeap) {
            cout << item;
        }
    }
};

// da eli by2ra el data mn el file
template<class T>
void readItemsHeap(istream &input, MinHeap<T> &minHeap, MaxHeap<T> &maxHeap, string filename) {
    ifstream fin(filename);

    if (!fin) { // law 7asal error return da
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
        minHeap.insert(item);
        maxHeap.insert(item);
    }
    cout << "Data read successfully." << endl; // yeeeaaaah
}


int main() {
    Item item("item1", "CS", 10);
    BST *bst = new BST;
    BSTN *bstn = new BSTN;
    AVLTree<Item> avl(item);
    AVLTreeSortedByName Navl(item);
    MinHeap<Item> minHeap;
    MaxHeap<Item> maxHeap;

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
                            << "9. Read Data From File\n"

                            << "Enter choice: ";
                    cin >> bstChoice;

                    switch (bstChoice) {
                        case 1: {
                            string name, category;
                            double price;
                            cout << "Enter Name of item: ";
                            cin >> name;
                            cout << "\nEnter Category: ";
                            cin >> category;
                            cout << "\nEnter Price: ";
                            cin >> price;
                            bstn->insert(Item(name, category, price));
                            bst->insert(Item(name, category, price));
                        }
                            break;
                        case 2: {
                            string name;
                            cout << "Enter Name of item: ";
                            cin >> name;
                            bstn->remove(bstn, name);
                            bst->remove(bst, name);

                        }
                            break;
                        case 3: {
                            bst->displayAsc();
                        }
                            break;
                        case 4: {
                            bstn->displayAsc();
                        }
                            // Display all the items sorted by their name ascending.
                            break;
                        case 5:
                            bstn->displayDisc();

                            // Display all the items sorted by their name descending.
                            break;
                        case 6:
                            bst->displayAsc();
                            // Display all the items sorted by their prices ascending.
                            break;
                        case 7:
                            bst->displayDisc();
                            // Display all the items sorted by their prices descending.
                            break;
                        case 8:
                            bstFlag = false;
                            break;
                        case 9:{
                            cout << "\nEnter File Name(with .txt): ";
                            string filename;
                            cin >> filename;
                            readItemsBST(cin, bst, filename);
                            readItemsBSTN(cin, bstn, filename);
                    }
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
                            cout << "Enter Name of item: ";
                            cin >> name;
                            cout << "\nEnter Category: ";
                            cin >> category;
                            cout << "\nEnter Price: ";
                            cin >> price;
                            avl.insert(Item(name, category, price));
                            break;
                        }
                        case 2: {
                            string name, category;
                            double price;
                            cout << "Enter Name of item: ";
                            cin >> name;
                            cout << "\nEnter Category: ";
                            cin >> category;
                            cout << "\nEnter Price: ";
                            cin >> price;
                            avl.delete_value(Item(name, category, price));
                            break;
                        }
                        case 3: {
                            cout << "\nEnter File Name(with .txt): ";
                            string filename;
                            cin >> filename;
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
                            cout << "Enter Name of item: ";
                            cin >> name;
                            cout << "\nEnter Category: ";
                            cin >> category;
                            cout << "\nEnter Price: ";
                            cin >> price;
                            Navl.insert(Item(name, category, price));
                            break;
                        }
                        case 2: {
                            string name, category;
                            double price;
                            cout << "Enter Name of item: ";
                            cin >> name;
                            cout << "\nEnter Category: ";
                            cin >> category;
                            cout << "\nEnter Price: ";
                            cin >> price;
                            Navl.delete_value(Item(name, category, price));
                            break;
                        }
                        case 3: {
                            cout << "\nEnter File Name(with .txt): ";
                            string filename;
                            cin >> filename;
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
                         << "1. Add item data to MinHeap\n"
                         << "2. Add item data to MaxHeap\n"
                         << "3. Remove item data from MinHeap\n"
                         << "4. Remove item data from MaxHeap\n"
                         << "5. Read Data From File\n"
                         << "6. Display MinHeap\n"
                         << "7. Display MaxHeap\n"
                         << "8. Display all items sorted by prices ascending (MinHeap)\n"
                         << "9. Display all items sorted by prices descending (MaxHeap)\n"
                         << "10. Display all items sorted by Name ascending (MinHeap)\n"
                         << "11. Display all items sorted by Name descending (MaxHeap)\n"
                         << "12. Exit\n"
                         << "Enter choice: ";
                    cin >> heapChoice;

                    switch (heapChoice) {
                        case 1: {
                            string name, category;
                            double price;
                            cout << "Enter item name: ";
                            cin.ignore();
                            getline(cin, name);
                            cout << "Enter category: ";
                            getline(cin, category);
                            cout << "Enter price: ";
                            cin >> price;
                            Item item(name, category, price);
                            minHeap.insert(item);
                            break;
                        }
                        case 2: {
                            string name, category;
                            double price;
                            cout << "Enter item name: ";
                            cin.ignore();
                            getline(cin, name);
                            cout << "Enter category: ";
                            getline(cin, category);
                            cout << "Enter price: ";
                            cin >> price;
                            Item item(name, category, price);
                            maxHeap.insert(item);
                            break;
                        }
                        case 3: {
                            string name, category;
                            double price;
                            cout << "Enter item name: ";
                            cin.ignore();
                            getline(cin, name);
                            cout << "Enter category: ";
                            getline(cin, category);
                            cout << "Enter price: ";
                            cin >> price;
                            Item item(name, category, price);
                            minHeap.remove(item);
                            break;
                        }
                        case 4: {
                            string name, category;
                            double price;
                            cout << "Enter item name: ";
                            cin.ignore();
                            getline(cin, name);
                            cout << "Enter category: ";
                            getline(cin, category);
                            cout << "Enter price: ";
                            cin >> price;
                            Item item(name, category, price);
                            maxHeap.remove(item);
                            break;
                        }
                        case 5:
                            readItemsHeap(cin, minHeap, maxHeap, "items.txt");
                            break;
                        case 6:
                            minHeap.display();
                            break;
                        case 7:
                            maxHeap.display();
                            break;
                        case 8:
                            minHeap.displaySorted();
                            break;
                        case 9:
                            maxHeap.displaySorted();
                            break;
                        case 10:
                            minHeap.displaySortedByNameAscending();
                            // lw fe capital letter byb2a fo2 even lw 7arf "z"
                            // 3shan howa by sort bl ascii
                            break;
                        case 11:
                            maxHeap.displaySortedByNameDescending();
                            // same as above bas el 3aks
                            break;
                        case 12:
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