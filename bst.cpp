#include <iostream>
#include <string>

using namespace std;

#define DATA House

struct House {
    string ownerName;
    int ownerAge;
    double price;

    bool operator<(const House& other) const {
        return price < other.price;
    }

    bool operator>(const House& other) const {
        return price > other.price;
    }

    bool operator==(const House& other) const {
        return price == other.price;
    }
};

struct Node {
    DATA data;
    Node* left;
    Node* right;
};

struct Tree {
    Node* root;
};

void initTree(Tree& tree) {
    tree.root = nullptr;
}

Node *createNode(DATA x) {
    Node *p = new Node;
    if (p == NULL) {
        exit(1);
    }

    p->data = x;
    p->left = NULL;
    p->right = NULL;

    return p;
}

// Them phan tu vao cay trung de quy
Node* insertNodeRecursion(Node* root, DATA x) {
    if (root == NULL) {
        return createNode(x);
    }

    if (x < root->data) {
        root->left = insertNodeRecursion(root->left, x);
    } else {
        root->right = insertNodeRecursion(root->right, x);
    }

    return root;
}

void insertNodeRecursion(Tree& tree, DATA x) {
    tree.root = insertNodeRecursion(tree.root, x);
}

// Them phan tu vao cay khong dung de quy
void insertNodeNonRecursion(Tree& tree, DATA x) {
    Node *p = createNode(x);

    if (tree.root == NULL) {
        tree.root = p;
        return;
    }
    
    Node *cur = tree.root;
    Node *par = NULL;

    while (cur != NULL) {
        par = cur;
        if (x < cur->data) {
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }

    if (x < par->data) {
        par->left = p;
    } else {
        par->right = p;
    }
}

// Xoa phan tu khoi cay dung de quy
Node* findMin(Node* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

Node* deleteNodeRecursion(Node* root, DATA x) {
    if (root == NULL) {
        return root;
    }

    if (x < root->data) {
        root->left = deleteNodeRecursion(root->left, x);
    } else if (x > root->data) {
        root->right = deleteNodeRecursion(root->right, x);
    } else {
        if (root->left == NULL) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNodeRecursion(root->right, temp->data);
    }

    return root;
}

void deleteNodeRecursion(Tree& tree, DATA x) {
    tree.root = deleteNodeRecursion(tree.root, x);
}

// Xoa nut khoi cay khong dung de quy
void deleteNodeNonRecursion(Tree& tree, DATA x) {
    Node* parent = NULL;
    Node* current = tree.root;

    while (current != NULL && !(current->data == x)) {
        parent = current;
        if (x < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (current == NULL) {
        return; // Node to be deleted not found
    }

    if (current->left == NULL || current->right == NULL) {
        Node* newCurr;

        if (current->left == NULL) {
            newCurr = current->right;
        } else {
            newCurr = current->left;
        }

        if (parent == NULL) {
            tree.root = newCurr;
        } else if (parent->left == current) {
            parent->left = newCurr;
        } else {
            parent->right = newCurr;
        }

        delete current;
    } else {
        Node* p = NULL;
        Node* temp;

        temp = current->right;
        while (temp->left != NULL) {
            p = temp;
            temp = temp->left;
        }

        if (p != NULL) {
            p->left = temp->right;
        } else {
            current->right = temp->right;
        }

        current->data = temp->data;
        delete temp;
    }
}

// Tinh chieu cao cua day dung de quy
int heightRecursion(Node* root) {
    if (root == NULL) {
        return 0;
    }

    int leftHeight = heightRecursion(root->left);
    int rightHeight = heightRecursion(root->right);

    return (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;
}

void inOrderTraversal(Node* root) {
    if (root == NULL) {
        return;
    }

    inOrderTraversal(root->left);
    cout << "Owner: " << root->data.ownerName << ", Age: " << root->data.ownerAge << ", Price: " << root->data.price << endl;
    inOrderTraversal(root->right);
}

int main() {
    Tree tree;
    initTree(tree);

    int choice;
    do {
        cout << "Menu:\n";
        cout << "0. Exit\n";
        cout << "1. Insert a house (Recursion)\n";
        cout << "2. Insert a house (Non-Recursion)\n";
        cout << "3. Delete a house (Recursion)\n";
        cout << "4. Delete a house (Non-Recursion)\n";
        cout << "5. Display height of tree\n";
        cout << "6. Display the tree\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                House house;
                cout << "Enter owner name: ";
                cin >> house.ownerName;
                cout << "Enter owner age: ";
                cin >> house.ownerAge;
                cout << "Enter house price: ";
                cin >> house.price;
                insertNodeRecursion(tree, house);
                break;
            }
            case 2: {
                House house;
                cout << "Enter owner name: ";
                cin >> house.ownerName;
                cout << "Enter owner age: ";
                cin >> house.ownerAge;
                cout << "Enter house price: ";
                cin >> house.price;
                insertNodeNonRecursion(tree, house);
                break;
            }
            case 3: {
                double price;
                cout << "Enter house price to delete: ";
                cin >> price;
                House house;
                house.price = price;
                deleteNodeRecursion(tree, house);
                break;
            }
            case 4: {
                double price;
                cout << "Enter house price to delete: ";
                cin >> price;
                House house;
                house.price = price;
                deleteNodeNonRecursion(tree, house);
                break;
            }
            case 5: {
                cout << "Height of tree: " << heightRecursion(tree.root) << endl;
                break;
            }
            case 6: {
                cout << "Tree contents (in-order traversal):\n";
                inOrderTraversal(tree.root);
                break;
            }
            case 0: {
                cout << "Exit the program\n" << endl;
                break;
            }
            default: {
                cout << "Invalid choice. Please try again.\n" << endl;
                break;
            }
        }
    } while (choice != 6);
    
    return 0;
}